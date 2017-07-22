# 210裸机项目中多个Makefile协同工作的模板
CC		= arm-linux-gcc
LD 		= arm-linux-ld
OBJCOPY	= arm-linux-objcopy
OBJDUMP	= arm-linux-objdump
AR		= arm-linux-ar

INCDIR	:= $(shell pwd)
# C预处理器的flag，flag就是编译器可选的选项
# -I指定头文件的的目录
CPPFLAGS	:= -nostdlib -nostdinc -I$(INCDIR)/include
# C编译器的flag
CFLAGS		:= -Wall -O2 -fno-builtin

#导出这些变量到全局，其实就是给子文件夹下面的Makefile使用
export CC LD OBJCOPY OBJDUMP AR CPPFLAGS CFLAGS

name:=uart_printf
objs := start.o clock.o sdram_init.o  main.o uart.o
objs += lib/libc.a

$(name).bin:$(objs)
	$(LD) -Tlink.lds -o $(name).elf $^
	$(OBJCOPY) -O binary $(name).elf $(name)_usb.bin
	$(OBJDUMP) -D $(name).elf > $(name)_elf.dis
	gcc mkv210_image.c -o mkgec210
	./mkgec210 $(name)_usb.bin $(name)_sd.bin

lib/libc.a:
	cd lib;	make;	cd ..
	
%.o : %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c 

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c
	
clean:
	rm *.o *.elf *.bin *.dis mkgec210 -f
	cd lib; make clean; cd ..
