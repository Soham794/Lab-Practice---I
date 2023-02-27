#include <dht.h> 
#define dht_apin A0 
dht DHT; 
void setup()
{ Serial.begin(9600); 
  delay(500); 
}
void loop()
{   DHT.read11(dht_apin); 
    Serial.print("Current humidity = "); 
    Serial.print(DHT.humidity); 
    Serial.print("%  "); 
    Serial.print("temperature = "); 
    Serial.print(DHT.temperature);  
    Serial.println("C  ");
    delay(5000);
}

int main(){
    
return 0;
}