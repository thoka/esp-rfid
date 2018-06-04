/* support for Seeedstudio 125KHz RFID Module */
 
#include <SoftwareSerial.h>

class RFID125
{
 public:
    RFID125(int receive_at_pin);

    bool available();     
    String getId();
 
 private:
    SoftwareSerial *rc;
    String id;
};
