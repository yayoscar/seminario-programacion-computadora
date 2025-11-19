# 🎓 Presentación Académica - Simulador de CPU y Ensamblador

## 📖 Descripción

Presentación profesional de nivel licenciatura que explica la arquitectura, diseño e implementación de un simulador de CPU de 16 bits con ensamblador en español.

## 🚀 Cómo Abrir la Presentación

### Opción 1: Navegador Web (Recomendado)

```bash
# Desde la raíz del proyecto
cd docs
python3 -m http.server 8000
```

Luego abre en tu navegador: `http://localhost:8000/presentacion.html`

### Opción 2: Abrir Directamente

Simplemente abre el archivo `docs/presentacion.html` con tu navegador favorito (Chrome, Firefox, Edge).

## ⌨️ Controles de la Presentación

| Tecla | Acción |
|-------|--------|
| **→** o **Espacio** | Siguiente slide |
| **←** | Slide anterior |
| **Home** | Primera slide |
| **End** | Última slide |
| **ESC** o **O** | Vista general (overview) |
| **S** | Modo presentador (con notas) |
| **F** | Pantalla completa |
| **B** o **.** | Pantalla en negro |

## 📑 Contenido de la Presentación

### Parte I: Fundamentos (Slides 1-6)
1. **Portada** - Título y contexto del proyecto
2. **Agenda** - Estructura de la presentación
3. **Introducción y Motivación** - Objetivos y características
4. **Arquitectura del Sistema** - Von Neumann, registros, memoria
5. **Formato de Instrucción** - Estructura de 16 bits
6. **Conjunto de Instrucciones** - Tabla completa del ISA

### Parte II: Implementación (Slides 7-11)
7. **Ensamblador de Dos Pasadas** - Proceso de traducción
8. **Código del Programa Ejemplo** - Código fuente y código máquina
9. **Análisis de la Ejecución** - Traza y métricas
10. **Estado Final de la CPU** - Registros y flags
11. **Arquitectura del Software** - Estructura del código

### Parte III: Contexto y Futuro (Slides 12-15)
12. **Comparación con Arquitecturas Reales** - ARM, RISC-V
13. **Trabajo Futuro** - Compilador C y funciones recursivas
14. **Conclusiones** - Resumen de logros
15. **Referencias y Recursos** - Bibliografía

## 🎨 Tecnologías Utilizadas

- **[Reveal.js](https://revealjs.com/)** - Framework de presentaciones HTML5
- **[Tailwind CSS](https://tailwindcss.com/)** - Framework de estilos utility-first
- **[Highlight.js](https://highlightjs.org/)** - Resaltado de sintaxis de código

## 📊 Características de la Presentación

✅ **Diseño Moderno** - Gradientes, tarjetas, animaciones suaves
✅ **Responsive** - Se adapta a diferentes tamaños de pantalla
✅ **Código Resaltado** - Sintaxis coloreada para mejor legibilidad
✅ **Tablas Interactivas** - Información organizada y clara
✅ **Gráficos Visuales** - Diagramas de arquitectura y flujo
✅ **Estadísticas en Vivo** - Métricas del sistema destacadas

## 🎯 Audiencia Objetivo

- Estudiantes de Licenciatura en Ciencias de la Computación
- Profesores de Arquitectura de Computadoras
- Desarrolladores interesados en diseño de ISA
- Investigadores en educación computacional

## 🖼️ Capturas de Pantalla

La presentación incluye:
- Portada con degradado profesional
- Tablas comparativas con arquitecturas reales
- Diagramas de flujo del pipeline
- Código fuente con resaltado de sintaxis
- Análisis de ejecución paso a paso
- Métricas de rendimiento visuales

## 💡 Consejos para la Presentación

1. **Practica la navegación** - Familiarízate con los controles
2. **Usa el modo presentador** - Presiona `S` para ver notas
3. **Vista general** - Presiona `ESC` para ver todas las slides
4. **Timing** - ~2-3 minutos por slide = ~40-45 minutos total
5. **Interacción** - Usa las animaciones para mantener atención

## 🔧 Personalización

Para personalizar la presentación, edita `docs/presentacion.html`:

### Cambiar colores
```css
/* Busca las clases de Tailwind */
text-blue-400  → text-purple-400
bg-slate-800   → bg-gray-900
```

### Cambiar tema
```javascript
// En la configuración de Reveal.js
Reveal.initialize({
    theme: 'black', // Opciones: black, white, league, beige, sky, night, serif, simple, solarized
    ...
});
```

### Agregar nuevos slides
```html
<section>
    <h2>Tu Título</h2>
    <p>Tu contenido aquí</p>
</section>
```

## 📱 Exportar a PDF

Para crear un PDF de la presentación:

1. Abre la presentación en Chrome
2. Agrega `?print-pdf` a la URL: `presentacion.html?print-pdf`
3. Abre el diálogo de impresión (Ctrl+P)
4. Selecciona "Guardar como PDF"
5. Ajusta márgenes a "Ninguno"
6. Guarda el archivo

## 🤝 Contribuciones

Esta presentación es parte del proyecto académico. Para sugerencias o mejoras:

1. Revisa la presentación completa
2. Identifica áreas de mejora
3. Propón cambios específicos
4. Mantén el estilo profesional y académico

## 📄 Licencia

Esta presentación es parte del proyecto educativo del Seminario de Programación de Computadora.

---

**Última actualización:** 15 de Noviembre de 2025

**Versión:** 1.0

**Contacto:** Proyecto de Seminario - Programación de Computadora
