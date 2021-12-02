#include <pitches.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(30,31);
int led[8] = {13,11,9,7,5,3,22,24}; //두더지 8마리
int sensor[] = {12,10,8,6,4,2,23,25}; //두더지 잡는 센서 8개
int randNumber=0;
int score=0;
int ResetSW = 35;    //재시작 스위치 핀 번호
int TRY=5;
int speakerPin = 57;//부저핀
int wrongmelody[] = {//틀렸을 때 멜로디
  NOTE_AS4
};
int noteDuration_1 = 8;//음표길이
int endmelody[] = {//관짝밈
  NOTE_A3,0,NOTE_A3,NOTE_E4,NOTE_D4,0,NOTE_C4,0,NOTE_B3,0,NOTE_B3,NOTE_B3,NOTE_D4,0,NOTE_C4,NOTE_B3,
  NOTE_A3,0,NOTE_A3,NOTE_C5,NOTE_B4,NOTE_C5,NOTE_B4,NOTE_C5,NOTE_A3,
  0,NOTE_A3,NOTE_C5,NOTE_B4,NOTE_C5,NOTE_B4,NOTE_C5,
  NOTE_C4,NOTE_C4,NOTE_C4,NOTE_C4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_D4,NOTE_D4,NOTE_D4,NOTE_D4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,
  NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4
};
int noteDuration_2 = 4;
int rightmelody[]={//맞았을때
  NOTE_C4, NOTE_E4, NOTE_G4
};
int noteDuration_3 = 16;

LiquidCrystal lcd(44, 45, 46, 47, 48, 49);//lcd
byte leftheart[8]={B00000, B00110,B01001,B01000,B00100,B00010,B00001,B00000};
byte rightheart[8]={B00000, B01100,B10010,B00010,B00100,B01000,B10000,B00000};

unsigned long time_previous = 0;
unsigned long time_current = 0;

void setup() {
  srand(analogRead(0)); 
  Serial.begin(9600);
  for(int i=0;i<8;i++){
      pinMode(led[i], OUTPUT);
      digitalWrite(led[i], LOW);
      pinMode(sensor[i], INPUT);
  }
  mySerial.begin(9600);
  pinMode(ResetSW, INPUT);     //리셋용 스위치 사용
  lcd.createChar(0, leftheart);//lcd
  lcd.createChar(1, rightheart);
  lcd.begin(16, 2);
}

void loop() {
  int state = digitalRead(ResetSW);
  Serial.println(state);
  time_current = millis();

  
  
  if(state){
    score=0;
    TRY=5;
    Serial.println("start");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HELLO");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Let's go!");
    while(TRY!=0){
      int hit = 0;//점수 획득여부 저장
      randNumber = random(8);//랜덤두더지 번호
      Serial.println(randNumber);
      time_current = millis();
      time_previous = time_current;
      digitalWrite(led[randNumber], HIGH);
      while(time_current - time_previous < 500){//0.5초동안 버튼입력확인
        if(digitalRead(sensor[randNumber]) == LOW){
          for(int thisNote=0; thisNote<sizeof(rightmelody)/sizeof(int);thisNote++){
             int noteLength = 1000 / noteDuration_3 ;
             tone(speakerPin,rightmelody[thisNote],noteLength);
             delay(noteLength);
             noTone(speakerPin);
          }//맞으면 소리
          Serial.print("point:");
          Serial.println(score++);
          hit=1;
          break;
        }
        time_current = millis();
      }
      digitalWrite(led[randNumber], LOW);
      if(!hit){//못눌렀을때
        for(int thisNote=0; thisNote<sizeof(wrongmelody)/sizeof(int);thisNote++){
         int noteLength = 1000 / noteDuration_1 ;
         tone(speakerPin,wrongmelody[thisNote],noteLength);
         delay(noteLength);
         noTone(speakerPin);
        }//틀린소리
        TRY--;//생명감소
        Serial.print("TRY==");
        Serial.println(TRY);
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Let's go!");
      for(int k=0;k<TRY;k++){//생명출력
        lcd.setCursor(2*k,1);
        lcd.write(byte(0));
        lcd.write(byte(1));
      }     
      delay(2000);
    }
    if(TRY==0) //게임 끝
    {
      mySerial.write('0');//게임 끝났음을 알림
      lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("The End :(");
          lcd.setCursor(0,1);
          lcd.print("Score : ");
          lcd.setCursor(9,1);
          lcd.print(score);
      state=0;
      for(int thisNote=0; thisNote<sizeof(endmelody)/sizeof(int);thisNote++){
            int noteLength = 1000 / noteDuration_2;
            tone(speakerPin,endmelody[thisNote],noteLength);
            delay(noteLength);
            noTone(speakerPin);
      }
      mySerial.write('1');//게임 새로 시작이므로 바퀴 멈추기
    }
  }
  delay(1000);
}
