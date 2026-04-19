# Space Invaders Raylib

Un clon del clásico arcade **Space Invaders** desarrollado en **C++17** utilizando la biblioteca [raylib](https://www.raylib.com/).

## ✨ Características

- 🎮 **Jugabilidad Clásica:** Movimiento fluido, oleadas de enemigos y sistema de disparos
- 🏆 **Sistema de Puntuación:** Siga su progreso durante la partida
- 🎨 **Arquitectura Simple:** Código limpio y fácil de entender
- 🛠️ **Múltiples métodos de compilación:** CMake, scripts batch, Python

## 📋 Requisitos Previos

### **Windows (Recomendado para este proyecto)**
* **w64devkit** - ambiente de desarrollo MinGW
* **raylib** compilada para Windows
* **CMake** 3.15+ (opcional)

###  **Linux**
```bash
sudo apt-get install build-essential cmake libraylib-dev
```

### **macOS**
```bash
brew install cmake raylib
```

## 🚀 Compilación

### **Opción 1: Script Batch (Windows - Recomendado)**

```cmd
cd space-invaders-raylib
compile.bat
```

### **Opción 2: Python (Multiplataforma)**

```bash
python3 build.py
```

Esto intentará automáticamente varias estrategias de compilación.

### **Opción 3: CMake**

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### **Opción 4: Compilación Manual**

```bash
g++ -std=c++17 \
  -I C:\raylib\raylib\src \
  -L C:\raylib\w64devkit\x86_64-w64-mingw32\lib \
  -o space-invaders.exe src/main.cpp
  -lraylib -lopengl32 -lgdi32 -lwinmm
```

## 🎮 Cómo Jugar

Una vez compilado:

```bash
./space-invaders.exe      # Linux/macOS
space-invaders.exe        # Windows
```

### **Controles**

| Acción | Tecla |
|--------|-------|
| Moverse Izquierda | ← o A |
| Moverse Derecha | → o D |
| Disparar | Espacio |
| Pausar | P |
| Iniciar | ENTER |
| Reiniciar | R |

## 🏗️ Estructura del Proyecto

```
space-invaders-raylib/
├── src/
│   └── main.cpp              # Código principal del juego
├── CMakeLists.txt            # Configuración CMake
├── compile.bat               # Script de compilación Windows
├── build.py                  # Constructor automático Python
├── Makefile.simple           # Makefile alternativo
├── README.md                 # Este archivo
└── INSTRUCCIONES_COMPILACION.md  # Guía detallada
```

## 🐛 Solución de Problemas

### **Error: "bad register name" o errores de assembler**

Esto indica un problema de compatibilidad entre GCC y Binutils en w64devkit.

**Soluciones:**
1. Actualizar w64devkit a la última versión
2. Usar Visual Studio 2022 en su lugar
3. Ver `INSTRUCCIONES_COMPILACION.md`

### **Error: "No se encontró raylib.h"**

Verifique que raylib está en:
- Windows: `C:\raylib\raylib\src\`
- Linux: `/usr/include/`
- macOS: `/usr/local/include/`

### **Error: "No se encontró libraylib.a"**

Asegúrese de que raylib está compilada correctamente:
```bash
# En el directorio de raylib
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

## 📖 Requisitos de Compilación por Plataforma

### **Windows**
- w64devkit (o MinGW 64-bit)
- raylib compilada para Windows
- CMake 3.15+ (opcional)

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Si encuentras problemas de compilación previos, limpia el directorio de build primero:
```bash
rm -rf build
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

*Nota: Si usas **vcpkg**, recuerda añadir `-DCMAKE_TOOLCHAIN_FILE=[ruta-a-vcpkg]/scripts/buildsystems/cmake/vcpkg.cmake` al primer comando.*

### Windows con w64devkit + CMake (Recomendado)

Para Windows, recomendamos usar **w64devkit** (64-bit) con raylib precompilado:

1. **Instala w64devkit y raylib:**
   - Descarga w64devkit desde [https://github.com/skeeto/w64devkit](https://github.com/skeeto/w64devkit)
   - Instala raylib siguiendo [https://github.com/raysan5/raylib/wiki/Working-on-Windows](https://github.com/raysan5/raylib/wiki/Working-on-Windows)
   - Asegúrate de que `C:/raylib/w64devkit/x86_64-w64-mingw32/lib/libraylib.a` existe

2. **Compila con CMake:**
   ```powershell
   # Configura el PATH para w64devkit
   $env:PATH = 'C:\raylib\w64devkit\bin;' + $env:PATH
   
   # Configura y compila
   cmake -G "MinGW Makefiles" -B build -DCMAKE_BUILD_TYPE=Release `
         -DCMAKE_C_COMPILER=C:/raylib/w64devkit/bin/gcc.exe `
         -DCMAKE_CXX_COMPILER=C:/raylib/w64devkit/bin/g++.exe
   cmake --build build --config Release
   ```

3. **Ejecuta:**
   ```powershell
   .\build\space-invaders.exe
   ```

*Nota: El proyecto está configurado para detectar automáticamente w64devkit. Si tienes raylib en rutas diferentes, usa variables de entorno: `RAYLIB_DEVKIT_ROOT`, `RAYLIB_INCLUDE_DIR`, `RAYLIB_LIBRARY`.*

### 3. Ejecutar el programa

Una vez compilado correctamente, ejecuta el juego:

```bash
./build/space-invaders
```

El ejecutable se encontrará en el directorio `build/` después de la compilación.

## 📖 Documentación (Doxygen)

Este proyecto utiliza **Doxygen** para generar documentación técnica a partir de los comentarios en los archivos de cabecera (`.h`).

Para generar la documentación en formato HTML:
1. Asegúrate de tener Doxygen instalado.
2. Ejecuta en la raíz del proyecto:
   ```bash
   doxygen Doxyfile
   ```
3. Abre `docs/html/index.html` en tu navegador.

## 🎮 Controles

| Tecla | Acción |
|-------|--------|
| **A / D** o **← →** | Mover nave lateralmente |
| **Espacio** | Disparar |
| **P** | Pausar juego |
| **ESC** | Salir al menú / Cerrar |

## 📁 Estructura del Proyecto

```text
space-invaders-raylib/
├── assets/              # Texturas, sonidos y fuentes
├── docs/                # Documentación generada por Doxygen
├── include/             # Archivos de cabecera (.h)
│   ├── core/            # Engine y Game Loop
│   └── entities/        # Definiciones de Player, Alien, etc.
├── src/                 # Implementación (.cpp)
├── CMakeLists.txt       # Configuración de CMake
├── Doxyfile             # Configuración de Doxygen
└── README.md            # Este archivo
```

## 👥 Equipo de Desarrollo

Este proyecto es el resultado del trabajo colaborativo de:
- **Líder Técnico:** [Angelito91] - Arquitectura y Core.
- **Dev 2:** [Sasuke44LQ] - Gameplay y Sistema de Disparos.
- **Dev 3:** [Nombre] - IA de Enemigos y Movimiento de Grupo.
- **Dev 4:** [Nombre] - UI, Sonido y Persistencia.

## 🤝 Contribución (Git Workflow)

Para mantener la integridad del código, seguimos estas reglas:
1. **Ramas:** No trabajamos directamente en `main`. Creamos ramas `feature/nombre-de-tarea`.
2. **Commits:** Mensajes claros y descriptivos.
3. **Doxygen:** Es obligatorio documentar cada nueva función en el `.h` antes de hacer el *Pull Request*.