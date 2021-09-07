package week1

import mooc.EdxIO

fun main() {
    EdxIO.create().use { io ->
        val arr = Array(io.nextInt()) { io.nextDoublePrecise() }
        val indexes = Array(arr.size) { it + 1 }
        for (i in 1 until arr.size) {
            for (j in i downTo 1) {
                if (arr[j - 1] > arr[j]) {
                    arr[j] = arr[j - 1].also { arr[j - 1] = arr[j] }
                    indexes[j] = indexes[j - 1].also { indexes[j - 1] = indexes[j] }
                }
            }
        }
        io.println("${indexes.first()} ${indexes[indexes.size / 2]} ${indexes.last()}")
    }
}