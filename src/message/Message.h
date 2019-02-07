#include <stdint.h> //library to use uint variable
#include <Arduino.h>


//Class represents radio message

class Message {

  private:
    uint8_t value;

  public:

    //Setters
    void setValue(uint8_t val);

    //Getters
    uint8_t getValue();

};
