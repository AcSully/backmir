# CommonModule (Reconstructed)

`CommonModule/` 是 BMClient 与 BMServer 的共享层。**当前目录是从两侧调用点
反向重建的产物**——原始仓库未提供 `CommonModule/`。

## 状态

按计划 `C:\Users\Administrator\.claude\plans\1-2-ubuntu-debian-cheerful-marshmallow.md`
分阶段重建。每个文件第一行注释会标明：

```
// [reconstructed] 重建于 YYYY-MM-DD —— 来源调用点：<file:line, file:line, ...>
```

或对于公开第三方文件：

```
// [vendored] <upstream URL> @ <version/commit>
```

未带任何标注的文件视为尚未重建（不应入仓）。

## 协议兼容性

- **`loginsvr.proto` 是反向重建版**——Tag 编号从 1 起重新分配，与历史已部署
  服务器的 `.pb.cc` **不二进制兼容**。本仓库重建后的客户端必须连本仓库重建后
  的服务器。
- `ByteBuffer` 字节序约定：小端、紧凑写入（无对齐 padding）、`std::string`
  采用 `[uint16 length][bytes...]` 形式。这是从 `BMServer/Net/PacketHandler.cpp`
  与 `BMClient/Net/ClientSocket.cpp` 用法反推的，详见 `ByteBuffer.h` 头注释。
- `GamePacket` opcode 表与 `BMServer/tolua/GamePacket.pkg` 对齐。

## 子目录约定

`CommonModule/` 是平铺的（与原仓库 `BMServer/BackMirServer13.vcxproj` 中的
`..\CommonModule\<file>` 引用形式一致）。不要新建子目录，避免破坏 .vcxproj
里的 `<ClCompile Include="..\CommonModule\xxx.cpp" />` 路径。
