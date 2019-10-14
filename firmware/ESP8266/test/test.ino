#include "HomeLine.h"
#include "Output.h"
#include "Input.h"

HomeLine* h{nullptr};
Input<int> i0(D2, 81);
Input<int> i1(D1, 82);

String hello() {
    auto ip = WiFi.localIP();
    auto ipString = String(ip[0]) + "." + ip[1] + "." + ip[2] + "." + ip[3];
    return String("HELLO{TYPE{IO},IP{")+ ipString + "}," + i0.hello() + "," + i1.hello() + "}";
}

void setup() {
  Serial.begin(115200);
  h = new HomeLine([&] { return hello(); });
  i0.init();
  i1.init();
}

void loop() {
  i0.loop();
  i1.loop();
  h->loop();
}
