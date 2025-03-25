/*
      Programa para RX de um controle RF com módulo NRF24L01 - RECEPTOR

      Componentes:
        - Arduino Uno;
        - Módulo NRF24L01 com adaptador;

      Pinos:
      RF      UNO
      CE      9
      CSN     10
      SCK     13
      MISO    12
      MOSI    11

      Versão 1.0 - Versão inicial com leitura multicanais de dados recebidos via rádio - 15/mai/2021; programa base fonte: by Dejan Nedelkovski, www.HowToMechatronics.com
             2.0 - Versão de teste do controle de PS2 - 05/06/21
             
 *    * Criado por Cleber Borges - FunBots - @cleber.funbots  *     *

      Instagram: https://www.instagram.com/cleber.funbots/
      Facebook: https://www.facebook.com/cleber.funbots
      YouTube: https://www.youtube.com/c/funbots
      Telegram: https://t.me/cleberfunbots

*/

#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Servo Servo1;

RF24 radio(9, 10);  // CE, CSN

uint64_t address[6] = { 0x7878787878LL,
                        0xB3B4B5B6F1LL,
                        0xB3B4B5B6CDLL,
                        0xB3B4B5B6A3LL,
                        0xB3B4B5B60FLL,
                        0xB3B4B5B605LL };

struct joystick {
  byte potLX;
  byte potLY;
  byte potRX;
  byte potRY;
  byte buttons1;
  byte buttons2;
};

joystick joystickData;

int button0 = 0;
int button1 = 0;
int button2 = 0;
int servo1pos = 0;

Servo Servo1;

void setup() {
  // Inicia Serial
  Serial.begin(57600);
  Serial.println("Iniciando");

  Servo1.attach(3);

  // Configura e inicializa RF
  if (!radio.begin()) {
    Serial.println(F("radio não responde!!"));
    while (1) {}  // preso em loop
  }

  radio.setPALevel(RF24_PA_LOW);

  for (uint8_t i = 0; i < 6; ++i)
    radio.openReadingPipe(i, address[i]);

  radio.startListening();

  //zeraVariaveis();
}

void loop() {
  // Checa se RF recebeu dados
  if (radio.available()) {
    radio.read(&joystickData, sizeof(joystick));
  }

  // Transfere dados dos botões para variáveis
  // Criar conforme necessidade para cada botão
  button0 = !bitRead(joystickData.buttons1, 0);
  button1 = !bitRead(joystickData.buttons1, 1);
  button2 = !bitRead(joystickData.buttons1, 2);

  // Imprime na Serial dados recebidos
  Serial.print("Pot LX: ");
  Serial.print(joystickData.potLX);
  Serial.print("; Pot LY: ");
  Serial.print(joystickData.potLY);
  Serial.print("; Pot RX: ");
  Serial.print(joystickData.potRX);
  Serial.print("; Pot RY: ");
  Serial.print(joystickData.potRY);

  Serial.print("; Botão 1: ");
  Serial.print(joystickData.buttons1);
  Serial.print("; Botão 2: ");
  Serial.println(joystickData.buttons2);

  servo1pos = map(joystickData.potLX, 0, 255, 0, 180);
  Servo1.write(servo1pos);
  delay(50);
}
