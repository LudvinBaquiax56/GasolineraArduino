#include <ArduinoJson.h>

// Tamaño del buffer de entrada para el JSON (ajústalo según tu necesidad)
#define JSON_BUFFER_SIZE 128

// Pin del LED
const int ledPin = 13;
String inputString = "";

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    //{"Codigo":"0","LitrosDisponibles":30}
    // Si se recibe un carácter de nueva línea, se procesa el mensaje completo
    if (inChar == '\n') {
      procesarMensaje(inputString);
      Serial.println(inputString);
      inputString = "";
    }
  }
}

void procesarMensaje(String mensaje) {
  // Aquí puedes analizar el mensaje JSON recibido y realizar las acciones correspondientes
  Serial.println("Mensaje recibido: " + mensaje);
  
  const char* json = mensaje.c_str();

  // Crear un buffer para almacenar el JSON
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;

  // Deserializar el JSON
  DeserializationError error = deserializeJson(doc, json);

  // Verificar si hubo errores durante la deserialización
  if (error) {
    Serial.print(F("Error durante la deserialización: "));
    Serial.println(error.c_str());
    return;
  }

  // Leer el valor deserializado de "Codigo"
  const char* codigo = doc["Codigo"];

  // Si el valor de "Codigo" es igual a "1", encender el LED
  if (strcmp(codigo, "1") == 0) {
    digitalWrite(ledPin, HIGH); // Encender el LED
    Serial.println("LED encendido");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("No se enciende el LED");
  }
  
}
