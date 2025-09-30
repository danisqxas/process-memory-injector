# 📄 Documentación Técnica del Agente Educativo

Este documento describe la estructura y el funcionamiento interno del agente de ingeniería de memoria incluido en este repositorio. El agente está diseñado con fines académicos y de investigación: combina módulos para cifrado, análisis de procesos, comunicaciones en red y gestión de memoria de manera ética y segura. Cada sección se ha estructurado para que sea comprensible por estudiantes y profesionales que deseen explorar técnicas avanzadas de programación sin exponer sistemas a riesgos innecesarios.

## 📦 Arquitectura del agente

El agente sigue un diseño modular donde cada componente cumple una responsabilidad específica:

- **Capa de configuración**: lee los parámetros desde un archivo JSON o estructura embebida y valida las rutas, dominios y puertos.
- **Utilidades de codificación**: implementa cifrado XOR y codificación Base64 para proteger cadenas y datos sensibles antes de transmitirlos o almacenarlos.
- **Gestor de hilos**: abstrae la creación y el control de hilos para aislar tareas como monitoreo o comunicaciones.

## ⚙️ Configuración y Utilidades

El archivo `config.h` define los parámetros que rigen la ejecución:

- 🧾 **Dominio DNS** y **URL de baliza HTTP**: destinos para las comunicaciones.
- 🔐 **Clave XOR**: semilla para ofuscar datos.
- 🕑 **Intervalo de balizas** y **ruta de registro**: controlan la frecuencia con la que el agente informa su estado y el fichero en el que se guardan los eventos.

Las utilidades de codificación se usan para ofuscar y restaurar datos, manteniendo un equilibrio entre claridad y seguridad.

## 🌐 Comunicación de Red

El agente implementa dos mecanismos de salida de información:

- 🛰️ **Túnel DNS**: construye consultas DNS personalizadas que encapsulan datos. En esta versión educativa solo registra la consulta generada para su análisis y no envía tráfico real.
- 📡 **Baliza HTTP**: prepara una solicitud POST con información del agente y la registraría en un servidor de mando y control. El envío efectivo debe implementarse en un entorno controlado.

Estas funciones demuestran cómo estructurar protocolos encubiertos sin comprometer la seguridad de terceros.

## 🖥️ Módulos de Sistema

El núcleo del agente incluye rutinas para interactuar con el sistema operativo:

- 🧩 **Detección de depuradores**: verifica permisos y comprueba la presencia de herramientas de depuración leyendo `/proc/self/status` o invocando APIs en macOS.
- 👁️ **Captura de pantalla y teclado**: define interfaces que un desarrollador puede implementar según la plataforma para registrar eventos y generar capturas de manera segura.
- 📃 **Enumeración de procesos**: recorre `/proc` en Linux y utiliza APIs en macOS para listar procesos, documentando su PID y la línea de comandos para análisis.
- 📦 **Inyección de payload**: ilustra cómo reservar memoria en un proceso destino y copiar en ella un payload de prueba. En lugar de ejecutarlo, la versión educativa registra los pasos realizados.

## 🧠 Gestión de Memoria y Payloads

Se presenta un ejemplo de cómo preparar un payload benigno, reservar memoria remota, escribir los datos y anotar la dirección resultante. Esta sección es clave para comprender técnicas de inyección sin ejecutar código arbitrario.

## 💻 Conexión Shell y Beaconing

La función de shell inversa documenta cómo redirigir entradas y salidas a un servidor remoto para depuración interactiva. De igual forma, el sistema de **beaconing** gestiona la periodicidad con la que el agente reporta su estado, permitiendo ajustar intervalos y limitar el ancho de banda.

## 📚 Uso y Extensión

Para compilar el agente en entornos Unix/macOS:

```
gcc -pthread -o agente main.c
```

Antes de la compilación, revise los archivos de configuración y asegúrese de que los módulos no realicen conexiones reales en su entorno de pruebas. Puede extender cada componente reemplazando las funciones de demostración por implementaciones controladas (por ejemplo, enviar datos a un servidor local).

## ⚠️ Advertencia y Ética

Este proyecto es estrictamente educativo. No está destinado a desplegarse en sistemas de producción ni a emplearse en actividades no autorizadas. El uso indebido de técnicas de inyección o exfiltración puede violar leyes y acuerdos de servicio. Aplique siempre las buenas prácticas de seguridad y obtenga permisos antes de realizar pruebas.
