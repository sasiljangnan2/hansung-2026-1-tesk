fun find_number(a: Int, list: List<Int>): Int {
    var left = 0
    var right = list.size - 1

    while (left <= right) {
        val mid = (left + right) / 2
        val value = list[mid]

        if (value == a) {
            return mid
        }

        if (value < a) {
            left = mid + 1
        } else {
            right = mid - 1
        }
    }

    return -1
}

fun main() {
    val a = listOf(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
    println(find_number(2, a))
    println(find_number(9, a))
    println(find_number(5, a))
}
