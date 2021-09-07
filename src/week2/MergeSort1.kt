package week2

import mooc.EdxIO

class MergeSort1 {

    companion object {
        val io: EdxIO = EdxIO.create()

        @JvmStatic
        fun main(args: Array<String>) {
            val arr = IntArray(io.nextInt()) { io.nextInt() }
            mergeSort(arr, 1, arr.size).forEach { io.print("$it ") }
            io.close()
        }

        fun mergeSort(arr: IntArray, first: Int, last: Int): IntArray =
            if (arr.size == 1) {
                arr
            } else {
                mergeSort(
                    arr.sliceArray(0 until (arr.size / 2)),
                    first, ((first + last).toDouble() / 2 - 0.5).toInt()
                ).merge(
                    mergeSort(
                        arr.sliceArray((arr.size / 2) until arr.size),
                        ((first + last).toDouble() / 2 + 0.5).toInt(), last
                    ), first, last
                )
            }

        fun IntArray.merge(arr: IntArray, startIndex: Int, endIndex: Int): IntArray {
            val mergedArr = IntArray(this.size + arr.size)
            var i = 0
            var j = 0
            while (i < this.size || j < arr.size) {
                if (j == arr.size || (i < this.size && this[i] < arr[j])) {
                    mergedArr[i + j] = this[i++]
                } else {
                    mergedArr[i + j] = arr[j++]
                }
            }
            io.println("$startIndex $endIndex ${mergedArr.first()} ${mergedArr.last()}")
            return mergedArr
        }
    }

}
