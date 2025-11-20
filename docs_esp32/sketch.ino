#include <WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// --- Configurações de Rede e MQTT ---
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "44.223.43.74"; 
const int mqtt_port = 1883;
const char* mqtt_topic = "homeoffice/mesa01"; 

WiFiClient espClient;
PubSubClient client(espClient);

// --- Hardware ---
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define PIR_PIN 26
#define DHTPIN 27
#define DHTTYPE DHT22
#define LDR_PIN 34     
#define BUZZER_PIN 18   

DHT dht(DHTPIN, DHTTYPE);

// --- Variáveis de Controle ---
unsigned long lastMotionTime = 0;
const unsigned long TIMEOUT_NO_MOTION = 10000; 
bool salaOcupada = false;
bool alertaTemp = false;

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect_mqtt() {
  while (!client.connected()) {
    if (client.connect("EcoWork_Buzzer_Client")) {
    } else {
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT); 

  dht.begin();
  lcd.init();
  lcd.backlight();
  
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) reconnect_mqtt();
  client.loop();

  // --- 1. Leitura de Sensores ---
  int movimento = digitalRead(PIR_PIN);
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int ldrValue = analogRead(LDR_PIN); 
  int luzAmbientePct = map(ldrValue, 0, 4095, 0, 100); 

  // --- 2. Lógica de Presença ---
  if (movimento == HIGH) {
    lastMotionTime = millis();
    salaOcupada = true;
  }

  if (salaOcupada && (millis() - lastMotionTime > TIMEOUT_NO_MOTION)) {
    salaOcupada = false;
  }

  // --- 3. Lógica de Alerta (Buzzer) ---
  if (salaOcupada) {
    // Se ocupado e quente (>32C), toca alarme
    if (temp > 32.0) {
      alertaTemp = true;
      // Toca o buzzer (Frequência 1000Hz)
      tone(BUZZER_PIN, 1000);
    } else {
      alertaTemp = false;
      noTone(BUZZER_PIN); 
    }
  } else {
    // Sala vazia, desliga tudo
    salaOcupada = false;
    alertaTemp = false;
    noTone(BUZZER_PIN);
  }

  // --- 4. LCD ---
  lcd.setCursor(0, 0);
  if(salaOcupada) lcd.print("OCUPADA ");
  else lcd.print("LIVRE (ECO)");

  lcd.setCursor(10, 0);
  lcd.print("T:");
  lcd.print((int)temp);
  lcd.print("C");

  lcd.setCursor(0, 1);
  if(alertaTemp) {
    lcd.print("ALERTA CALOR!   ");
  } else {
    lcd.print("Luz Nat: ");
    lcd.print(luzAmbientePct);
    lcd.print("%   ");
  }
  
  // --- 5. MQTT ---
  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > 2000) {
    lastMsg = millis();
    char jsonPayload[256];
    snprintf(jsonPayload, sizeof(jsonPayload),
        "{\"sala\":\"Sala01\",\"status\":\"%s\",\"temp\":%.1f,\"hum\":%.1f,\"luz_nat\":%d,\"alerta\":%d}",
        salaOcupada ? "Ocupada" : "Livre", temp, hum, luzAmbientePct, alertaTemp
    );
    client.publish(mqtt_topic, jsonPayload);
  }
}