#include <RFID125.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

/*

Pin <-> GPIO assignment
note: note every pin may be used for receive

0   GPIO16	7	GPIO13
1	GPIO5	8	GPIO15
2	GPIO4	9	GPIO3
3	GPIO0	10	GPIO1
4	GPIO2	11	GPIO9
5	GPIO14	12	GPIO10
6	GPIO12		

*/

RFID125::RFID125(int receive_at_pin)
{
    rc = new SoftwareSerial(receive_at_pin,-1,false,128);
    rc->begin(9600); 
}

const int id_len = 8;
const int extra_bytes = 3;
const int msg_len = id_len + extra_bytes;

bool RFID125::available() {

    // throw away until 0x02 found
    while ( rc->available()>0 ) {
        char c = rc->peek();
        if ( c == 0x02 ) break;
        rc->read();
    }

    // try later if not enough bytes are available    
    if (rc->available()<msg_len) return false; 
   
    // skip 0x02
    rc->read(); 
    
    id = "";
    for (int i=0;i<id_len;i++) {
        char c = rc->read();
        id += c;
    }

    // skip checksum and 0x03
    rc->flush();
 
    return true;
}

String RFID125::getId() {
    return id; // todo: reset id ?
}
