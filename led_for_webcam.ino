#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Configuración WiFi
const char* ssid = "WIFI-SSID";
const char* password = "WIFI-PWD";
const char* hostname = "linterna";  // Cambiado a const char* para consistencia

// Definición de pines
const int LED_PIN = 2;      // GPIO2 en ESP-01S
const int SWITCH_PIN = 0;   // GPIO0 en ESP-01S

// Variables globales
bool ledState = false;
bool blinkMode = false;
int blinkFrequency = 1; // Hz
unsigned long lastBlinkTime = 0;

ESP8266WebServer server(80);

// Variable para controlar el tiempo de envío de IP
unsigned long lastIPPrintTime = 0;
const unsigned long IP_PRINT_INTERVAL = 10000; // 10 segundos en milisegundos

void setup() {
  // Iniciar Serial
  Serial.begin(115200);
  Serial.println("Iniciando ESP-01S...");
  
  // Configuración de pines
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);
  
  // Configuración WiFi y hostname
  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname);

  // Iniciar conexión WiFi
  WiFi.begin(ssid, password);
  
  // Esperar conexión
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Inicializar mDNS
  if (MDNS.begin(hostname)) {
    Serial.println("mDNS iniciado");
    Serial.print("Ahora puedes acceder usando http://");
    Serial.print(hostname);
    Serial.println(".local");
    
    // Anunciar el servicio HTTP
    MDNS.addService("http", "tcp", 80);
  } else {
    Serial.println("Error iniciando mDNS!");
  }
  
  // Configurar rutas del servidor web
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/blink", handleBlink);
  server.on("/frequency", handleFrequency);
  
  // Iniciar servidor
  server.begin();
}

void loop() {
  MDNS.update();  // Actualizar mDNS
  server.handleClient();
  
  // Enviar IP cada 10 segundos
  unsigned long currentMillis = millis();
  if (currentMillis - lastIPPrintTime >= IP_PRINT_INTERVAL) {
    Serial.print("Dirección IP del dispositivo: ");
    Serial.println(WiFi.localIP());
    lastIPPrintTime = currentMillis;
  }
  
  // Manejar interruptor físico
  if (digitalRead(SWITCH_PIN) == LOW) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    delay(200); // Debounce
  }
  
  // Manejar modo parpadeo
  if (blinkMode) {
    unsigned long currentTime = millis();
    if (currentTime - lastBlinkTime >= (1000 / (blinkFrequency * 2))) {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
      lastBlinkTime = currentTime;
    }
  }
}

// Página web principal
void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Control LED ESP-01S</h1>";
  html += "<p><button onclick='toggle()'>Toggle LED</button></p>";
  html += "<p><button onclick='toggleBlink()'>Toggle Blink</button></p>";
  html += "<p>Frecuencia (Hz): <input type='number' id='freq' value='1'>";
  html += "<button onclick='setFreq()'>Set</button></p>";
  html += "<script>";
  html += "function toggle(){fetch('/toggle');}";
  html += "function toggleBlink(){fetch('/blink');}";
  html += "function setFreq(){";
  html += "var f=document.getElementById('freq').value;";
  html += "fetch('/frequency?hz='+f);}";
  html += "</script></body></html>";
  server.send(200, "text/html", html);
}

void handleToggle() {
  if (!blinkMode) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
  server.send(200, "text/plain", "OK");
}

void handleBlink() {
  blinkMode = !blinkMode;
  server.send(200, "text/plain", "OK");
}

void handleFrequency() {
  if (server.hasArg("hz")) {
    blinkFrequency = server.arg("hz").toInt();
  }
  server.send(200, "text/plain", "OK");
}