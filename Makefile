PROJECT = drone

CC = avr-gcc
CCFLAGS = -mmcu=atmega328p -DF_CPU=16000000UL
OBJCOPY = avr-objcopy

SRC = \
	main.c

OBJS = $(SRC:.c=.o)

LIBS =

$(PROJECT).hex: $(PROJECT).elf
	$(OBJCOPY) -j .text -j .data -O ihex $(PROJECT).elf $(PROJECT).hex

$(PROJECT).elf: $(OBJS)
	$(CC) $(CCFLAGS) -o $(PROJECT).elf $^ $(LIBS)

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<

flash: $(PROJECT).hex
	avrdude -p atmega328p -c usbasp -e -U flash:w:$(PROJECT).hex:i

install: flash

clean:
	rm -Rf *.hex *.elf *.o
