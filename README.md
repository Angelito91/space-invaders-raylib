# Space Invaders Raylib

Un clon profesional del clásico arcade **Space Invaders** desarrollado en **C++17** utilizando la biblioteca [raylib](https://www.raylib.com/). Este proyecto ha sido diseñado con un enfoque modular y orientado a objetos, ideal para el aprendizaje de desarrollo de videojuegos y sistemas de software.

## ✨ Características

- 🎮 **Jugabilidad Clásica:** Movimiento fluido, oleadas de enemigos y sistema de disparos.
- 🏆 **Persistencia:** Sistema de *High Score* local para guardar récords.
- 🎨 **Arquitectura Modular:** Separación clara entre lógica de juego, entidades y renderizado.
- 📖 **Documentación Automática:** Comentarios en formato Doxygen para generación de manuales técnicos.
- 🛠️ **Build System:** Configuración robusta con CMake y gestión de dependencias con vcpkg.

## 📋 Requisitos Previos

### **Dependencias del Sistema**
* **Arch Linux:** `sudo pacman -S raylib cmake doxygen`
* **Ubuntu/Debian:** `sudo apt install libraylib-dev doxygen`
* **Windows:** Visual Studio 2022 + [vcpkg](https://github.com/Microsoft/vcpkg)

## 🚀 Instalación y Compilación

### 1. Clonar el repositorio
```bash
git clone <URL-del-repositorio>
cd space-invaders-raylib
```

### 2. Compilar con CMake
Recomendamos usar el flujo estándar de CMake:

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
*Nota: Si usas **vcpkg**, recuerda añadir `-DCMAKE_TOOLCHAIN_FILE=[ruta-a-vcpkg]/scripts/buildsystems/cmake/vcpkg.cmake` al primer comando.*

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
- **Líder Técnico:** [Tu Nombre] - Arquitectura y Core.
- **Dev 2:** [Sasuke44LQ] - Gameplay y Sistema de Disparos.
- **Dev 3:** [Nombre] - IA de Enemigos y Movimiento de Grupo.
- **Dev 4:** [Nombre] - UI, Sonido y Persistencia.

## 🤝 Contribución (Git Workflow)

Para mantener la integridad del código, seguimos estas reglas:
1. **Ramas:** No trabajamos directamente en `main`. Creamos ramas `feature/nombre-de-tarea`.
2. **Commits:** Mensajes claros y descriptivos.
3. **Doxygen:** Es obligatorio documentar cada nueva función en el `.h` antes de hacer el *Pull Request*.
