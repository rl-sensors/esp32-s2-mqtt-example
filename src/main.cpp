#include <WiFi.h>
#include <MQTT.h>

const char ssid[] = "smc3";
const char pass[] = "nejaketazkeheslo";
//const char mqt_ip[] = "192.168.15.127";
const char mqt_ip[] = "192.168.86.202";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("arduino", "public", "public")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("hello");
  // client.unsubscribe("hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.print(millis());
  Serial.println(" incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  client.begin(mqt_ip, net);
  client.onMessage(messageReceived);

  connect();
}

char msg[100] = "";

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();

    sprintf(msg, "Hello world %lu", lastMillis);
    client.publish("hello", msg);
  }
}