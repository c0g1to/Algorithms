package week1

import mooc.EdxIO

fun main() {
    EdxIO.create().use { io ->
        val arr = Array(io.nextInt()) { io.nextInt() }
        io.print("1 ")
        for (i in 1 until arr.size) {
            var j = i
            while (j > 0 && arr[j - 1] > arr[j]) {
                arr[j] = arr[j - 1].also { arr[j - 1] = arr[j] }
                j--
            }
            io.print("${j + 1} ")
        }
        io.print("\n")
        arr.forEach { io.print("$it ") }
    }
}