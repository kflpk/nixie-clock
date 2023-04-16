FCPU=16000000UL
MMCU=atmega328p
PROGRAMMER=arduino
SRC=src

main.hex: src/main.c obj/main.o obj/ds1307.o
	avr-g++ -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o obj/main.o main.c
	avr-g++ -o main.bin obj/*.o
	avr-objcopy -O ihex -R .eeprom main.bin main.hex

obj/%.o: $(SRC)/%.cpp $(SRC)/config.h
	mkdir -p obj
	avr-gcc -Os -DF_CPU=$(FCPU) -mmcu=$(MMCU) -c -o $@ $<

flash: main.hex
	avrdude -F -V -c $(PROGRAMMER) -p $(MMCU) -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex

clean:
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.o
