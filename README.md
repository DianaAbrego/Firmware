# ⚙️ Firmware para el Control del Robot Pololu 3Pi+ con Pinza

Este repositorio contiene el **firmware diseñado para el microcontrolador ESP32-WROOM-32D**, utilizado para integrar el control de velocidad para los motores y mover el servomotor para la pinza.

---

## 📄 Archivos Principales

- [**`src/main.cpp`**](./src/main.cpp)  
  Este archivo contiene el **firmware principal** que permite al Pololu 3Pi+ **controlar simultáneamente las velocidades de las ruedas y la pinza**.  
  Es el código que debe cargarse al **ESP32** para ejecutar ambas funciones de forma integrada.

- [**`mainConexionPololu.txt`**](./mainConexionPololu.txt)   
  Contiene una **versión simplificada del código**, utilizada únicamente para **controlar las velocidades del robot**, sin incluir el control de la pinza.  
  Este archivo puede emplearse para pruebas o validaciones iniciales de comunicación entre el ESP32 y el Pololu 3Pi+.

---
## 🧰 Entorno de Programación

El firmware fue desarrollado utilizando el entorno **Visual Studio Code**, mediante la extensión **PlatformIO**.  
Este entorno facilita la gestión de librerías, la compilación del código y la carga del programa al microcontrolador **ESP32-WROOM-32D**.  
Se recomienda mantener la misma configuración de entorno para asegurar la compatibilidad del proyecto.


Además, se incluye un archivo **ZIP compacto** con todo el proyecto completo.  
Para utilizarlo, basta con **descomprimir el archivo** y **abrir la carpeta como un nuevo proyecto en Visual Studio Code**.  
Dentro de la estructura del proyecto, el archivo principal (`main.cpp`) se encuentra en la carpeta `/src`.

## ⚠️ Consideraciones Importantes

- Antes de cargar cualquiera de los programas al **ESP32**, asegúrese de que el **robot Pololu 3Pi+ esté completamente apagado**.  
- En caso contrario, **no conecte el ESP32 directamente al Pololu** durante la carga del firmware.  
- Una vez finalizada la programación, puede reconectar el ESP32 al Pololu para ejecutar el control integrado.

---

## 🧠 Desarrollado por

**Diana Lucía Abrego Barrera**  
Facultad de Ingeniería Mecatrónica – *Universidad del Valle de Guatemala*
