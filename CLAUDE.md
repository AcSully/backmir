# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository layout

This repo is the source for **BackMIR**, a Mir2-style 2D MMORPG. It contains two
sibling projects:

- `BMClient/` — Windows game client (DirectX 8 / HGE). Final binary: `BackMir.exe`.
- `BMServer/` — Game server (libevent / IOCP, console + MFC shell). Final binary: `GameSvr.exe`.

Both projects expect a third sibling directory `CommonModule/` (referenced as
`..\CommonModule\...` from the `.vcxproj` files: `ByteBuffer`, `GamePacket`,
`SaveFile`, `SettingLoader`, `DataParser`, `BMHttpManager`, `cJSON`, etc.).
**`CommonModule/` is not in this checkout.** If a build fails on missing
`..\..\CommonModule\<file>.h`, the shared module is the missing piece — flag
it rather than trying to recreate the headers from include sites.

The READMEs note this is old code from the author's first job, kept for archival/
open-source release rather than active maintenance.

## Build

Visual Studio solutions are provided for VS2008 / VS2010 / VS2013 (the `13` suffix
is the canonical one — it has the maintained `.vcxproj`):

- Client: `BMClient/BackMir13.sln` → `BackMir13.vcxproj` (Application, Win32, MBCS)
- Server: `BMServer/BackMirServer13.sln` → `BackMirServer13.vcxproj`

Output directories are **outside the source tree**, in `..\BackMir\Bin` (Release)
and `..\BackMir\BinDebug` (Debug) — both client `BackMir.exe` and server
`GameSvr.exe` land in the same folder, which is treated as the deploy/runtime
root by the executables (see `GetRootPath` usage in `BMClient/BackMir/main.cpp`).

`clearproj.bat` in each project wipes `debug/`, `release/`, and the VS
intellisense cache (`.ncb` / `.sdf`).

### Required environment

- `DEVLIB_DIR` — env var pointing at a prebuilt third-party libs tree. Both
  projects pull headers from `$(DEVLIB_DIR)\Inc\<libname>` (or
  `$(DEVLIB_DIR)\Incvc12\<libname>` for VS2013-specific builds) and libs from
  `$(DEVLIB_DIR)\Libvc12\<libname>`.

  Client deps: DuiLib, hge, DirectX 8.1, fmodex, sqlite3, zlib, ZipArchive,
  protobuf, curl, luajit, tolua++, fastdelegate.
  Server deps: libevent, pthread (pthreads-w32), glog, sqlite3, zlib,
  ZipArchive, protobuf, curl, luajit, fastdelegate, vld (debug only).

  Library linkage is declared via `#pragma comment(lib, ...)` in
  `BMClient/Import/ImportModule.cpp` and `BMServer/Import/ImportModule.cpp`
  rather than the vcxproj — that's the file to edit when adding a dependency.

- Optional code-protection SDKs: `_THEMIDA_` (Themida) and `_SHIELDEN_`
  (Shielden) preprocessor flags in Release. The SDKs ship under
  `BMServer/Themida/` and `BMServer/Shielden/`. Disable both flags for plain
  Release builds.

### Delay-loaded DLLs

The client supports a `_DELAY_LOAD_DLL` build mode (see `WinMain` in
`BMClient/BackMir/main.cpp` and `BMClient/Doc/delayload_dll.txt`). When set, it
calls `SetDllDirectory` to a `deps\` (release) or `deps_d\` (debug) folder
beside the exe — sqlite3, fmodex, duilib, hge, zlibwapi must live there.

### Lua bindings (tolua++)

Both projects expose C++ classes to Lua via tolua++. The `.pkg` files in
`BMClient/tolua/` and `BMServer/tolua/` are the binding declarations; running
`generate.bat` in either folder regenerates the `luaClient.cpp` / `luaServer.cpp`
glue file (which is then compiled into the project). Edit the `.pkg` and
re-run, do not hand-edit the generated `.cpp`. `.pkg.bak` files are stale
backups, ignore them.

## Runtime / launching

The server entry point parses a config string like:

```
listenip=127.0.0.1:8400 loginsvr=127.0.0.1:8201 outerip=127.0.0.1:8400 serverid=1
```

(see `BMServer/login_command.txt`). The client connects via the pre-connect
window (`BMPreConnWnd`) before the main game loop starts.

The client creates `conf\` and `Save\` directories under its install root on
first launch (`CreateGameDirs` in `BMClient/BackMir/main.cpp`).

In **debug** the client looks for UI XML in `../BackMirClientVC12/UI` relative
to the exe; in **release** it uses `./UI`. Keep this path quirk in mind when
running a debug build — it's looking up one level for a sibling source
checkout, not in the install dir.

## Architecture

### Client (`BMClient/`)

The game is built on **HGE** (a 2D engine over DirectX 8). `SGameBase` is the
HGE app shell; `MirGame : SGameBase` (`BMClient/BackMir/BackMir.{h,cpp}`) is the
single game object — `pTheGame` is a global pointer to it.

Major subsystems live in their own folders. Each is largely self-contained
and references the others by include path:

- `LoginScene/` — login + character select scenes.
- `GameScene/` — in-game scene: map, player, monsters, NPCs, magic effects,
  textures (`SIB`/`SPB`/`Wil` are the legacy Mir asset formats — see
  `Common/SIBFile`, `SPBFile`, `SWilFile`).
- `Common/` — rendering helpers, map data, GUI primitives, file format
  loaders, global functions. Note: `GfxFont.cpp1` / `GfxFont.h1` /
  `ObjectData.h1` are dead snapshots — current code is in the non-`1` files.
- `GameDialog/` — every in-game UI dialog (bag, attrib, chat, store, etc.).
  All inherit from `GameDlgBase`.
- `DuiWnd/` — DuiLib-based windows (the pre-connect window, assist panes,
  donate/password dialogs).
- `UI/` — XML layouts + `.uiproj` for the DuiLib UIs in `DuiWnd/`.
- `Net/` — `ClientSocket` + `PacketHandler` + `PacketQueue`. Game packets
  are routed through `GamePacketHandler`. Packet structs come from
  `..\CommonModule\GamePacket.*`.
- `Astar/` — pathfinding (`SAstar`).
- `Widget/` — small reusable UI widgets.
- `TinyXML/` — vendored TinyXML.
- `tolua/` — Lua binding generator (see Lua section above). The runtime
  Lua engine is `LuaClientEngine` in `BackMir/`.
- `Import/ImportModule.cpp` — single TU that holds `#pragma comment(lib,...)`
  for every external dependency.

The startup sequence is in `BMClient/BackMir/main.cpp`:
`LoadGlobalLuaConfig` → DuiLib `BMPreConnWnd` modal → if user pressed connect,
construct `MirGame`, `Init()`, `Exec()`. Game mode is one of `g_eGameMode`
values (`GM_LOGIN`, `GM_NORMAL`, etc.) decided by the pre-connect dialog.

### Server (`BMServer/`)

- `IOServer/` — networking layer. `IOServer` wraps libevent (or IOCP via
  `bUseIOCP`) and exposes accept/recv/disconnect/timer callbacks.
  `NetbaseWrapper` is an older shim around the same idea (see commented-out
  alternate path in `IOServer/main.cpp`). `IOServer` is the live one.
- `CMainServer/` — top-level server orchestrator (`CMainServer`, singleton via
  `GetInstance()`). Owns the network engine, the world, and the database.
  `CMainServer_Deprecated.cpp` holds legacy paths kept compiled — don't
  delete without grepping callers.
- `GameWorld/` — the actual game simulation: scenes (`GameScene`,
  `GameInstanceScene`), `GameSceneManager`, objects (`HeroObject`,
  `MonsterObject`, `NPCObject`, `MonsterTemplateObject`), AI logic
  (`MonsterLogic/`), damage calc (`HumDamCalc`, `WeightCalc`, `DamagePool`),
  DB write-back buffer (`GameDbBuffer`, `DBThread`, `DBDropDownContext`),
  scripting hooks (`LuaServerEngine`, `LuaItemHelper`), and event dispatch
  (`WorldEventDispatcher`, `SceneEvent`).
- `WinShell/` — MFC dialog-based control panel (`MainFrm`, `ServerDlg`,
  `ConfigDlg`, etc.). The exe is an MFC app whose UI shells the underlying
  CMainServer.
- `Interface/ServerShell.h` — abstract bridge between `CMainServer` and the
  MFC shell so the simulation layer doesn't depend on MFC.
- `Net/` — `ClientSocket` + `Packet` headers shared with peer servers.
- `common/` — small headers shared inside server only (`shared.h`, `glog.h`,
  `cmsg.h`, `view.h`, `memleak.h`).
- `tolua/` — server-side Lua bindings (see Lua section).
- `Import/ImportModule.cpp` — server-side `#pragma comment(lib,...)` hub.

`CMainServer::GetInstance()` is the global accessor; sub-systems reach it
directly. The DB layer is asynchronous: gameplay code pushes mutations into
`GameDbBuffer`, and `DBThread` flushes them to SQLite on a background thread.

### Cross-cutting

- **Packet format** is shared via `CommonModule/GamePacket.*` (protobuf +
  hand-rolled `ByteBuffer` framing). The client serializes via
  `SendBufferToGS` / `SendBufferToLS` / `SendProto` (see `BackMir.h`); the
  server dispatches in `GameWorld/HeroObject_Packet.cpp` and packet-routing
  files in `CMainServer/`.
- **Encoding**: source files are GBK / Shift-JIS-ish (Chinese comments).
  Treat existing comments as opaque bytes — do not "fix" mojibake by
  reinterpreting them as UTF-8, you'll corrupt the file.
- **Config defines** worth knowing:
  - `_NET_GAME_` (client) — networked vs. local-only build.
  - `_BIN_PATH` — runtime paths are resolved relative to the exe's bin dir.
  - `_LUAJIT_` (server) — link luajit instead of stock lua.
  - `_LIB` (server `IOServer`) — when set, `IOServer/main.cpp` is excluded so
    `IOServer` builds as a static lib for `CMainServer` to link against.
    The standalone `IOServer.exe` (echo server test harness) only builds
    when `_LIB` is unset.
