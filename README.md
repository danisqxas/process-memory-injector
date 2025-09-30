# 🤠 Agente Educativo de Ingeniería de Memoria

Este repositorio contiene un agente en C diseñado para estudiar técnicas avanzadas de programación de sistemas y ciberseguridad de manera ética. Se centra en el procesamiento en memoria e integra múltiples módulos que se ejecutan en sistemas Unix/macOS. Cada función está implementada de forma segura y sus acciones se registran en un fichero de log para análisis.

## Objetivos

- Proporcionar un ejemplo realista de cómo estructurar un agente modular que combine comunicación, ofuscación y monitorización de procesos.
- Facilitar la comprensión de técnicas como el cifrado simple, la codificación, el análisis de procesos y la comunicación en red sin enviar tráfico real.
- Servir como base para investigaciones y prácticas de programación segura.

## Módulos destacados

- 🔐 **Cifrado XOR y codificación Base64:** utilidades para ofuscar y recuperar cadenas.
- ⚙️ **Carga de configuración:** parámetros de dominio DNS, URL de baliza HTTP, dirección y puerto de la shell inversa, clave XOR, intervalo de balizas y ruta de log.
- 🌐 **Túnel DNS:** codifica datos y construye la consulta DNS correspondiente; en lugar de exfiltrar, registra los detalles para su revisión.
- 🛱 **Baliza HTTP:** prepara la estructura de una solicitud POST a un servidor de comando y control y registra la URL y el cuerpo.
- 🕵️ **Detección de privilegios y depuradores:** comprueba permisos efectivos y detecta procesos de depuración leyendo `/proc/self/status`.
- 💻 **Captura de teclado y pantalla:** incluye directrices y estructura para implementar estas funciones de forma segura según el sistema operativo.
- 📋 **Enumeración de procesos:** recorre `/proc` en Linux y utiliza APIs de macOS para listar procesos en ejecución con su línea de comando.
- 💾 **Inyección de payload:** muestra cómo copiar un payload de prueba a memoria y documentar su ubicación sin modificar procesos externos.
- 🔄 **Shell inversa:** explica la estructura de una shell inversa, indicando cómo redirigir entradas y salidas a un servidor remoto sin establecer ninguna conexión.

## 🛠️ Compilación

Para compilar el agente en sistemas Linux o macOS:

```bash
gcc -o agent src/PayloadInject.c -lpthread
```

## ▶️ Uso

Ejecuta el binario indicando el módulo a probar. Por ejemplo:

```bash
./agent dns           # Demostración de túnel DNS
./agent http          # Demostración de baliza HTTP
./agent list          # Enumeración de procesos activos
./agent inject        # Copia de payload en memoria local
```

Consulta el archivo `docs/README.md` para información detallada de cada módulo.

## ⚠️ Advertencia

El código de este repositorio tiene fines exclusivamente educativos. Está prohibido usarlo para comprometer sistemas o redes sin autorización. Usa este proyecto para aprender, investigar y reforzar tus conocimientos sobre programación de bajo nivel y ciberseguridad defensiva.
