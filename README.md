# 🧠 Aerthex Scripts

Repositorio de herramientas y scripts de propósito ofensivo y analítico desarrollados por **Aerthex**. Enfocado en **ciberseguridad**, **automatización** y **pruebas de concepto técnicas**.

---

<div align="center">

<img src="https://img.shields.io/badge/status-active-brightgreen" />
<img src="https://img.shields.io/badge/license-MIT-blue" />
<img src="https://img.shields.io/badge/platform-multiplatform-purple" />
<img src="https://img.shields.io/badge/focus-cybersecurity-red" />

</div>

---

## 📁 Estructura del repositorio

\`\`\`
aerthex-scripts/
├── payloads/           # Inyección de código y exploits
│   └── PayloadInject.c
├── scanners/           # Reconocimiento y análisis de red
│   ├── scan_hosts.py
│   └── LeakScan-Script.py
├── helpers/            # Scripts complementarios
│   └── User_Activity_V1.1.py
└── screenshots/        # Evidencias visuales y ejemplos de uso
\`\`\`

---

## ⚙️ Requisitos generales

- Python 3.x (para scripts en `.py`)
- GCC (MinGW para Windows) para compilar C
- Librerías Python: `requests`, `beautifulsoup4`

\`\`\`bash
pip install -r requirements.txt
\`\`\`

---

## 🚀 Uso por script

### 🔹 PayloadInject.c  
> Inyección de DLL en procesos activos de Windows  
📌 Lenguaje: C

**Compilación:**
\`\`\`bash
x86_64-w64-mingw32-gcc PayloadInject.c -o injector.exe
\`\`\`

**Ejecución:**
\`\`\`bash
injector.exe <PID> C:\\ruta\\a\\la\\dll.dll
\`\`\`

---

### 🔹 scan_hosts.py  
> Escáner de red para detección de hosts activos

\`\`\`bash
python3 scan_hosts.py --target 192.168.1.0/24
\`\`\`

---

### 🔹 LeakScan-Script.py  
> Verifica si un correo aparece en bases de datos filtradas

\`\`\`bash
python3 LeakScan-Script.py -e correo@ejemplo.com
\`\`\`

---

### 🔹 User_Activity_V1.1.py  
> Analiza actividad reciente del sistema

\`\`\`bash
python3 User_Activity_V1.1.py
\`\`\`

---

## 🖼️ Captura de ejemplo

<p align="center">
  <img src="screenshots/demo.png" alt="demo" width="700"/>
</p>

---

## 📜 Licencia

Este proyecto está licenciado bajo la [MIT License](LICENSE).

---

## 📬 Contacto

- GitHub: [@danisqxas](https://github.com/danisqxas)
- Twitter/X: [@daniiwnet](https://x.com/daniiwnet?s=21)

---

<div align="center">
  <strong>💻 Desarrollado con pasión por Aerthex</strong>
</div>
