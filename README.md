SmokeOS
=======
**SmokeOS** is a barebones OS I'm tinkering with.

## Usage

```shell
$ git clone https://github.com/colatkinson/simple_os.git
$ nasm -f elf kernel_start.asm -o ks.o
$ gcc -c kernel.c -o kernel.o -m32
$ ld -T link.ld -o kernel.bin ks.o kernel.o -m elf_i386
$ qemu-system-i386 -kernel kernel.bin
```
