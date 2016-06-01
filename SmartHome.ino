//#define BLYNK_DEBUG
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266_SoftSer.h>
#include <BlynkSimpleShieldEsp8266_SoftSer.h>
#include <dht.h>
#include <SimpleTimer.h>
dht DHT;
WidgetLCD lcd(V3);
int nRainVal;
#define DHT11_PIN 5 // DHT11 PIN FOR NOW
int nRainIn = A1;
int nRainDigitalIn = 9;
// Set ESP8266 Serial object
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX
ESP8266 wifi(EspSerial);
SimpleTimer timer;
char auth[] = "dcaa75d3d50541008064204cb845f847";

void sendUptime()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, millis() / 1000);
  Blynk.virtualWrite(V1, millis() / 1000);
  Blynk.virtualWrite(V2, millis() / 1000);
  Blynk.virtualWrite(V3, millis() / 1000);
}

void setup()
{
  // Set console baud rate
  Serial.begin(9600);
  delay(10);
  // Set ESP8266 baud rate
  // 9600 is recommended for Software Serial
  EspSerial.begin(9600);
  delay(10);
 Blynk.begin(auth, wifi, "net_9718015549call", "macbeth123" );
  timer.setInterval(1000L, rain);
  timer.setInterval(1000L, tempe);
}
void rain()
{

   Blynk.virtualWrite(2, nRainVal);
     lcd.clear();
  if (nRainVal< 550)
  {
       lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "Raining"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(4, 1, "Heavily!");
 // Blynk.email("kaustubhagarwal18@gmail.com","Subject","Message");
  }
  if (nRainVal> 700 && nRainVal < 1000)
  {
      lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "Rain"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(4, 1, "Warning!");
  
  //Blynk.email("kaustubhagarwal18@gmail.com","Subject","Message");
  } 
    if (nRainVal> 1000)
  {
       lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "No"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(4, 1, "Rain!!");
  //Blynk.notify("No");
  }
}

void tempe() {

  int chk = DHT.read11(DHT11_PIN);
    Blynk.virtualWrite(0, DHT.temperature);  // Write values to the app
  Blynk.virtualWrite(1, DHT.humidity);
}
void loop()
{
  Blynk.run();
  timer.run();
}
