# M121 IOT Fan Control Project

In this document, our M121 project is presented. Its aim is to function similarly to a CPU cooler: A temperature sensor is used, which outputs the current temperature. Depending on predefined temperature intervals, the speed of the "FanMotor" is increased; also, an LED lights up to indicate the corresponding level (Green: "OK", Yellow: "Warm", Red: "Hot").

> For more information visit: [m121.ch](https://www.m121.ch)

## Schema

IoT-Education-Board 1.3.1

![alt text](/M121/images/m121-schema.jpg)

## Controller Logic

### PWM

PWM (Pulse Width Modulation) is a method used to control the amount of power delivered to a device, like a motor or LED. It works by rapidly turning the power on and off at varying intervals, where the duration of the 'on' time (pulse width) determines the average power supplied. By changing the ratio of 'on' time to 'off' time, PWM can effectively control the speed, brightness, or position of the device.

The modulation signal influences the duty cycle: By changing the duty cycle of the PWM signal, you effectively control the average power or voltage delivered to a device. In applications like motor control, this control over average power translates to control over the speed or position of the motor.

![alt text](/M121/images/pwm-signal.png)

### Duty-Cycle

![alt text](/M121/images/duty-cycle.JPG)

To calculate the duty cycle percentage, you divide the ON time by the total time (period) and then multiply by 100. In this case:

For a duty cycle of 0:

Duty cycle percentage = (0 / 255) * 100 = 0%
For a duty cycle of 175:

Duty cycle percentage = (175 / 255) * 100 ≈ 68.63%
For a duty cycle of 255:

Duty cycle percentage = (255 / 255) * 100 = 100%

### System-Diagram

![alt text](/M121/images/system-diagram.png)

### Truth Table

- HIGH (H) represents a logic level of 1 or a voltage level that activates the corresponding input.
- LOW (L) represents a logic level of 0 or a voltage level that deactivates the corresponding input.

| INA | INB | Motor Direction     |
| --- | --- | ------------------- |
|  H  |  L  |   Clockwise         |
|  L  |  H  | Counter-clockwise   |
|  H  |  H  |      Brake          |
|  L  |  L  |      Brake          |

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

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  // Ensure that x is within the input range
  if (x < in_min) {
    x = in_min;
  } else if (x > in_max) {
    x = in_max;
  }
  
  // Map x from the input range to the output range
  float mappedValue = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  
  return mappedValue;
}

void loop() {

  redOFF;
  yellowOFF;
  greenOFF;

  // get temp
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  // print temp to serial monitor
  Serial.print(temperatureC);
  Serial.println("*C");
  
  // calculate mappedspeed > linear progression
  float mappedspeed = mapFloat(temperatureC, 22, 25, minspeed, maxspeed);
  // calculate reference number for fanspeed
  int fanRPM = map(mappedspeed, 0, 255, 0, 100);
  // print rmp
  Serial.print("Fan RPM: ");
  Serial.print(fanRPM);
  Serial.println("%");

  delay(50);

  if (temperatureC <= 22.0) {
    greenON;
    ledcWrite(PWM_KANAL_0,0); // INA = 0
    ledcWrite(PWM_KANAL_1,minspeed); // INB = 255
    delay(50);
  } else if (temperatureC > 22.0 && temperatureC < 25.0) {
    yellowON;
    ledcWrite(PWM_KANAL_0,0); // INA = 0
    ledcWrite(PWM_KANAL_1,mappedspeed); // INB = 255
    delay(50);
  } else {
    redON;
    ledcWrite(PWM_KANAL_0,0); // INA = 0
    ledcWrite(PWM_KANAL_1,maxspeed); // INB = 255
    delay(50);
  }
}
```

## Componants

### esp32

![alt text](/M121/images/esp32-olimex-dev-lipo.jpg)

### temp sensor

![alt text](/M121/images/temp-sensor.jpg)

### fan 

![alt text](/M121/images/fan.jpg)

### IoT Education Board, full setup

![alt text](/M121/images/full-setup.jpg)