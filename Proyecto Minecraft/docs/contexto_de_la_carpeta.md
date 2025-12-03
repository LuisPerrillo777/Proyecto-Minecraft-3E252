# Contexto de la carpeta

Este documento resume la estructura y el propósito de los archivos y carpetas del proyecto "Proyecto Minecraft".

Resumen rápido:

- `makefile`: tareas de compilación/ejecución.
- `README.md`: documentación principal del proyecto (se añadió una sección de contexto).
- `TODO.md`: lista de tareas.
- `assets/`: recursos multimedia (fuentes, imágenes, música).
- `bin/`: binarios o compilados de ejemplo.
- `docs/`: documentación y guías adicionales.
- `include/`: encabezados C++ con las definiciones de clases usadas por `src/`.
- `src/`: implementaciones y ejemplos en C++ (ventana, imágenes, sprites, entrada, audio, físicas, etc.).

Descripción breve de carpetas y archivos principales:

- `include/`:
  - `Ball.hpp` — definición de una bola para demos físicas.
  - `GameWindow.hpp` — encapsula la creación y manejo de la ventana de la aplicación.
  - `Ground.hpp` — definición del suelo/escenario.
  - `PhysicsSpace.hpp` — gestor o espacio de físicas.

- `src/` (ejemplos y demos):
  - `00_Ventana.cpp` — ejemplo de creación de ventana.
  - `01_Imagen.cpp` — carga y render de imágenes.
  - `02_Sprite.cpp` — manejo y animación de sprites.
  - `03_0_Teclado.cpp` — entrada por teclado.
  - `03_1_Pikachu.cpp` — ejemplo con sprite Pikachu.
  - `04_Texto.cpp` — renderizado de texto en pantalla.
  - `05_Audio.cpp` — reproducción de audio.
  - `06_Primitivas.cpp` — dibujo de primitivas gráficas.
  - `07_Fisica.cpp` — demo de física.
  - `08_Tron.cpp` — ejemplo de juego estilo Tron.

Notas:

- El repositorio parece orientado a la enseñanza/práctica: cada archivo en `src/` es un ejemplo autónomo.
- Revisa el `makefile` para saber cómo compilar/ejecutar los ejemplos en tu entorno.

Opciones siguientes (dime si quieres que haga alguna):
- Ampliar la descripción por archivo con dependencias y funciones clave.
- Generar `CONTRIBUTING.md` o instrucciones de compilación más detalladas.
- Ejecutar una compilación de prueba en tu entorno.
