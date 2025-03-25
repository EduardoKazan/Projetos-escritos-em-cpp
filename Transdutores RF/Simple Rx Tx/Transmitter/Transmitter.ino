#include <VirtualWire.h>

char *controller;
const int buttonPin1 = 2;
int buttonState1 = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPin1, INPUT);

  pinMode(13, OUTPUT);
  vw_set_ptt_inverted(true);  //
  vw_set_tx_pin(12);
  vw_setup(4000);  // speed of data transfer Kbps
  delay(100);
}
void loop() {
  buttonState1 = digitalRead(buttonPin1);
  Serial.println(controller);

  if (buttonState1 == HIGH) {

    controller = "1";
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx();  // Wait until the whole message is gone
    digitalWrite(13, LOW);

  } else {
    controller = "0";
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx();  // Wait until the whole message is gone
    digitalWrite(13, HIGH);
  }
}