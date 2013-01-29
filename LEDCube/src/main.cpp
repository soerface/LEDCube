#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

class LEDCube {

    public:
        LEDCube();
        int Update();

};

LEDCube::LEDCube() {
    DDRA = 0x1F;
    DDRB = 0x1F;
    DDRD = 0x1F;

    PORTD = 0x1F;
    PORTA = 0x00;
    PORTD = 0x00;
}

int LEDCube::Update() {
    for (int i=0; i<5; i++) {
        PORTB = 1 << i;
        _delay_ms(100);
    }
    return 0;
}

int main(void) {
    LEDCube cube;
    PORTD = 0b00101;
    PORTA = 0b00001;

    while(1) {
        cube.Update();
    }

}
