#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); //Rx, Tx (HC05 모듈 통신용)
 
void setup() {
    Serial.begin(9600);
    BTSerial.begin(38400);
}
 
void loop() {
    if (BTSerial.available())           // 1. HC05모듈에서 입력되는 신호를
        Serial.write(BTSerial.read());  //    아두이노 시리얼로 전달
    if (Serial.available())             // 2. 아두이노로 입력되는 신호를
        BTSerial.write(Serial.read());  //    HC05모듈로 전달
}
