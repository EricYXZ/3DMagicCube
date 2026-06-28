# Pocket Cube 0.0.1

基于 C++、OpenGL/freeglut/GLEW 和 EasyX 的二阶魔方课程设计项目。程序会打开一个 EasyX 操作说明窗口和一个 OpenGL 魔方窗口，支持键盘旋转、鼠标调整视角、随机打乱和自动复原。

## 环境

- Windows
- Visual Studio 2022 Community 或 Build Tools，安装 MSVC v143
- Windows 10 SDK 10.0.18362.0 或更新版本
- EasyX，已安装到 Visual Studio 的 `VC\Auxiliary\VS` 目录
- VS Code，推荐安装 Microsoft C/C++ 扩展

本仓库保留了旧工程依赖的 `packages/nupengl.*` NuGet 包，因为 `.vcxproj` 直接导入其中的 OpenGL/freeglut/GLEW 目标文件。
Debug 配置会链接 MSVC Debug CRT，`.vscode/launch.json` 已为当前本机补充 VS 2022 的 Debug CRT 路径。

## 用 VS Code 运行

1. 用 VS Code 打开仓库根目录。
2. 按 `Ctrl+Shift+B` 执行默认任务 `build debug x64`。
3. 按 `F5` 运行 `Pocket Cube (Debug x64)`。

调试配置会先构建 `Pocket Cube.sln`，再运行 `x64/Debug/pocket cube.exe`，工作目录设置为 `GLtest`，这样程序可以找到 `pic.bmp` 和 `assets/Show_How_Use.jpg`。
构建任务实际调用 `scripts/build-debug-x64.cmd`，避免 Windows 路径中空格造成命令解析失败。

## 操作

- `U D F B R L X Y Z` 及对应小写字母：旋转魔方或整体视角
- 鼠标左键、中键、右键：调整观察视角
- `S`：随机打乱
- `Enter`：自动复原

## 项目结构

- `Pocket Cube.sln`：Visual Studio 解决方案
- `GLtest/Pocket Cube 0.0.1.cpp`：主源码
- `GLtest/pic.bmp`：OpenGL 纹理
- `GLtest/assets/Show_How_Use.jpg`：EasyX 操作说明图片
- `.vscode/`：VS Code 构建、调试和 IntelliSense 配置
