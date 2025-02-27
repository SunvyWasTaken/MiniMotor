# Welcome to MiniMotor.
## What is MiniMotor?
- **MiniMotor** first came out of a prototype, I was making to learn **OpenGL**.
  > So there is actully like 3 more version of this Engine but we are not gonna talk about them.
- I want to keep learning and progress so **MiniMotor** is my sandbox to test things out.
  > I'm unemployed so this project keep me busy and ~~is~~ *(will be)* my Showcase.
- The project is base from the [Game Engine](https://youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&si=tWydNMZS-z3zxjo2) serie from the cherno.
  > Huge thanks to him. For giving me the motivation to learn graphic rendering.
## How to Start
### Clone
Start by clonning the main branch somewhere on your computer.
### Build Solution
To build the solution you can directly launch the **vcpkgInstall.bat**
> Or you can do the following command line on GitBash, powershell or directly Cmd (assuming you have git install)
```cmd
git clone https://github.com/microsoft/vcpkg.git
```
```cmd
cd vcpkg && bootstrap-vcpkg.bat -disableMetrics
```
```cmd
vcpkg install
```
```cmd
cd ..
```
```cmd
cmake -DCMAKE_TOOLCHAIN_FILE=%cd%/vcpkg/scripts/buildsystems/vcpkg.cmake  -S %cd% -B %cd%/Build
```
> You can directly found explanation [Here](https://learn.microsoft.com/fr-fr/vcpkg/get_started/get-started?pivots=shell-cmd).
### Run
You will found the solution on the build folder who was create by CMake.
Now you can **Build/Run** the code.
### Movement
You can move with your typical **WASD**, Go Up and Down with **QE**, look around with the **mouse** and close the window with **Escape**
## Third Party
- **GLFW**
- **OpenGL** *(including : glad)*
- **Vulkan** *(soon)*
- **Entt**
- **GLM**
> I wanted to add **ImGui** but I run into a issues with the definition of the function to **Init ImGui with OpenGL** wasn't define which is weird cause I was downloading the last version of **ImGui** with the correct features with vcpkg. So, I set it aside.
> I also wanted to add **Assimp** but couldn't for the same reason of **ImGui**.

# Sandbox
For the sandbox at first I wanted a physical solar system with the calcul of force and gravitation to predict movement from the aster. But i quickly released that if I wanted to be accurate I would need a better ~~computer~~ *(brain)*. I couldn't figure it out how to do it properly and I wanted something quick to come out of this project so I just use the Astronomical unit and supossed that every aster orbit at a perfect cercle. I know it's not accurate but *if it works* ¯\\_(ツ)_/¯. 
 
