
all:
	avr-g++ -mmcu=atmega32 -std=c++11 -Wall -O2 LEDCube/src/main.cpp LEDCube/src/LEDCube.cpp
	avr-objcopy -j .text -j .data -O ihex a.out ledcube.hex
	avrdude -p m32 -c stk500 -P /dev/ttyACM0 -U flash:w:"ledcube.hex":a
