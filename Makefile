PROJECT = pidbalancer
ARCH = atmega328p
F_CPU = 16000000UL

CC = avr-gcc
CCFLAGS = -mmcu=$(ARCH) -DF_CPU=$(F_CPU)
OBJCOPY = avr-objcopy

SRC = \
	main.c \
	uart.c \
	i2c.c \
	mpu6050.c

OBJS = $(SRC:.c=.o)

LIBS =

$(PROJECT).hex: $(PROJECT).elf
	$(OBJCOPY) -j .text -j .data -O ihex $(PROJECT).elf $(PROJECT).hex

$(PROJECT).elf: $(OBJS)
	$(CC) $(CCFLAGS) -o $(PROJECT).elf $^ $(LIBS)

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<

flash: $(PROJECT).hex
	#avrdude -p $(ARCH) -c usbasp -e -U flash:w:$(PROJECT).hex:i
	avrdude -v -p $(ARCH) -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:$(PROJECT).hex:i

install: flash

clean:
	rm -Rf *.hex *.elf *.o
