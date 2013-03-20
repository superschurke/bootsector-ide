CC = i586-elf-gcc
LD = i586-elf-ld
OBJCOPY = i586-elf-objcopy
OBJDUMP = i586-elf-objdump

all: supersch

supersch: supersch.o
	$(OBJDUMP) -d $< > $@.asm
	$(OBJCOPY) -O binary $< $@
	
supersch.o: $(wildcard *.c)
	$(CC) -fomit-frame-pointer -fwhole-program -combine -Os -nostdlib -T link.ld -Wl,-Map=supersch.map -o $@ $(filter boot.c,$+) $(filter-out boot.c,$+)

clean:
	rm -rf supersch supersch.o supersch.asm supersch.map

QEMU = /c/Program\ Files/Qemu/qemu.exe
.phony: qemu
qemu: supersch
	$(QEMU) -fda supersch -hda hda.img