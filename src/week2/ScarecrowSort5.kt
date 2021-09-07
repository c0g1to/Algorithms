package week2

import mooc.EdxIO

class ScarecrowSort5 {
    companion object {
        val io = EdxIO.create()

        @JvmStatic
        fun main(args: Array<String>) {
            val n = io.nextInt()
            val k = io.nextInt()
            val arr = IntArray(n) { io.nextInt() }
            if (k == 1) {
                io.print("YES").close()
                return
            }
            val inversions = Array(k) { IntArray(n / k + 1) }
            for (i in 0 until k) {
                for (j in 0..((n - i - 1) / k)) {
                    inversions[i][j] = arr[i + k * j]
                }
            }
            arr.sort()
            for (i in arr.indices) {
                val index = inversions[i % k].indexOf(arr[i])
                if (index == -1) {
                    io.print("NO").close()
                    return
                }
                inversions[i % k][index] = Int.MAX_VALUE
            }
            io.print("YES").close()
        }
    }
}