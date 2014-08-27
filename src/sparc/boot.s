.section .text
.align 16
.global _start
 
_start:
        call 1f                      ! put PC on the stack.
          mov %o7, %l0               ! use the delay slot to grab it
1:      call kernel_main
 
 
dataptr:
        .byte 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', 0
