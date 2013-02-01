#include <stdio.h>
#include <stdlib.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "LEDCube.h"

int main(void);
int animation_rain(Cube::LEDCube &cube);
int animation_tetris(Cube::LEDCube &cube);
int animation_wireframe(Cube::LEDCube &cube);
