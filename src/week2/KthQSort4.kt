package week2

import mooc.EdxIO

class KthQSort4 {
    companion object {
        val io = EdxIO.create()
        var k1 = 0
        var k2 = 0

        @JvmStatic
        fun main(args: Array<String>) {
            val arr = IntArray(io.nextInt())
            k1 = io.nextInt() - 1
            k2 = io.nextInt() - 1
            val abc = IntArray(3) { io.nextInt() }
            arr[0] = io.nextInt()
            arr[1] = io.nextInt()
            for (i in 2 until arr.size) {
                arr[i] = abc[0] * arr[i - 2] + abc[1] * arr[i - 1] + abc[2]
            }
            arr.qSort()
            for (i in k1..k2) {
                io.print("${arr[i]} ")
            }
            io.close()
        }

        fun IntArray.qSort(left_i: Int = 0, right_i: Int = this.lastIndex) {
            if (right_i < k1 || k2 < left_i) return
            var i = left_i
            var j = right_i
            val pivot = this[(right_i + left_i) / 2]
            while (i <= j) {
                while (this[i] < pivot) {
                    i++
                }
                while (pivot < this[j]) {
                    j--
                }
                if (i <= j) {
                    this[i] = this[j].also { this[j] = this[i] }
                    i++
                    j--
                }
            }
            if (left_i < j) qSort(left_i, j)
            if (i < right_i) qSort(i, right_i)
        }

//        fun IntArray.qSort(leftBorder: Int = 0, rightBorder: Int = this.lastIndex) {
//            if (leftBorder >= rightBorder || rightBorder < k1 || k2 < leftBorder) return
//            else {
//                var pivotIndex = (leftBorder + rightBorder) / 2
//                var j = leftBorder
//                for (i in leftBorder..rightBorder) {
//                    if (this[i] < this[pivotIndex]) {
//                        this[i] = this[j].also { this[j] = this[i] }
//                        if (j == pivotIndex) pivotIndex = i
//                        j++
//                    }
//                }
//                this[pivotIndex] = this[j].also { this[j] = this[pivotIndex] }
//                qSort(leftBorder, j - 1)
//                qSort(j + 1, rightBorder)
//            }
//        }
    }
}