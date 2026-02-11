#include "painlessMesh.h"
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

#define MESH_PREFIX "DISASTER_MESH"
#define MESH_PASSWORD "rescue123"
#define MESH_PORT 5555

painlessMesh mesh;
DHT dht(DHTPIN, DHTTYPE);

Scheduler userScheduler;

void sendSensorData() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) return;

  String msg = "{";
  msg += "\"node\":\"sensor\",";
  msg += "\"temp\":" + String(temp) + ",";
  msg += "\"humidity\":" + String(hum);
  msg += "}";

  mesh.sendBroadcast(msg);
  Serial.println(msg);
}

Task taskSendData(5000, TASK_FOREVER, &sendSensorData);

void setup() {
  Serial.begin(115200);
  dht.begin();

  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  userScheduler.addTask(taskSendData);
  taskSendData.enable();

  Serial.println("Sensor node started");
}

void loop() {
  mesh.update();
}
