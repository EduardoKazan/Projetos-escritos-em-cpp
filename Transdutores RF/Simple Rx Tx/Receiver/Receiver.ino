#include <VirtualWire.h>
void setup() {
  vw_set_ptt_inverted(true);  // Required for DR3100
  vw_set_rx_pin(12);
  vw_setup(4000);  // Bits per sec
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  vw_rx_start();  // Start the receiver PLL running
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  Serial.println();


  if (vw_get_message(buf, &buflen))  // Non-blocking

  {
    if (buf[0] == '1') {

      digitalWrite(13, HIGH);

    } else {

      digitalWrite(13, LOW);
    }
  }
}