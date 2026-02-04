# MO OpenGL Renderer v2.0.1

Un motor de renderizado OpenGL moderno diseñado para aplicaciones gráficas 3D educativas y de alto rendimiento, escrito en C++20.

---

## 📋 Descripción

**MO OpenGL Renderer v2.0.1** es un motor de renderizado 3D basado en OpenGL 4.0+ que proporciona una arquitectura limpia y extensible para crear aplicaciones gráficas interactivas. El proyecto implementa patrones de diseño modernos como Factory Pattern y separación de responsabilidades entre renderizado, entrada y lógica de escena.

## ✨ Características Principales

- **Arquitectura Modular**: Separación clara entre rendering, input management y lógica de mundo
- **OpenGL 4.0+**: Aprovecha las características modernas de OpenGL para renderizado eficiente
- **Sistema de Materiales**: Soporte para shaders GLSL personalizados con gestión de texturas
- **Sistema de Cámaras**: Cámaras configurables con control de teclado/ratón
- **Gestión de Escenas**: World system para organizar objetos 3D, cámaras e iluminación
- **Pipeline Programable**: Shaders vertex/fragment completamente personalizables
- **Transformaciones 3D**: Sistema de matrices Model-View-Projection con GLM
- **Texturas**: Soporte para texturas 2D con múltiples formatos

## 🏗️ Arquitectura del Sistema

```
┌─────────────────────────────────────┐
│          Application Layer          │
│         (APIS3D_2025.cpp)           │
└────────────┬────────────────────────┘
             │
             ▼
┌─────────────────────────────────────┐
│           System Core               │
│  ┌──────────────────────────────┐   │
│  │    System (Singleton)        │   │
│  │  - initSystem()              │   │
│  │  - mainLoop()                │   │
│  │  - addObject()               │   │
│  └──────────┬───────────────────┘   │
└─────────────┼───────────────────────┘
              │
      ┌───────┴────────┬──────────────┐
      ▼                ▼              ▼
┌──────────┐   ┌──────────────┐  ┌─────────┐
│  Render  │   │    World     │  │  Input  │
│ (GL4)    │   │ - Objects    │  │ Manager │
│          │   │ - Cameras    │  │ (GLFW)  │
└────┬─────┘   └──────┬───────┘  └─────────┘
     │                │
     │                ▼
     │         ┌──────────────┐
     │         │   Object     │
     │         │ - Mesh       │
     │         │ - Material   │
     │         │ - Transform  │
     │         └──────┬───────┘
     │                │
     ▼                ▼
┌────────────┐  ┌─────────────┐
│  Material  │  │    Mesh     │
│ - Program  │  │ - Vertices  │
│ - Textures │  │ - Indices   │
└────────────┘  └─────────────┘
```

### Componentes Clave

#### **System** (Núcleo Central)
- Gestiona el ciclo de vida de la aplicación
- Coordina Render, World e InputManager
- Proporciona el main loop con delta time

#### **FactoryEngine** (Patrón Factory)
- Crea instancias de Render, InputManager, Materials y Textures
- Permite cambiar entre diferentes backends (OpenGL 4.0)

#### **Render (GL4Render)**
- Implementa el pipeline de renderizado OpenGL
- Gestiona VAOs, VBOs e IBOs
- Maneja el contexto GLFW y la ventana

#### **World**
- Contenedor de objetos 3D y cámaras
- Actualiza transformaciones y lógica de escena
- Gestiona la cámara activa

#### **Material System**
- GLSLMaterial: Gestiona shaders GLSL
- Soporte para texturas con samplers
- Configuración de uniformes (MVP, color, etc.)

## 🚀 Inicio Rápido

### Requisitos Previos

- **Compilador**: Visual Studio 2022 o compilador compatible con C++20
- **Librerías**:
  - OpenGL 4.0+
  - GLFW 3.x
  - GLAD
  - GLM (OpenGL Mathematics)
  - STB Image (opcional, para carga de texturas)

### Compilación

#### Windows (Visual Studio)

```bash
# Clonar el repositorio
git clone https://github.com/master-computacion-grafica/mo-opengl-renderer

# Abrir el proyecto en Visual Studio
# Compilar en Release o Debug
```

#### Linux (Make)

```bash
# Instalar dependencias
sudo apt-get install libglfw3-dev libglm-dev

# Compilar
make
```

### Ejemplo de Uso Básico

```cpp
#include "mo/System.h"
#include "mo/World.h"
#include "mo/CameraKeyboard.h"
#include "mo/CubeTex.h"

int main(int argc, char** argv)
{
    // Inicializar sistema con OpenGL 4.0 y GLFW
    System::initSystem(MO_RENDER_ENGINE_TYPE_GL4, MO_INPUT_MANAGER_TYPE_GLFW);

    // Configurar cámara
    auto camera = std::make_shared<CameraKeyboard>(
        MO_PROJECTION_TYPE_PERSPECTIVE,
        glm::vec3(1, 1, 3),    // posición
        glm::vec3(0, 1, 0),    // up
        glm::vec3(0, 0, 0)     // lookAt
    );
    
    System::getWorld()->addCamera(camera);

    // Añadir objetos a la escena
    System::addObject(std::make_shared<CubeTex>());

    // Ejecutar loop principal
    System::mainLoop();

    return 0;
}
```

## 📁 Estructura del Proyecto

```
mo-opengl-renderer/
├── src/
│   └── mo/
│       ├── System.h/cpp           # Core del sistema
│       ├── World.h/cpp            # Gestión de escena
│       ├── Render.h               # Interfaz de renderizado
│       ├── GL4Render.h/cpp        # Implementación OpenGL 4.0
│       ├── FactoryEngine.h/cpp    # Factory pattern
│       ├── Material.h             # Interfaz de material
│       ├── GLSLMaterial.h/cpp     # Material GLSL
│       ├── GLSLProgram.h/cpp      # Gestión de shaders
│       ├── Object.h/cpp           # Objeto 3D base
│       ├── Camera.h/cpp           # Sistema de cámaras
│       └── ...
├── data/
│   ├── shader.vert                # Vertex shader
│   ├── shader.frag                # Fragment shader
│   └── textures/                  # Texturas del proyecto
├── externalLibs/                  # Librerías externas
├── APIS3D_2025.cpp                # Punto de entrada
└── README.md
```

## 🎓 Conceptos Implementados

- **Shaders GLSL**: Vertex y Fragment shaders programables
- **Transformaciones 3D**: Matrices Model-View-Projection
- **Iluminación**: Sistema de materiales con colores y texturas
- **Texturas 2D**: Mapeo de texturas con samplers
- **Gestión de Buffers**: VAO, VBO, IBO con OpenGL
- **Cámara Interactiva**: Control por teclado y ratón
- **Delta Time**: Independencia de framerate

## 👥 Autores

| Autor              | Email                                                                     |
|--------------------|---------------------------------------------------------------------------|
| Oscar Viudez       | [oscarviudez24@gmail.com](mailto:oscarviudez24@gmail.com)                 |
| Miguel Gutiérrez   | [miguel.gutierrez@live.u-tad.com](mailto:miguel.gutierrez@live.u-tad.com) |

## 📄 Licencia

Este proyecto es parte del máster en Computación Gráfica de U-tad (2026).

## 🔗 Enlaces Útiles

- [OpenGL Documentation](https://www.khronos.org/opengl/)
- [GLFW Documentation](https://www.glfw.org/documentation.html)
- [GLM Documentation](https://glm.g-truc.net/)
- [LearnOpenGL Tutorial](https://learnopengl.com/)

---

**Versión**: 2.0.1  
**Año**: 2026  
**Institución**: U-tad Master en Computación Gráfica