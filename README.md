# Carga_Celulares
# Proyecto: Sistema de Carga de Celulares  

## Descripción  
El proyecto consiste en el desarrollo de un sistema de carga de celulares en el que los usuarios registrados pueden acceder a compartimentos temporales para cargar sus dispositivos. Se incluyen herramientas para que los administradores gestionen el sistema y obtengan datos relevantes, asegurando aspectos de seguridad.  

El sistema se desarrollará en dos versiones:  
1. **Prototipo simulado**, que incluirá todas las funcionalidades principales.  
2. **Prototipo físico**, que representará una versión inicial para su posible implementación real.  

## Componentes y Funcionamiento  
- **Interfaz de usuario**: Pantalla LCD, matriz de LEDs 8x8, teclado numérico y botones para interactuar con el sistema.  
- **Microcontroladores**: Se usarán dos Arduinos, uno para manejar datos y la interfaz de usuario, y otro para controlar sensores y salidas.  
- **Aplicación móvil**: Permitirá la interacción remota con el sistema y la visualización de datos.  
- **Seguridad**: Se cifrarán los datos almacenados y se implementará autenticación de usuarios.  
- **Sensores**: Se emplearán sensores de temperatura y fotoresistencia para monitorear el estado de los compartimentos.  

## Funciones Principales  
- **Registro e inicio de sesión de usuarios y administradores**.  
- **Gestión de compartimentos**: Los usuarios pueden ingresar y retirar celulares.  
- **Administración del sistema**: Los administradores pueden monitorear el estado del sistema y consultar registros de actividad (logs).  
- **Registro de eventos**: Se guardan intentos de acceso, ingresos y retiros de celulares, entre otros.  
- **Prototipo físico**: Simulación de compartimentos con sensores para verificar la presencia de dispositivos y el cierre de las puertas.  

## Lenguajes de Programación Utilizados  
- **C++ (Arduino)**: Para programar los microcontroladores y controlar sensores, actuadores e interfaz de usuario.  
- **Proteus (Simulación)**: No es un lenguaje, pero se usará para simular el hardware antes de implementarlo físicamente.  

## Tecnologías Utilizadas  
- **Arduino** para el control del hardware.  
- **Proteus** para la simulación del sistema.  
- **Bluetooth** para la comunicación con la aplicación móvil.  
- **EEPROM** para el almacenamiento de datos de usuarios y eventos.  
- **Librerías de Arduino**:  
  - `LiquidCrystal`: Para manejar la pantalla LCD.  
  - `EEPROM`: Para el almacenamiento de datos.  
  - `LedControl`: Para la matriz de LEDs.  

## Conclusión  
El proyecto busca diseñar un sistema funcional y seguro para la gestión de carga de celulares, combinando software y hardware en un entorno simulado y físico.  
