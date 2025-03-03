// Código realizado para utilizar sensores de presión XGZP6847A 
// con el microcontrolador ESP32 y un display OLED

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// #include "LUT.h" ; Incluir sólo si se requiere mayor precisión en las mediciones

// Definir pines SPI para el OLED
#define OLED_MOSI 23  // Pin SDA
#define OLED_CLK 18   // Pin SCLk
#define OLED_DC 19    // Pin DC
#define OLED_CS 5     // Pin CS
#define OLED_RESET 4  // Pin RST

// Crear objeto de pantalla OLED
Adafruit_SSD1306 display(128, 64, &SPI, OLED_DC, OLED_RESET, OLED_CS);

#define ADC1 39
#define ADC2 36
#define ADC3 34

float valorVolts1 = 0.0;
float presion1 = 0.0;

float valorVolts2 = 0.0;
float presion2 = 0.0;

float valorVolts3 = 0.0;
float presion3 = 0.0;

float num_muestras = 50.0; // Número de muestras a promediar para que el sistema sea más estable

float redondeadoA3(float value) {
    return round(value * 1000) / 1000.0;
}

void setup() {
  // Inicializar puerto serial y ajustar canales ADC
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  // Inicializar pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("No se pudo inicializar el OLED"));
    for (;;);
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  // Obtener valores para promediar
  float promedio1 = 0.0;
  float valorVolts1_redondeo = 0.0;
  
  float promedio2 = 0.0;
  float valorVolts2_redondeo = 0.0;

  float promedio3 = 0.0;
  float valorVolts3_redondeo = 0.0;

  for (int ii = 0; ii < num_muestras; ii++) {
    promedio1 += (analogRead(ADC1));
    promedio2 += (analogRead(ADC2));
    promedio3 += (analogRead(ADC3));

    /* 
    En caso de utilizar el archivo LUT.h de calibración se modifica esta sección a:

    int rawReading = analogRead(ADC1);
    int calibratedReading = (int)ADC_LUT[rawReading];
    promedio1 += calibratedReading;
    int rawReading2 = analogRead(ADC2);
    int calibratedReading2 = (int)ADC_LUT[rawReading2];
    promedio2 += calibratedReading2;
    int rawReading3 = analogRead(ADC3);
    int calibratedReading3 = (int)ADC_LUT[rawReading3];
    promedio3 += calibratedReading3;
    delay(50); 
    */
  }

  promedio1 /= num_muestras;
  promedio2 /= num_muestras;
  promedio3 /= num_muestras;
  
  promedio1 = promedio1 > 4095 ? 4095 : promedio1;
  promedio2 = promedio2 > 4095 ? 4095 : promedio2;
  promedio3 = promedio3 > 4095 ? 4095 : promedio3;

  // Convertir a valores de presión
  valorVolts1 = 3.9 * promedio1 / (pow(2.0, 12.0) - 1.0); // Esta ecuación 
  // depende de la resolución de los ADC y de la precisión de medición de cada ESP32.
  valorVolts1_redondeo = redondeadoA3(valorVolts1);
  presion1 = (valorVolts1_redondeo - 0.5) / 0.04; // Esta ecuación depende del rango de 
  // medición de cada sensor de presión, lea el README para más información.

  valorVolts2 = 3.9 * promedio2 / (pow(2.0, 12.0) - 1.0);
  valorVolts2_redondeo = redondeadoA3(valorVolts2);
  presion2 = (valorVolts2_redondeo - 0.5) / 0.04;

  valorVolts3 = 3.9 * promedio3 / (pow(2.0, 12.0) - 1.0);
  valorVolts3_redondeo = redondeadoA3(valorVolts3);
  presion3 = (valorVolts3_redondeo - 0.5) / 0.04;

  // Imprimir valores en el monitor serial
  Serial.print("Sensor 1 = ");
  Serial.print(promedio1);
  Serial.print(" Dec , ");
  Serial.print(valorVolts1_redondeo, 3);
  Serial.print(" V , ");
  Serial.print(presion1, 3);
  Serial.println(" kPa");
  
  Serial.print("Sensor 2 = ");
  Serial.print(promedio2);
  Serial.print(" Dec , ");
  Serial.print(valorVolts2_redondeo, 3);
  Serial.print(" V , ");
  Serial.print(presion2, 3);
  Serial.println(" kPa");

  Serial.print("Sensor 3 = ");
  Serial.print(promedio3);
  Serial.print(" Dec , ");
  Serial.print(valorVolts3_redondeo, 3);
  Serial.print(" V , ");
  Serial.print(presion3, 3);
  Serial.println(" kPa");

  // Mostrar valores en el OLED
  display.clearDisplay();
  display.setTextSize(1); // Valor ajustable 
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0); // Valor ajustable 
  display.print("Presiones:");

  display.setCursor(0, 10); // Valor ajustable 
  display.print("Sensor 1: ");
  display.print(presion1, 3);
  display.print(" kPa");

  display.setCursor(0, 20); // Valor ajustable 
  display.print("Sensor 2: ");
  display.print(presion2, 3);
  display.print(" kPa");

  display.setCursor(0, 30); // Valor ajustable 
  display.print("Sensor 3: ");
  display.print(presion3, 3);
  display.print(" kPa");

  display.display();

  delay(1000); // Actualizar cada segundo
}
