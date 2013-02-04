#include <stdio.h>
#include <stdlib.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "LEDCube.h"

int main(void);
int shuffle(int data[], int size);
int animation_blink(Cube::LEDCube &cube);
int animation_rain(Cube::LEDCube &cube);
int animation_run(Cube::LEDCube &cube);
int animation_sparkles(Cube::LEDCube &cube);
int animation_tetris(Cube::LEDCube &cube);
int animation_top_down(Cube::LEDCube &cube);
int animation_top_down2(Cube::LEDCube &cube);
int animation_wireframe(Cube::LEDCube &cube);
