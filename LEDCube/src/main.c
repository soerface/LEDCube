#include <avr/io.h>
#include <util/delay.h>

void init(void);

int main(void) {
    init();

    while(1) {
        PORTA = 0b11111;
        PORTB = 0b11111;
        PORTD = 0b11111;
    }

}

void init(void) {
    DDRA = 0xFF;
    DDRB = 0xFF;
    DDRD = 0xFF;
}
