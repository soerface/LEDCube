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

    cube.SetLayer(0);

    cube.Show();

    int counter = 0;
    while(1) {
        counter++;
        counter = counter % 30;
        if (!counter) {
            cube.Shift(0, 1, 0);
            cube.SetLayer(0, true);
            cube.Show();
        }
        cube.Draw();
    }

}

ISR(TIMER0_OVF_vect) {
}
