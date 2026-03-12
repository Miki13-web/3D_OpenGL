<h1 align="center">Minecraft 3D Scene (OpenGL & C++)</h1>

<p align="center">
<i>An interactive 3D scene inspired by the popular game Minecraft.This project was built from scratch using modern OpenGL to demonstrate fundamental and advanced computer graphics techniques.</i>
</p>

---
## About the project

We chose a scene from the popular game Minecraft as the theme for our project.
The model we created depicts a scene from the aforementioned game, featuring a building/house, a tree,
a Creeper that can be moved, a pig's head that can be scaled (zoomed in and out), 
and an animated sun that moves across the sky, illuminating other objects. The speed of the sun's movement can be changed.
The background and sky were created by texturing a cube with skybox graphics. Our project also features camera movement, 
a Phong lighting model, and the ability to enable a Gaussian blur effect.

## 📸 Project Gallery

<p align="center">
  <img src="gif1.gif" width="700" alt="Gameplay Preview">
  <br>
  <i>Dynamic sun lighting and post-processing blur effect in action.</i>
</p>

### Screenshots
<p align="center">
  <img src="TUTAJ_WPISZ_NAZWE_ZDJECIA_1.png" width="45%" alt="Scene View 1">
  <img src="TUTAJ_WPISZ_NAZWE_ZDJECIA_2.png" width="45%" alt="Scene View 2">
</p>

---

## Key Features

* [cite_start]**Custom 3D Engine Architecture:** Object-oriented design separating concerns into distinct classes (VAO, VBO, EBO, Shader, Texture) for clean and maintainable code[cite: 256].
* [cite_start]**FPS Camera System:** Fully controllable perspective camera with mouse look, zoom (scroll), and keyboard movement[cite: 34, 35, 36].
* [cite_start]**Dynamic Phong Lighting:** Realistic lighting model utilizing ambient, diffuse, and specular components[cite: 109, 110]. [cite_start]The scene features an animated sun moving across a SkyBox, dynamically affecting object illumination and sky colors[cite: 5, 109, 176].
* [cite_start]**Post-Processing (Framebuffers):** Implementation of an off-screen Framebuffer Object (FBO) allowing for real-time post-processing, specifically a togglable Gaussian Blur effect[cite: 205, 206, 207].
* [cite_start]**Interactive Entities:** A movable Creeper character [cite: 5, 174] [cite_start]and a dynamically scalable Pig head[cite: 5, 175].

## 💻 Tech Stack

* **Language:** C++
* [cite_start]**Graphics API:** OpenGL 3.3 Core Profile [cite: 10]
* [cite_start]**Libraries:** * `GLFW` - Window creation and input handling [cite: 10]
  * [cite_start]`GLAD` - OpenGL function pointer management [cite: 10]
  * [cite_start]`GLM` - Mathematics (matrices, vectors, transformations) [cite: 38]
  * [cite_start]`stb_image` - Texture loading [cite: 153, 155]

## 🎮 Controls

[cite_start]The application features a comprehensive input system for scene interaction[cite: 97]:

| Action | Input |
| :--- | :--- |
| **Camera Movement** | `W` `A` `S` `D` |
| **Camera Up / Down** | [cite_start]`Space` / `Left Shift` [cite: 35] |
| **Camera Look / Zoom**| [cite_start]`Mouse` / `Scroll` [cite: 36] |
| **Move Creeper** | [cite_start]`Arrow Keys` (Up, Down, Left, Right) [cite: 100, 174] |
| **Scale Pig Head** | [cite_start]`Numpad +` / `Numpad -` [cite: 103, 175] |
| **Toggle Gaussian Blur** | [cite_start]`B` [cite: 104, 207] |
| **Adjust Light Speed** | [cite_start]`+` / `-` [cite: 102] |
| **Exit** | `ESC` |

## 🛠️ Installation & Build

1. Clone the repository:
   ```bash
   git clone [https://github.com/Miki13-web/3D_OpenGL.git](https://github.com/Miki13-web/3D_OpenGL.git)

