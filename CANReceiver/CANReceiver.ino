/*
 * CAN Receiver for CANGraph
 * @version: 0.0.1
 * @author: Rumman Waqar
 * 
 * CAN API Definitions in can_message_def.h
 */

#include <FLEXCAN.h>
#include <kinetis_flexcan.h>

#define ToggleLed(led) digitalWrite(led, !digitalRead(led));

// status led
const int led = 13;

// CAN Object
FlexCAN CANRx(500000);
static CAN_message_t msg;

void setup() {
  pinMode(led, OUTPUT);

  // init CAN
  CANRx.begin();
  delay(500);
}

void loop() {
  while( CANRx.read(msg) ) {
    ToggleLed(led);
    
    Serial.print(msg.id); Serial.print(" ");
    
    for(int i=0; i<msg.len; i++) {
      Serial.print(msg.buf[i]); Serial.print(" ");
    }
    Serial.println("");
  }
}
