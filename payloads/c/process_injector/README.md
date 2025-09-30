# 🧠 Inyector de Código Educativo en C

Este subproyecto ofrece un ejemplo técnico de cómo un inyector de código puede interactuar con la memoria de procesos en sistemas Windows, enfocado exclusivamente con fines educativos y de análisis. Se ha eliminado cualquier carga maliciosa y no se incluyen binarios peligrosos; en su lugar, se detalla la arquitectura y los pasos que seguiría una herramienta legítima de inyección.

## 🎯 Objetivo
Demostrar las técnicas de enumeración de procesos e inyección de un fragmento de código en un proceso remoto de Windows utilizando las API nativas del sistema operativo, con código completamente comentado para facilitar su comprensión.

## 🛠️ Características

- **Enumeración de procesos** mediante funciones como `CreateToolhelp32Snapshot` y `Process32First/Next`.
- **Asignación de memoria remota** en el proceso destino (`VirtualAllocEx`) y escritura del payload en esa memoria (`WriteProcessMemory`).
- **Creación de hilo remoto** (`CreateRemoteThread`) para ejecutar el código en el contexto del proceso inyectado.
- **Cifrado y codificación** opcional del payload con XOR y Base64 para ocultar su contenido en tránsito.
- **Registro detallado** de cada operación en un archivo de log para auditoría y estudio posterior.

## ⚙️ Compilación

1. Asegúrate de tener un entorno de desarrollo en Windows con MinGW o Visual Studio.
2. Clona el repositorio y navega hasta `payloads/c/process_injector`.
3. Compila con:

```bash
gcc -Wall -o injector.exe PayloadInject.c -lws2_32
```

El flag `-lws2_32` enlaza la biblioteca de sockets de Windows si deseas extender la funcionalidad a comunicaciones de red controladas.

## 🚦 Ejecución

> **Advertencia:** Este proyecto no debe ejecutarse en sistemas de producción. Utilízalo en máquinas virtuales o entornos de laboratorio sin datos sensibles.

Al ejecutarlo, proporciona el PID del proceso destino:

```bash
injector.exe <pid_objetivo>
```

El programa solicitará privilegios de administrador para poder abrir el proceso y asignar memoria. Si careces de permisos, la herramienta registrará un error y se detendrá de forma segura.

## 🔒 Ética y Buenas Prácticas

Este código está destinado a aprender sobre ingeniería inversa y técnicas de inyección de manera responsable. Antes de probarlo, lee y respeta las leyes de tu país y las políticas de la organización donde desarrolles pruebas. No utilices este conocimiento para comprometer sistemas sin autorización.

Además, se recomienda:

- Ejecutar las pruebas en entornos aislados.
- Analizar los logs generados para entender cada paso.
- Experimentar modificando el payload para observar cómo cambian las interacciones con el proceso destino.
