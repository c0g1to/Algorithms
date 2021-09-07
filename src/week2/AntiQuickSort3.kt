package week2

import mooc.EdxIO

class AntiQuickSort3 {

    companion object {
        val io: EdxIO = EdxIO.create()
        var comparsions = 0L
        const val N = 9
        const val threshold = 51

        @JvmStatic
        fun main(args: Array<String>) {
//            for (arr in rearr(N)) {
//                val str = StringBuilder()
//                arr.forEach { str.append("$it ") }
//                qSort(arr, 0, arr.lastIndex)
//                if (comparsions >= threshold) {
//                println("$str     $comparsions")
//                }
//                comparsions = 0
//            }
            val n = io.nextInt()
            generateHardArr(n).forEach { io.print("$it ") }
            io.close()
        }

        fun generateHardArr(n: Int): IntArray {
            val oddShift = n % 2
            val hardArr = IntArray(n) { it + 1 }
            val last = n - 1
            var temp = hardArr[last / 2]
            for (i in (last / 2 - 1) downTo oddShift) {
                hardArr[i] = temp.also { temp = hardArr[i] }
                hardArr[last - i + oddShift] = temp.also { temp = hardArr[last - i + oddShift] }
            }
            if (oddShift == 1) {
                hardArr[0] = temp.also {temp = hardArr[0]}
            }
            hardArr[last / 2] = temp.also {temp = hardArr[last / 2]}
            return hardArr
        }

        fun qSort(a: IntArray, left_i: Int, right_i: Int) {
            val key = a[(left_i + right_i) / 2]
            var i = left_i
            var j = right_i
            while (i <= j) {
                comparsions++
                while (a[i] < key) {
                    i++
                    comparsions++
                }
                while (key < a[j]) {
                    j--
                    comparsions++
                }
                if (i <= j) {
                    a[i] = a[j].also { a[j] = a[i] }
                    i++
                    j--
                    comparsions++
                }
            }
            if (left_i < j) qSort(a, left_i, j)
            if (i < right_i) qSort(a, i, right_i)
        }
//
//        fun rearr(n: Int): Array<IntArray> {
//            val arrOfArr = Array(factorial(n)) { IntArray(n) }
//            val numbers = IntArray(n) { it + 1 }
//            for (i in 0 until factorial((n))) {
//                var coef = i
//                val localStack = numbers.toMutableList()
//                for (j in n downTo 1) {
//                    arrOfArr[i][j - 1] = localStack.removeAt(coef % j)
//                    coef /= j
//                }
//            }
//            return arrOfArr
//        }
//
//        fun factorial(n: Int): Int {
//            var fact = 1
//            (2..n).forEach { fact *= it }
//            return fact
//        }
    }

}