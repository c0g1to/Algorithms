package week1

import mooc.EdxIO

fun main() {
    EdxIO.create().use { io ->
        val a = io.nextLong().toBigDecimal()
        val b = io.nextLong().toBigDecimal()
        io.print((a + b * b).toString())
    }
}