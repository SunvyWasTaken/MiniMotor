# Welcome to MiniMotor.
## What is MiniMotor?
- **MiniMotor** first came out of a prototype, I was making to learn **OpenGL**.
  > So there is actully like 3 more version of this Engine but we are not gonna talk about them.
- I want to keep learning and progress so **MiniMotor** is my sandbox to test things out.
  > I'm unemployed so this project keep me busy and ~~is~~ *(will be)* my Showcase.
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
 
