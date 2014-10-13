; Declare constants used for creating a multiboot header.
MBALIGN     equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MBALIGN | MEMINFO      ; this is the Multiboot 'flag' field
MAGIC       equ  0x1BADB002             ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum of above, to prove we are multiboot
 
; Declare a header as in the Multiboot Standard. We put this into a special
; section so we can force the header to be in the start of the final program.
; You dont need to understand all these details as it is just magic values that
; is documented in the multiboot standard. The bootloader will search for this
; magic sequence and recognize us as a multiboot kernel.
section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
 
; Currently the stack pointer register (esp) points at anything and using it may
; cause massive harm. Instead, well provide our own stack. We will allocate
; room for a small temporary stack by creating a symbol at the bottom of it,
; then allocating 16384 bytes for it, and finally creating a symbol at the top.
section .bootstrap_stack
align 4
stack_bottom:
times 16384 db 0
stack_top:
 
; The linker script specifies _start as the entry point to the kernel and the
; bootloader will jump to this position once the kernel has been loaded. It
; doesnt make sense to return from this function as the bootloader is gone.
[section .text]
global _start
_start:
    ; Welcome to kernel mode! We now have sufficient code for the bootloader to
    ; load and run our operating system. It doesnt do anything interesting yet.
    ; Perhaps we would like to call printf("Hello, World\n"). You should now
    ; realize one of the profound truths about kernel mode: There is nothing
    ; there unless you provide it yourself. There is no printf function. There
    ; is no <stdio.h> header. If you want a function, you will have to code it
    ; yourself. And that is one of the best things about kernel development:
    ; you get to make the entire system yourself. You have absolute and complete
    ; power over the machine, there are no security restrictions, no safe
    ; guards, no debugging mechanisms, there is nothing but what you build.
 
    ; By now, you are perhaps tired of assembly language. You realize some
    ; things simply cannot be done in C, such as making the multiboot header in
    ; the right section and setting up the stack. However, you would like to
    ; write the operating system in a higher level language, such as C or C++.
    ; To that end, the next task is preparing the processor for execution of
    ; such code. C doesnt expect much at this point and we only need to set up
    ; a stack. Note that the processor is not fully initialized yet and stuff
    ; such as floating point instructions are not available yet.
 
    ; To set up a stack, we simply set the esp register to point to the top of
    ; our stack (as it grows downwards).
    mov esp, stack_top
 
    ; We are now ready to actually execute C code. We cannot embed that in an
    ; assembly file, so well create a kernel.c file in a moment. In that file,
    ; well create a C entry point called kernel_main and call it here.
    extern kernel_main
    call kernel_main
 
    ; In case the function returns, well want to put the computer into an
    ; infinite loop. To do that, we use the clear interrupt ('cli') instruction
    ; to disable interrupts, the halt instruction ('hlt') to stop the CPU until
    ; the next interrupt arrives, and jumping to the halt instruction if it ever
    ; continues execution, just to be safe.
    cli
.hang:
    hlt
    jmp .hang

; Loads the IDT defined in 'idtp' into the processor.
; This is declared in C as 'extern void idt_load();'
; based off of http://www.osdever.net/bkerndev/Docs/idt.htm
global idt_load
extern iidtp
idt_load:
;loads the IDT table. idtp is the IDT pointer.
lidt[iidtp]
ret


; The project is licensed under GNU GPL v3. See $(PROJECT_ROOT)/doc/gpl.txt for more details.
;
; phOS Operating System
; Copyright (C) 2009 Cristian Bidea
[EXTERN fault_handler]
%macro ISR_NOERRCODE 1
[GLOBAL isr%1]
isr%1
cli
push byte 0
push byte %1
jmp isr_common_stub
%endmacro
%macro ISR_ERRCODE 1
[GLOBAL isr%1]
isr%1
cli
push byte %1
jmp isr_common_stub
%endmacro
isr_common_stub:
pusha
mov ax, ds
push eax
mov ax, 0x10
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
call fault_handler
pop eax
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
popa
add esp, 8
sti
iret
ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

[GLOBAL gdt_flush]
 
gdt_flush:
    mov eax, [esp+4]
    lgdt [eax]
 
    mov ax, 0x10    
    mov ds, ax      
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush  
.flush:
    ret