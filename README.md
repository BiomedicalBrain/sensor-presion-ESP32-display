# ESP32 Lector de Sensor de Presión - XGZP6847A con Display OLED

Este proyecto utiliza un **ESP32 DevKit V1** para leer los valores de presión de tres sensores **XGZP6847A** analógicos y mostrar las mediciones en un **Display OLED SPI 2.4" 128x64**. El código está diseñado para leer los valores de presión de tres canales ADC del ESP32 y promediarlos para obtener medidas más estables. Además, los resultados se despliegan en una pantalla OLED en tiempo real.



## **Descripción del Proyecto**

Este repositorio contiene el código para:

- Leer los valores de presión de tres sensores **XGZP6847A** utilizando los pines ADC del **ESP32 DevKit V1**.
- Promediar y redondear las lecturas de los sensores para mejorar la estabilidad.
- Convertir las lecturas analógicas a valores de presión (en kPa), cuya ecuación fue obtenida del datasheet proporcionao por [CFSensor](https://cfsensor.com/wp-content/uploads/2022/11/XGZP6847A-Pressure-Sensor-V2.7.pdf).
- Mostrar las mediciones de presión en tiempo real en un **Display OLED SPI 2.4" 128x64**.



## **Componentes Requeridos**

- **ESP32 DevKit V1**  
- **Sensor de presión XGZP6847A** (3 unidades)  
- **Display OLED SPI 2.4" 128x64**  
- **Cables de conexión (jumper wires)**  
- **Fuente de alimentación adecuada para el ESP32, sensores y display** (Sugerencia: Fuente conmutada + Regulador Step Down LM2596)



## **Esquema de Conexión**

![Diagrama del circuito](EsquemaV2.png)



## **Instalación**

1. **Arduino IDE**  
   - Asegúrate de tener instalada la última versión de [Arduino IDE](https://www.arduino.cc/en/software).

2. **Librerías necesarias**  
   Antes de cargar el código, necesitarás instalar las siguientes librerías en Arduino IDE:

   - **Adafruit SSD1306** para el Display OLED:
     - Ve a **Sketch → Incluir Librería → Gestionar Librerías...**
     - Busca **"Adafruit SSD1306"** e instálala.

   - **Adafruit GFX** (dependencia de SSD1306):
     - Instálala de la misma forma que la anterior.

   - **ESP32 Board**:
     - Ve a **Archivo → Preferencias** y en **Gestor de URLs adicionales de tarjetas**, agrega esta URL:  
       `https://dl.espressif.com/dl/package_esp32_index.json`
     - Luego, ve a **Herramientas → Placa → Gestor de placas...**, busca **ESP32** e instálala.



## **Uso**

1. Conecta el ESP32, los sensores XGZP6847A y el Display OLED según el esquema de conexión.
2. Abre la carpeta `SensorPresion_ESP32_DisplayOLED` en Arduino IDE.
3. Selecciona la placa **ESP32 DevKit V1** en **Herramientas → Placa**.
4. Selecciona el puerto correspondiente en **Herramientas → Puerto**.
5. Sube el código al ESP32.

## Notas Importantes

1. **Calibración de los ADC de la ESP32**  
   La presición de los ADC de ESP32 no es óptima, por lo tanto es recomendable su previa calibración. En este proyecto se realizó la calibración utilizando un repositorio de código abierto disponible en GitHub: [esp32-adc-calibrate](https://github.com/e-tinkers/esp32-adc-calibrate/tree/master). Este repositorio proporciona un método para mejorar la precisión de las lecturas de los ADC de la ESP32.

2. **Verificación de la Precisión de las Mediciones**  
   La precisión de las mediciones de presión fue verificada con la ayuda de un manómetro casero basado en el diseño disponible en: [MPS20N0040D Pressure Sensor Calibration with Arduino](https://makersportal.com/blog/2020/6/4/mps20n0040d-pressure-sensor-calibration-with-arduino). Este manómetro permitió comprobar la exactitud de los valores de presión medidos por el sistema.


## Contribución

¡Las contribuciones son bienvenidas! Si deseas contribuir a este proyecto, sigue estos pasos:

1. **Haz un Fork** del repositorio.
2. **Crea una nueva rama** para tu cambio (`git checkout -b feature/nueva-funcionalidad`).
3. **Realiza los cambios** y haz commit con mensajes claros (`git commit -m 'Agrega nueva funcionalidad'`).
4. **Envía un Pull Request** detallando los cambios que realizaste.

Asegúrate de seguir las buenas prácticas de codificación y de probar los cambios antes de enviar tu Pull Request. ¡Gracias por contribuir!



## Licencia

Este proyecto está bajo la licencia [MIT](https://opensource.org/licenses/MIT). Consulta el archivo [LICENSE](LICENSE) para más detalles.

