FCPU=16000000UL
MMCU=atmega328p
PROGRAMMER=arduino
SRC=./src

main.hex: obj/main.o obj/two_wire.o obj/nixie.o obj/ds1307.o obj/uart.o obj/uart_hal.o
	avr-gcc -DF_CPU=$(FCPU) -mmcu=$(MMCU) -o main.bin $(wildcard obj/*.o) 
	avr-objcopy -O ihex -R .eeprom main.bin main.hex

obj/%.o: $(SRC)/%.c
	mkdir -p obj
	avr-gcc -Os -DF_CPU=$(FCPU) -mmcu=$(MMCU) -c -o $@ $<

flash: main.hex
	avrdude -F -V -c $(PROGRAMMER) -p $(MMCU) -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex

clean:
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -rf obj
