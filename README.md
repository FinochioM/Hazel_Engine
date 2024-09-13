# HazelEngine 2D Game Framework

**HazelEngine** es un motor de juegos 2D creado desde cero en C++ con soporte para **SDL2** y **OpenGL**, enfocado exclusivamente en Windows. Este motor está diseñado para proporcionar una estructura flexible y modular para el desarrollo de videojuegos 2D, inspirado en motores populares como **MonoGame** y **Godot**.

## Características Principales

### Renderizado 2D con OpenGL y SDL2
- Sistema de renderizado eficiente usando OpenGL para gráficos en 2D.
- Soporte para diferentes tipos de filtros de texturas: **Point**, **Bilinear**, **Trilinear**.

### Sistema de Animaciones Flexible
- Manejo de ciclos de animación con soporte para transiciones suaves entre diferentes animaciones.
- Control manual de animaciones: avanza y retrocede frame por frame, ideal para debugging.
- Flexibilidad para seleccionar un frame de inicio y de finalización, con opciones de loop o finalización automática.
- Si no hay una animación en ejecución, se renderiza automáticamente el primer frame de la animación `idle`.

### Sistema de Transiciones
- Transiciones dinámicas entre animaciones basadas en condiciones personalizadas.
- Control sobre la duración de las transiciones y la interpolación de opacidades entre ciclos.

### Entradas de Teclado y Ratón
- Manejo de eventos de entrada para controlar la lógica del juego y las animaciones.
- Configuración manual de animaciones basadas en la entrada del usuario (avance/retroceso de frames).

### Sistema de Componentes y Entidades
- Arquitectura basada en **Entidades y Componentes** (ECS-like).
- Los componentes actuales incluyen:
  - **SpriteRenderer**: Renderizado de sprites 2D.
  - **Animator**: Manejo avanzado de animaciones.
  - **BoxCollider**: Sistema básico de colisiones.

### Manejo de Widgets y GUI
- Soporte para elementos de la interfaz gráfica como botones, con un sistema modular para manejar eventos.

# Roadmap de HazelEngine

Este es el plan de desarrollo actual para **HazelEngine**. El objetivo es proporcionar un framework sólido para el desarrollo de videojuegos 2D con soporte para gráficos, sonido, física y una arquitectura modular que permita la expansión fácil del motor.

## Etapas del Desarrollo

### ✔️ Funcionalidades Completadas

#### 🔧 Core del Motor
- ✅ Implementación del ciclo de vida del motor (Inicialización, Renderizado, Actualización y Apagado).
- ✅ Integración de **SDL2** para la gestión de ventanas y eventos.
- ✅ Renderizado 2D con **OpenGL**.
- ✅ Sistema de componentes básicos (SpriteRenderer, Animator, BoxCollider).
- ✅ Sistema de **Escenas** y **Nodos**.
- ✅ Soporte para texturas con diferentes filtros (Point, Bilinear, Trilinear).
- ✅ Manejo de eventos de entrada (teclado y mouse).

#### 🎥 Sistema de Animaciones
- ✅ Sistema de animaciones con soporte para múltiples ciclos de animación.
- ✅ Control manual de animaciones (avanzar y retroceder frame por frame).
- ✅ Transiciones suaves entre animaciones con interpolación de opacidad.
- ✅ Renderizado de un frame fijo cuando no hay animación activa.

#### 🖱️ GUI y Widgets
- ✅ Sistema básico de Widgets (Botones, manejo de eventos).
- ✅ Manejo modular de eventos en la interfaz gráfica.

### 🚧 Funcionalidades Pendientes

#### ⚙️ Motor
- ⏳ Implementar un sistema de física 2D más avanzado (detección de colisiones y resolución).
- ⏳ Optimización del renderizado para manejar múltiples elementos en pantalla sin perder rendimiento.
- ⏳ Mejorar el sistema de gestión de recursos (carga y descarga automática de texturas, sonidos, etc.).

#### 🎨 Editor de Motor
- ⏳ Comenzar el desarrollo de un editor gráfico similar a **Godot** o **Unity** para facilitar la creación y gestión de escenas, entidades y componentes.
- ⏳ Integrar herramientas visuales para la manipulación de nodos y transformaciones.

#### 🕹️ Nuevos Componentes
- ⏳ Añadir más tipos de componentes, como:
  - **SoundEmitter**: Soporte para efectos de sonido y música.
  - **ParticleSystem**: Sistema de partículas básico.
  - **TextRenderer**: Renderizado de texto dinámico.

#### 🎮 Gameplay y Física
- ⏳ Sistema de física con fuerzas, aceleración, gravedad, etc.
- ⏳ Detección de colisiones más avanzada (basada en formas y bounding boxes).
- ⏳ Implementar un sistema de eventos de colisión para manejar interacciones entre entidades.

#### 🗂️ Editor de Recursos
- ⏳ Crear un **Resource Compiler** para la conversión de archivos a formatos compatibles con el motor.
- ⏳ Sistema para manejar assets en tiempo de ejecución (como un gestor de recursos eficiente).

### 🛠️ Mejoras Generales
- ⏳ Refactorización y optimización del código para mejorar el rendimiento y la escalabilidad.
- ⏳ Documentación completa de todas las funcionalidades para facilitar la colaboración y el desarrollo.
- ⏳ Creación de ejemplos más avanzados para mostrar las capacidades del motor.



