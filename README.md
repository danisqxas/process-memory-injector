## PayloadInject 🚀


Script en C para realizar la inyección de DLLs en procesos Windows usando técnicas directas en memoria.  
Ideal para entornos de laboratorio, pruebas controladas o aprendizaje de conceptos de ciberseguridad ofensiva.

---
## 📚 Tabla de contenidos

- ✨ [Características](#características)
- 📦 [Requisitos](#requisitos)
- 🛠️ [Compilación](#compilación)
- ⚙️ [Ejecución](#ejecución)
- 🖼️ [Vista previa](#vista-previa)
- 📫 [Contacto](#contacto)
- ⚠️ [Disclaimer](#disclaimer)

---
## ✨ Características

- Inyección de DLL sin escribir en disco.
- Uso de APIs nativas de Windows.
- Código modular y comentado.
- Funcional para laboratorios o pruebas locales.

---
## 📦 Requisitos

- Windows 10 o superior.
- MinGW o Visual Studio para compilar.
- DLL personalizada a inyectar.


---
## 🛠️ Compilación

Usá el siguiente comando:

```bash
x86_64-w64-mingw32-gcc PayloadInject.c -o injector.exe
```

---
## ⚙️ Ejecución

Ejecutá el binario generado como administrador e indicá el PID y ruta de la DLL:

```bash
injector.exe <PID> C:\ruta\a\la\dll.dll
```

---
## 🖼️ Vista previa

<img src="https://raw.githubusercontent.com/danisqxas/process-memory-injector/main/payload-preview.png" width="600px"/>

---
## 📫 Contacto

- Twitter: [@daniiwnet](https://x.com/daniiwnet?s=21)
- GitHub: [danisqxas](https://github.com/danisqxas)

---
## ⚠️ Disclaimer

Este proyecto tiene fines exclusivamente educativos.  
El autor no se hace responsable del uso indebido del código.

