#define F_CPU 16000000UL //frequência de trabalho

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Definições de macros para o trabalho com bits .
#define set_bit(y,bit) (y|=(1<<bit))  //coloca em 1 o bit x da variável Y
#define clr_bit(y,bit) (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit) (y^=(1<<bit))  //troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit) (y&(1<<bit))   //retorna 0 ou 1 conforme leitura do bit


int main()
{
  // Configuração do timer1
  cli();  //Disable global interrupts
  // Enable PCIE2 Bit3 = 1 (Port D)
  // Pin Change Interrupt Control Register
  PCICR |= (1<<PCIE2);
  // Select PCINT23 Bit 7 = 1 (Port D7)
  PCMSK2 |= (1<<PCINT23) | (1<<PCINT18);

  //Setup the I/O for the LED
  DDRB = 0b00101000;    //Set PortB Pin5 and Pin3 as an output
  PORTB = 0x00;   //Apaga os LEDS
  DDRD = 0x00;   //Set PortD as an input
  PORTD = 0xFF;  //Enable pull-up resistors on PortD
  sei();   // habilita interrupções globais

  while(1) {}  //Loop forever, interrupts do the restde v swe
}

// Interrupt Service Routine
ISR(PCINT2_vect)
{

  if (!tst_bit(PIND,PD7))
  {
    cpl_bit(PORTB,PB5);
  }
  else if (!tst_bit(PIND,PD2))
  {
    cpl_bit(PORTB,PB3);
  }
  _delay_ms(200);

}

