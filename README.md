# GeoTool
[![Build and Release](https://github.com/romaricbeltran/GeoTool/actions/workflows/build.yml/badge.svg)](https://github.com/romaricbeltran/GeoTool/actions/workflows/build.yml)

🛠️ 3D visualization tool written in C++ with OpenGL & ImGui.  
📦 Built with CMake, works on Windows with MSVC.

## ✅ Build (Windows / MSVC)

```bash
cmake -S . -B build -G "Visual Studio 17 2022" && cmake --build build --config Release
```

## 🧪 Run tests

```bash
ctest --test-dir build --output-on-failure
```

## 📷 Preview

(Coming soon)

## 🔧 Stack
- C++20
- OpenGL 3.3 Core
- GLFW / GLAD / ImGui / GLM
- GoogleTest
- CMake 3.20+
- GitHub Actions (CI/CD)
