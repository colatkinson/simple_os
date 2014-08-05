.PHONY: all compile clean iso

override CFLAGS += -c -m32
override LDFLAGS += -m elf_i386

all: compile

compile:
	@echo "Compiling..."
	$(CC) $(CFLAGS) src/kernel_start_gas.s -o ks.o
	$(CC) $(CFLAGS) src/kernel.c -o kernel.o
	$(CC) $(CFLAGS) src/functions.c -o functions.o
	@echo "Linking..."
	ld -T link.ld $(LDFLAGS:-Wl,%=%) -o smokeos.bin ks.o kernel.o functions.o

iso: compile
	@mkdir -p isodir
	@mkdir -p isodir/boot
	@cp smokeos.bin isodir/boot/smokeos.bin
	@mkdir -p isodir/boot/grub
	@cp grub.cfg isodir/boot/grub/grub.cfg
	@echo "Creating ISO..."
	@grub-mkrescue -o smokeos.iso isodir > /dev/null 2>&1

style:
	astyle --options=astylerc "src/*.c" "src/*.h"

clean:
	rm -rf *.o *.bin *.iso isodir/
