#include <Stepper.h>//Arduino官方库
const int stepsPerRevolution = 200; //根据步进电机步距角调整
Stepper myStepper(stepsPerRevolution, 8,9,10,11);//输出引脚
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
//步进电机撞击快门
void back(){
  myStepper.step(stepsPerRevolution);
}
//步进电机回到初始位置
void loop()
{   

  while (Serial.available() > 0)  
  {       
    comdata += char(Serial.read());  
    delay(2);
  }
    int ex_time=(comdata[1]-48)*100+(comdata[2]-48)*10+(comdata[3]-48)*1;//设置手动模式下的曝光时间（s）000~999
    int rl_time=(comdata[4]-48)*100+(comdata[5]-48)*10+(comdata[6]-48)*1;//设置两次拍摄的间隔时间，缩时摄影必备（s）000~999
    int pic_num=(comdata[7]-48)*100+(comdata[8]-48)*10+(comdata[9]-48)*1;//设置自动化拍摄时的拍摄张数000~999

  if (comdata[0]=='a')//当输入字符串第一位为a时
  {
    shoot();
    back();
    Serial.println("Picture Taken");//串口输出方便了解工作状态
    comdata = String("");//清空字符串
  }
  else if (comdata[0]=='b')
  {
    shoot(); 
    delay(ex_time*1000);//手动模式下曝光时间  （*1000秒转换为毫秒）
    back();
    Serial.println("Picture Taken");
    comdata = String("");//同上
  }
  else if(comdata[0]=='c')
  {
    for(i=pic_num;i>0;i--)//拍摄张数 循环TT看了就明白了  说不清楚了TT
    {
      shoot();
      delay(ex_time*1000);//同b
      back();
      Serial.println("Picture Taken");
      delay(rl_time*1000);//两张照片拍摄间隔时间
    }
    comdata = String("");//同上
  }

}
