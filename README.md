# PBR-DX11
Tiny PBR And IBL Renderer which implement with DirectX11
# 
I have Found A lot of IBL are Implementated use OpenGL and the rare respository I found is use equirectangular dds to create skybox and has some compile error and file path found error.
this project is modify form https://github.com/JJJohan/PBR.
I have modify this project to use Premake to generate and Add CubeMap support to debug our IBL Implementation in DirectX11. which I can help to debug your IBL Implementation in Direcx11

# Windows Build
just run the Win-GenerateProjects.bat, Open the PBR-IBL.sln

# Debug Result
roughness = 0, metallic = 0, the directional light is rotate Z with 45
