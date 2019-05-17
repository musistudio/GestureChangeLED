/****************************************************************
IMPORTANT: The APDS-9960 can only accept 3.3V!
 
 Arduino Pin  APDS-9960 Board  Function
 
 3.3V         VCC              Power
 GND          GND              Ground
 A4           SDA              I2C Data
 A5           SCL              I2C Clock
 2            INT              Interrupt

****************************************************************/

#include <Wire.h>
#include <SparkFun_APDS9960.h>

// Pins
#define APDS9960_INT    2 // Needs to be an interrupt pin

// Constants

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;


//三种颜色对应的引脚
int red = 9;
int green = 5;
int blue = 6;
//自变色状态下三种颜色的初始强度（相当于3个呼吸灯）
int valx = 60;
int valy = 130;
int valz = 195;
//自变色状态下三种颜色的变化速度
int fadeAmount1 = 3;
int fadeAmount2 = 6;
int fadeAmount3 = 9;

// 灯光模式
// 0为白光
// 1-7分别为红橙黄绿蓝靛紫
// 8为自变色
int model = 0;


void setup() {

  // Set interrupt pin as input
  pinMode(APDS9960_INT, INPUT);

  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  
  // Initialize interrupt service routine
  attachInterrupt(0, interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
}

void loop() {
  if( isr_flag == 1 ) {
    detachInterrupt(0);
    handleGesture();
    isr_flag = 0;
    attachInterrupt(0, interruptRoutine, FALLING);
  }
  checkModel();
   
}

void interruptRoutine() {
  isr_flag = 1;
}

void checkModel() {
  Serial.println(model);
  switch ( model ) {
      case 0:
        white();
        break;
      case 1:
        redLight();
        break;
      case 2:
        orange();
        break;
      case 3:
        yellow();
        break;
      case 4:
        greenLight();
        break;
      case 5:
        blueLight();
        break;
      case 6:
        indigo();
        break;
      case 7:
        violet();
        break;
      case 8:
        fading();
        break;
      default:
        redLight();
        break;
  }
}

void handleGesture() {
    if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        break;
      case DIR_LEFT:
        if( model == 0) {
          model = 8;
        }else{
          model--;  
        }
        break;
      case DIR_RIGHT:
        if(model == 8) {
          model = 0;
        }else{
          model++;
        }
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
      default:
        Serial.println("NONE");
    }
  }
}

void white() {                                                                   
  // 熄灭
  analogWrite(red, 255);
  analogWrite(green, 255);
  analogWrite(blue, 255);
  // 返回主程序
  // return; 
}

void redLight() {
  // 红光函数
  analogWrite(red, 255);
  analogWrite(green, 0);
  analogWrite(blue, 0);
}

void orange() {
  // 橙光函数
  analogWrite(red, 255);
  analogWrite(green, 125);
  analogWrite(blue, 0);
}

void yellow() {
  // 黄光函数
  analogWrite(red, 255);
  analogWrite(green, 255);
  analogWrite(blue, 0);
}

void greenLight() {
  // 绿光函数
  analogWrite(red, 0);
  analogWrite(green, 255);
  analogWrite(blue, 0);
}

void blueLight() {
  // 蓝光函数
  analogWrite(red, 0);
  analogWrite(green, 0);
  analogWrite(blue, 255);
}

void indigo() {
  // 靛 函数
  analogWrite(red, 0);
  analogWrite(green, 255);
  analogWrite(blue, 255);
}

void violet() {
  // 紫光函数
  analogWrite(red, 255);
  analogWrite(green, 0);
  analogWrite(blue, 255);
}


void fading() {                                                                
  //自变色函数
 
  analogWrite(red, valx);
  analogWrite(green, valy);
  analogWrite(blue, valz);
  valx = valx + fadeAmount1;
  valy = valy + fadeAmount2;
  valz = valz + fadeAmount3;
  if (valx <= 4 || valx >= 252) {
    fadeAmount1 = -fadeAmount1 ;
  }
  if (valy <= 7 || valy >= 249) {
    fadeAmount2 = -fadeAmount2 ;
  }
  if (valz <= 10 || valz >= 246) {
    fadeAmount3 = -fadeAmount3 ;
  }
  delay(90); 
}
