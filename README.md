```cpp
/*
  🚨 Decentralized Offline Disaster Response Network
  ESP32 Mesh + Edge AI
  Author: Vijay
  Board: ESP32 Dev Kit
*/

#include <painlessMesh.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050.h>

// ================= CONFIG =================

// true  = Display / Command Node
// false = Sensor Node
#define IS_COMMAND_NODE false

#define MESH_PREFIX     "DisasterMesh"
#define MESH_PASSWORD   "12345678"
#define MESH_PORT       5555

// Pin Definitions (Based on Hardware Document)
#define DHTPIN      4
#define DHTTYPE     DHT11
#define GAS_PIN     34
#define BUZZER_PIN  25
#define LED_PIN     26

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// ==========================================

Scheduler userScheduler;
painlessMesh mesh;

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
MPU6050 mpu;

// ===== Edge AI Classification =====
String classifyDisaster(float temp, int gas, float vibration) {

  if (temp > 50 && gas > 2000)
    return "🔥 FIRE + GAS";

  if (vibration > 2.5)
    return "🌍 EARTHQUAKE";

  if (temp > 50)
    return "🔥 FIRE ALERT";

  if (gas > 2000)
    return "⚠ GAS LEAK";

  return "✅ NORMAL";
}

// ===== Sensor Broadcast Task =====
void sendMessage();

Task taskSendMessage(TASK_SECOND * 5, TASK_FOREVER, &sendMessage);

void sendMessage() {

  float temp = dht.readTemperature();
  int gas = analogRead(GAS_PIN);

  // Read MPU6050
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  float vibration = abs(ax) / 16384.0;  // Simple vibration magnitude

  String status = classifyDisaster(temp, gas, vibration);

  String msg = "Node:" + String(mesh.getNodeId()) +
               " T:" + String(temp) +
               " G:" + String(gas) +
               " V:" + String(vibration) +
               " S:" + status;

  mesh.sendBroadcast(msg);

  Serial.println("Broadcasting:");
  Serial.println(msg);

  // Local alert indicators (Sensor Node only)
  if (status != "✅ NORMAL") {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
}

// ===== Receive Callback =====
void receivedCallback(uint32_t from, String &msg) {

  Serial.println("Received from: " + String(from));
  Serial.println(msg);

  if (IS_COMMAND_NODE) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("DISASTER ALERT");
    display.println("----------------");
    display.println(msg);
    display.display();
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  mesh.setDebugMsgTypes(ERROR | STARTUP);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);

  if (!IS_COMMAND_NODE) {

    dht.begin();
    Wire.begin(21, 22);
    mpu.initialize();

    userScheduler.addTask(taskSendMessage);
    taskSendMessage.enable();
  }

  if (IS_COMMAND_NODE) {

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Command Node Ready");
    display.display();
  }

  Serial.println("System Initialized");
}

void loop() {
  mesh.update();
}


# NOTE = Run and upload code in Arduino UNO to Upload in KIT


}
```
