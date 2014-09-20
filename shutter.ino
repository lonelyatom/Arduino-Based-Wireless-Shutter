#include <Stepper.h>
const int stepsPerRevolution = 200; 
Stepper myStepper(stepsPerRevolution, 8,9,10,11); 
int i;
String comdata = "";

void setup()
{
  myStepper.setSpeed(60);
  Serial.begin(9600);
}

void shoot(){ 
  myStepper.step(-stepsPerRevolution);  
}

void back(){
  myStepper.step(stepsPerRevolution);
}

void loop()
{   

  while (Serial.available() > 0)  
  {       
    comdata += char(Serial.read());  
    delay(2);
  }
  int ex_time=(comdata[1]-48)*100+(comdata[2]-48)*10+(comdata[3]-48)*1;
  int rl_time=(comdata[4]-48)*100+(comdata[5]-48)*10+(comdata[6]-48)*1;
  int pic_num=(comdata[7]-48)*100+(comdata[8]-48)*10+(comdata[9]-48)*1;

  if (comdata[0]=='a')
  {
    shoot();
    back();
    Serial.println("Picture Taken");
    comdata = String("");
  }
  else if (comdata[0]=='b')
  {
    shoot(); 
    delay(ex_time*1000);
    back();
    Serial.println("Picture Taken");
    comdata = String("");
  }
  else if(comdata[0]=='c')
  {
    for(i=pic_num;i>0;i--)
    {
      shoot();
      delay(ex_time*1000);
      back();
      Serial.println("Picture Taken");
      delay(rl_time*1000);
    }
    comdata = String("");
  }

}
