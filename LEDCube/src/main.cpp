#include "main.h"

int main(void) {
    //TCCR0 |= (1<<CS00);
    //TIMSK |= (1<<TOIE0);
    //TCNT0 = 0;

    //// enable global interrupts
    //sei();

    Cube::LEDCube cube;

    cube.Show();

    int frame = 0;
    int current_animation = 1;
    while(1) {
        frame++;
        frame = frame % 15;
        if (!frame) {
            switch (current_animation) {
                case 0:
                    animation_rain(cube);
                    break;
                case 1:
                    animation_tetris(cube);
                    break;
            }
        }
        cube.Draw();
    }
}

int animation_rain(Cube::LEDCube &cube) {
    cube.SetLayer(4, false);
    cube.Shift(0, 1, 0);
    int i = rand() % 25;
    cube.SetPixel(i);
    cube.Show();
    return 0;
}

int animation_tetris(Cube::LEDCube &cube) {
    int i = rand() % 25;
    cube.SetPixel(i);
    cube.Show();
    return 0;
}

ISR(TIMER0_OVF_vect) {
}
