+++
date = '2026-02-20T17:36:54-08:00'
draft = false
title = 'Practica 0: Manejo de repositorios'
+++

# Subsecciones
- Descripcion de la practica
- Desarrollo de la practica
  - Sesion 1
  - Sesion 2
  - Sesion 3
- Conclusiones

# Descripcion de la practica
Primera sesión.
Sintaxis y uso de markdown. Crear un reporte de que es Markdown, cómo se utiliza, y su sintaxis.

Segunda sesión.
Uso de Git y GitHub. Añadir al reporte que es Git y Github, como se utiliza, comandos escenciales para usar Git y subir la información a Github, como crear un repositorio y suben su información a la nube.

Tercera sesión.
Combinar los conocimientos de Markdown y Git para generar páginas estáticas con Hugo y GitHub Actions. Añadir al reporte que es Hugo y Github Actions, como crear un sitio estático en hugo, como suben esta información a Github, como configurar Github Actions para publicar el sitio en Github Pages.

Añadir al reporte el enlace a su portafolio en Github y su página estática en Github Pages.

Este reporte será la primera entrada en su portafolio/página estática. De aquí van a utilizar alguna extensión para convertir este archivo de Markdown a PDF.

Subir aquí en Classroom el reporte en PDF. No olvides tener el código fuente de tu reporte (archivo markdown) y los archivos que se usaron dentro del repositorio de la materia (Página estática) en tu portafolio (repositorio en Github).



# Desarrollo de la practica
## Sesión 1:
¿Qué es Markdown?

Markdown es un lenguaje de marcado ligero creado por John Gruber (2004) que permite escribir texto con formato de manera sencilla usando caracteres especiales.

Su objetivo es:
Ser fácil de leer
Ser fácil de escribir
Convertirse fácilmente a HTML, PDF u otros formatos


Es ampliamente utilizado en:
- Documentación técnica
- Repositorios en GitHub
- Blogs
- Portafolios
- README.md


¿Cómo se utiliza?

Se escribe en archivos con extensión .md

Ejemplo:

```
reporte.md
README.md
```

Puede editarse en:
- VS Code
- Notepad++
- GitHub directamente
- Typora
- Obsidian
- Sintaxis básica de Markdown

### Encabezados
``` 
# Título 1
## Título 2
### Título 3
```

### Negritas y cursivas

```
**Negrita**
*Cursiva*
```

### Listas
```
Lista ordenada:
1. Elemento
2. Elemento
Lista no ordenada:
- Elemento
- Elemento
```

### Enlaces
```
[Texto del enlace](https://ejemplo.com)
Imágenes
![Texto alternativo](imagen.png)
```

### Código
```
Código en línea:
`codigo`
Bloque de código:
```python
print("Hola mundo")
```

### Tablas

```markdown
| Nombre | Edad |
|--------|------|
| Oscar  | 20   |
```

## Sesión 2:

¿Qué es Git?

Git es un sistema de control de versiones distribuido creado por Linus Torvalds (2005).
Permite:
- Guardar versiones del proyecto
- Trabajar en equipo
- Recuperar versiones anteriores
- Llevar historial de cambios


¿Qué es GitHub?

GitHub es una plataforma en la nube que permite alojar repositorios Git.
Permite:
- Subir proyectos
- Trabajar colaborativamente
- Publicar páginas web (GitHub Pages)
- Automatizar tareas (GitHub Actions)


Comandos esenciales de Git:

- Inicializar repositorio
```
git init
```
- Ver estado
```
git status
```
- Añadir archivos
```
git add .
```
- Guardar cambios
```
git commit -m "Primer commit"
```
- Conectar con GitHub
```
git remote add origin https://github.com/usuario/repositorio.git
```

- Subir cambios
```
git push -u origin main
```

Cómo crear un repositorio en GitHub
1. Ir a github.com
2. Clic en "New Repository"
3. Asignar nombre
Público
4. Crear repositorio

Luego conectar desde terminal.

## Sesión 3:
¿Qué es Hugo?

Hugo es un generador de sitios web estáticos escrito en Go.

Permite:
- Crear blogs
- Crear portafolios
- Generar páginas rápidas
- Convertir Markdown en HTML automáticamente


¿Qué es GitHub Actions?

GitHub Actions es un sistema de automatización (CI/CD) que permite:
- Compilar proyectos
- Ejecutar pruebas
- Publicar sitios automáticamente

Crear sitio con Hugo:

Instalar Hugo

Windows:
```
choco install hugo
```
Crear nuevo sitio
```
hugo new site portafolio
cd portafolio
```
Agregar tema
```
git init
git submodule add https://github.com/theNewDynamic/gohugo-theme-ananke.git themes/ananke
```
Editar:
```
config.toml
```
Añadir:
```
theme = "ananke"
```
Crear contenido
```
hugo new posts/my-new-hugo-site.md
```
Copiar el contenido del reporte.md dentro.

Probar localmente
```
hugo server
```
Abrir:
```
http://localhost:1313
```
Subir todo a GitHub

Configurar GitHub Actions, crear archivo:
```
.github/workflows/hugo.yml
```

Activar GitHub Pages
1. Ir a Settings
2. Pages
3. Branch: gh-pages
4. Guardar


## Conclusiones

La practica permitio comprender el flujo de desarrollo y publicacion de proyectos utilizando herramientas de la industria del software. Se integraron conocimientos teoricos y practicos que fortalecen competencias fundamentales para los profesionales en areas tecnologicas.

El uso de markdown facilito la creacion de documentacion estructurada, clara y profesional, demostrando la importancia de escribirla de forma organizada y portable. Esto es esencial para el desarrollo de reportes, documentacion de proyectos y presentacion de portafolios digitales.

El aprendizaje de Git y GitHub introdujo el concepto de control de versiones, permitiendo comprender el como gestionar cambios, mantener un historial de modificaciones y trabajar con repositorios remotos en la nube. El dominio de estos conceptos no solo mejora la organizacion del trabajo individual, sino que tambien sienta las bases para el trabajo colaborativo en equipos de desarrollo.

La integracion de Hugo y GitHub Actions permitio combinar documentacion y automatizacion para generar y publicar un sitio web estatico. Este proceso mostro como las herramientas modernas permiten transformar archivos Markdown en paginas web profesionales, automatizando su despliegue.

El resultado de la pracica: un repositorio en GitHub, un sitio publicado en GitHub pages representan un primer paso en la construccion de un portafolio profesional que podra ampliarse a lo largo de la formacion academica y profesional.

[Repositorio/Portafolio de GitHub](https://github.com/Kuro991/proyectos-PdP)

[Pagina estatica en GitHub Pages](https://kuro991.github.io/proyectos-PdP/)
