#include <SoftwareSerial.h>

#define TX_PIN 11
#define RX_PIN 12

#define INTERVAL_MS 10 
String bytesRead="";

void setup() {
  Serial.begin(9600);
  pinMode(TX_PIN, OUTPUT);
  pinMode(RX_PIN, INPUT);
}

void loop() {
//
//  if(digitalRead(RX_PIN)==HIGH){
//    Serial.println(HIGH);
//  } else{
//    Serial.println(LOW);
//  }
//  delay(10);
  char serialData = Serial.read();
  if((int)serialData!=-1){
    transmit(serialData);
  }
  
  char recievedData = recieve();

  if((int)recievedData!=-1){
    Serial.write(recievedData);
  }
  
  
}

void transmit(char code){

  digitalWrite(TX_PIN, HIGH);
  delay(INTERVAL_MS);
  
  int tempInt;
  for(int i=0; i<8; i++){
    tempInt = (code >> i)%2;
    if(tempInt==0){
      digitalWrite(TX_PIN, HIGH);
    } else{
      digitalWrite(TX_PIN, LOW);
    }
    delay(INTERVAL_MS);
  }

  digitalWrite(TX_PIN, LOW);
}

char recieve(){
  char dataToReturn=-1;
  
    int counter = 0;
    while(digitalRead(RX_PIN)==LOW && counter<100){
      delay(1);
      counter++;
    }

    if(digitalRead(RX_PIN)==HIGH){
      delay((INTERVAL_MS*2)+INTERVAL_MS);
      dataToReturn=0;

      int pinState;
      for(int i=0; i<8; i++){

        if(digitalRead(RX_PIN)==HIGH){
          pinState=0;
        } else{
          pinState=1;
        }

        dataToReturn= (dataToReturn+pinState) << 1;
        
        delay(INTERVAL_MS);
      }
    }
  
  return dataToReturn;
}
