#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Pin de reset para RC522
#define SS_PIN          10         // Pin de Slave Select para RC522
#define BUZZER_PIN      8         // Pin para controlar el buzzer pasivo
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Crear instancia del objeto MFRC522

// Datos a escribir en la tarjeta (16 bytes máximo)
byte dataBlock[] = {
  0x01, 0x02, 0x03, 0x04, 
  0x05, 0x06, 0x07, 0x08, 
  0x09, 0x0A, 0x0B, 0x0C, 
  0x0D, 0x0E, 0x0F, 0x10
};

void setup() {
  Serial.begin(9600);    // Iniciar comunicación serial
  SPI.begin();           // Iniciar SPI bus
  mfrc522.PCD_Init();    // Iniciar RC522
  pinMode(BUZZER_PIN, OUTPUT);  // Configurar el pin del buzzer como salida
  
  Serial.println("Acerca una tarjeta para escribir los datos...");
}

void loop() {
  // Verificar si una nueva tarjeta se ha detectado
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.print("UID de la tarjeta: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();
    
    // Autenticar con una clave en el sector 1
    MFRC522::MIFARE_Key key;
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;  // Clave por defecto: FFFFFFFFFFFF

    // Autenticar en el bloque 4 (un bloque en un sector)
    byte block = 4; // Número del bloque que deseas escribir
    MFRC522::StatusCode status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
      Serial.print("Error al autenticar: ");
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }

    // Escribir datos en el bloque
    status = mfrc522.MIFARE_Write(block, dataBlock, 16);
    if (status != MFRC522::STATUS_OK) {
      Serial.print("Error al escribir: ");
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    Serial.println("Datos escritos correctamente!");

    // Emitir sonido de notificación
    tone(BUZZER_PIN, 1000, 200); // Tono de 1000 Hz durante 200 ms
    delay(250);                  // Pausa de 250 ms
    tone(BUZZER_PIN, 1500, 200); // Tono de 1500 Hz durante 200 ms
    delay(250);                  // Pausa de 250 ms
    tone(BUZZER_PIN, 2000, 200); // Tono de 2000 Hz durante 200 ms
    delay(500);                  // Pausa de 500 ms

    noTone(BUZZER_PIN);          // Detener cualquier tono

    // Poner la tarjeta en modo de suspensión
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }
}
 