# 🧠 Process Memory Injector

**Process Memory Injector** es una herramienta avanzada de ciberseguridad ofensiva que permite la inyección de código en la memoria de procesos activos. Su propósito principal es educativo y de investigación, enfocándose en el análisis del comportamiento de procesos, técnicas de evasión y ejecución de payloads. Esta utilidad puede ser usada como laboratorio personal, entorno de pruebas o base para futuros desarrollos.

> “Aquel que domina la memoria, controla la ejecución.”

---

## 🌟 Objetivos del Proyecto

Este proyecto fue creado con la intención de:

- Explorar el funcionamiento interno de los procesos y su gestión de memoria.
- Desarrollar un entorno controlado para probar técnicas de inyección.
- Servir como referencia técnica para estudiantes de seguridad ofensiva.
- Fomentar la curiosidad y la investigación autodidacta en bajo nivel.

---

## 🚀 Características Principales

- **Inyección remota de shellcode** en procesos activos.
- **Payloads personalizables** en formato binario.
- **Uso de llamadas nativas (WinAPI)** para mejor comprensión del sistema operativo.
- **Código modular, claro y mantenible**.
- **Listo para compilar sin dependencias externas.**
- **Ejemplos incluidos** para comenzar fácilmente.
- **Posibilidad de integración en otros proyectos mayores.**

---

## 🧠 Conceptos Clave Aplicados

- `OpenProcess`, `VirtualAllocEx`, `WriteProcessMemory`, `CreateRemoteThread`
- Manejo de errores y validación de entradas
- Conversión y manejo de shellcode
- Control y manipulación de procesos a bajo nivel

---

## 📂 Estructura del Repositorio

```
process-memory-injector/
├── src/
│   ├── injector.c           # Código principal del inyector
│   └── utils.h              # Funciones auxiliares (memoria, errores)
├── payloads/
│   └── calc_payload.bin     # Ejemplo básico de shellcode
├── examples/
│   └── how_to_use.md        # Guía rápida de uso
├── docs/
│   ├── process_injection.md # Documentación técnica profunda
│   └── ethics.md            # Uso responsable y advertencias
├── LICENSE
└── README.md
```

---

## ⚙️ Instalación y Compilación

Requiere un compilador C compatible (MinGW, MSVC).

```bash
git clone https://github.com/danisqxas/process-memory-injector.git
cd process-memory-injector
gcc src/injector.c -o injector.exe
```

---

## 🧪 Ejemplo Rápido de Uso

```bash
injector.exe 1234 payloads/calc_payload.bin
```

- `1234`: PID del proceso objetivo (puedes obtenerlo desde el administrador de tareas).
- `payloads/calc_payload.bin`: Payload con código a inyectar.

---

## 📌 Recomendaciones de Seguridad

- Usar en máquinas virtuales o entornos de prueba.
- Ejecutar con permisos administrativos si es necesario.
- Validar el payload antes de inyectar para evitar fallos.

---

## 🕵️ Casos de Uso Didáctico

- Análisis de comportamiento del shellcode.
- Laboratorios de malware (sin riesgos reales).
- Comparación entre técnicas de inyección.
- Estudio de detección por antivirus (AV Evasion).

---

## ⚖️ Advertencia Ética

> **Este software NO debe ser usado en sistemas ajenos o sin autorización.**

Su propósito es únicamente **educativo, experimental y de investigación** en entornos controlados. El uso indebido puede constituir delito informático.

---

## ✨ Futuras Mejoras (Roadmap)

- Añadir soporte para técnicas como `Reflective DLL Injection`, `APC Queueing`, `Thread Hijacking`.
- GUI simple en C# o Python para manejo visual.
- Compatibilidad con Linux (via ptrace).
- Módulos de evasión automatizada.

---

## 👨‍💻 Sobre el Autor

Proyecto creado y mantenido por **danisqxas** — entusiasta del desarrollo en bajo nivel, scripting, seguridad ofensiva y con una fuerte pasión por crear herramientas que enseñen y desafíen.

> “Todo comenzó con curiosidad, y terminó en conocimiento.”

GitHub: [https://github.com/danisqxas](https://github.com/danisqxas)

---

## 📝 Licencia

Este repositorio está bajo la licencia MIT. Eres libre de usarlo, modificarlo o distribuirlo citando al autor original.

---

## ❤️ Agradecimientos

- A la comunidad que comparte sin esperar nada a cambio.
- A los que fallan, insisten, aprenden y mejoran.
- A quienes buscan entender cómo funciona realmente el software por dentro.

**Hacking no es destrucción. Hacking es comprensión.**