# 🧠 Process Memory Injector

**Toolkit multiplataforma para inyección de payloads en memoria en sistemas Unix/macOS.**  
Este proyecto tiene fines educativos y de investigación en ciberseguridad, permitiendo explorar técnicas de post-explotación y evasión de defensas en entornos controlados.

---

## 🚀 Características

- **Inyección de shellcode** en procesos activos mediante técnicas como `ptrace` y manipulación de memoria.
- **Compatibilidad multiplataforma**: diseñado para sistemas Unix y macOS.
- **Modularidad**: estructura de carpetas organizada para facilitar la comprensión y extensión del código.
- **Ejemplos prácticos**: incluye payloads y scripts de ejemplo para pruebas y demostraciones.

---

## 📁 Estructura del Proyecto

```
process-memory-injector/
├── docs/           # Documentación y recursos adicionales
├── examples/       # Ejemplos de uso y payloads de prueba
├── payloads/       # Payloads listos para inyección
├── src/            # Código fuente principal del injector
└── README.md       # Este archivo
```

---

## ⚙️ Requisitos

- **Sistema operativo**: Unix o macOS
- **Compilador C**: gcc o clang
- **Permisos**: privilegios adecuados para interactuar con procesos (puede requerir `sudo`)

---

## 🛠️ Compilación y Uso

### Compilación

```bash
gcc -o injector src/injector.c
```

### Uso

```bash
sudo ./injector <PID> <ruta_al_payload>
```

- `<PID>`: ID del proceso objetivo.
- `<ruta_al_payload>`: ruta al archivo binario del payload a inyectar.

---

## ⚠️ Advertencia

Este proyecto es exclusivamente para fines educativos y de investigación en entornos controlados. El uso indebido de estas técnicas puede ser ilegal y está fuera del alcance y responsabilidad de este proyecto.

---

## 📄 Licencia

Este proyecto está licenciado bajo la [MIT License](LICENSE).