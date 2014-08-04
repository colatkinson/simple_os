.PHONY: all compile clean iso

all: compile

compile:
	$(CC) -c -m32 src/kernel_start_gas.asm -o ks.o
	$(CC) -m32 -c src/kernel.c -o kernel.o
	ld -m elf_i386 -T link.ld -o kernel.bin ks.o kernel.o

iso: compile
	mkdir -p isodir
	mkdir -p isodir/boot
	cp kernel.bin isodir/boot/smokeos.bin
	mkdir -p isodir/boot/grub
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o smokeos.iso isodir

clean:
	rm -rf *.o *.bin isodir/
