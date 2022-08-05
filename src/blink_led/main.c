#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
/*   //Setup the clock
  cli();			//Disable global interrupts
  TCCR1B |= 1<<CS11 | 1<<CS10;	//Divide by 64
  OCR1A = 15624;		//Count 15624 cycles for 1 second interrupt
  TCCR1B |= 1<<WGM12;		//Put Timer/Counter1 in CTC mode
  TIMSK1 |= 1<<OCIE1A;		//enable timer compare interrupt
  sei();			//Enable global interrupts */

  // Configuração do timer1
  cli();                       			 //Disable global interrupts
  TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0;                        //limpa registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1

  TCNT1 = 0xC2F7;                    // incia timer com valor para que estouro ocorra em 1 segundo
                                     // 65536-(16MHz/1024/1Hz) = 49911 = 0xC2F7

  TIMSK1 |= (1 << TOIE1);            // habilita a interrupção do TIMER1
  sei();                             // habilita interrupções globais

  //Setup the I/O for the LED

  DDRB |= (1<<5);		//Set PortB Pin5 as an output
  PORTB |= (1<<5);		//Set PortB Pin5 high to turn on LED

  while(1) { }			//Loop forever, interrupts do the rest
}

ISR(TIMER1_COMPA_vect)		//Interrupt Service Routine
{
  PORTB ^= (1<<5);		//Use xor to toggle the LED
}

ISR(TIMER1_OVF_vect)  //interrupção do TIMER1
{
  TCNT1 = 0xC2F7;     // Renicia TIMER
  PORTB ^= (1<<5);		//Use xor to toggle the LED
}

