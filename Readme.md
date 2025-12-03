与其规定几点几分必须做什么，不如设定**每日核心任务块（Deep Work Blocks）**。你根据当天的课表，灵活把这些模块塞进空闲时间里。

核心原则：**保证每天有“有效输出”，而不是“无效时长”。**

---

### 📅 弹性高效作息方案（任务驱动型）

我们把一天的学习拆分为三个“能量块”。

#### 🟦 **模块 A：大脑预热与门槛硬仗（约 1.5 - 2 小时）**
**最佳时间：** 早起后 或 没课的上午（脑子最清醒的时候）。
**目标：** 搞定面试最容易挂的第一关——算法和 C++ 基础。

*   **必须完成：**
    1.  **LeetCode 一道题（30-45分钟）：**
        *   **策略：** 不要贪多。只做《剑指Offer》或《LeetCode 热题 100》。
        *   **要求：** 先思考，写不出来直接看答案，理解思路后，**用 C++ 默写一遍**。
    2.  **C++ 重点概念攻克（45分钟）：**
        *   **策略：** 每天只搞懂**一个**知识点。
        *   *例子：今天我就搞懂“虚函数表（vptr/vtbl）的内存布局”。明天我就搞懂“shared_ptr 引用计数怎么加减的”。*

#### 🟧 **模块 B：项目实战与核心产出（约 3 - 4 小时）**
**最佳时间：** 下午大块时间 或 晚上（需要长时间专注，进入心流）。
**目标：** 推进《Endless Warrior》Demo 的进度。

*   **必须完成：**
    *   **功能推进：** 按照之前的周计划，每天只实现**一个具体的 C++ 功能**。
    *   *例子：今天下午的任务就是“写出 Weapon 类，让角色能把武器拿在手上”。做完这个就视为胜利。*
    *   **调试（Debug）：** 遇到报错不要慌，解决报错也是学习的一部分。

#### 🟩 **模块 C：碎片时间与理论补给（约 1 小时）**
**最佳时间：** 睡前、吃饭时、坐车时、不想写代码时。
**目标：** 应对面试中的“八股文”和概念题。

*   **轻松完成：**
    *   看视频：B站搜 UE5 教程（如 GAS 入门、渲染管线讲解）。
    *   看文档：刷一下 UE 官方文档的 API 页面。
    *   看面经：牛客网上看别人的面试题，在脑子里想一下“这题我会怎么答”。

---

### 🗓️ 基础月：炼气期——重铸 C++ 与 引擎底层

**目标：** 彻底抛弃蓝图思维，用 C++ 掌控世界。

#### **第 1 周：C++ 极限特训与 UE 宏魔法**
*   **周一：内存与指针**
    *   **任务：** 搞懂 Stack vs Heap。手写一个简易 `SmartPtr` 理解引用计数。
    *   **UE实操：** 理解 `TObjectPtr<T>` (UE5) 与 `T*` 的区别。
*   **周二：STL 与 UE 容器**
    *   **任务：** 彻底搞懂 `std::vector` 扩容机制。
    *   **UE实操：** 熟练使用 `TArray`, `TMap`。用 `Algo::Sort` 对 TArray 进行排序（自定义 Predicate）。
*   **周三：宏与反射 (Reflection)**
    *   **任务：** 阅读 `UCLASS`, `UPROPERTY` 源码宏定义。
    *   **UE实操：** 创建一个 `UObject` 子类，尝试用 `FindField` 或 `FindFunction` 动态调用函数（理解反射的威力）。
*   **周四：代理与事件 (Delegates)**
    *   **UE实操：** 声明一个 `FOnIntChanged` 委托。在 Actor A 中绑定，在 Actor B 中触发。这是解耦的核心。
*   **周五-周日：实战作业 01 —— “纯 C++ 搭建的舞台”**
    *   **产出：** 一个空场景，包含一个会上下浮动的平台（C++ Tick计算），和一个进入范围自动亮灯的触发器（C++ Overlap）。

#### **第 2 周：Gameplay 架构与输入系统**
*   **周一：GameMode 体系**
    *   **理论：** 理解 `GameMode` (规则) vs `GameState` (状态) vs `PlayerState` (玩家数据)。
    *   **任务：** 自定义这三个类，并在 `WorldSettings` 里配置。
*   **周二：Enhanced Input (增强输入)**
    *   **任务：** 废弃旧 Input，使用 `UInputMappingContext`。
    *   **代码：** 在 C++ 中绑定 `IA_Move` 到 `MyCharacter::Move` 函数。
*   **周三：Character Movement 深度**
    *   **任务：** 实现 冲刺（Sprint）和 蹲下（Crouch）。
    *   **API：** `GetCharacterMovement()->MaxWalkSpeed`, `Crouch()`, `UnCrouch()`。
*   **周四：摄像机控制**
    *   **任务：** C++ 创建 `USpringArmComponent` 和 `UCameraComponent`。实现类似于《只狼》的锁定视角逻辑雏形（FindLookAtRotation）。
*   **周五-周日：实战作业 02 —— “听话的人偶”**
    *   **产出：** 一个能跑、跳、蹲、冲刺的角色。所有参数（冲刺速度、跳跃高度）必须暴露给蓝图可调 (`EditAnywhere`)。

#### **第 3 周：3D数学与战斗基础**
*   **周一：向量数学 (必考)**
    *   **任务：** 实现“背后刺杀”判定。
    *   **公式：** `FVector::DotProduct(EnemyForward, ToPlayerDir) > 0`。
*   **周二：碰撞检测 (LineTrace/Sweep)**
    *   **任务：** 武器攻击判定。不准用简单的 Overlap。
    *   **API：** 使用 `GetWorld()->SweepSingleByChannel` (形状扫描)，模拟挥刀轨迹。
*   **周三：伤害框架**
    *   **任务：** 重写 `TakeDamage`。
    *   **架构：** 定义 `UDamageType` 子类（物理、火焰）。
*   **周四：接口 (Interface)**
    *   **任务：** `IHitInterface`。所有可被打的东西（敌人、木箱、草丛）都继承它。攻击时只管调接口，不管具体类。
*   **周五-周日：实战作业 03 —— “靶场”**
    *   **产出：** 角色可以挥刀（播放 Montage），前方扇形范围内的敌人受击变色并扣血。

#### **第 4 周：对象生命周期与资源管理**
*   **周一：Spawn 与 Destroy**
    *   **任务：** 编写 `EnemySpawner`。
    *   **难点：** 理解 `DeferedSpawn` (延迟生成)，在生成前设置参数。
*   **周二：软引用 (Soft Reference)**
    *   **任务：** 优化内存。将敌人 Mesh 改为 `TSoftObjectPtr`，异步加载。
*   **周三：垃圾回收 (GC)**
    *   **理论：** 深入理解“标记-清除”算法。
    *   **任务：** 写一个 Bug，让对象被意外 GC（不加 UPROPERTY），然后修复它（AddToRoot 或 UPROPERTY）。
*   **周四：DataAsset (数据驱动)**
    *   **任务：** 用 `UPrimaryDataAsset` 定义怪物属性表（血量、掉落物）。
*   **周五-周日：12月 总结节点**
    *   **验收：** 你的 GitHub 仓库应该有至少 20 次提交。你的 Demo 应该有一个可玩的战斗原型。

---

### 🛠️ 核心月：筑基期——核心系统与 GAS 进阶

**目标：** 攻克大厂最看重的技术栈（AI、动画、GAS）。

#### **第 5 周：动画编程（C++ 里的动作灵魂）**
*   **周一：Native AnimInstance**
    *   **任务：** 抛弃蓝图 Update 里的逻辑。重写 `NativeUpdateAnimation`。
    *   **优化：** 使用 `ThreadSafe` 方式获取数据。
*   **周二：动画通知 (AnimNotify)**
    *   **任务：** C++ 实现 `UAnimNotify_AttackWindow`。
    *   **逻辑：** 通知开始时开启碰撞检测，通知结束时关闭。
*   **周三：状态机与混合**
    *   **任务：** 理解 BlendSpace 1D/2D。C++ 控制 Layered blend per bone（上半身攻击，下半身移动）。
*   **周四：运动匹配 (Motion Matching) 概念**
    *   **加分项：** 只要了解概念，能在面试时扯两句 UE5 这一新特性即可。
*   **周五-周日：实战作业 04 —— “流畅的动作”**
    *   **产出：** 角色移动起停有惯性动画，攻击时有连招（Combo）逻辑（通过检测 Montage 播放进度实现）。

#### **第 6 周：AI 行为树与黑板**
*   **周一：Perception System**
    *   **任务：** 配置 `AIPerception`，让 AI 能“看见”和“听见”玩家。
*   **周二：C++ Custom Task**
    *   **任务：** 编写 `UBTTask_Attack`。
    *   **重点：** 必须处理 `EBTNodeResult::InProgress`，直到动画播完才返回 `Succeeded`。
*   **周三：C++ Custom Decorator**
    *   **任务：** 编写 `UBTDecorator_CanSeePlayer`。
*   **周四：EQS (环境查询)**
    *   **任务：** 让 AI 寻找最近的掩体。
*   **周五-周日：实战作业 05 —— “聪明的敌人”**
    *   **产出：** 敌人会巡逻，发现玩家后包围，玩家躲起来会去最后消失点搜索。

#### **第 7 周：UI 系统与 MVVM 雏形**
*   **周一：UMG C++ 基类**
    *   **任务：** 创建 `UUserWidget` 子类。
    *   **绑定：** 使用 `BindWidget` 宏将 C++ 变量与 UMG 控件自动连接。
*   **周二：MVVM 模式实践**
    *   **任务：** 绝不在 Tick 里刷 UI。
    *   **实现：** 属性变化 -> 广播 Delegate -> UI 监听并刷新。
*   **周三：血条与伤害飘字**
    *   **任务：** 将 3D Widget 组件化，挂在敌人头顶。
*   **周五-周日：实战作业 06 —— “完整的界面”**
    *   **产出：** 主菜单、HUD（血条、耐力）、暂停菜单、背包界面雏形。

#### **第 8 周：GAS (Gameplay Ability System) —— 核心必杀技**
*   **导师提示：** 这一周最难，但也是腾讯/米哈游面试官最爱问的。
*   **周一：GAS 环境搭建**
    *   **任务：** `AbilitySystemComponent`, `AttributeSet`。
*   **周二：Gameplay Attributes**
    *   **任务：** 实现 Health, Mana, Stamina。处理 `PreAttributeChange` (限制数值范围)。
*   **周三：Gameplay Abilities (GA)**
    *   **任务：** 实现一个“火球术”技能。
    *   **流程：** 消耗 Mana -> 播放 Montage -> 等待 Event -> 发射 Projectile -> 造成 Damage。
*   **周四：Gameplay Effects (GE)**
    *   **任务：** 实现 瞬间伤害(Instant)、持续回血(Duration)、无限Buff(Infinite)。
*   **周五-周日：实战作业 07 —— “GAS 重构”**
    *   **产出：** 将角色的普通攻击和技能全部迁移到 GAS 系统中。

---

### 🚀 关键月：冲刺期——性能、网络与面经

**目标：** 补齐最后一块短板，准备好简历和话术。

#### **第 9 周：网络同步 (Replication)**
*   **导师提示：** 大厂默认你会做网游，即使你做单机。
*   **周一：基础同步**
    *   **任务：** `bReplicates = true`。理解 `GetLifetimeReplicatedProps`。
*   **周二：RPC (远程过程调用)**
    *   **任务：** 区分 `Server`, `Client`, `NetMulticast`。
    *   **场景：** 攻击动作（Multicast），扣血（Server）。
*   **周三：变量复制与通知 (RepNotify)**
    *   **任务：** 使用 `OnRep_Health` 更新客户端 UI。
*   **周四：移动同步**
    *   **任务：** 理解 `CharacterMovementComponent` 是如何做预测和回滚的（面试理论题）。
*   **周五-周日：实战作业 08 —— “双人联机”**
    *   **产出：** 打包项目，开启两个窗口，实现 Client A 看到 Client B 跑动、攻击、掉血。

#### **第 10 周：性能优化与 Profiling**
*   **周一：Unreal Insights**
    *   **任务：** 学会看 Trace。找出 Tick 耗时最高的 Actor。
*   **周二：渲染优化**
    *   **理论：** Draw Call, LOD, HLOD, Cull Distance。
    *   **任务：** 编写代码批量合并 Instanced Static Mesh (ISM)。
*   **周三：CPU 优化**
    *   **任务：** 减少 Tick 使用，改用 Timer 或 Event。
*   **周四：内存优化**
    *   **任务：** 检查内存泄漏，分析 Texture Streaming。

#### **第 11 周：CS 基础与图形学八股文（背诵周）**
*   **图形学：** 渲染管线（VS->PS）、冯氏光照、PBR 原理（金属度/粗糙度）、四元数 vs 欧拉角。
*   **C++：** 虚表、内存布局、右值引用、Lambda 原理、智能指针线程安全性。
*   **操作系统：** 进程/线程、死锁条件、虚拟内存。
*   **网络：** TCP 三次握手/四次挥手、UDP 可靠性实现（KCP/QUIC概念）。

#### **第 12 周：简历包装与模拟面试**
*   **Demo 录制：** 重点展示 GAS Debug 界面、网络同步效果、AI 逻辑视图。
*   **GitHub 整理：** Readme 必须精美，代码注释完善。
*   **简历撰写：**
    *   不要写：“熟悉 UE4/5”
    *   要写：“实现基于 GAS 的技能系统，包含自定义 AttributeSet 和 GE 计算逻辑...”
    *   要写：“使用 Unreal Insights 分析性能，通过将 500 个 Actor 转为 ISM 实例，降低 DrawCall 40%...”
*   **投递策略：** 3月1日准时投递。

---

### 💡 导师的最后三条锦囊

1.  **关于 GAS：** 如果这一周你觉得太难啃不动，**不要卡死**。先用简易版实现，但面试前必须把 GAS 的**概念**（GA, GE, ASC, Tag）背得滚瓜烂熟。面试官问你“懂不懂 GAS”，你说“我看过文档，懂原理，但Demo里没完全用上”，比“完全不知道”强一百倍。
2.  **关于算法：** 很多做游戏的学生轻视 LeetCode。**大错特错**。腾讯网易的一面全是算法题。做不出算法题，你连展示 UE 技术的机会都没有。**每天两道，雷打不动**。
3.  **遇到问题：**
    *   报错了？ -> 复制 Error Log 给 Gemini。
    *   原理不懂？ -> 搜 "UE5 C++ [关键字] explained"。
    *   想偷懒？ -> 想想如果你进不去大厂，以后每个月少拿的 1-2 万块钱。

---

### 🛑 导师的底线要求（Minimum Viable Effort）

无论你那天多忙，多累，心情多差，如果你想明年 3 月进大厂，请守住这条**底线**：

1.  **代码不能断更：** GitHub 每天至少要有一次 Commit（提交）。哪怕只是改了一行注释，或者修了一个微小的 Bug。保持手感是程序员的生命线。
2.  **算法不能停：** 如果没时间写代码，至少在手机上看一道算法题的解法，脑补一遍过程。
