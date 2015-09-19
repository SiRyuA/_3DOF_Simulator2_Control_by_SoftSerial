/*
 * Arduino Mega / UNO
 * 3DOF Simulator
 * Control by SoftwareSerial
 * 
 * Date : 20150920
 * Artist by SiRyuA.
 */

#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 13); // RX12 TX13

char buffers[18];  //데이터 수신 버퍼

int Motor1,
    Motor2,
    Motor3;

#define Motor1_UP 3
#define Motor2_UP 4
#define Motor3_UP 5

#define Motor1_DOWN 8
#define Motor2_DOWN 9
#define Motor3_DOWN 10

void setup() {
  Serial.begin(115200);
  mySerial.begin(4800);
  Serial.flush();
  mySerial.flush();
  
  pinMode(Motor1_UP, OUTPUT);
  pinMode(Motor1_DOWN, OUTPUT);
  pinMode(Motor2_UP, OUTPUT);
  pinMode(Motor2_DOWN, OUTPUT);
  pinMode(Motor3_UP, OUTPUT);
  pinMode(Motor3_DOWN, OUTPUT);
}

void loop() {
  if(mySerial.available() > 0) {
    int index = 0;
    delay(20);
    
    int numChar = mySerial.available();
    delay(100);
    
    if (numChar > 18) { //데이터 크기 제한
      numChar = 18;
    }
    
    while (numChar--) { //수신 데이터 버퍼 저장.
      buffers[index++] = mySerial.read();
    }
    
    splitString(buffers);    
  }
}

void splitString(char* data) {
  Serial.print("Data read : ");
  Serial.println(data);
  char* parameter;
  parameter = strtok(data, " ,"); // "," 기준 데이터 값 잘라내기
  while(parameter != NULL) { // 아닐경우 다시 ","기준 재기
    setMotor(parameter);
    parameter = strtok (NULL, " ,");
  }
  
  //버퍼 초기화
  for(int x = 0; x < 16; x++) {
    buffers[x] = '\0';
  }
  Serial.flush();
}

void setMotor(char* data) { 
  if((data[0] == 'L') || (data[0] == 'l')) {
    int Axisdata = strtol(data+1, NULL, 10); //10진수 int형 변환
    Axisdata = constrain(Axisdata, 0, 255);  //int형 값을 최소0 최대255로 제한

    int Axis = map(Axisdata, 0, 255, -100, 100);

    Serial.print("M1 > Data : ");
    Serial.print(Axisdata);
    Serial.print(", Axis : ");
    Serial.print(Axis);

    if(Axis > 10){
      digitalWrite(Motor1_UP, HIGH);
      digitalWrite(Motor1_DOWN, LOW);
      Serial.println(", UP");
    }else if(Axis < -10){
      digitalWrite(Motor1_UP, LOW);
      digitalWrite(Motor1_DOWN, HIGH);
      Serial.println(", DOWN");
    }else{
      digitalWrite(Motor1_UP, LOW);
      digitalWrite(Motor1_DOWN, LOW);
      Serial.println(", CENTER");
    }
  }
  
  if((data[0] == 'R') || (data[0] == 'r')) {
    int Axisdata = strtol(data+1, NULL, 10);
    Axisdata = constrain(Axisdata, 0, 255);

    int Axis = map(Axisdata, 0, 255, -100, 100);

    Serial.print("M2 > Data : ");
    Serial.print(Axisdata);
    Serial.print(", Axis : ");
    Serial.print(Axis);

    if(Axis > 10){
      digitalWrite(Motor2_UP, HIGH);
      digitalWrite(Motor2_DOWN, LOW);
      Serial.println(", UP");
    }else if(Axis < -10){
      digitalWrite(Motor2_UP, LOW);
      digitalWrite(Motor2_DOWN, HIGH);
      Serial.println(", DOWN");
    }else{
      digitalWrite(Motor2_UP, LOW);
      digitalWrite(Motor2_DOWN, LOW);
      Serial.println(", CENTER");
    }
  }
  
  if((data[0] == 'C') || (data[0] == 'c')) {
    int Axisdata = strtol(data+1, NULL, 10);
    Axisdata = constrain(Axisdata, 0, 255);

    int Axis = map(Axisdata, 0, 255, -100, 100);

    Serial.print("M3 > Data : ");
    Serial.print(Axisdata);
    Serial.print(", Axis : ");
    Serial.print(Axis);

    if(Axis > 10){
      digitalWrite(Motor3_UP, HIGH);
      digitalWrite(Motor3_DOWN, LOW);
      Serial.println(", UP");
    }else if(Axis < -10){
      digitalWrite(Motor3_UP, LOW);
      digitalWrite(Motor3_DOWN, HIGH);
      Serial.println(", DOWN");
    }else{
      digitalWrite(Motor3_UP, LOW);
      digitalWrite(Motor3_DOWN, LOW);
      Serial.println(", CENTER");
    }
  }
}
