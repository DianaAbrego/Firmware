#include <Arduino.h>
#include <WiFi.h>
#include <driver/ledc.h>

// ---------- Configuración WiFi ----------
const char* ssid = "Robotat";
const char* password = "iemtbmcit116";
//const char* ssid = "Nexxt_AF9F54";
//const char* password =  "Cocina_Zona6";
WiFiServer wifiServer(9090);

// ---------- PWM Servo ----------
#define SERVO_PIN      23
#define PWM_CHANNEL    0
#define PWM_FREQ       50
#define PWM_RES        12
#define SERVO_ABIERTO  307  // PWM para abrir
#define SERVO_CERRADO  366  // PWM para cerrar 80


void initPWM() {
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES);
  ledcAttachPin(SERVO_PIN, PWM_CHANNEL);
  ledcWrite(PWM_CHANNEL, SERVO_ABIERTO); // Estado inicial abierto
}

// ---------- Estados del sistema ----------
bool modoGripper = false;
bool modoMotores = false;
uint8_t cborBuffer[11];
uint8_t cborIndex = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  initPWM();

  WiFi.begin(ssid, password);
  Serial.println("Servidor TCP iniciado");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  wifiServer.begin();
}

void loop() {
  WiFiClient client = wifiServer.available();

  if (client) {
    while (client.connected()) {
      while (client.available() > 0) {
        uint8_t c = client.read();
        Serial.print("Recibido byte: ");
        Serial.println(c);

        // ----- Modo Motores (lectura CBOR de 11 bytes) -----
        if (modoMotores) {
          Serial.println("Caracter recibido");
          Serial.println(c);
          cborBuffer[cborIndex++] = c;


          if (cborIndex == 11) {
            // Ya tenemos el mensaje completo
            Serial.println("Mensaje CBOR completo recibido. Enviando a Serial2...");
            Serial2.write(cborBuffer, 11);
            
            cborIndex = 0;
            modoMotores = false;
          }
          continue; // No seguir procesando este byte
        }

        // ----- Modo Gripper (espera segundo byte) -----
        if (modoGripper) {
          if (c == 10) {
            ledcWrite(PWM_CHANNEL, SERVO_ABIERTO);
            Serial.println("Gripper ABIERTO");
          } else if (c == 20) {
            ledcWrite(PWM_CHANNEL, SERVO_CERRADO);
            Serial.println("Gripper CERRADO");
          } else {
            Serial.print("Comando de gripper no reconocido: ");
            Serial.println(c);
          }
          modoGripper = false;
          continue;
        }

        // ----- Identificación de Modo inicial -----
        if (c == 50) {
          modoGripper = true;
          Serial.println("Modo GRIPPER activado. Esperando comando...");
        } else if (c == 130) {
          modoMotores = true;
          cborIndex = 0;
          cborBuffer[cborIndex++] = c; // Guardar el 130 como primer byte
          Serial.println("Modo MOTORES activado. Recibiendo CBOR...");
        } else {
          Serial.print("Byte no reconocido fuera de modo: ");
          Serial.println(c);
        }
      }
      delay(10);
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}
