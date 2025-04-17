# 🧬 Process Memory Injector — Inyector de Código en C para Windows

Este repositorio contiene una prueba de concepto (PoC) escrita en lenguaje C para realizar técnicas avanzadas de inyección de código en procesos activos de sistemas Windows. Diseñado para profesionales en ciberseguridad ofensiva, auditorías técnicas y entornos de laboratorio controlado, esta herramienta simula tácticas reales de post-explotación utilizadas en campañas avanzadas.

![estado](https://img.shields.io/badge/estado-estable-brightgreen)
![lenguaje](https://img.shields.io/badge/lenguaje-C-blue)
![sistema](https://img.shields.io/badge/so-Windows-purple)
![licencia](https://img.shields.io/badge/licencia-MIT-blue)

---

## 📁 Estructura del Repositorio

```bash
process-memory-injector/
├── payloads/
│   └── c/
│       └── process_injector/
│           ├── PayloadInject.c         # Payload principal en C
│           └── README.md               # Documentación técnica del payload
├── .gitignore
└── README.md
```

---

## ⚙️ Requisitos Técnicos

- Sistema Operativo: **Windows** (compilable desde Linux con MinGW)
- Compilador C: `x86_64-w64-mingw32-gcc`
- Librería: `libcurl`
- Privilegios: Se requiere ejecución como **Administrador** para algunas operaciones

---

## 🧠 Funcionalidades del Payload

Este payload se ejecuta con distintos modos (argumentos) para simular múltiples técnicas:

- `inject_payload <pid>`: Inyección en procesos
- `reverse_shell`: Shell inversa TCP
- `dns_tunnel`: Exfiltración por DNS
- `http_beacon`: Beacon HTTP con info del sistema
- `list_processes`: Enumeración de procesos activos
- `explore_filesystem <path>`: Reconocimiento del sistema de archivos
- `beacon`: Beaconing en segundo plano

---

## 🛠️ Compilación

```bash
x86_64-w64-mingw32-gcc payloads/c/process_injector/PayloadInject.c -o injector.exe -lcurl
```

---

## 🚀 Ejecución

```bash
injector.exe <modo> [argumento]
```

### 🔸 Ejemplos

```bash
injector.exe inject_payload 1234
injector.exe reverse_shell
injector.exe dns_tunnel
injector.exe http_beacon
injector.exe list_processes
injector.exe explore_filesystem C:\Users
injector.exe beacon
```

---

## 🔍 ¿Por qué este proyecto es diferente?

- 🧠 Código comentado y preparado para análisis técnico.
- 🛠️ Enfoque modular para facilitar su extensión y reutilización.
- 🧪 Simula técnicas reales en entornos de laboratorio ofensivo.
- 🧰 Ideal para prácticas, desafíos técnicos, entrevistas o CTFs internos.

---

## ⚠️ Consideraciones Éticas

Este repositorio tiene un propósito **exclusivamente educativo y de simulación**.

- No está autorizado para entornos reales sin consentimiento explícito.
- El autor no se responsabiliza por usos indebidos.
- Usalo con responsabilidad, ética y criterio técnico.

---

## 📜 Licencia

Este proyecto está licenciado bajo la [MIT License](LICENSE).

---

## 👤 Autor

**Desarrollado por [@danisqxas](https://github.com/danisqxas)** — apasionado de la ciberseguridad ofensiva y el desarrollo técnico enfocado a PoCs y herramientas personalizadas.

Podés seguir avances y publicaciones en:

- GitHub: [@danisqxas](https://github.com/danisqxas)
- Twitter/X: [@daniiwnet](https://x.com/daniiwnet?s=21)

---

<div align="center">
  <strong>💉 Desarrollado con precisión quirúrgica y ética profesional.</strong><br>
  <em>“Simulá al atacante para fortalecer la defensa.”</em>
</div>
