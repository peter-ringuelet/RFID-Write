# Escritura de Datos en Tarjeta RFID con Arduino y MFRC522

Este proyecto permite escribir un bloque de datos en una tarjeta RFID utilizando el módulo MFRC522 y un Arduino. Una vez que los datos son escritos exitosamente, se emite un sonido de notificación a través de un buzzer.

## Componentes Necesarios

- Arduino (por ejemplo, Uno, Nano, Mega)
- Módulo RFID RC522
- Tarjeta RFID o llavero RFID
- Buzzer pasivo
- Cables de conexión
- Protoboard (opcional)

## Diagrama de Conexión

- **VCC** del RC522 -> **3.3V** en Arduino
- **GND** del RC522 -> **GND** en Arduino
- **SDA/SS** del RC522 -> **Pin Digital 10** en Arduino
- **SCK** del RC522 -> **Pin Digital 13** en Arduino
- **MOSI** del RC522 -> **Pin Digital 11** en Arduino
- **MISO** del RC522 -> **Pin Digital 12** en Arduino
- **RST** del RC522 -> **Pin Digital 9** en Arduino
- **Pin Positivo del Buzzer** -> **Pin Digital 8** en Arduino
- **Pin Negativo del Buzzer** -> **GND** en Arduino

## Explicación del Código

Este código permite escribir un conjunto de datos (definido en `dataBlock`) en un bloque específico de una tarjeta RFID. Después de que los datos se escriben en la tarjeta, el Arduino emite un sonido de notificación utilizando un buzzer.

### Variables Clave

- `RST_PIN`: Pin de reset del módulo RFID RC522.
- `SS_PIN`: Pin de selección del esclavo (SDA) para el bus SPI.
- `BUZZER_PIN`: Pin que controla el buzzer pasivo.
- `dataBlock[]`: Array que contiene los datos que se escribirán en la tarjeta RFID.

### Configuración

1. Iniciar la comunicación SPI y el módulo RFID.
2. Configurar el pin del buzzer como salida.

### Bucle Principal

1. Verificar si hay una nueva tarjeta presente.
2. Leer el UID de la tarjeta y mostrarlo en el Monitor Serial.
3. Autenticar y escribir los datos en el bloque especificado de la tarjeta.
4. Emitir un sonido de notificación para indicar que los datos han sido escritos correctamente.
5. Poner la tarjeta en modo de suspensión para ahorrar energía.

## Cómo Usar

1. Conecta los componentes según el diagrama de conexión.
2. Sube el código a tu Arduino.
3. Acerca una tarjeta RFID al lector.
4. Observa el resultado en el Monitor Serial y escucha el sonido del buzzer para verificar que los datos han sido escritos correctamente.

## Ejemplo de Salida

```bash
UID de la tarjeta: 04 1A 7B 2C
Datos escritos correctamente!
```
(Sonido de notificación en el buzzer)

## Notas

- Asegúrate de que el módulo RFID esté correctamente alimentado con 3.3V.
- El buzzer debe estar correctamente conectado al pin especificado para emitir los sonidos.
- Los datos que se escriben en la tarjeta están definidos en el array `dataBlock[]` y pueden ajustarse según tus necesidades.

## Licencia

Este proyecto es de código abierto y está disponible bajo la [Licencia MIT](LICENSE).
