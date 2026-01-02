// Pines usados en ESP32
#define LORA_RX 16
#define LORA_TX 17
#define pulso 23
#define led1 2


// Puerto serial para LoRa
HardwareSerial LoRaSerial(2);

// Estructura de datos que se enviará por LoRa
struct DATA {
  int identificador = 0;
};

DATA MyData;

// Variables para controlar cambios de estado
bool pulsoAnterior = LOW;  // Estado previo del botón

void setup() {
  pinMode(pulso, INPUT);
  pinMode(led1, OUTPUT);

  Serial.begin(115200);  // Monitor Serial
  LoRaSerial.begin(9600, SERIAL_8N1, LORA_RX, LORA_TX);  // Comunicación LoRa

  Serial.println("ESP32 and LoRa E32 are Ready!");
  digitalWrite(led1, HIGH);
  delay(1000);
}

void loop() {
  bool pulsoActual = digitalRead(pulso);  // Leer estado actual del botón

  // Detectar cambios en el estado del botón
  if (pulsoActual != pulsoAnterior) {
    if (pulsoActual == HIGH) {
      MyData.identificador = 1;  // Establecer identificador cuando se presiona el botón
    } else {
      MyData.identificador = 0;  // Restablecer identificador cuando se suelta el botón
    }
    enviarDatos(MyData);  // Enviar los datos solo si hubo cambio
    pulsoAnterior = pulsoActual;  // Actualizar el estado previo del botón
  }

  delay(100);  // Esperar un corto tiempo para evitar rebotes
}

// Función para enviar la estructura de datos por LoRa
void enviarDatos(const DATA &data) {
  // Enviar los datos de forma binaria por LoRa
  LoRaSerial.write((uint8_t*)&data, sizeof(data));

  // Mostrar los datos enviados en el monitor serial para depuración
  Serial.println("Datos enviados:");
  Serial.print("Identificador: ");
  Serial.println(data.identificador);
  Serial.println("------------------------");
}

