#include <Adafruit_Sensor.h>

#include "BluetoothSerial.h" 
#include "DHT.h"
#define DHTPIN 4    
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
float h,tc,tf,DPV;
float calculoVPD(float, float);
BluetoothSerial ESP_BT; 
void setup()
{
  //delay(200);
  
  ESP_BT.begin("ESP32_Control");
  pinMode(DHTPIN, INPUT);
  Serial.begin(9600);
  dht.begin();
  //delay(1000);
  //Serial.println("DHT11 Temperature and Humidity ");
}

void loop()
{
  h = dht.readHumidity();
  tc = dht.readTemperature();
  tf = dht.readTemperature(true);
  //DPV = calculoVPD(tc,h);
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  Temperature: ");
  Serial.print(tc);
  Serial.print("°C Farenheit: ");
  Serial.print(tf);
  Serial.print("°F");
  //Serial.print('\n');
  //Serial.print("Humidity = ");
  //Serial.print(h);
  //Serial.print("%");
  //Serial.print("|");
  //Serial.print("Temperature = ");
  //Serial.print(tc);
  //Serial.print("°C");
  //Serial.print(tf);
  //Serial.println("°F");
  //Serial.print("VPD = ");
  //Serial.print(DPV);
  delay(2000);
}

//VPD Calculation function
float calculoVPD(float temperatura, float humedad){
  float vpd;
  //MODELO VPD
  float POL20 = (6.26561892657228e-07 * pow(temperatura, 4)) + (-2.42404249300208e-05 * pow(temperatura, 3)) + (0.000677192727485077 * pow(temperatura, 2)) + (0.00834036776366291 * pow(temperatura, 1)) + (0.128892036461472);
  float POL40 = (2.88743637651074e-07 * pow(temperatura, 4)) + (-1.34446997709635e-06 * pow(temperatura, 3)) + (0.000967524093043568 * pow(temperatura, 2)) + (0.0122511086135658 * pow(temperatura, 1)) + (0.262449535973739);
  float POL50 = (-1.65261612471285e-07 * pow(temperatura, 4)) + (4.23933812042046e-05 * pow(temperatura, 3)) + (-1.58140996421941e-05 * pow(temperatura, 2)) + (0.0276666556542913 * pow(temperatura, 1)) + (0.303486026630953);
  float POL60 = (5.20948415975800e-07 * pow(temperatura, 4)) + (-6.07372352676187e-06 * pow(temperatura, 3)) + (0.00139646590321512 * pow(temperatura, 2)) + (0.0215714180949708 * pow(temperatura, 1)) + (0.390624528199147);
  float POL70 = (7.46752022857438e-07 * pow(temperatura, 4)) + (-1.28421896423739e-05 * pow(temperatura, 3)) + (0.00165982707217517 * pow(temperatura, 2)) + (0.0260204731604330 * pow(temperatura, 1)) + (0.441147688545347);
  float POL80 = (3.25724050505333e-07 * pow(temperatura, 4)) + (2.75795815597804e-05 * pow(temperatura, 3)) + (0.000794588805205322 * pow(temperatura, 2)) + (0.0397042495299292 * pow(temperatura, 1)) + (0.490692982957548);
  float POL90 = (8.84999406094890e-07 * pow(temperatura, 4)) + (-1.58086533762941e-05 * pow(temperatura, 3)) + (0.00220647688772624 * pow(temperatura, 2)) + (0.0327146743159317 * pow(temperatura, 1)) + (0.564509753987312);
  float POL100 = (4.21596410759925e-06 * pow(temperatura, 4)) + (-0.000226295675673540 * pow(temperatura, 3)) + (0.00662616084934007 * pow(temperatura, 2)) + (0.0105421798545494 * pow(temperatura, 1)) + (0.652697052808198);

  float minim1 = ((humedad - 0) / (20 - 0));
  float minim2 = (40 - humedad) / (40 - 20);
  float minim12 = min(minim1, minim2);
  float fp1 = max((int)minim12, 0);
  float sal1 = fp1 * POL20;

  float minim3 = (humedad - 20) / (40 - 20);
  float minim4 = (50 - humedad) / (50 - 40);
  float minim34 = min(minim3, minim4);
  float fp2 = max((int)minim34, 0);
  float sal2 = fp2 * POL40;

  float minim5 = (humedad - 40) / (50 - 40);
  float minim6 = (60 - humedad) / (60 - 50);
  float minim56 = min(minim5, minim6);
  float fp3 = max((int)minim56, 0);
  float sal3 = fp3 * POL50;

  float minim7 = (humedad - 50) / (60 - 50);
  float minim8 = (70 - humedad) / (70 - 60);
  float minim78 = min(minim7, minim8);
  float fp4 = max((int)minim78, 0);
  float sal4 = fp4 * POL60;

  float minim9 = (humedad - 60) / (70 - 60);
  float minim10 = (80 - humedad) / (80 - 70);
  float minim910 = min(minim9, minim10);
  float fp5 = max((int)minim910, 0);
  float sal5 = fp5 * POL70;

  float minim11 = (humedad - 70) / (80 - 70);
  float minim122 = (90 - humedad) / (90 - 80);
  float minim11122 = min(minim11, minim122);
  float fp6 = max((int)minim11122, 0);
  float sal6 = fp6 * POL80;

  float minim13 = (humedad - 80) / (90 - 80);
  float minim14 = (100 - humedad) / (100 - 90);
  float minim1314 = min(minim13, minim14);
  float fp7 = max((int)minim1314, 0);
  float sal7 = fp7 * POL90;

  float minim15 = (humedad - 90) / (100 - 90);
  float minim16 = (101 - humedad) / (101 - 100);
  float minim1516 = min(minim15, minim16);
  float fp8 = max((int)minim1516, 0);
  float sal8 = fp8 * POL100;

  float deno = fp1 + fp2 + fp3 + fp4 + fp5 + fp6 + fp7 + fp8;
  float nume = sal1 + sal2 + sal3 + sal4 + sal5 + sal6 + sal7 + sal8;
  float salglob = nume / deno;
  vpd = POL100 - salglob;
  return vpd;
}
