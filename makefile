
all:
	avr-g++ -mmcu=atmega32 -std=gnu99 -Wall LEDCube/src/main.cpp
	avr-objcopy -j .text -j .data -O ihex a.out ledcube.hex
	avrdude -p m32 -c stk500 -P /dev/ttyACM0 -U flash:w:"ledcube.hex":a
