//
//
// hello.array.44.c
//
// Charlieplex LED array hello-world
//
// Neil Gershenfeld
// 11/13/10
//
// David Montenegro e Fiore Basile
// 13 maggio 2015
//
// (c) Massachusetts Institute of Technology 2010
// This work may be reproduced, modified, distributed,
// performed, and displayed for any purpose. Copyright is
// retained and must be preserved. The work is provided
// as is; no warranty is provided, and users accept all
// liability.
//

/*
Matrix Map

#define DNC  =   IN
#define VCC  =   OUT Vcc
#define GND  =   OUT Gnd

led0                led1                led2                led3                led4
pinA: OUT, Vcc      pinA: OUT, Gnd      pinA: OUT, Vcc      pinA: OUT, Gnd      pinA: OUT, Vcc
pinB: OUT, Gnd      pinB: OUT, Vcc      pinB: IN            pinB: IN            pinB: IN
pinC: IN            pinC: IN            pinC: OUT, Gnd      pinC: OUT, Vcc      pinC: IN
pinD: IN            pinD: IN            pinD: IN            pinD: IN            pinD: OUT, Gnd
pinE: IN            pinE: IN            pinE: IN            pinE: IN            pinE: IN

led5                led6                led7                led8                led9
pinA: OUT, Gnd      pinA: OUT, Vcc      pinA: OUT, Gnd      pinA: IN            pinA: IN
pinB: IN            pinB: IN            pinB: IN            pinB: OUT, Vcc      pinB: OUT, Gnd
pinC: IN            pinC: IN            pinC: IN            pinC: OUT, Gnd      pinC: OUT, Vcc
pinD: OUT, Vcc      pinD: IN            pinD: IN            pinD: IN            pinD: IN
pinE: IN            pinE: OUT, Gnd      pinE: OUT, Vcc      pinE: IN            pinE: IN

led10               led11               led12               led13               led14
pinA: IN            pinA: IT            pinA: IN            pinA: IN            pinA: IN
pinB: OUT, Vcc      pinB: OUT, Gnd      pinB: OUT, Vcc      pinB: OUT, Gnd      pinB: IN
pinC: IN            pinC: IN            pinC: IN            pinC: IN            pinC: OUT, Vcc
pinD: OUT, Gnd      pinD: OUT, Vcc      pinD: IN            pinD: IN            pinD: IN
pinE: IN            pinE: IN            pinE: OUT, Gnd      pinE: OUT, Vcc      pinE: OUT, Gnd

*/
#include <avr/io.h>
#include <util/delay.h>

#define output(directions,pin) (directions |= pin) // set port direction for output
#define input(directions,pin) (directions &= (~pin)) // set port direction for input
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set

#define led_delay() _delay_ms(1) // LED delay

//#define led_port PORTA

//#define led_direction DDRA

/*
Neil's pinout
#define A (1 << PA1) // row 1
#define B (1 << PA2) // row 2
#define C (1 << PA3) // row 3
#define D (1 << PA4) // row 4
#define E (1 << PA5) // row 5
*/

//David's pinout
#define A 0 // led pin A
#define B 1 // led pin B
#define C 2 // led pin C
#define D 3 // led pin D
#define E 4 // led pin E
#define BUTTON (1 << PB7) // button pin

uint8_t ledPin(uint8_t ledNumber){
 if (ledNumber == A){
   return (1<< PA2);
 }
if (ledNumber == B){
   return (1<< PA3);
 }
if (ledNumber == C){
   return (1<< PB0);
 }
if (ledNumber == D){
   return (1<< PB1);
 }
if (ledNumber == E){
   return (1<< PB2);
 }
}

volatile uint8_t* ledPort(uint8_t ledNumber){
 if (ledNumber == A || ledNumber == B) {
     return &PORTA;
 } else {
     return &PORTB;
 }
}

volatile uint8_t* ledDir(uint8_t ledNumber){
 if (ledNumber == A || ledNumber == B) {
     return &DDRA;
 } else {
     return &DDRB;
 }
}


void flash(uint8_t f, uint8_t t, uint8_t delay) {
   //
   // source from, sink to, flash
   //
   uint8_t from = ledPin(f);
   uint8_t to = ledPin(t);

   static uint8_t i;
   //set(ledPort(from),from);
   //clear(ledPort(to),to);
   *ledPort(from) |= from;
   *ledPort(to) &= (~to);

   *ledDir(from) |= from;
   *ledDir(to) |= to;
   for (i = 0; i < delay; ++i)
       led_delay();
   *ledDir(from)  &= (~from) ;
   *ledDir(to)  &= (~to) ;
}

   void ledOn(uint8_t from, uint8_t to, uint8_t delay){


   }

void led_cycle(uint8_t number, uint8_t delay) {
   //
   // cycle through LEDs
   //
   uint8_t i;
   for (i = 0; i < number; ++i) {
      flash(B,A,delay);
      flash(C,A,delay);
      flash(D,A,delay);
      flash(E,A,delay);
      flash(A,B,delay);
      flash(C,B,delay);
      flash(D,B,delay);
      flash(E,B,delay);
      flash(A,C,delay);
      flash(B,C,delay);
      flash(D,C,delay);
      flash(E,C,delay);
      flash(A,D,delay);
      flash(B,D,delay);
      flash(C,D,delay);
      flash(E,D,delay);
      flash(A,E,delay);
      flash(B,E,delay);
      flash(C,E,delay);
      flash(D,E,delay);
      }
}

int main(void) {
   //
   // set clock divider to /1
   //
   CLKPR = (1 << CLKPCE);
   CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
   //
   // main loop
   //
   while (1) {
      led_cycle(1,100);
      led_cycle(3,20);
      led_cycle(100,1);
   }
   return 0;
}
