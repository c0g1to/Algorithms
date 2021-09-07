package week4

import mooc.EdxIO
import java.util.*

class PostfixNotation {
    companion object {
        val io = EdxIO.create()

        @JvmStatic
        fun main(args: Array<String>) {
            val stack = Stack<Int>()
            val n = io.nextInt()
            for (i in 1..n) {
                var values = io.getIndex()
                when (values) {
                    "+" -> stack.push(stack.pop() + stack.pop())
                    "-" -> stack.push(-1 * (stack.pop() - stack.pop()))
                    "*" -> stack.push(stack.pop() * stack.pop())
                    else -> stack.push(values.toInt())
                }
            }
            io.print(stack.pop())
            io.close()
        }
    }

}