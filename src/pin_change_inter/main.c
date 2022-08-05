#include <avr/io.h>
#include <avr/interrupt.h>

#define tst_bit(Y,bit_x) (Y&(1<<bit_x))

int main()
{
  // Configuração do timer1
  cli();                             //Disable global interrupts
  TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0;                        //limpa registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1

  TCNT1 = 0xC2F7;                    // incia timer com valor para que estouro ocorra em 1 segundo
                                     // 65536-(16MHz/1024/1Hz) = 49911 = 0xC2F7
  TIMSK1 |= (1 << TOIE1);            // habilita a interrupção do TIMER1

  // Enable PCIE2 Bit3 = 1 (Port D)
  // Pin Change Interrupt Control Register
  PCICR |= (1<<PCIE2);
  // Select PCINT23 Bit 7 = 1 (Port D7)
  PCMSK2 |= (1<<PCINT23) | (1<<PCINT18);
  sei();                             // habilita interrupções globais

  //Setup the I/O for the LED
  DDRB |= (1<<DDB5) | (1<<DDB3);     //Set PortB Pin5 and Pin3 as an output
  DDRD |= (0<<DDD7) | (0<<DDD2);     //Set PortD Pin7 as an input

  while(1) {}  //Loop forever, interrupts do the rest
}

ISR(PCINT2_vect)
{
  if (tst_bit(PIND,7))
  {
    PORTB ^= (1<<PORTB5);
  }

  if (tst_bit(PIND,2))
  {
    PORTB ^= (1<<PORTB3);
  }
}

