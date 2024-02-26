# M121 IOT Fan Control Project

In diesem Dokument wird unser M121-Projekt vorgestellt. Dieses hat das Ziel, ähnlich wie eine CPU-Kühlung zu funktionieren: Es wird ein Temperatur-Sensor genutzt, welcher die aktuelle Temperatur ausgibt. Abhängig von vordefinierten Temperatur-Intervallen wird die Geschwindigkeit des "FanMotors" erhöht; auch leuchtet ein LED um die entsprechende Stufe anzuzeigen (Grün: "OK", Gelb: "Warm", Rot: "Heiss").

> Für genauerer Informationen zum Board und den Komponenten, siehe [m121.ch](https://www.m121.ch)

## Schema

IoT-Education-Board 1.3.1

![alt text](/M121/m121-schema.jpg)

## Code

Using the esp32 olimex dev-lipo

```C
// nötige def für led

#define startRed pinMode(27, OUTPUT);
#define startYellow pinMode(26, OUTPUT);
#define startGreen pinMode(25, OUTPUT);

#define redON digitalWrite(27, HIGH);
#define yellowON digitalWrite(26, HIGH);
#define greenON digitalWrite(25, HIGH);
#define redOFF digitalWrite(27, LOW);
#define yellowOFF digitalWrite(26, LOW);
#define greenOFF digitalWrite(25, LOW);

// nötige def für temp
#include <OneWire.h>
#include <DallasTemperature.h>

const int oneWireBus = 23;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);


// nötige def für venti
#define PWM_KANAL_0 0
#define PWM_KANAL_1 1
#define PWM_AUFLOESUNG 8
#define PWM_FREQ 5000
#define INB_PIN 22
#define INA_PIN 21

#define CW    (digitalWrite(INA_PIN,LOW),ledcWrite(INB_KANAL_0,255))
#define CCW   (digitalWrite(INA_PIN,HIGH),ledcWrite(INB_KANAL_0,0))
#define STOP  (digitalWrite(INA_PIN,LOW),digitalWrite(INB_PIN,LOW))

int maxspeed = 255;
int medspeed = 175;
int minspeed = 100;
int speed = 0;


void setup() {

  // setup für led
  startRed;
  startYellow;
  startGreen;

  // setup für temp
  Serial.begin(115200);
  sensors.begin();

  // setup für venti
  pinMode(INA_PIN,OUTPUT);
  pinMode(INB_PIN,OUTPUT);
  ledcSetup(PWM_KANAL_0,PWM_FREQ,PWM_AUFLOESUNG);
  ledcSetup(PWM_KANAL_1,PWM_FREQ,PWM_AUFLOESUNG);
  ledcAttachPin(INA_PIN, PWM_KANAL_0);
  ledcAttachPin(INB_PIN, PWM_KANAL_1);
}

void loop() {

  redOFF;
  yellowOFF;
  greenOFF;

  // get temp
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);

  Serial.print(temperatureC);
  Serial.println("*C");
  delay(250);

  if (temperatureC <= 23.0) {
    greenON;
    ledcWrite(PWM_KANAL_0,0); // INA = 0
    ledcWrite(PWM_KANAL_1,minspeed); // INB = 255
    delay(250);
  } else if (temperatureC > 23.0 && temperatureC < 25.0) {
    yellowON;
    ledcWrite(PWM_KANAL_0,0); // INA = 0
    ledcWrite(PWM_KANAL_1,medspeed); // INB = 255
    delay(250);
  } else {
    redON;
    ledcWrite(PWM_KANAL_0,0); // INA = 0
    ledcWrite(PWM_KANAL_1,maxspeed); // INB = 255
    delay(250);
  }
}
```
