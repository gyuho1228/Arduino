#include <SoftwareSerial.h>
SoftwareSerial BTSerial(9, 8); //9번을 RX로 8번을 TX로 지정한다. BTSerial이라는 이름으로 블루투스 모듈을 사용한다.


int length_sensor_out = 10;
int length_sensor_in = 11;
int status;



void setup() {
  pinMode(12,OUTPUT);
  Serial.begin(9600); // 시리얼통신
  BTSerial.begin(9600); // HC05의 AT mode 와 데이터송수신에 사용


  pinMode(length_sensor_out, OUTPUT);
  pinMode(length_sensor_in, INPUT);

  }


void loop() {

  delay(1000);      
  if (BTSerial.available()) 
  {
    char c = BTSerial.read(); // c 읽기
    Serial.println(c);        // 1 = 닫기 신호 , 0 = 상태 유지

    
    if(c == '0')   //닫기 신호 안받음
    {
    //motor OFF
    digitalWrite(12, LOW);  // 모터 정지
    Serial.println("상태 상관 x 신호 x 모터 정지");
    }

    
    else if(c == '1')       //닫기 신호 받음
    {


      
      if (status == 1)      // 열린상태 
      {
        //motor ON
        Serial.print("열린 상태 ");
        Serial.print("신호 O 닫기 실행");
        digitalWrite(12, HIGH);   // 닫기 실행
      }

      
      else      // 닫힌 상태
      {
      Serial.println("닫힌 상태");
      Serial.print("신호 O 정지");
      digitalWrite(12, LOW);     // 모터 정지
      } 
    }  
    Serial.println("");


  digitalWrite(10,HIGH);// 초음파 센서
  delayMicroseconds(10);
  digitalWrite(10,LOW);

  
  
  long duration = pulseIn(11, HIGH);
  
  if(duration ==0)
  {
    return;
  }

  float distance = duration / 58.2; // 거리값 계산
  Serial.print("거리: ");
  Serial.println(distance);

   

  if (distance < 
  5)
  {
    status = 1; // 열린상태 
  } 
  else 
  {
    status = 0; // 닫힌상태 
  }
}
}
