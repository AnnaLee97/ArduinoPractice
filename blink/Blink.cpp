#include "Blink.h"

Blink:: Blink(uint8_t pinNumber){
  this.PIN = pinNumber;
}

void Blink:: on(int onTime){
  digitalWrite(PIN, HIGH);
  delay(onTime);
}

void Blink:: off(int offTime){
  digitalWrite(PIN, LOW);
  delay(offTime);
}
