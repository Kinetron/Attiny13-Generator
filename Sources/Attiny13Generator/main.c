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

uint8_t timeCounter1 = 0; //�������� ������������ ��������.
uint32_t pulseLength = 0; //�������� ����� ��������.
uint32_t pulseLengthCounter = 0; //������� ����� ��������.
uint8_t pulseLevel = 0; //������� ������� �� ������ 1/0.

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
		//if(btnDown != 0x04) //��������� � �����.
		//{
			////if(pulseLength)
		//}	
	//}
}

//�������� ������� ������� �� ������.
void changeLevelOnOutput()
{
	if(pulseLevel == 1)
	{
		PORTB&= 0b11111110; //������ ���������� 0 �� ������.
		pulseLevel = 0;
	}
	else
	{
		pulseLevel = 1;
		PORTB|= 0x01; //1 �� ������.
	}
}

int main(void)
{
	TIMSK0 = TIMSK0 | 2;
	TCCR0A = TCCR0A | 5;
	DDRB = 1;
	PORTB = 0x18; //���������� ������ ����� ��������� � +.
	sei(); //��������� ����������.
	
	pulseLength = 400000; //2 ������� ����� ��������.
	pulseLength = 200000; //0,5 ������� ����� �������� ��� 1��. 
	pulseLength = 20000; //~10��
	pulseLength = 2000; //100 ��
	
	changeLevelOnOutput(); //������������� 1 �� ������.
	
    while (1) 
    {
		pulseLengthCounter++; //������� ����� ��������.
		
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

