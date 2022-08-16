#include<LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);

int i=0;
int ok,cancel,up,down;
char  count[4];
char  count1[4];
char buffer1[20];
void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print("   Login pswd   ");

pinMode(A0,INPUT_PULLUP);
pinMode(A1,INPUT_PULLUP);
pinMode(A2,INPUT_PULLUP);
pinMode(A3,INPUT_PULLUP);

count[0]='0';
count[1]='0';
count[2]='0';
count[3]='0';

}

void loop() {
  // put your main code here, to run repeatedly:
while(1)
{  
ok=digitalRead(A0);
cancel=digitalRead(A1);
up=digitalRead(A2);
down=digitalRead(A3);
if (ok==LOW)
{ 
  while(digitalRead(A0)==LOW);
  count1[i]=count[i];
  count[i]='*';
  i++;
  
  if (i>=4)
  break;
  
  }
if (cancel==LOW)
{ 
  while(digitalRead(A1)==LOW);
  break;

  }
if (up==LOW)
{ 
  while(digitalRead(A2)==LOW);
  count[i]++;
  if(count[i]>'9')
  count[i]='0';

  }
if (down==LOW)
{ 
  while(digitalRead(A3)==LOW);
  count[i]--;
  if(count[i]<'0')
  count[i]='9';

  }
sprintf(buffer1,"      %c%c%c%c      ",count[0],count[1],count[2],count[3]);  
lcd.setCursor(0,1);
lcd.print(buffer1);
}

if((count1[0]=='1')&&(count1[1]=='2')&&(count1[2]=='3')&&(count1[3]=='4'))
{
lcd.setCursor(0,0);  
lcd.clear();
lcd.print("Successfully done ");
  }
  else
  {
lcd.clear();
lcd.print("faild ");
    }
while(1);

}
