#define NOP asm volatile(“nop”)
#define NOP2 NOP; NOP
#define NOP3 NOP2; NOP
#define NOP5 NOP3; NOP2
#define NOP6 NOP3; NOP3
#define NOP12 NOP6; NOP6
#define NOP13 NOP6; NOP6; NOP
#define CODE0 PORTD |= 0b00000100; NOP5; PORTD &= 0b11111011; NOP13
#define CODE1 PORTD |= 0b00000100; NOP12; PORTD &= 0b11111011; NOP6
#define RES PORTD &= 0b00000000; delayMicroseconds(50)
void setup()
{
pinMode(35, OUTPUT);
}
void loop()
{
RES; // WS2812B 리셋, 0 상태로 50us delay
CODE0; CODE0; CODE0; CODE0; CODE0; CODE0; CODE0; CODE0; // G(Green)
CODE0; CODE0; CODE0; CODE0; CODE0; CODE0; CODE0; CODE0; // R(Red)
CODE1; CODE1; CODE1; CODE1; CODE1; CODE1; CODE1; CODE1; // B(Blue)
}
