#define TX_PIN 11
#define RX_PIN 12

#define INTERVAL_US 10000 // 10ms

void setup() {
  Serial.begin(9600);
  pinMode(TX_PIN, OUTPUT);
  pinMode(RX_PIN, INPUT);
}

void loop() {
  char serialData = Serial.read();
  if((int)serialData!=-1){
    transmit(serialData);
  }
  
  char recievedData = recieve();

  if((int)recievedData!=-1){
    Serial.write(recievedData);
  }
  
  delayMicroseconds(100); // to make sure serial line is not saturated
}

void transmit(char code){

  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(INTERVAL_US);
  
  for(int i=0; i<8; i++){
    if(((code >> i)%2)==1){
      digitalWrite(TX_PIN, HIGH);
    } else{
      digitalWrite(TX_PIN, LOW);
    }
    delayMicroseconds(INTERVAL_US);
  }

  digitalWrite(TX_PIN, LOW);
}

char recieve(){
  char dataToReturn=-1;
  
    int counter = 0;
    while(digitalRead(RX_PIN)==HIGH && counter<100){
      delayMicroseconds(INTERVAL_US/10);
      counter++;
    }

    if(digitalRead(RX_PIN)==LOW){
      delayMicroseconds((int)(INTERVAL_US*1.5)); //jump to center of first bit
      dataToReturn=0;

      int pinState;
      for(int i=0; i<8; i++){

        if(digitalRead(RX_PIN)==HIGH){
          pinState=0;
        } else{
          pinState=1;
        }

        dataToReturn= (dataToReturn+pinState) << 1;
        
        delayMicroseconds(INTERVAL_US);
      }
    }
  
  return dataToReturn;
}
