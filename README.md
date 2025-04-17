# PayloadInject.c — Payload de Inyección de Código para Simulación de Técnicas Post-Explotación

Este archivo representa un payload técnico escrito en **lenguaje C** cuyo objetivo es **inyectar código dentro de procesos activos** en sistemas Windows. Su enfoque es **educativo y profesional**, diseñado para comprender cómo operan técnicas reales de post-explotación utilizadas por actores avanzados.

---

## Funcionalidades Implementadas

Este payload está pensado para ejecutarse en diferentes modos según el argumento recibido. A continuación, se detallan sus funcionalidades:

### 🔹 Modo `inject_payload`
Inyecta un payload arbitrario (por ejemplo, shellcode) en un proceso específico utilizando:
- `OpenProcess` para obtener acceso al proceso objetivo.
- `VirtualAllocEx` para reservar memoria remota.
- `WriteProcessMemory` para escribir el payload en la memoria del proceso remoto.
- `CreateRemoteThread` para ejecutarlo.

### 🔹 Modo `reverse_shell`
Establece una shell inversa TCP hacia un servidor de escucha. Permite ejecución remota de comandos.

### 🔹 Modo `dns_tunnel`
Implementa un canal encubierto basado en peticiones DNS para exfiltración de datos.

### 🔹 Modo `http_beacon`
Envía información del sistema (hostname, usuario, PID, etc.) a un servidor remoto mediante solicitudes HTTP POST.

### 🔹 Modo `list_processes`
Enumera todos los procesos activos con su nombre, PID y ruta del ejecutable.

### 🔹 Modo `explore_filesystem`
Permite listar archivos y directorios en rutas específicas del sistema, simulando técnicas de reconocimiento post-explotación.

---

## Uso

### Compilación
```bash
x86_64-w64-mingw32-gcc PayloadInject.c -o injector.exe -lcurl
