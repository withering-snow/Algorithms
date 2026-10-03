# Algorithms

个人算法学习、复习与默写仓库。

这个仓库的目的不是单纯保存算法模板，而是通过：

**理解 → 默写 → 自动测试 → 归档 → 间隔复习**

让常用算法能够在忘记具体实现后，仍然根据原理重新写出来。

## 目录结构

算法按类别组织，例如：

```text
Algorithms/
├── String/
│   └── KMP/
├── Graph/
├── DP/
├── Sort/
└── DataStructure/
```

每个算法目录通常包含：

```text
Algorithm/
├── current.cpp       # 当前练习文件
├── template.cpp      # current.cpp 的空白框架
├── *.hpp             # 固定接口
├── test.cpp          # 自动测试
├── README.md         # 原理、实现思路与易错点
├── reference/        # 已确认正确的参考实现
└── archive/          # 历次独立默写结果
```

## 使用方式

平时只编辑：

```text
current.cpp
```

需要重新默写时，在 VSCode 中执行：

```text
Algorithm: Reset Current
```

脚本会根据当前文件所在目录找到最近的 `template.cpp`，
并用它恢复 `current.cpp`。

完成实现后：

1. 使用 CMake 编译；
2. 使用 CTest / VSCode Testing 运行测试；
3. 测试通过后，可将 `current.cpp` 手动归档到 `archive/`；
4. 隔一段时间再次从模板开始默写。

## 文件职责

### `template.cpp`

只保存函数框架，不保存算法实现。

用于快速恢复一张“空白卷”。

### `current.cpp`

唯一的自由练习文件。

平时所有算法默写、修改和调试都在这里完成。

### `test.cpp`

固定测试程序。

用于判断当前实现是否正确，并尽量覆盖典型情况和边界情况。

### `reference/`

保存已经确认正确的标准实现。

只有在根据 README 和原理仍然无法恢复算法时再查看。

### `archive/`

保存过去某次独立默写的结果。

主要用于观察自己的学习和遗忘情况，不参与默认编译。

## CMake

整个仓库只有一个顶层 CMake 工程。

所有构建文件统一生成到：

```text
Algorithms/build/
```

各算法目录不单独创建 `build/`。

常用命令：

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

VSCode 使用 CMake Tools 时，也始终以仓库根目录作为 source directory。

## 学习原则

不要求永久记住每一行模板代码。

更重要的是记住算法中的核心不变量和推导过程，使自己在遗忘具体实现后，仍能重新写出正确代码。

如果：

```text
README → 能恢复
```

说明原理仍然掌握。

如果：

```text
README → 仍然无法恢复
```

再查看 `reference/` 并重新理解。