
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
const int xpin = A0;
const int ypin = A1;
const int zpin = A2;
byte p[8] = {
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F
};
float threshhold=80.0;

float xval[100]={0};
float yval[100]={0};
float zval[100]={0};
float xavg;
  float yavg;
  float zavg;
 
int steps,flag=0;

void setup()

{

  Serial.begin(9600);
  lcd.createChar(0, p);
  lcd.begin(16, 2);
  lcd.setCursor(4, 0);
  lcd.print("PIS");
  lcd.setCursor(4, 1);
  lcd.print("Pedometer");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 1);
  delay(1000);
  calibrate();
}

void loop()
{
    lcd.setCursor(0, 1);
    lcd.print("Processing....");
    
    lcd.setCursor(0,0);
    for (int w = 0; w < 16; w++)
    {
      lcd.write(byte(0));
      delay(500);
    }
 
    int acc=0;
    float totvect[100]={0};
    float totave[100]={0};
    //float sum1,sum2,sum3=0;
    float xaccl[100]={0};
    float yaccl[100]={0};
    float zaccl[100]={0};
   
 
    for (int i=0;i<100;i++)
    {
      xaccl[i]=float(analogRead(xpin));
      delay(1);
      yaccl[i]=float(analogRead(ypin));
      delay(1);
      zaccl[i]=float(analogRead(zpin));
      delay(1);
      totvect[i] = sqrt(((xaccl[i]-xavg)* (xaccl[i]-xavg))+ ((yaccl[i] - yavg)*(yaccl[i] - yavg)) + ((zval[i] - zavg)*(zval[i] - zavg)));
      totave[i] = (totvect[i] + totvect[i-1]) / 2 ;
      //acc=acc+totave[i];
      Serial.println(totave[i]);
       delay(100);

      if (totave[i]>threshhold && flag==0)
      {
          steps=steps+1;
          flag=1;
      }
      else if (totave[i] > threshhold && flag==1)
      {//do nothing
      }
      if (totave[i] <threshhold  && flag==1)
      {flag=0;}
      
      Serial.print("steps=");
      Serial.println(steps);
      lcd.print("Steps Taken:");
      lcd.print(steps - 1);
      delay(1000);
      lcd.clear();

    }


      float tim=acc/100;
      Serial.println(tim);
      delay(1000);
      //stepcal(totave);

 
}

void calibrate()

{
 
  float sum=0;
  float sum1=0;
  float sum2=0;
  for (int i=0;i<100;i++)
{
xval[i]=float(analogRead(xpin));

sum=xval[i]+sum;
}
delay(100);
xavg=sum/100.0;

Serial.println(xavg);

for (int j=0;j<100;j++)
{
xval[j]=float(analogRead(xpin));

sum1=xval[j]+sum1;
}
yavg=sum1/100.0;

Serial.println(yavg);
delay(100);
for (int i=0;i<100;i++)
{
zval[i]=float(analogRead(zpin));

sum2=zval[i]+sum2;
}
zavg=sum2/100.0;
delay(100);
Serial.println(zavg);


}
