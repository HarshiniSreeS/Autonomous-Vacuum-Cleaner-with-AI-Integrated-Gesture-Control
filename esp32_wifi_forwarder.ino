#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);

#define RXD2 16
#define TXD2 17

void handleCmd() {
  if (!server.hasArg("d")) {
    server.send(400, "text/plain", "Missing command");
    return;
  }

  char cmd = server.arg("d")[0];
  Serial2.write(cmd);

  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("ESP32 IP:");
  Serial.println(WiFi.localIP());

  server.on("/cmd", handleCmd);
  server.begin();
}

void loop() {
  server.handleClient();
}
