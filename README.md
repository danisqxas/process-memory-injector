# PayloadInject

Script en C para realizar la inyección de DLLs en procesos Windows usando técnicas directas en memoria.  
Ideal para entornos de laboratorio, pruebas controladas o aprendizaje de conceptos de ciberseguridad ofensiva.

---

## 🛠️ Características

- Inyección de DLL sin tocar disco.
- Uso de APIs nativas de Windows.
- Código comentado y modular.
- Pruebas de concepto para entornos Windows.

---

## 📦 Requisitos

- Windows 10 o superior
- Python 3.x (solo si automatizás pruebas con otros scripts)
- DLL de prueba (creada por vos o personalizada)
- Compilador C (MinGW, Visual Studio, etc.)

---

## ⚙️ Compilación

Usando MinGW desde la terminal:

```bash
gcc PayloadInject.c -o injector.exe

