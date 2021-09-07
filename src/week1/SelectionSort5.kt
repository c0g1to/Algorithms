package week1

import mooc.EdxIO

fun main() {
    EdxIO.create().use { io ->
        val arr = Array(io.nextInt()) { io.nextInt() }
        for (i in arr.indices) {
            var minIndex = i
            for (j in i until arr.size) {
                minIndex = if (arr[j] < arr[minIndex]) j else minIndex
            }
            if (i != minIndex) {
                arr[i] = arr[minIndex].also { arr[minIndex] = arr[i] }
                io.println("Swap elements at indices ${i + 1} and ${minIndex + 1}.")
            }
        }
        io.print("No more swaps needed.")
    }
}