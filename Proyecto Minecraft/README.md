# EjemplosJuego

El proyecto esta desarrollado sobre MinGW64 utilizando Msys2
y como editor se esta utilizando Visual Studio Code.

## Prerequisitos

[Instalar las herramientas necesarias](./docs/herramientas.md)

[Instalar las Extensiones VSCode](./docs/extensiones.md)

[Instalar las librerias](./docs/librerias.md)

[Clonar el repositorio](./docs/fork.md)

## Como ejecutar los ejemplos

Instalar todas las dependencias descritas arriba y dentro de una terminal de vscode ejecutar:

> make run'NombreEjecutable'

Por ejemplo para ejecutar '00_Ventana.cpp' correr el comando en la terminal de vscode:

> make run00_Ventana

## Errores comunes
- [Los diagramas de PUML no se visualizan bien]()

## Buenas Practicas
- [Como Crear un buen readme](https://www.makeareadme.com/)
- [Patrones de diseño](https://refactoring.guru/es/design-patterns)
- [Como hacer commits semanticos]()
- [Como estructurar un proyecto]()
- [Que tipos de licencias existen]()

## Tutoriales Github
- [Creacion de un repositorio]()
- [Como colaborar en un proyecto]()
- [Solicitar developer pack]()

## Recursos Gratis
- [Fuentes de texto gratis](https://www.dafont.com/es/)
- [Recursos gratis de Videojuegos](https://opengameart.org/)

## Contexto de la carpeta

Esta carpeta contiene ejemplos y recursos para aprender y probar conceptos básicos de programación de juegos en C++.

- `src/` contiene ejemplos independientes (ventana, imágenes, sprites, input, audio, físicas, etc.).
- `include/` contiene los encabezados que definen las clases y estructuras usadas por los ejemplos.
- `assets/` agrupa recursos multimedia (fuentes, imágenes, música) utilizados por las demos.
- Usa el `makefile` para compilar y ejecutar los ejemplos (p. ej. `make run00_Ventana`).

Para más detalles sobre la estructura del proyecto, consulta `docs/contexto_de_la_carpeta.md`.

## Ejemplo: Juego 2D tipo "Minecraft" (consola)

Se añadió un ejemplo sencillo en `src/09_Minecraft2D.cpp` que implementa un mundo predeterminado pequeño
y mecánicas básicas: moverse, picar y construir. El juego es por consola y no requiere librerías externas.

Compilar (MinGW / MSYS2) desde la raíz del proyecto:

```powershell
g++ -std=c++17 -O2 -o bin/minecraft2d "src/09_Minecraft2D.cpp"
```

Ejecutar:

```powershell
.\bin\minecraft2d
```

Controles (teclear y pulsar Enter):
- `a`/`d`/`w`/`s`: mover
- `x`: picar (quita el bloque frente al jugador y lo añade al inventario)
- `c`: construir (coloca el bloque seleccionado frente al jugador si hay espacio)
- `1`-`5`: seleccionar tipo de bloque
- `h`: ayuda, `q`: salir

Si quieres, puedo adaptar el ejemplo para usar una librería gráfica (SDL2/SFML), añadir soporte de mouse, o mejorar la física/colisiones.
