// C++ code
//
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(9, 8); //9번을 RX로 8번을 TX로 지정한다. BTSerial이라는 이름으로 블루투스 모듈을 사용한다.


int temperature_sensor = A0;

int dust_sensor = A1;

int Raindrops_sensor = A2;

int sound_sensor = A3;
float Sound;

int Gas_sensor = A4;

int sensor_led     = 12;         // 미세먼지 센서 안에 있는 적외선 led 핀 번호
int sampling = 280;    // 적외선 led를 키고, 센서 값을 읽어 들여 미세먼지를 측정하는 샘플링 시간
int waiting = 40;    
float stop_time = 9680;   // 센서를 구동하지 않는 시간


float temperature_value = 100;
float dust_value = 0;  // 센서에서 입력 받은 미세먼지 값
float dustDensityug = 0;  // ug/m^3 값을 계산

float rain = 0;
float Gas = 0;


int state = 0;

void setup()
{
  pinMode(temperature_sensor, INPUT);
  pinMode(dust_sensor, INPUT);
  pinMode(sensor_led,OUTPUT);
  pinMode(Raindrops_sensor, INPUT);
  pinMode(sound_sensor, INPUT);
  pinMode(Gas_sensor, INPUT);
  Serial.begin(9600); // 시리얼통신
  BTSerial.begin(9600); // HC05의 AT mode 와 데이터송수신에 사용
}

void loop()
{
  temperature_value = (analogRead(temperature_sensor)  / 9.31); // 센서에 따른 온도값 계산 
  Serial.print("온도:"); 
  Serial.println(temperature_value);// 온도 입력, 출력


  digitalWrite(sensor_led, LOW);    // LED 켜기
  delayMicroseconds(sampling);   // 샘플링해주는 시간. 
 
  dust_value = analogRead(dust_sensor); // 센서 값 읽어오기
  
  delayMicroseconds(waiting);  // 너무 많은 데이터 입력을 피해주기 위해 잠시 멈춰주는 시간. 
 
  digitalWrite(sensor_led, HIGH); // LED 끄기
  delayMicroseconds(stop_time);   // LED 끄고 대기 



  dustDensityug =(0.17 * (dust_value * (5.0 / 1024)) - 0.1) * 1000;    // 미세먼지 값 계산
  Serial.print("Dust Density [ug/m3]: ");            // 시리얼 모니터에 미세먼지 값 출력
  Serial.println(dustDensityug);

  rain = analogRead(Raindrops_sensor);
  Serial.print("빗방울 수위: ");
  Serial.println(rain);

  Sound = analogRead(sound_sensor);
  Serial.print("소음: ");
  Serial.println(Sound);

  Gas = analogRead(Gas_sensor);
  Serial.print("가스: ");
  Serial.println(Gas);
  Serial.println("");

  
  Serial.print("state: ");
  Serial.println(state);

  delay(1000);
  // 모터작동 if 문
  if (  (rain < 500) or (Sound >800) ) { 
    state = 1;        // 대기 중 미세먼지가 나쁨 (80)이상일 때  빗물감지 시  소리 감지 시  온도(0도 이하)에 따른 state 변경
  }
  
  else {
    state = 0;
  }

  if(state == 1){
    //버튼이 눌러졌다면~
    BTSerial.write('1');
    
  }else{
    //버튼이 안눌러졌다면~
    BTSerial.write('0');
  }
  delay(200);
    
  }


  
