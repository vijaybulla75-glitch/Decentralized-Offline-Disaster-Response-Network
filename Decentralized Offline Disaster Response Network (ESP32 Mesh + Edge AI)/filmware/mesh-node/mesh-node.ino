#include "painlessMesh.h"

#define   MESH_PREFIX     "DISASTER_MESH"
#define   MESH_PASSWORD   "rescue123"
#define   MESH_PORT       5555

painlessMesh mesh;

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u: %s\n", from, msg.c_str());
}

void setup() {
  Serial.begin(115200);

  mesh.setDebugMsgTypes(ERROR | STARTUP);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);

  Serial.println("Mesh node started");
}

void loop() {
  mesh.update();
}
