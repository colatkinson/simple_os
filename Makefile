.PHONY: all compile clean iso

override CFLAGS += -c -m32
override LDFLAGS += -m elf_i386
override PLATFORM = x86

all: compile

compile:
	@echo "Compiling..."
	#$(CC) $(CFLAGS) src/$(PLATFORM)/boot_gas.s -o boot.o
	nasm -f elf32 src/$(PLATFORM)/boot.s -o boot.o
	$(CC) src/*.c src/$(PLATFORM)/*.c -I src/include/*.h -I src/$(PLATFORM)/include/*.h -o kernel.o
	#$(CC) $(CFLAGS) src/functions.c -o functions.o
	@echo "Linking..."
	ld -Isrc/include/*.h -Isrc/$(PLATFORM)/include/*.h -T link.ld $(LDFLAGS:-Wl,%=%) -o smokeos.bin ks.o kernel.o functions.o

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

