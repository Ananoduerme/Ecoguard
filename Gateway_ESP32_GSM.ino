// Pin used in ESP32 for LoRa
#define LORA_RX 15
#define LORA_TX 2

// Configuración del puerto serial para LoRa
HardwareSerial LoRaSerial(2);

// Estructura de datos que esperamos recibir
struct DATA {
  int identificador;
  //float longitud;
  //float latitud;
};

DATA MyData;  // Variable para almacenar los datos recibidos

void setup() {
  // Inicialización de comunicaciones seriales
  Serial.begin(115200);  // Monitor Serial
  LoRaSerial.begin(9600, SERIAL_8N1, LORA_RX, LORA_TX);  // LoRa Serial
  Serial.println("ESP32 LoRa Receiver is Ready!");
}

void loop() {
  // Verificar si hay datos disponibles desde LoRa
  if (LoRaSerial.available() >= sizeof(MyData)) {
    // Leer los datos binarios recibidos en la estructura `MyData`
    LoRaSerial.readBytes((char*)&MyData, sizeof(MyData));
    // Mostrar los datos recibidos en el monitor serial
    mostrarDatos(MyData);
  }
  delay(500);  // Espera de 500 ms entre verificaciones
}

// Función para mostrar los datos recibidos en el monitor serial
void mostrarDatos(const DATA &data) {
  Serial.println("Datos recibidos:");
  Serial.print("Identificador: ");
  Serial.println(data.identificador);
  /*Serial.print("Longitud: ");
  Serial.println(data.longitud);
  Serial.print("Latitud: ");
  Serial.println(data.latitud);*/
  Serial.println("------------------------");
}
