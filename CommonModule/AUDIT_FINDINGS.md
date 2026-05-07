# CommonModule 审计发现（待修复）

随 Phase 1.x 推进发现的不一致问题汇总。**这些不修，BMServer/BMClient 编译会报错。**

## 1. `PkgObjectActionNot` 字段定义错误（高优先级）

**位置**：`GamePacket.h:602-611`

**当前定义**（用户外部工具生成）：
```cpp
struct PkgObjectActionNot : public PacketHeader
{
    unsigned int dwID;
    BYTE         bAction;
    WORD         wPosX;
    WORD         wPosY;
    BYTE         bDir;
    DWORD        dwParam;
};
```

**调用点要求**（`BMClient/Common/GameRenderObject.cpp:1252-1300+`）：
```cpp
PkgObjectActionNot not;
not.uTargetId = _not.uTargetId;   // 需要 uTargetId 字段
not.uAction = ACTION_TURN;        // 需要 uAction 字段
not.uParam0 = MAKELONG(...);      // 需要 uParam0
not.uParam1 = ...;                // 需要 uParam1
```

**正确定义应为**：
```cpp
struct PkgObjectActionNot : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int uAction;     // 或 BYTE，调用点既有 ACTION_TURN 这类常量也有 _not.cExtAction(char)
    DWORD        uParam0;
    DWORD        uParam1;
};
```

**对策**：`GamePacket.cpp` 中 `PkgObjectActionNot` 的 `operator<<`/`operator>>` 序列化也需相应更新——按 `uTargetId/uAction/uParam0/uParam1` 顺序读写。

---

## 2. `bitop.h` 与 `GDefine.h` 中 flag 宏重复（低优先级）

`bitop.h` 当前空壳，`TEST_FLAG_BOOL/SET_FLAG/CLR_FLAG` 全部由 `GDefine.h` 定义。
功能正确——但若未来 CommonModule 内某文件只 include `bitop.h` 不 include `GDefine.h`，
则会缺少这些宏。**建议把 flag 宏从 `GDefine.h` 移到 `bitop.h`**，由 `GDefine.h`
include `bitop.h` 引入。本次先不动，编译跑通后再清理。

---

## 3. 待 Phase 1.6 重检的字段

`StateController.{cpp,h}` 在用户生成时未对照 `OfflineSellSystem`、`StoveManager` 等
消费者验证。Phase 1.6 重建那些模块时若发现 `m_xState` 风格调用而 StateController 不
支持，回过来加方法。

---

## 4. `loginsvr.proto` Tag 编号假设

我们从 1 开始顺序分配。若用户后续找到原 `.pb.h`，需要逐字段比对 Tag——否则历史
存档中携带的 protobuf 消息会反序列化失败。**已在 README 中记录此风险。**

---

修复执行顺序建议：
1. 先做 Phase 1.4-1.6 全部文件的初稿（让模块清单完整）。
2. 然后做 Phase 1 验收：在 VS2013 下点编译。
3. 编译错误就是真正的修复 backlog——AUDIT_FINDINGS.md 中记录的与编译器报错合并。
