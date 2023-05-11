#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

Servo ServoRight;
Servo ServoHand;
Servo ServoDown;
Servo ServoLeft;
const char* ssid = "Robot Arm";
const char* password = "12345678";
int x ,y;
int c =0;
int V = 1;
ESP8266WebServer Server(80);
IPAddress local_ip(192, 168, 5, 2), gateway(192, 168, 5, 1), subnet(255, 255, 255, 0);

void setup() 
{
  Serial.begin(115200);
  ServoRight.attach(D1);
  ServoHand.attach(D3);
  ServoDown.attach(D2);
  ServoLeft.attach(D0);
  WiFi.softAP(ssid, password);
  delay(100);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  Serial.println("SoftAP started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  Server.on("/ArmMove", HTTP_GET, MIT_Messege);
  Server.on("/LeftServo", HTTP_GET, LeftServo);
  Server.on("/RightServo", HTTP_GET, RightServo);
  Server.on("/DownServo", HTTP_GET, DownServo);
  Server.on("/HandServo", HTTP_GET, HandServo);
  Server.on("/Attack", HTTP_GET, Attack);
  Server.on("/Hello", HTTP_GET, Hello);
  Server.on("/Ta3qip", HTTP_GET, Ta3qip);
  Server.on("/SpeedUp", HTTP_GET, SpeedUp);
  Server.on("/SpeedDown", HTTP_GET, SpeedDown);
  Server.on("/Aw3a", HTTP_GET, Aw3a);
  
  Server.begin();
}

void loop() {
  Server.handleClient();
  
}
void Aw3a()
{
  Server.send(200, "text/plain", "Ok");
  Serial.println("Aw3a");
  ServoLeft.write(180);
  ServoRight.write(20);
  ServoDown.write(90);
  delay(1500);
  ServoLeft.write(70);
  delay(100);
  ServoRight.write(70);
  delay(100);
  ServoRight.write(20);
  ServoLeft.write(180);
  ServoDown.write(90);
}
void SpeedUp()
{
  Server.send(200, "text/plain", "Ok");
  if(V < 10)
  {
    V++;  
    Serial.print("Speed Up to: ");
    Serial.println(V);
  }
  
}
void SpeedDown()
{
  Server.send(200, "text/plain", "Ok");
  if(V > 1)
  {
    V--;  
    Serial.print("Speed Downed to: ");
    Serial.println(V);
  }
  
}
void MIT_Messege() {
  String som = "position :" + (String)Server.arg("pos");
  Server.send(200, "text/plain", "Ok");
  Serial.print("C = ");
  Serial.println(c);
}
void Ta3qip()
{
  ServoLeft.write(180);
  ServoRight.write(20);
  ServoDown.write(90);
  Server.send(200, "text/plain", "Ok");
  Serial.println("Ta3qip");
  for(int i = 0; i < 4; i++)
  {
     ServoRight.write(20);
     ServoLeft.write(180);
     delay(1000);
     ServoLeft.write(40);
     delay(1000);
     
  }
  ServoLeft.write(180);
  ServoRight.write(20);
  ServoDown.write(90);
}
void Attack()
{
  Server.send(200, "text/plain", "Ok");
   Serial.println("Attack");
   ServoLeft.write(180);
  ServoRight.write(20);
  ServoDown.write(90);
  delay(1500);
  ServoLeft.write(40);
  delay(100);
  ServoRight.write(80);
  delay(100);
  ServoRight.write(20);
  ServoLeft.write(180);
  ServoDown.write(90);
}
void Hello()
{
  Server.send(200, "text/plain", "Ok");
  Serial.println("Hello");
   ServoLeft.write(180);
  ServoRight.write(20);
  ServoDown.write(90);
  delay(500);
  for(int i = 0; i < 4; i++)
  {
    ServoDown.write(100);
    delay(300);
    ServoDown.write(150);
    delay(300);
  }
  ServoLeft.write(180);
  ServoRight.write(20);
  ServoDown.write(90);
}
void LeftServo()
{
  
  Server.send(200, "text/plain", "Ok");
  String x = (String)Server.arg("pos");
  if(x == "1")
  {
      
    int curnet = ServoLeft.read() ;
    int newpos = curnet + (10 * V);
    if (newpos > 180)
    {
      newpos = 180;
    }
    if(curnet != newpos)
    {
      for(int i=curnet ; i<= newpos ; i+=V)
      {
        ServoLeft.write(i);
      } //delay(5);
    
    }
    Serial.println("up");
  }
  else if (x == "2")
  {
    int curnet = ServoLeft.read() ;
    int newpos = curnet - (10 * V);
    if (newpos < 40)
    {
      newpos = 40;
    }
    if(curnet != newpos)
    {
      for(int i=curnet ; i>= newpos ; i-=V)
      {
        ServoLeft.write(i);
      }
       
    
    }
   
    Serial.println("Down");
  }
}
void RightServo()
{
  Server.send(200, "text/plain", "Ok");
  String x = (String)Server.arg("pos");
  if(x == "1")
  {
      
    int curnet = ServoRight.read() ;
    int newpos = curnet + (10 * V);
    if (newpos > 110)
    {
      newpos = 110;
    }
    if(curnet != newpos)
    {
      for(int i=curnet ; i<= newpos ; i+=V)
      {
        ServoRight.write(i);
      } //delay(5);
    
    }
    Serial.println("ForWard");
  }
  else if (x == "2")
  {
    int curnet = ServoRight.read() ;
    int newpos = curnet - (10 * V);
    if (newpos < 20)
    {
      newpos = 20;
    }
    if(curnet != newpos)
    {
      for(int i=curnet ; i>= newpos ; i-=V)
      {
        ServoRight.write(i);
      }
       
    
    }
   
    Serial.println("BackWard");
  }
  
}
void HandServo()
{
    Server.send(200, "text/plain", "Ok");
  String x = (String)Server.arg("pos");
  if(x == "1")
  {
      
    int curnet = ServoHand.read() ;
    int newpos = curnet + (10 * V);
    if (newpos > 180)
    {
      newpos = 180;
    }
    if(curnet != newpos)
    {
      for(int i=curnet ; i<= newpos ; i+=V)
      {
        ServoHand.write(i);
      } //delay(5);
    
    }
    Serial.print("Leave ");
    Serial.println(newpos);
  }
  else if (x == "2")
  {
    int curnet = ServoHand.read() ;
    int newpos = curnet - (10 * V);
    if (newpos < 50)
    {
      newpos = 50;
    }
    if(curnet != newpos)
    {
      for(int i=curnet ; i>= newpos ; i-=V)
      {
        ServoHand.write(i);
      }
       
    
    }
   
    Serial.print("Hold ");
    Serial.println(newpos);
  }
}
void DownServo()
{
   
  Server.send(200, "text/plain", "Ok");
  String x = (String)Server.arg("pos");
  if(x == "2")
  {
      
    int curnet = ServoDown.read() ;
    int newpos = curnet + (10 * V);
    if (newpos > 180)
    {
      newpos = 180;
    }
    if(curnet != newpos)
    {
      for(int i=curnet ; i<= newpos ; i+=V)
      {
        ServoDown.write(i);
       } //delay(5);
    
    }
    Serial.println("Right");
  }
  else if (x == "1")
  {
    int curnet = ServoDown.read() ;
    int newpos = curnet - (10 * V);
    if (newpos < 0)
    {
      newpos = 0;
    }
    if(curnet != newpos)
    {
      for(int i=curnet ; i>= newpos ; i-=V)
      {
        ServoDown.write(i);
      }
       
    
    }
   
    Serial.println("Left");
  }
  
}
void extractValues(String inputString) {
  // find the positions of the "=" signs
  int xPos = inputString.indexOf('=') + 2;
  int yPos = inputString.lastIndexOf('=') + 2;

  // extract the substrings that contain the numerical values
  String xStr = inputString.substring(xPos, yPos - 4);
  String yStr = inputString.substring(yPos);

  // convert the substrings to doubles
   x = xStr.toDouble();
   y = yStr.toDouble();

  // print the values to the serial monitor for verification
  Serial.print("x = ");
  Serial.print(x);
  Serial.print(" y = ");
  Serial.println(y);
}

  
