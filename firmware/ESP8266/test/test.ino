#include "HomeLine.h"

HomeLine* h;

const char* hello() {
    return "HELLO{}"
}

void setup() {
  Serial.begin(115200);
  h = new HomeLine();
  Serial.println(h != nullptr);
  h->sendMessage<const char*>(hello());
  h->sendMessage<const char*>("IN 0");
  h->sendMessage<const char*>("OUT 1");

  pinMode(D0, INPUT);
  pinMode(D1, OUTPUT);
}

int lastSend = LOW;

void loop() {
  auto val = digitalRead(D0);
  if(val != lastSend) {
    lastSend = val;
    h->sendMessage<String>(String("0: ") + val);
  }

  h->loop();
}
