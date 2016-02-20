#ifndef CAN_MESSAGE_DEF_H
#define CAN_MESSAGE_DEF_H

/*
 * Message ID format (11 bits)
 *  Bit [2-0] store the message data type
 *  Bit [4-3] device id
 *  Bit [8-5] message id
 *  Bit [10-9] priority level
 *    0 - mission critical
 *    1 - important
 *    2 - information
 *    3 - logging
 */

namespace can_msg {
  /*
   * message type (3bits)
   */
  typedef enum {
    BOOL = 0,
    INT8 = 1,   // -128 to 127
    UINT8 = 2,  // 0 to 256
    INT16 = 3,  // -32768 to 32767
    UINT16 = 4, // 0 to 65535
    INT32 = 5,  // -2147483648 to 2147483647
    UINT32 = 6, // 0 to 4294967295
    INT64 = 7   // -2^63 to 2^63-1
  } format_t;

  /*
   * device ids (2bits)
   */
  typedef enum {
    FUEL_CELL = 0,
    MOTOR = 1,
    AUX = 3
  } device_t;
  
  /*
   * priority (2bits)
   */
  typedef enum {
    CRITICAL = 0,
    IMPORTANT = 1,
    INFORMATION = 2,
    LOGGING = 3
  } priority_t;
  
  /*
   * Fuel cell
   */
  typedef enum {
    FVOLTAGE = 0
  } fuel_cell_t;
  
  /*
   * Motor system
   */
  typedef enum {
    THROTTLE = 0, // len:1
    BRAKE = 1,    // len:1
    MERROR = 3,   // len:2  [motor_error_t]
    MCURRENT = 4, // len:1
    MSPEED = 6    // len:1
  } motor_t;
  typedef enum {
    MERROR_STALL = 0,
    MERROR_OVERCURRENT = 1
  } motor_error_t;
};

#endif
