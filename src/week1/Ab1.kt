package week1

import mooc.EdxIO

fun main() {
    EdxIO.create().use { io ->
        io.print(io.nextInt() + io.nextInt())
    }
}