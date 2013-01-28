#include <avr/io.h>
#include <util/delay.h>

void test(void);
void testaufbau(void);
void starteBildchen(void);
void init(void);
void led_aus(void);
void led_alle_an(void);
void led_durchlauf(void);
void einzel_durchlauf(void);
void led_aufbau(void);
void led_abbau(void);

int main(void)
{
	init();
	led_aus();

	//PORTA = 0x10;
	//PORTB = 0x01;
	//PORTD = 16;
	//PORTD = 0x00;

	while(1)
	{
		starteBildchen();
		//testaufbau();
		//led_aufbau();
		//led_abbau();
		//test();
	}
	
}

void test(void)
{
	led_aus();
	PORTA = 0x10;
	PORTB = 0x11;
	PORTD = 0x06;
	PORTD = 0x00;
	_delay_ms(2);
	led_aus();
	PORTA = 0x10;
	PORTB = 0xFF;
	PORTD = 0x01;
	PORTD = 0x00;
	_delay_ms(2);
	led_aus();
	PORTA = 0x10;
	PORTB = 0x0E;
	PORTD = 0x08;
	PORTD = 0x00;
	_delay_ms(2);
	led_aus();
	
}

void testaufbau(void)
{
	PORTA = 0x01;
	PORTD = 0x01;
	PORTD = 0x00;
	PORTB = 0x01;
	
	_delay_ms(500);
	
	PORTA = 0x03;
	PORTD = 0x03;
	PORTD = 0x00;
	PORTB = 0x03;
	
	_delay_ms(500);
	
	PORTA = 0x07;
	PORTD = 0x07;
	PORTD = 0x00;
	PORTB = 0x07;
	
	_delay_ms(500);
	
	PORTA = 0x0F;
	PORTD = 0x0F;
	PORTD = 0x00;
	PORTB = 0x0F;
	
	_delay_ms(500);
	
	PORTA = 0xFF;
	PORTD = 0xFF;
	PORTD = 0x00;
	PORTB = 0xFF;
	
	_delay_ms(500);
	
	led_aus();
}

void starteBildchen(void)
{
	//led_aus();
	//_delay_ms(100);
	
	led_alle_an();
	_delay_ms(100);
	led_aus();
	_delay_ms(100);
	//led_aufbau();
	//_delay_ms(100);
	led_durchlauf();
	_delay_ms(100);
	einzel_durchlauf();
	_delay_ms(100);
}

void init(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRD = 0xFF;

	PORTA = 0xFF;
	PORTB = 0xFF;
	PORTD = 0xFF;
	PORTD = 0x00;
}

void led_aus(void)
{
	PORTA = 0x00;
	PORTD = 0xFF;
	PORTD = 0x00;
	PORTB = 0x00;
}

void led_alle_an(void)
{
	PORTA = 0xFF;
	PORTD = 0xFF;
	PORTB = 0xFF;
	PORTD = 0x00;
}

void led_durchlauf(void)
{
	int i = 0, j = 0;
	
	for(j = 1; j < 17; j=j*2)
	{
		for(i = 1; i < 17; i=i*2)
		{
			PORTA = i;
			PORTB = j;
			PORTD = 0xFF;
			PORTD = 0x00;
			_delay_ms(50);
		}
	}
}

void einzel_durchlauf(void)
{
	int a=0,b=0,d=0;
	
	for(d=1; d<17; d=d*2)
	{
		for(b=1; b<17; b=b*2)
		{
			for(a=1; a<17; a=a*2)
			{
				led_aus();
				PORTA = a;
				PORTB = b;
				PORTD = d;
				PORTD = 0x00;
				_delay_ms(20);
			}
		}
	}
}

void led_aufbau()
{
	int i=0;
	
	for(i=0; i<33;i*=2)
	{
		led_aus();
		i++;
		
		PORTA = i;
		PORTB = i;
		PORTD = i;

		PORTD = 0x00;
		
		_delay_ms(100);
	}
}

void led_abbau(void)
{
	int i=0;
	
	for(i=31; i>=1; i/=2)
	{
		led_aus();
		
		PORTA = i;
		PORTB = i;
		PORTD = i;

		PORTD = 0x00;
		
		i--;
		
		_delay_ms(100);
	}
}

void D_Buchstabe(void)
{
	led_aus();
	PORTA = 0x10;
	PORTB = 0x11;
	PORTD = 0x06;
	PORTD = 0x00;
	_delay_ms(2);
	led_aus();
	PORTA = 0x10;
	PORTB = 0xFF;
	PORTD = 0x01;
	PORTD = 0x00;
	_delay_ms(2);
	led_aus();
	PORTA = 0x10;
	PORTB = 0x0E;
	PORTD = 0x08;
	PORTD = 0x00;
	_delay_ms(2);
}