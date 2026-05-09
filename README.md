# BackMIR

BackMIR 是一款仿热血传奇风格的 2D MMORPG，包含完整的客户端与服务端源码。本仓库是作者早年工作时的代码，以开源存档形式发布。

## 仓库结构

```
backmir/
├── BMClient/        # Windows 游戏客户端（DirectX 8 / HGE）→ BackMir.exe
├── BMServer/        # 游戏服务端（libevent / IOCP）→ GameSvr.exe
├── CommonModule/    # 客户端与服务端共享模块（ByteBuffer、GamePacket 等）
└── thirdparty/      # 第三方依赖
```

> `CommonModule/` 是从两侧调用点反向重建的产物，原始仓库未提供该目录。

## 技术栈

| 模块 | 技术 |
|------|------|
| 客户端渲染 | HGE（DirectX 8.1） |
| 客户端 UI | DuiLib（XML 布局） |
| 服务端网络 | libevent / IOCP |
| 脚本 | LuaJIT + tolua++ |
| 序列化 | Protobuf + 自研 ByteBuffer |
| 数据库 | SQLite3（异步写回） |
| 音频 | FMOD Ex |
| 编译工具 | Visual Studio 2013（VS2008/2010 解决方案保留） |

## 构建

### 前置条件

1. **Visual Studio 2013**
2. **DEVLIB_DIR** 环境变量，指向预编译第三方库目录。

   客户端依赖：DuiLib、HGE、DirectX 8.1、FMOD Ex、SQLite3、zlib、ZipArchive、Protobuf、libcurl、LuaJIT、tolua++、FastDelegate

   服务端依赖：libevent、pthreads-w32、glog、SQLite3、zlib、ZipArchive、Protobuf、libcurl、LuaJIT、FastDelegate、vld（仅 Debug）

   各库下载与配置方式见 [DEVLIB_DOWNLOAD.md](DEVLIB_DOWNLOAD.md)，或直接运行 `setup_devlib.bat` 一键下载。

3. **CommonModule/**（共享模块）需与 `BMClient/` 和 `BMServer/` 同级。

### 编译步骤

**客户端** - TODO: 目前还存在编译问题

```
打开 BMClient/BackMir13.sln
生成 → 重新生成解决方案

```

**服务端**

```
# 进入目录
cd backmir/

# 2. CMake 使用当前目录 (.) 作为源，指定子目录作为构建路径
cmake -S . -B build_test

# 3. 进入 build_test 并编译
cd build_test && make
```

> 依赖通过 `Import/ImportModule.cpp` 中的 `#pragma comment(lib, ...)` 声明，而非 vcxproj 属性页。添加新依赖时编辑该文件。

### 清理

```bat
BMClient\clearproj.bat   # 清理 debug/、release/、.ncb/.sdf
BMServer\clearproj.bat
```

## 运行

### 服务端

```
../BackMir/Bin/GameSvr "listenip=127.0.0.1:8400 loginsvr=127.0.0.1:8201 outerip=127.0.0.1:8400 serverid=1"
BackMIR GameSvr (Linux build)
Server initialized. Press Ctrl+C to stop.
```

### 客户端

TODO:



### 运行时 DLL

以下 DLL 需与 `BackMir.exe` 放在同一目录：

```
fmodex.dll      # FMOD 音频
lua51.dll       # LuaJIT
sqlite3.dll     # SQLite3
zlibwapi.dll    # zlib
libcurl.dll     # libcurl（动态链接时）
```

## 架构概览

### 客户端（BMClient/）

以 HGE 为渲染壳，`MirGame : SGameBase` 是唯一的游戏对象（全局指针 `pTheGame`）。

| 目录 | 职责 |
|------|------|
| `LoginScene/` | 登录、角色选择场景 |
| `GameScene/` | 游戏内场景：地图、玩家、怪物、NPC、魔法特效 |
| `GameDialog/` | 所有游戏内 UI 对话框（背包、属性、聊天、商店等） |
| `DuiWnd/` | DuiLib 窗口（预连接窗口、辅助面板等） |
| `Net/` | ClientSocket + PacketHandler + PacketQueue |
| `Astar/` | A* 寻路 |
| `Common/` | 渲染工具、地图数据、GUI 基础组件、文件格式加载器 |

启动流程：`LoadGlobalLuaConfig` → `BMPreConnWnd`（模态）→ 构造 `MirGame` → `Init()` → `Exec()`

### 服务端（BMServer/）

| 目录 | 职责 |
|------|------|
| `IOServer/` | 网络层，封装 libevent / IOCP |
| `CMainServer/` | 顶层服务编排，持有网络引擎、世界、数据库 |
| `GameWorld/` | 游戏模拟：场景、对象、AI、伤害计算、DB 写回缓冲 |
| `WinShell/` | MFC 控制面板（服务器管理 UI） |
| `Net/` | 与对端服务器共享的 ClientSocket + Packet 头文件 |

数据库层异步：游戏逻辑将变更推入 `GameDbBuffer`，`DBThread` 在后台线程刷写 SQLite。

### 共享层（CommonModule/）

- `ByteBuffer` — 小端、紧凑、无对齐 padding；`std::string` 采用 `[uint16 length][bytes...]`
- `GamePacket` — Protobuf + ByteBuffer 帧格式，opcode 表与 `BMServer/tolua/GamePacket.pkg` 对齐
- `loginsvr.proto` — 反向重建版，Tag 从 1 重新分配，**与历史部署版本不二进制兼容**

## Lua 脚本绑定

客户端和服务端均通过 tolua++ 向 Lua 暴露 C++ 类。

- 绑定声明：`BMClient/tolua/*.pkg` / `BMServer/tolua/*.pkg`
- 重新生成绑定：在对应目录运行 `generate.bat`，会输出 `luaClient.cpp` / `luaServer.cpp`
- **不要手动编辑生成的 `.cpp` 文件**，修改 `.pkg` 后重新生成

## 注意事项

- 源文件编码为 GBK / Shift-JIS（中文注释）。不要将注释按 UTF-8 重新解释，否则会损坏文件。
- `CommonModule/` 缺失时，构建报错 `..\..\CommonModule\<file>.h not found`，需补充共享模块，而非尝试重建头文件。
- Release 构建可选代码保护：`_THEMIDA_`（Themida）和 `_SHIELDEN_`（Shielden）预处理宏，普通 Release 构建关闭即可。

## 仓库地址

原仓库地址：https://github.com/sryanyuan/BMServer / https://github.com/sryanyuan/BMClient/commits/master/

| 仓库 | 地址 |
|------|------|
| 主仓库 | https://github.com/AcSully/backmir |
| 客户端（BMClient） | https://github.com/AcSully/BMClient |
| 服务端（BMServer） | https://github.com/AcSully/BMServer |

BMClient 和 BMServer 以 git submodule 形式引入主仓库。克隆时需加 `--recurse-submodules`：

```bash
git clone --recurse-submodules https://github.com/AcSully/backmir.git
```

## 许可

本仓库以开源存档形式发布，代码质量参差不齐（作者自注：刚毕业时写的，现在看起来惨不忍睹）。欢迎提 Issue 或 PR。
