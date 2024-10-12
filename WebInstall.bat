set currentPath=%cd%
if exist %currentPath%/emsdk(
	ECHO Update emsdk
	cmd /c "cd emsdk && git pull"
	) else (
	cmd /c git clone https://github.com/emscripten-core/emsdk.git
)

cd emsdk

emsdk install latest
emsdk activate latest

cd %currentPath%/vcpkg

git pull

bootstrap-vcpkg.bat -disableMetrics

vcpkg install --triplet wasm32-emscripten

cd %currentPath%

cmake -S %currentPath% -B %currentPath%/build-wasm -G Ninja -DCMAKE_TOOLCHAIN_FILE=%currentPath%/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=wasm32-emscripten
