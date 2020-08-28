//pin connectons

//gnd-gng
//vcc-5v
//sng-a1 s
#include "Oxygen.h"
#include "arduino.h"
float calibration_voltage; 
#define O2_percentage 20.80
float O2_value()    
{
  unsigned int sum = 0;
  if (O2_init_flag == 0)
  {
    O2_init_flag = 1;         
    pinMode(O2_pin, INPUT);
    for (unsigned char i = 64;i > 0;i--)
    {
      sum = sum + analogRead(O2_pin);
      delay(100);
    }
    sum = sum >> 6;
    calibration_voltage = sum / O2_percentage;
    //SerialUSB.println(calibration_voltage);
    return 20.80;          
  }
  else
  {
    for (unsigned char i = 32;i > 0;i--)
    {
      sum = sum + analogRead(O2_pin);
      delay(50);
    }
    sum = sum >> 5;
    //SerialUSB.println(sum);
    float output = sum / calibration_voltage;
    //SerialUSB.println(sum);
    return output;
  }
}

// readO2.ino
    #include "Oxygen.h"
    void setup() {
      // put your setup code here, to run once:
      Serial.begin(9600);
      Serial.println("Calibration sensor...This needs one minute");
      O2_value();
      Serial.println("Finish Calibration");
    }

    void loop() {
      // put your main code here, to run repeatedly:
      float O2 = 0;
      O2 = O2_value();
      Serial.print("The percentage of oxygen is:");
      Serial.print(O2);
      Serial.println("%");
      delay(1000);
    } 
