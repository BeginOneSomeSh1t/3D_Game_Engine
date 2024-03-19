# 3D_Game_Engine
Simple 3d game engine.

Here is a sample README file for a 3D game engine written in C++ using DirectX 11:

# DirectX 11 3D Game Engine

## Description

This project is a 3D game engine written from scratch in C++ using the DirectX 11 graphics API. The goal was to create a foundation for building 3D games by implementing the core components and systems needed in a game engine.

Some key features include:

- DirectX 11 rendering pipeline
- Shader loading and compiling 
- Model loading (custom format)
- Texturing and materials
- Basic lighting (directional light)
- Keyboard/mouse input
- 3D camera
- Simple scene graph

The engine was built as an educational project to better understand modern graphics programming and the architecture of a game engine. It provides a starting point to expand on for creating a complete game.

## Getting Started

### Prerequisites

- Windows 10 
- Visual Studio 2019
- Windows 10 SDK
- DirectX 11

## Engine Architecture

The main components of the engine include:

- **GraphicsEngine**: Initializes DirectX, creates the rendering pipeline, and handles the core rendering loop
- **InputSystem**: Processes keyboard and mouse input events 
- **SceneGraph**: Basic hierarchy for managing entities in the 3D scene
- **Mesh**: Loads and renders 3D models 
- **Texture**: Loads and applies 2D textures to meshes
- **Shader**: Loads, compiles and binds vertex/pixel shaders
- **Camera**: Manages 3D camera transform and view/projection matrices

The engine follows a simplified Entity-Component-System (ECS) architecture where the Scene contains a collection of Entities, each holding transform data and any graphics components like Mesh, Texture, etc.

## Future Work

Some planned features and improvements include:

- Physically based rendering (PBR) shaders
- Shadow mapping 
- Post-processing effects
- Skeletal animation system
- Lua scripting for gameplay
- Editor GUI 

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- DirectX Tutorial Resources:
  - [DirectX 12 Programming Guide - Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/direct3d12/directx-12-programming-guide)
  - [DirectX Tutorial - 3D Game Engine Programming](https://www.youtube.com/playlist?list=PLqCJpWy5Fohd3S7ICFXwUomYW0Wv67pDD)

- Helpful Libraries Used:
  - [DirectXTK](https://github.com/microsoft/DirectXTK) - DirectX 11 utility library 
  - [Assimp](https://github.com/assimp/assimp) - Open asset import library for loading 3D models
