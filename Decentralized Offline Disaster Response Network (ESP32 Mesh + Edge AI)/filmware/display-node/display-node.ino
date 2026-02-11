#include "painlessMesh.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define MESH_PREFIX "DISASTER_MESH"
#define MESH_PASSWORD "rescue123"
#define MESH_PORT 5555

painlessMesh mesh;

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received: %s\n", msg.c_str());

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Disaster Network");
  display.println("----------------");
  display.println(msg);
  display.display();
}

void setup() {
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.display();

  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);

  Serial.println("Display node started");
}

void loop() {
  mesh.update();
}
