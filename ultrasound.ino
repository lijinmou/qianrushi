/*
功能：利用SR04超声波传感器进行测距，并用串口显示测出的距离值
*/
#include <LiquidCrystal.h>   //引用1602液晶的函数库
// 设定SR04超声波模块连接的Arduino的数字口
const int EchoPin = 3; //Echo回声引脚连到数字口3
const int TrigPin = 2;  //Trig触发引脚连到数字口2
int ledpin=13;//定义数字口13
float distance;
const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);   //4位连接法
void setup()
{   // 初始化串口通信及连接超声波模块的引脚
    Serial.begin(9600);                                  
    lcd.begin(16, 2);  //初始化1602液晶, 显示范围为2行16列字符
    lcd.clear();  //清屏
    lcd.setCursor(2, 0); //把光标定位在第0行，第2列
    lcd.print("power on");
    pinMode(TrigPin, OUTPUT);  //Arduino在TigPin产生的触发信号作为输出 送到超声模块的Echo引脚
    pinMode(EchoPin, INPUT);    //超声模块Echo引脚产生的电平信号 输入到Arduino的EchoPin
   
    Serial.println("Ultrasonic sensor:");
}
void loop()
{
    // 产生一个10us的高脉冲去触发TrigPin
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);
   
    // 读取EchoPin引脚上的高电平脉冲宽度（单位：微秒），并计算出距离（单位：厘米）
    distance = pulseIn(EchoPin, HIGH) / 58.00;  //自己分析为何这么计算？
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print("cm");
    Serial.println();
    int x = analogRead(A0);
    if (x<=200){
       digitalWrite(ledpin,LOW);//熄灭数字13口的LED
       Serial.print("LDR Reading: ");  //通过串口监视器
       Serial.println(x); //输出LDR读数    
      }
      else{
         pinMode(ledpin,OUTPUT);//设置数字13 口为输出口，Arduino 上我们用到的I/O 口都要进行类似这样的定义。
         digitalWrite(ledpin,HIGH);//点亮数字13口的LED。
        }
    delay(200);
    
}
