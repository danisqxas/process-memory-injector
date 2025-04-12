# PayloadInject 🚀

![status](https://img.shields.io/badge/status-active-brightgreen)
![license](https://img.shields.io/github/license/danisqxas/process-memory-injector)
![language](https://img.shields.io/badge/language-C-blue)

Script en C para realizar la inyección de DLLs en procesos Windows usando técnicas directas en memoria.  
Ideal para entornos de laboratorio, pruebas controladas o aprendizaje de conceptos de ciberseguridad ofensiva.

---

## 📚 Tabla de contenidos

- [🛠️ Características](#️-características)
- [📦 Requisitos](#️-requisitos)
- [🧪 Compilación](#️-compilación)
- [⚙️ Ejecución](#️-ejecución)
- [🖼️ Vista previa](#️-vista-previa)
- [📫 Contacto](#️-contacto)
- [⚠️ Disclaimer](#️-disclaimer)

---

## 🛠️ Características

- Inyección de DLL sin escribir en disco.
- Uso de APIs nativas de Windows.
- Código modular y comentado.
- Funcional para laboratorios o pruebas locales.

---

## 📦 Requisitos

- Windows 10 o superior.
- MinGW o Visual Studio para compilar.
- Una DLL propia o modificada para pruebas.

---

## 🧪 Compilación

Compilá el script con MinGW:

```bash
x86_64-w64-mingw32-gcc PayloadInject.c -o injector.exe

