#include "GyverTimers.h"

int grnPin = 11;  
int yelPin = 10;
int redPin = 9;
int timer_flag=0;
bool button_flag=false;
uint32_t button_timer = 0;
volatile uint32_t spring;

void setup() {
  Timer2.setFrequency(1);  // запустим второй таймер
  Timer2.enableISR(CHANNEL_A);   
  pinMode(redPin, OUTPUT);   
  pinMode(grnPin, OUTPUT);   
  pinMode(yelPin, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, button_event, CHANGE);           
}

void semafor_day(){
    if ((timer_flag>=0)&&(timer_flag<20))  // Красный 
    { 
      digitalWrite(redPin, HIGH);
      digitalWrite(yelPin, LOW);
      digitalWrite(grnPin, LOW);                 
    }
    else if ((timer_flag>=40)&&(timer_flag<60)) // Желтый 
    {
      digitalWrite(yelPin, HIGH);
      digitalWrite(grnPin, LOW);
      digitalWrite(redPin, LOW);
    }
    else if ((timer_flag>=20)&&(timer_flag<40))  // Зеленый 
    {
      digitalWrite(grnPin, HIGH);
      digitalWrite(yelPin, LOW);
      digitalWrite(redPin, LOW);
    }
  }

void semafor_night(){
  digitalWrite(grnPin, LOW);
  digitalWrite(redPin, LOW);
  timer_flag>=30 ? digitalWrite(yelPin, HIGH) : digitalWrite(yelPin, LOW);
}

void button_event(){
  cli();
  if (millis() - spring >= 100 && digitalRead(2)) {
    spring = millis();
    button_flag = button_flag ? false : true;
  }
  sei();
}

void loop() {
  button_flag ? semafor_night() : semafor_day();
}

// Прерывание А таймера 2
ISR(TIMER2_A) {   
  timer_flag++;
  if(timer_flag>=60){
    timer_flag=0;
  }
}
