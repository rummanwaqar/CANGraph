/*
 * Test CAN Transmitter for CANGraph
 * @version: 0.0.1
 * @author: Rumman Waqar
 * 
 * CAN API Definitions in can_message_def.h
 * Simulates:
 *    throttle
 *    brake
 *    motor error
 *    motor speed
 *    motor current
 */

// can libraries
#include <FLEXCAN.h>
#include <kinetis_flexcan.h>
// scheduling library
#include <Metro.h>
// can bus message definitions
#include "can_message_def.h"
#include "can_message.h"

#define ToggleLed(led) digitalWrite(led, !digitalRead(led));

// status led
const int led = 13;

// CAN object
FlexCAN CANTx(500000);
static CAN_message_t msg;

/*
 * Create CAN Message Descriptors
 */
can_msg::MsgEncode throttle_msg( can_msg::UINT8, can_msg::MOTOR, can_msg::THROTTLE, can_msg::CRITICAL, 1 );
can_msg::MsgEncode brake_msg( can_msg::UINT8, can_msg::MOTOR, can_msg::BRAKE, can_msg::CRITICAL, 1 );
can_msg::MsgEncode merror_msg( can_msg::BOOL, can_msg::MOTOR, can_msg::MERROR, can_msg::IMPORTANT, 2 );
can_msg::MsgEncode mspeed_msg( can_msg::INT16, can_msg::MOTOR, can_msg::MSPEED, can_msg::INFORMATION, 1 );
can_msg::MsgEncode mcurrent_msg( can_msg::INT16, can_msg::MOTOR, can_msg::MCURRENT, can_msg::INFORMATION, 1 );

/*
 * Timers
 */
Metro throttle_timer = Metro(2000); // every 100 ms
Metro encoder_timer = Metro(500);   // every 20ms
Metro current_timer = Metro(1000);   // every 50ms

void setup() {
  pinMode(led, OUTPUT);
  // init CAN
  CANTx.begin();
  delay(500);
  Serial.println("CAN Transmitter Initialized");
}

void loop() {
  if(throttle_timer.check()) {
    set_throttle(78);
    set_brake(69);
  }
  if(encoder_timer.check()) {
    set_error(0, 1);
    set_speed(0x1234);
  }
  if(current_timer.check()) {
    set_current(0x4568);
  }
}

void set_throttle(uint8_t val) {
  // send throttle
  msg.id = throttle_msg.id();
  msg.len = throttle_msg.len();
  throttle_msg.buf(msg.buf, val);
  CANTx.write(msg);
}

void set_brake(uint8_t val) {
  // send brake
  msg.id = brake_msg.id();
  msg.len = brake_msg.len();
  brake_msg.buf(msg.buf, val);
  CANTx.write(msg);
}

void set_error(bool stall, bool overcurrent) {
  // send error
  msg.id = merror_msg.id();
  msg.len = merror_msg.len();
  merror_msg.buf(msg.buf, stall << can_msg::MERROR_STALL | overcurrent << can_msg::MERROR_OVERCURRENT);
  CANTx.write(msg);
}

void set_speed(uint16_t val) {
  // send brake
  msg.id = mspeed_msg.id();
  msg.len = mspeed_msg.len();
  mspeed_msg.buf(msg.buf, val);
  CANTx.write(msg);
}

void set_current(uint16_t val) {
  // send brake
  msg.id = mcurrent_msg.id();
  msg.len = mcurrent_msg.len();
  mcurrent_msg.buf(msg.buf, val);
  CANTx.write(msg);
}
