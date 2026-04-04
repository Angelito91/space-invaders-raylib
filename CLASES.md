# Documentación de Clases - Space Invaders POO

## Descripción General

Este documento describe la arquitectura POO del proyecto Space Invaders después de la refactorización desde la rama `feature/core`.

## Clases Extraídas

### **Directorio: include/core/**

#### 1. **Game.h**
**Responsabilidad:** Orquestador principal del juego.

**Responsabilidades:**
- Inicializar ventana y sistemas raylib
- Ejecutar el loop principal del juego
- Actualizar lógica de juego cada frame
- Renderizar todos los elementos
- Gestionar transiciones de estado

**Métodos públicos:**
- `Game()` - Constructor
- `void init()` - Inicializa sistemas
- `void run()` - Loop principal
- `void update()` - Actualiza lógica
- `void draw()` - Renderiza escena
- `static void close()` - Limpia recursos

#### 2. **AssetManager.h**
**Responsabilidad:** Gestión centralizada de recursos.

**Responsabilidades:**
- Cargar texturas desde archivos
- Cargar sonidos desde archivos
- Cachear recursos para evitar cargas duplicadas
- Liberar memoria al finalizar

**Métodos públicos:**
- `Texture2D loadTexture(const std::string& path)`
- `Sound loadSound(const std::string& path)`
- `void unloadAll()`

#### 3. **EntityManager.h**
**Responsabilidad:** Gestión centralizada de entidades del juego.

**Responsabilidades:**
- Mantener lista de entidades activas
- Actualizar todas las entidades cada frame
- Renderizar todas las entidades
- Agregar nuevas entidades dinámicamente
- Remover entidades destructoras
- Detectar y manejar colisiones

**Métodos públicos:**
- `void update(float dt)` - Actualiza todas las entidades
- `void draw()` - Renderiza todas las entidades
- `void addEntity(Entity* entity)` - Agrega una entidad
- `void removeEntity(Entity* entity)` - Remueve una entidad
- `std::vector<Entity*> getEntities()` - Obtiene lista de entidades
- `void checkCollisions()` - Verifica colisiones entre entidades

---

### **Directorio: include/entities/**

#### 1. **Entity.h**
**Tipo:** Clase base abstracta

**Responsabilidad:** Interfaz común para todos los objetos del juego.

**Métodos virtuales puros:**
```cpp
virtual void update(float dt) = 0;       // Actualiza comportamiento
virtual void draw() = 0;                 // Renderiza entidad
virtual bool isAlive() const = 0;        // Verificar si existe
virtual Rectangle getBounds() const = 0; // Obtener área de colisión
```

**Atributos protegidos:**
- `Vector2 position` - Posición en pantalla
- `Vector2 velocity` - Velocidad de movimiento
- `Color color` - Color de renderizado
- `bool alive` - Estado de vida

#### 2. **Player.h**
**Hereda de:** Entity

**Responsabilidad:** Jugador controlable por el usuario.

**Características específicas:**
- Movimiento horizontal controlado por teclado
- Disparo de proyectiles con cooldown
- Colisión con proyectiles enemigos
- Sistema de vidas

**Métodos públicos:**
- `void update(float dt) override` - Maneja entrada y física
- `void draw() override` - Renderiza jugador
- `void shoot()` - Dispara proyectil
- `void takeDamage()` - Reduce vidas
- `int getLives() const` - Obtiene vidas restantes

#### 3. **Alien.h**
**Hereda de:** Entity

**Responsabilidad:** Enemigos que se mueven en formación.

**Características específicas:**
- Movimiento en formación con otros aliens
- Disparo coordinado
- AI para cambiar dirección
- Puntos al ser destruido

**Métodos públicos:**
- `void update(float dt) override` - Actualiza IA y física
- `void draw() override` - Renderiza enemigo
- `void shoot()` - Dispara proyectil enemigo
- `int getPointsValue() const` - Valor en puntos

#### 4. **Bullet.h**
**Hereda de:** Entity

**Responsabilidad:** Proyectiles del jugador y enemigos.

**Características específicas:**
- Movimiento recto en una dirección
- Destrucción al salir de pantalla
- Diferenciación entre proyectiles de jugador y enemigos
- Colisión con entidades

**Métodos públicos:**
- `void update(float dt) override` - Actualiza posición
- `void draw() override` - Renderiza proyectil
- `bool isPlayerBullet() const` - Verifica si es del jugador

#### 5. **BarrierBlock.h**
**Hereda de:** Entity

**Responsabilidad:** Barreras defensivas destructibles.

**Características específicas:**
- Salud/durabilidad
- Destrucción progresiva
- Protección del jugador contra proyectiles
- Desaparición al destruirse completamente

**Métodos públicos:**
- `void update(float dt) override` - (Puede no hacer nada)
- `void draw() override` - Renderiza con nivel de daño
- `void takeDamage(int amount)` - Recibe daño
- `int getHealth() const` - Obtiene salud actual

---

## Relaciones entre Clases

```
Game (Orquestador Principal)
├── AssetManager (Recursos)
└── EntityManager (Gestión de Entidades)
    ├── Entity* (Interfaz Base)
    │   ├── Player (Jugador)
    │   ├── Alien* N (Enemigos, N formación)
    │   ├── Bullet* N (Proyectiles)
    │   └── BarrierBlock* 4 (Barreras)
```

## Flujo de Ejecución Principal

```
main()
│
└─> Game::init()
    ├── InitWindow()
    ├── InitAudioDevice()
    └── EntityManager::init()
        └── Crear entidades iniciales
│
└─> Game::run()
    └─> Loop:
        ├── Game::update()
        │   ├── Actualizar entrada del jugador
        │   └── EntityManager::update()
        │       ├── Actualizar c/ entidad
        │       └── Detectar colisiones
        │
        ├── Game::draw()
        │   ├── ClearBackground()
        │   └── EntityManager::draw()
        │       └─ Renderizar c/ entidad
        │
        └─> Logitar puntuación y estado
│
└─> Game::close()
    ├── EntityManager::cleanup()
    ├── CloseAudioDevice()
    └── CloseWindow()
```

## Beneficios de la Arquitectura POO

✅ **Mantenibilidad:** Código modular y desacoplado  
✅ **Extensibilidad:** Fácil agregar nuevas entidades  
✅ **Reutilización:** Entity base para todas las entidades  
✅ **Testabilidad:** Cada clase tiene responsabilidad clara  
✅ **Escalabilidad:** Gestión centralizada sin duplicación  

---

**Documentación de Clases**  
**Versión:** 2.0 POO  
**Fecha:** Abril 2026
