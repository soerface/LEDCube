#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "LEDCube.h"

int main(void) {
    //TCCR0 |= (1<<CS00);
    //TIMSK |= (1<<TOIE0);
    //TCNT0 = 0;

    //// enable global interrupts
    //sei();

    Cube::LEDCube cube;

    int delay_counter = 100;
    int counter = 0;
    int current_element = 0;
    int pos = 0;
    int direction = 1;
    cube.SetLayer(0);
    cube.SetLayer(4);
    int top[13] =    { 5,  2, 14, 21, 10, 17, 23,  8,  9,  7,  0, 4,  6};
    int bottom[13] = {-1, 24,  1, 18, 13, 12, 15, 22, 20, 16, 19, 3, 11};

    for(int i=0; i<12; i++) {
        cube.SetPixel(4, top[i], false);
    }
    for(int i=0; i<12; i++) {
        cube.SetPixel(0, bottom[i], false);
    }

    int i = 0;
    while(1) {

        counter++;
        counter = counter % 2;
        if (!counter) {
            if (delay_counter > 0) {
                delay_counter--;
                continue;
            }
            if (direction == 1) {
                cube.SetPixel(pos, top[current_element], false);
                pos += direction;
                cube.SetPixel(pos, top[current_element], true);
            }
            else {
                cube.SetPixel(pos, bottom[current_element], false);
                pos += direction;
                cube.SetPixel(pos, bottom[current_element], true);
            }
            if (pos == 4 || pos == 0) {
                if (direction == 1) {
                    bottom[current_element] = top[current_element];
                    top[current_element] = -1;
                }
                else {
                    top[current_element] = bottom[current_element];
                    bottom[current_element] = -1;
                }
                direction = direction == 1 ? -1 : 1;
                delay_counter = 30;
                current_element++;
                current_element = current_element % 13;
            }
            cube.Show();
            cube.Draw();
        }
        cube.Show();
        cube.Draw();
    }

}

ISR(TIMER0_OVF_vect) {
}
