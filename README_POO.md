# Space Invaders - Programación Orientada a Objetos (POO)

Un clon del clásico arcade **Space Invaders** desarrollado en **C++17** con arquitectura robusta basada en **Programación Orientada a Objetos**, utilizando la biblioteca [raylib](https://www.raylib.com/).

## ✨ Características

- 🎮 **Arquitectura POO Completa:** Clases Entity, Player, Alien, Bullet, BarrierBlock
- 🏆 **Gestión Centralizada:** EntityManager y AssetManager para control modular
- 📦 **Código Profesional:** Separación clara de responsabilidades y headers
- 🎨 **Patrón Strategy:** Comportamiento polimórfico de entidades
- 🛠️ **CMake Moderno:** Sistema de compilación estándar de la industria

## 📋 Requisitos Previos

### **Windows**
- **w64devkit** - entorno de desarrollo MinGW actualizado
- **raylib** compilada para Windows (x86_64)
- **CMake** 3.15+

### **Linux**
```bash
sudo apt-get install build-essential cmake libraylib-dev
```

### **macOS**
```bash
brew install cmake raylib
```

## 🚀 Compilación

### **Método Recomendado: CMake**

```bash
# Crear directorio de build
mkdir build && cd build

# Configurar el proyecto
cmake ..

# Compilar
cmake --build .

# Ejecutar
./space-invaders          # Linux/macOS
space-invaders.exe        # Windows
```

### **Alternativa: Python**

```bash
python3 build.py
```

## 🎮 Cómo Jugar

### **Controles**

| Acción | Tecla |
|--------|-------|
| Moverse Izquierda | ← o A |
| Moverse Derecha | → o D |
| Disparar | Espacio |
| Pausar | P |

## 🏗️ Estructura del Proyecto

```
space-invaders-raylib/
├── include/
│   ├── core/
│   │   ├── Game.h              # Orquestador principal del juego
│   │   ├── AssetManager.h      # Gestor de recursos (texturas, sonidos)
│   │   └── EntityManager.h     # Gestor centralizado de entidades
│   └── entities/
│       ├── Entity.h             # Clase base abstracta
│       ├── Player.h             # Jugador controlable
│       ├── Alien.h              # Enemigos en formación
│       ├── Bullet.h             # Proyectiles
│       └── BarrierBlock.h       # Barreras defensivas
├── src/
│   ├── main.cpp                 # Punto de entrada
│   ├── Game.cpp                 # Implementación del juego
│   ├── AssetManager.cpp         # Implementación de recursos
│   ├── EntityManager.cpp        # Implementación de entidades
│   ├── Player.cpp               # Implementación de jugador
│   ├── Alien.cpp                # Implementación de enemigos
│   ├── Bullet.cpp               # Implementación de proyectiles
│   └── BarrierBlock.cpp         # Implementación de barreras
├── CMakeLists.txt               # Configuración CMake
├── build.py                     # Constructor Python
├── LICENSE
├── vcpkg.json                   # Dependencias (vcpkg)
└── README.md
```

## 📚 Arquitectura POO

### **Jerarquía de Clases**

```
Entity (Clase Base Abstracta)
├── Player
├── Alien
├── Bullet
└── BarrierBlock
```

### **Clases Principales**

#### **Game** - Orquestador
```cpp
class Game {
    void init();      // Inicializa sistemas
    void run();       // Loop principal
    void update();    // Actualiza lógica de juego
    void draw();      // Renderiza todo
    void close();     // Cierra recursos
};
```

#### **EntityManager** - Gestor de Entidades
```cpp
class EntityManager {
    void update(float dt);
    void draw();
    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);
    std::vector<Entity*> entities;
};
```

#### **AssetManager** - Gestor de Recursos
```cpp
class AssetManager {
    Texture2D loadTexture(const std::string& path);
    Sound loadSound(const std::string& path);
    void unloadAll();
};
```

#### **Entity** - Clase Base (Interfaz Común)
```cpp
class Entity {
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
    virtual bool isAlive() const = 0;
    virtual Rectangle getBounds() const = 0;
};
```

#### **Player** - Entidad Jugable
```cpp
class Player : public Entity {
    void update(float dt) override;
    void draw() override;
    void shoot();
    void move(float dx);
};
```

#### **Alien** - Enemigo
```cpp
class Alien : public Entity {
    void update(float dt) override;
    void draw() override;
    void shoot();
};
```

#### **Bullet** - Proyectil
```cpp
class Bullet : public Entity {
    void update(float dt) override;
    void draw() override;
};
```

#### **BarrierBlock** - Barrera
```cpp
class BarrierBlock : public Entity {
    void update(float dt) override;
    void draw() override;
    void takeDamage();
};
```

## 🎯 Características del Gameplay

- **Formaciones de Enemigos:** Alienígenas que se mueven sincronizadamente
- **Sistema de Disparos:** Jugador y enemigos pueden disparar
- **Barreras Defensivas:** Bloques destructibles que protegen al jugador
- **Detección de Colisiones:** Entre proyectiles y entidades
- **Aumento de Dificultad:** Velocidad e IA mejoran con el progreso
- **Sistema de Puntuación:** Acumula puntos derrotando enemigos

## 🔧 Compilación Manual

Si CMake falla por problemas del toolchain:

```bash
# Windows
g++ -std=c++17 \
  -I include -I C:\raylib\raylib\src \
  -L C:\raylib\w64devkit\x86_64-w64-mingw32\lib \
  -o space-invaders.exe \
  src/main.cpp src/Game.cpp src/AssetManager.cpp src/EntityManager.cpp \
  src/Player.cpp src/Alien.cpp src/Bullet.cpp src/BarrierBlock.cpp \
  -lraylib -lopengl32 -lgdi32 -lwinmm

# Linux
g++ -std=c++17 \
  -I include \
  -o space-invaders \
  src/*.cpp \
  -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

## 📖 Patrones de Diseño Implementados

### **1. Strategy Pattern**
Cada entidad hereda de Entity e implementa su propio comportamiento en `update()` y `draw()`.

### **2. Singleton Pattern**
`AssetManager` actúa como singleton para gestión centralizada de recursos.

### **3. Factory Pattern**
`EntityManager` crea y destruye entidades dinámicamente.

### **4. Observer Pattern** (Potencial)
Sistema de eventos para colisiones y puntuación.

## 🐛 Solución de Problemas

### **Error: "raylib.h: No such file or directory"**
Asegure que raylib esté en `C:\raylib\raylib\src\` (Windows) o `/usr/include/` (Linux).

### **Error de Compilación en w64devkit**
Actualice w64devkit a la última versión que resuelva incompatibilidades GCC/Binutils.

### **Executable no se crea**
Verifique que todos los archivos .cpp están incluidos en CMakeLists.txt.

## 🚀 Próximas Mejoras Sugeridas

- [ ] Sistema de animación frame-by-frame
- [ ] Menú principal y pausa
- [ ] Almacenamiento de high scores
- [ ] Efectos de sonido y música
- [ ] Partículas en explosiones
- [ ] Múltiples niveles
- [ ] Power-ups y bonificadores
- [ ] Modo multijugador (local)

## 📄 Licencia

Este proyecto está bajo la licencia especificada en el archivo `LICENSE`.

---

**Información del Proyecto**
- **Versión:** 2.0 (POO)
- **Lenguaje:** C++17
- **Motor:** raylib
- **Arquitectura:** Programación Orientada a Objetos
- **Última actualización:** Abril 2026
