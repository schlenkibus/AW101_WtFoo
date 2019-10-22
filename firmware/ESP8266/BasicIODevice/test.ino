#include "HomeLine.h"
#include <memory>
#include "Input.h"

HomeLine* h{nullptr};

std::array<Input*, 6> m_inputs{};

String hello() {
    auto ip = WiFi.localIP();
    auto ipString = String(ip[0]) + "." + ip[1] + "." + ip[2] + "." + ip[3];
    return String("HELLO{TYPE{IO},IP{" + ipString + "},INPUTS{0,1,2,3,4,5}}");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin("justus-tower", "aaaaaaaa");
  delay(1000);
  Serial.println("Setting up WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  h = new HomeLine([&] { return hello(); });
  m_inputs[0] = new Input{D1, 0, h};
  m_inputs[1] = new Input{D2, 1, h};
  m_inputs[2] = new Input{D6, 2, h};
  m_inputs[3] = new Input{D4, 3, h};
  m_inputs[4] = new Input{D5, 4, h};
  m_inputs[5] = new Input{A0, 5, h};

  Serial.println("Created Homeline");
}

void loop() {
    h->loop();
    if(h->isConnected()) {
        for(auto& i: m_inputs) {
            i->loop();
        }
    }
}
