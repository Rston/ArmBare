# 基于210裸机项目的Makefile模板

name:=set_svc_stack
$(name).bin:$(name).o 
	arm-linux-ld -Ttext 0x0 -o $(name).elf $^
	arm-linux-objcopy -O binary $(name).elf $(name)_usb.bin
	arm-linux-objdump -D $(name).elf > $(name)_elf.dis
	gcc mkv210_image.c -o mkgec210
	./mkgec210 $(name)_usb.bin $(name)_sd.bin
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c

%.o : %.c
	arm-linux-gcc -o $@ $< -c 

clean:
	rm *.o *.elf *.bin *.dis mkgec210 -f

	
	
