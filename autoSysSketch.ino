/**
offline/local auto watering pump

1. reads soil moisture
2. shows emotions on LED matrix depending on moisture level
3. automatically turns pump on when soil is dry 
4. stores last pump state in EEPROM (survive reset)
5. prints moisture & pump state to serial monitor
*/


#include <SPI.h>
#include <EEPROM.h>
#include "Arduino_LED_Matrix.h"


//define the soil moisture sensor pin and relay module signal pin 
#define moisture_sensor A0
#define relay A5

//matrix predefined function 
ArduinoLEDMatrix matrix;

int eeprom_addr = 0;
int sensorValue = 0;
int pump_status = 0;
float moist_percent = 0.0;

unsigned long lastSensorTime = 0;
const long interval = 1000;

//LED Frames
const uint32_t HAPPY_LED[] = {
  0x3fc48a95, 0x58019fd9, 0x5889871
};
const uint32_t NORMAL_LED[] = {
  0x3fc40298, 0xd98d8019, 0x5889871
};
const uint32_t SAD_LED[] = {
  0x3fc48a9d, 0xd8898018, 0x71889905
};

//initializes and sets the microcontroller peripherals, ADC, and LED matrix
void init_renesas_MCU_IO(){
  pinMode(relay, OUTPUT);
  pinMode(moisture_sensor, INPUT);
  analogReadResolution(12);
  matrix.begin();
}

//display facial expression on the LED matrix based on soil moisture level 
void track_soil_moisture() {
  sensorValue = analogRead(moisture_sensor);
  moist_percent = 100 - ((float)sensorValue / 4096.0) * 100;

  if(moist_percent >= 0 && moist_percent < 55.33) {
    Serial.println("Dry");
    matrix.loadFrame(SAD_LED);
    pump_status = 1; //auto on
  }

  else if (moist_percent >= 55.33 && moist_percent < 70.66) {
    Serial.println("Moderate");
    matrix.loadFrame(NORMAL_LED);
    pump_status = 0;
  }
  else {
    Serial.println("Wet");
    matrix.loadFrame(HAPPY_LED);
    pump_status = 0;
  }
}

void updatePump() {
  if (pump_status == 1){
    Serial.println("Water pump: ON");
    digitalWrite(relay, HIGH);
  } 
  else {
    Serial.println("Water pump: OFF");
    digitalWrite(relay, LOW);
  }

  EEPROM.write(eeprom_addr, pump_status);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  init_renesas_MCU_IO();
  int prev_pump_status = EEPROM.read(eeprom_addr);
  pump_status = prev_pump_status; //restores last pump state 
  //digitalWrite(relay, HIGH);
}

void loop() {
  //put your main code here, to run repeatedly:
  unsigned long currentMills = millis();

  //run every 1 sec 
  if(currentMills - lastSensorTime >= interval){
    lastSensorTime = currentMills;
    track_soil_moisture();
    updatePump();

    Serial.print("Soil moisture: ");
    Serial.print(moist_percent);
    Serial.println("%");
  }

}





