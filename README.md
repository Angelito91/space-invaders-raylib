# Space Invaders Raylib

Un clon del clásico arcade **Space Invaders** desarrollado en **C++** con [raylib](https://www.raylib.com/).

## ✨ Características

- 🎮 Jugabilidad clásica del arcade Space Invaders
- 🎨 Gráficos 2D modernos con raylib
- 🔧 Código limpio y modular en C++17
- 📦 Gestión de dependencias con vcpkg
- 🛠️ Compilación con CMake multiplataforma

## 📋 Requisitos Previos

**General:**
- CMake 3.10+
- Compilador C++17 (GCC 7+, Clang 5+, MSVC 2017+)
- Git

**Específico por sistema:**
- **Windows:** Visual Studio 2019+ o MinGW
- **Linux:** build-essential
- **macOS:** Xcode Command Line Tools

## 🚀 Instalación y Compilación

### 1. Instalar vcpkg

**Windows:**
```cmd
git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
cd C:\vcpkg
.\bootstrap-vcpkg.bat
```

**Linux/macOS:**
```bash
git clone https://github.com/Microsoft/vcpkg.git ~/vcpkg
cd ~/vcpkg
./bootstrap-vcpkg.sh
```

### 2. Clonar el repositorio

```bash
git clone <URL-del-repositorio>
cd space-invaders-raylib
```

### 3. Instalar raylib

**Windows:**
```cmd
C:\vcpkg\vcpkg install raylib:x64-windows
```

**Linux:**
```bash
~/vcpkg/vcpkg install raylib:x64-linux
```

**macOS:**
```bash
~/vcpkg/vcpkg install raylib:arm64-osx
# O para Intel: ~/vcpkg/vcpkg install raylib:x64-osx
```

### 4. Compilar

**Windows:**
```cmd
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\cmake\vcpkg.cmake -G "Visual Studio 17 2022"
cmake --build build --config Release
```

**Linux/macOS:**
```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/cmake/vcpkg.cmake
cmake --build build --config Release
```

## ▶️ Ejecución

**Windows:**
```cmd
.\build\Release\space-invaders.exe
```

**Linux/macOS:**
```bash
./build/space-invaders
```

## 🎮 Controles

| Tecla | Acción |
|-------|--------|
| **← →** | Mover nave |
| **Espacio** | Disparar |
| **ESC** | Salir |

## 📁 Estructura del Proyecto

```
space-invaders-raylib/
├── src/main.cpp           # Código fuente principal
├── assets/                # Recursos (texturas, sonidos)
├── build/                 # Directorio de compilación
├── CMakeLists.txt         # Configuración de compilación
├── vcpkg.json            # Manifiesto de dependencias
└── README.md             # Este archivo
```

## 📦 Dependencias

- **raylib 5.0+** - Librería gráfica 2D y manejo de entrada (gestionada automáticamente con vcpkg)

## 🐛 Solución de Problemas

**CMake no encuentra Visual Studio (Windows):**
```cmd
cmake -B build -S . -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\cmake\vcpkg.cmake
```

**CMake no encuentra raylib:**
- Verifica que vcpkg está en la ruta correcta
- Asegúrate de haber instalado raylib: `vcpkg install raylib:<arquitectura>`
- Usa la ruta completa del archivo toolchain

**Limpiar y recompilar todo:**
```bash
rm -rf build           # Linux/macOS
# rmdir /s build       # Windows
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<ruta-vcpkg>
cmake --build build --config Release
```

**Linux - Dependencias gráficas faltantes:**
```bash
sudo apt-get install libgl1-mesa-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev
```

## 📚 Recursos Útiles

- [Documentación raylib](https://www.raylib.com/)
- [Referencia API raylib](https://www.raylib.com/cheatsheet/cheatsheet.html)
- [CMake Documentation](https://cmake.org/documentation/)
- [vcpkg Quick Start](https://github.com/Microsoft/vcpkg#quick-start)

## 📄 Licencia

Este proyecto está bajo la licencia especificada en el archivo [LICENSE](LICENSE).

---

**¡Disfruta el juego! 🚀**