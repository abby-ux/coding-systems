# PYTHON IMPLEMENTATION:
# def collatz(n):
#   return f(n,1)
#
# def f(n,x):
#   if n == 1:
#     return x
#   elif n % 2 == 0:  # if n is even
#     return f(n//2, x+1)  # '//' is integer division in Python
#   elif n % 2 == 1:  # if n is odd (and greater than 1)
#     return f(3*n+1, x+1)
#
# for i in range(1, 100):
#   print("collatz(" + str(i) + "): " + str(collatz(i)))

         .data
collatz1:  .asciz "\ncollatz("
collatz2:  .asciz "): "
newline:   .asciz "\n"

         .text
main:
    li a3, 0 # i = 1 (0 to start because we increment right away)

loop:
 addi a3, a3, 1 # increment for the for loop
 mv a0, a3 # reset n to i
 li a1, 1 # x = 1
 jal even_or_odd

even_or_odd:
 # prolog: create call frame
 addi sp, sp, -8 # allocate 8 bytes on the stack
 sw ra, 0(sp) # save ra of a0 into first allocated word

 li t1, 1
 li t2, 2
 beq a0, t1, print # if n == 1: return x
 rem t4, a0, t2 # t1 = a0 % 2
 beqz t4, even # elif n % 2 == 0: (n is even)
 beq t4, t1, odd # elif n % 2 == 1:  # if n is odd (and greater than 1)

 lw ra, 0(sp)
 addi sp, sp, 8 # epilog: call back to print
 jr ra

exit:
 la a0, newline
 li a7, 4 # end file with new line to match collatz.out
 ecall
 li a7, 10 # exit
 ecall

print:
 # prolog: create call frame
 addi sp, sp, -8 # allocate 8 bytes on the stack
 sw ra, 0(sp) # save ra of a0 into first allocated word

 mv t0, a0 # save our n

 la a0, collatz1
 li a7, 4 # print "collatz("
 ecall
 mv a0, a3 # save our i
 li a7, 1 # print i
 ecall
 la a0, collatz2
 li a7, 4 # print "): "
 ecall
 mv a0, a1 # save our x
 li a7, 1 # print x
 ecall

 mv a0, t0 # put our n back

 li t3, 99
 bge a3, t3, exit

 jal loop

 lw ra, 0(sp)
 addi sp, sp, 8 # epilog: call back to loop
 jr ra

odd:
 # prolog: create call frame
 addi sp, sp, -8 # allocate 8 bytes on the stack
 sw ra, 0(sp) # save ra of a0 into first allocated word

 li t3, 3
 mul a0, a0, t3 # a0 = a0 * 3
 addi a0, a0, 1 # a0 = a0 + 1 (3*n+1)
 addi a1, a1, 1 # a1++ (x+1)

 jal even_or_odd

 lw ra, 0(sp)
 addi sp, sp, 8 # epilog: recursive call back to evenorodd
 jr ra

even:
 # prolog: create call frame
 addi sp, sp, -8 # allocate 8 bytes on the stack
 sw ra, 0(sp) # save ra of a0 into first allocated word

 li t2, 2
 div a0, a0, t2 # a0 = a0//2 (n//2)
 addi a1, a1, 1 # a1++ (x+1)

 jal even_or_odd

 lw ra, 0(sp)
 addi sp, sp, 8 # epilog: recursive call back to evenorodd
 jr ra
