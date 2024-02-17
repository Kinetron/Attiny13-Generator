/*
 * Attiny13Generator.c
 *
 * Created: 17.02.2024 8:59:47
 * Author : Team
 */ 
#define F_CPU 4800000UL
#include <Util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t timeCounter1 = 0; //Значение программного счетчика.
uint32_t pulseLength = 0; //Заданная длина импульса.
uint32_t pulseLengthCounter = 0; //Счетчик длины импульса.
uint8_t pulseLevel = 0; //Уровень сигнала на выходе 1/0.

//Timer/Counter0 Overflow
ISR(TIMER0_OVF_vect){
	
	//if(timeCounter1 > 5)
	//{
		//timeCounter1 --;
	//}
	//else
	//{
		//timeCounter1 = 0;
		//uint8_t btnDown = PINB && 0x04;
		//if(btnDown != 0x04) //Подключен к земле.
		//{
			////if(pulseLength)
		//}	
	//}
}

//Изменяет уровень сигнала на выходе.
void changeLevelOnOutput()
{
	if(pulseLevel == 1)
	{
		PORTB&= 0b11111110; //Ставим логический 0 на выходе.
		pulseLevel = 0;
	}
	else
	{
		pulseLevel = 1;
		PORTB|= 0x01; //1 на выходе.
	}
}

int main(void)
{
	TIMSK0 = TIMSK0 | 2;
	TCCR0A = TCCR0A | 5;
	DDRB = 1;
	PORTB = 0x18; //Подключаем кнопки через резисторы к +.
	sei(); //Разрешаем прерывания.
	
	pulseLength = 400000; //2 секунды длина импульса.
	pulseLength = 200000; //0,5 секунды длина импульса или 1Гц. 
	pulseLength = 20000; //~10гц
	pulseLength = 2000; //100 гц
	
	changeLevelOnOutput(); //Устанавливаем 1 на выходе.
	
    while (1) 
    {
		pulseLengthCounter++; //Считаем длину импульса.
		
		if(pulseLengthCounter > pulseLength)
		{
			pulseLengthCounter = 0;
			changeLevelOnOutput();
		}
		//changeLevelOnOutput();
		//_delay_ms(50);
		//changeLevelOnOutput();
		//_delay_ms(50);
    }
}

