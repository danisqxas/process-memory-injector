# 🧬 PayloadInject.c - Inyector de Código en C

Payload avanzado en C para realizar **inyección de código en procesos remotos en Windows**. Desarrollado como **PoC técnica** para entornos de análisis, simulaciones ofensivas y ejercicios de pentesting controlado.

---

![status](https://img.shields.io/badge/status-estable-brightgreen)
![lenguaje](https://img.shields.io/badge/lenguaje-C-blue)
![sistema](https://img.shields.io/badge/so-Windows-purple)
![tipo](https://img.shields.io/badge/tipo-Injector-orange)

---

## 🔍 ¿Qué hace este payload?

- Encuentra el **PID de un proceso objetivo**.
- Reserva memoria remota en él con `VirtualAllocEx`.
- Inyecta una DLL o payload con `WriteProcessMemory`.
- Lo ejecuta remotamente con `CreateRemoteThread`.

✅ Todo usando llamadas nativas a la API de Windows y sin dependencias externas.

---

## ⚙️ Requisitos Técnicos

- 🖥️ Windows 7/10/11 (64-bit)
- ⚙️ Compilador GCC compatible con WinAPI (ej: MinGW)
- 🛡️ Privilegios administrativos

---

## 🧪 Compilación

Con `MinGW`:

```bash
x86_64-w64-mingw32-gcc PayloadInject.c -o injector.exe

