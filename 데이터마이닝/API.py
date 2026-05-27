"""2024년 에어코리아 최종확정 측정자료에서 성북구 데이터만 CSV로 저장한다.

실행하면 공공데이터포털의 2024 원본 XLSX를 내려받고,
12개 월별 시트 전체에서 성북구가 포함된 행만 모아 CSV로 저장한다.
"""

from __future__ import annotations

import csv
import shutil
import zipfile
from pathlib import Path
from typing import Iterable
from urllib.request import Request, urlopen
from xml.etree import ElementTree as ET


DOWNLOAD_URL = (
    "https://www.data.go.kr/cmm/cmm/fileDownload.do"
    "?atchFileId=FILE_000000003159810"
    "&fileDetailSn=1"
    "&dataNm=%ED%95%9C%EA%B5%AD%ED%99%98%EA%B2%BD%EA%B3%B5%EB%8B%A8_"
    "%EC%97%90%EC%96%B4%EC%BD%94%EB%A6%AC%EC%95%84_%EC%B5%9C%EC%A2%85%ED%99%95%EC%A0%95%20%EC%B8%A1%EC%A0%95%EC%9E%90%EB%A3%8C_20241231"
)
REFERER_URL = "https://www.data.go.kr/data/15122830/fileData.do"
SOURCE_XLSX = Path(__file__).with_name("airkorea_2024.xlsx")
OUTPUT_CSV = Path(__file__).with_name("airkorea_2024_seongbuk.csv")
TARGET_KEYWORD = "성북"

XLSX_NS = {"main": "http://schemas.openxmlformats.org/spreadsheetml/2006/main"}
WORKBOOK_NS = {
    "main": "http://schemas.openxmlformats.org/spreadsheetml/2006/main",
    "rel": "http://schemas.openxmlformats.org/officeDocument/2006/relationships",
}
WORKBOOK_RELS_NS = {"rel": "http://schemas.openxmlformats.org/package/2006/relationships"}


def download_file(url: str, destination: Path) -> None:
    request = Request(
        url,
        headers={
            "User-Agent": "Mozilla/5.0",
            "Referer": REFERER_URL,
        },
    )
    with urlopen(request) as response, destination.open("wb") as file:
        shutil.copyfileobj(response, file)


def ensure_source_file() -> Path:
    if SOURCE_XLSX.exists() and SOURCE_XLSX.stat().st_size > 0:
        return SOURCE_XLSX

    download_file(DOWNLOAD_URL, SOURCE_XLSX)
    return SOURCE_XLSX


def has_target_text(row: Iterable[object]) -> bool:
    return any(isinstance(value, str) and TARGET_KEYWORD in value for value in row)


def column_index(cell_reference: str) -> int:
    index = 0
    for character in cell_reference:
        if character.isalpha():
            index = index * 26 + (ord(character.upper()) - ord("A") + 1)
    return index


def load_shared_strings(zip_file: zipfile.ZipFile) -> list[str]:
    if "xl/sharedStrings.xml" not in zip_file.namelist():
        return []

    root = ET.fromstring(zip_file.read("xl/sharedStrings.xml"))
    shared_strings: list[str] = []
    for entry in root.findall("main:si", XLSX_NS):
        text_parts = [node.text or "" for node in entry.findall(".//main:t", XLSX_NS)]
        shared_strings.append("".join(text_parts))
    return shared_strings


def workbook_sheet_paths(zip_file: zipfile.ZipFile) -> list[tuple[str, str]]:
    workbook = ET.fromstring(zip_file.read("xl/workbook.xml"))
    relationships = ET.fromstring(zip_file.read("xl/_rels/workbook.xml.rels"))

    relationship_map = {
        relation.attrib["Id"]: relation.attrib["Target"]
        for relation in relationships.findall("rel:Relationship", WORKBOOK_RELS_NS)
    }

    sheets: list[tuple[str, str]] = []
    for sheet in workbook.findall("main:sheets/main:sheet", WORKBOOK_NS):
        sheet_name = sheet.attrib.get("name", "")
        relationship_id = sheet.attrib.get("{http://schemas.openxmlformats.org/officeDocument/2006/relationships}id", "")
        target = relationship_map.get(relationship_id, "")
        if target:
            sheets.append((sheet_name, f"xl/{target}"))
    return sheets


def read_cell_value(cell: ET.Element, shared_strings: list[str]) -> object:
    cell_type = cell.attrib.get("t")
    value_element = cell.find("main:v", XLSX_NS)

    if cell_type == "s" and value_element is not None and value_element.text is not None:
        index = int(value_element.text)
        return shared_strings[index] if index < len(shared_strings) else ""

    if cell_type == "inlineStr":
        text_parts = [node.text or "" for node in cell.findall(".//main:t", XLSX_NS)]
        return "".join(text_parts)

    if value_element is None or value_element.text is None:
        return None

    text = value_element.text
    if cell_type == "b":
        return text == "1"

    if text.isdigit():
        try:
            return int(text)
        except ValueError:
            return text

    try:
        return float(text)
    except ValueError:
        return text


def iter_sheet_rows(zip_file: zipfile.ZipFile, sheet_path: str, shared_strings: list[str]) -> Iterable[list[object]]:
    root = ET.fromstring(zip_file.read(sheet_path))
    sheet_data = root.find("main:sheetData", XLSX_NS)
    if sheet_data is None:
        return

    for row_element in sheet_data.findall("main:row", XLSX_NS):
        row_values: list[object] = []
        for cell in row_element.findall("main:c", XLSX_NS):
            reference = cell.attrib.get("r", "A1")
            index = column_index(reference)
            while len(row_values) < index:
                row_values.append(None)
            row_values[index - 1] = read_cell_value(cell, shared_strings)
        yield row_values


def rows_to_dicts(workbook_path: Path) -> list[dict[str, object]]:
    collected: list[dict[str, object]] = []

    with zipfile.ZipFile(workbook_path) as zip_file:
        shared_strings = load_shared_strings(zip_file)
        sheet_paths = workbook_sheet_paths(zip_file)
        headers: list[str] | None = None

        for _, sheet_path in sheet_paths:
            for row_number, row in enumerate(iter_sheet_rows(zip_file, sheet_path, shared_strings), start=1):
                if row_number == 1:
                    if headers is None:
                        headers = [str(value) if value is not None else "" for value in row]
                    continue

                if headers is None or not has_target_text(row):
                    continue

                row_dict = {
                    headers[index]: row[index] if index < len(row) else None
                    for index in range(len(headers))
                }
                collected.append(row_dict)

    return collected


def write_csv(rows: list[dict[str, object]], output_path: Path) -> None:
    output_path.parent.mkdir(parents=True, exist_ok=True)

    if not rows:
        output_path.write_text("", encoding="utf-8-sig")
        return

    fieldnames: list[str] = []
    seen: set[str] = set()
    for row in rows:
        for key in row:
            if key not in seen:
                seen.add(key)
                fieldnames.append(key)

    with output_path.open("w", newline="", encoding="utf-8-sig") as file:
        writer = csv.DictWriter(file, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)


def main() -> int:
    workbook_path = ensure_source_file()
    rows = rows_to_dicts(workbook_path)
    write_csv(rows, OUTPUT_CSV)
    print(f"CSV 저장 완료: {OUTPUT_CSV}")
    print(f"행 수: {len(rows)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
