#define pinLed PE3
void setup(){pinMode(pinLed, OUTPUT);}
void loop() {
  digitalWrite(pinLed, HIGH);   delay(500);
  digitalWrite(pinLed, LOW);    delay(500); 
}
