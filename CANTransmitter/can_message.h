#ifndef CAN_MESSAGE_H
#define CAN_MESSAGE_H

#include "can_message_def.h"

namespace can_msg {
  /*
   * class will handle writing messages
   */
  class MsgEncode {
  private:
    uint16_t _id;
    uint8_t _len;
  public:
    // constructor sets id and length
    MsgEncode(uint8_t type, uint8_t dev_id, uint8_t msg_id, uint8_t priority, uint8_t len) :
    _id( (uint16_t) ( priority << 9 | msg_id << 6 | dev_id << 3 | type ) ) {
      // calculate real length of can message array
      switch(type) {
        case BOOL: 
          _len = ( (len-1)/8 ) + 1; break;
        case INT8:
        case UINT8: 
          _len = len; break;
        case INT16:
        case UINT16:
          _len = len * 2; break;
        case INT32:
          _len = len * 4; break;
      }
    }  
    // get id
    uint16_t id() { return _id; }
    // get length
    uint8_t len() { return _len; }

    void buf( uint8_t buf[], int32_t n ) {
      memcpy(buf, &n, _len);
    }
  };  

};

#endif
