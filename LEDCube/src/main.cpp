#define F_CPU 10000
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

class LEDCube {

    public:
        LEDCube();
        int Draw();
        int SetPixel(int x, int y, int z);

    private:
        uint8_t data[5][5] = {{0},{0},{0},{0},{0}};

};

LEDCube::LEDCube() {
    DDRA = 0x1F;
    DDRB = 0x1F;
    DDRD = 0x1F;
}

int LEDCube::Draw() {
    for (int Layer=0; Layer<5; Layer++) {
        // generate pattern for one layer
        for (int Row=0; Row<5; Row++) {
            PORTD = 1 << Row;
            PORTA = data[Layer][Row];
        }
        PORTB = 1 << Layer;
        _delay_ms(2);
        PORTB = 0x00;
    }
    PORTB = 0x00;
    return 0;
}

int LEDCube::SetPixel(int x, int y, int z) {
    data[y][x] |= 1 << z;
    return 0;
}

int main(void) {
    //TCCR0 |= (1<<CS00);
    //TIMSK |= (1<<TOIE0);
    //TCNT0 = 0;

    //// enable global interrupts
    //sei();

    LEDCube cube;

    while(1) {
        cube.SetPixel(0, 0, 3);
        cube.SetPixel(4, 4, 1);
        cube.SetPixel(2, 1, 4);
        cube.Draw();
    }

}

ISR(TIMER0_OVF_vect) {
}
