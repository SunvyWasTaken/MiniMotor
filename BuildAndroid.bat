set ANDROID_NDK_HOME=%cd%/ndk/android-ndk-r27

cmd /c "cd vcpkg && bootstrap-vcpkg.bat && vcpkg install --triplet x64-android"

Pause