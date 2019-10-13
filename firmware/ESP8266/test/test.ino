#include "HomeLine.h"
#include "Output.h"
#include "Input.h"

HomeLine* h{nullptr};
Output<int> o1(D1, 81);
Input<int> i1(D0, 82);

String hello() {
    auto ip = WiFi.localIP();
    auto ipString = String(ip[0]) + "." + ip[1] + "." + ip[2] + "." + ip[3];
    return String("HELLO{TYPE{IO},IP{")+ ipString + "}," + i1.hello() + "," + o1.hello() + "}";
}

void setup() {
  Serial.begin(115200);
  h = new HomeLine([&] { return hello(); });
  o1.init();
  i1.init();
}

void loop() {
  i1.loop();
  o1.loop();
  h->loop();
}


