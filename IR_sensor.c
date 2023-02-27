const int pin_ir = 1; 
const int pin_led = 2; 
void setup() {
  pinMode(pin_led, OUTPUT); 
  pinMode(pin_ir, INPUT); 
}
void loop() {
      if(digitalRead(pin_ir == 1){
        digitalWrite(pin_led, LOW);
      }
      else{
        digitalWrite(pin_led, HIGH);
      }
      delay(100); 
}

int main(){
    
    return 0;
}