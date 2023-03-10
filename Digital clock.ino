#include <LiquidCrystal.h>
#include <TimerOne.h>


const int rs = 12, e = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

int hrs = 0, mins = 0, secs = 0;
unsigned long time;
const int hr_btn = 2, min_btn = 3;

void timer_interrupt();
void hr_isr();
void min_isr();

void setup() {
  lcd.begin(16,2);

  attachInterrupt(digitalPinToInterrupt(hr_btn), hr_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(min_btn), min_isr, RISING);
  
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(timer_interrupt);
  
  
}

void loop() {



  lcd.setCursor(4, 0);
  if(hrs < 10){
    lcd.print(0);
  }
  lcd.print(hrs);
  lcd.print(':');
  if(mins < 10){
    lcd.print(0);
  }
  lcd.print(mins);
  lcd.print(':');
  if(secs < 10){
    lcd.print(0);
  }
  lcd.print(secs);

  delay(500);
  
}

void timer_interrupt(){
  
  secs++;
  if (secs == 60){
    mins++;
    secs = 0;
  }
  if (mins == 60){
    hrs++;
    mins = 0;
  }
  if (hrs == 24){
    hrs = 0;
  }
}

void hr_isr(){
  if (hrs == 24){
    hrs = 0;
    
  }
  else{
  hrs++;
  }
  secs = 0;
  delay(50);
}

void min_isr(){
  if (mins == 60){
    mins = 0;
    
  }
  else{
  hrs++;
  }
  secs = 0;
  delay(50);
}
