#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <SerialNumber.h>

const char* ssid = "rubikscube29";
const char* password = "rubikscube299";
const char* mqtt_server = "192.168.1.14";

WiFiClient espClient;
PubSubClient client(espClient);

String id = ""; // Corrected declaration
long lastMsg = 0; 


void reconnect();

void setup() {
  delay(100);
  Serial.begin(115200);
  while (!Serial);

  // Get and print the serial number
  id = getSerialNumber();
  Serial.println(id);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, 1883);
}

void loop() {

  if (!client.connected()) {
    reconnect();
    Serial.print(".");
  }

  StaticJsonDocument<80> doc;
  char output[80];

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    float temp = random(1,20);
    float pressure = random(20,40);
    float humidity = random(40,60);
    float gas = random(60,80);
    doc["w"] = temp;
    doc["v"] = pressure;
    doc["c"] = humidity;
    doc["p"] = gas;

    serializeJson(doc, output);
    Serial.println(output);
    client.publish("home/sensors", output);
  }
    
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = id;
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // TODO: add a led status

    } else {
      Serial.print("failed, rc= ");
      Serial.print(client.state());
      delay(5000);
      // TODO: add a led status
    }
  }
}


