bplist00�_WebMainResource�	
_WebResourceFrameName_WebResourceData_WebResourceMIMEType_WebResourceTextEncodingName^WebResourceURLPOB<html><head></head><body><pre style="word-wrap: break-word; white-space: pre-wrap;">NAME = main
OBJECTS =

CFLAGS  = -I$(CS107E)/include -g -Wall -Wpointer-arith
CFLAGS += -Og -std=c99 -ffreestanding
CFLAGS += -mapcs-frame -fno-omit-frame-pointer -mpoke-function-name
LDFLAGS = -nostdlib -T memmap -L. -L$(CS107E)/lib
LDLIBS  = -lmypi -lpi -lgcc

all : $(NAME).bin

%.bin: %.elf
	arm-none-eabi-objcopy $&lt; -O binary $@

%.elf: %.o $(OBJECTS) start.o cstart.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $&lt; -o $@

%.o: %.s
	arm-none-eabi-as $(ASFLAGS) $&lt; -o $@

%.list: %.o
	arm-none-eabi-objdump  --no-show-raw-insn -d $&lt; &gt; $@

install: $(NAME).bin
	rpi-install.py -p $&lt;

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean install

.PRECIOUS: %.o %.elf

# empty recipe used to disable built-in rules for native build
%:%.c
%:%.o

define CS107E_ERROR_MESSAGE
ERROR - CS107E environment variable is not set.

Please set it to point to the `cs107e.github.io/cs107e` directory using the
command `export CS107E=&lt;replace with path to your cs107e.github.io directory&gt;/cs107e`.

To have this done automatically, add the above command to your shell
environment configuration file (e.g. ~/.bashrc)
endef

ifndef CS107E
$(error $(CS107E_ERROR_MESSAGE))
endif
</pre></body></html>Ztext/plainUUTF-8_khttps://raw.githubusercontent.com/cs107e/cs107e.github.io/master/assignments/assign7/libmypi-usage/Makefile    ( ? Q g � � ����                           Z