# 快速稀疏矩阵转置（Fast Transpose）

## 1. 定位

这是一个**稀疏矩阵三元组表示上的经典技巧**。

仓库定位：

> DataStructure → SparseMatrix → FastTranspose

它不是需要长期高频默写的核心算法，更适合作为“理解一次、独立默写一次、测试通过、之后间隔复习”的经典技巧。

---

## 2. 问题

给定一个稀疏矩阵，用三元组表示：

```text
(row, col, value)
```

要求得到它的转置矩阵。

转置的规则：

```text
原来：A[row][col]
转置：T[col][row]
```

例如：

```text
A:
0 0 3
4 0 0
0 5 0
```

非零元素：

```text
(0, 2, 3)
(1, 0, 4)
(2, 1, 5)
```

转置后：

```text
0 4 0
0 0 5
3 0 0
```

非零元素：

```text
(0, 1, 4)
(1, 2, 5)
(2, 0, 3)
```

---

## 3. 为什么普通转置慢？

如果直接按照转置后的顺序寻找元素：

```text
找第 0 列有哪些元素
找第 1 列有哪些元素
找第 2 列有哪些元素
...
```

每一列都可能需要重新扫描整个三元组表。

非零元素数量为 `terms`，矩阵列数为 `cols` 时，最坏可能达到：

```text
O(cols * terms)
```

---

## 4. 快速转置的核心思想

不要反复寻找。

先做两件事：

```text
① 统计原矩阵每一列有多少个非零元素
② 根据每列数量计算它们在转置后的三元组表中的起始位置
```

然后：

```text
③ 扫描原三元组表
④ 当前元素属于哪一列，就直接放到那一列对应的位置
⑤ 该列的下一个元素位置向后移动
```

一句话：

> **先统计 → 算起点 → 直接放置**

---

## 5. 两个最重要的辅助数组

设原矩阵有 `cols` 列。

### colCount

```cpp
colCount[col]
```

表示：

> 原矩阵第 `col` 列有多少个非零元素。

例如：

```text
三元组：

(0, 2, 3)
(1, 0, 4)
(2, 1, 5)
```

那么：

```text
colCount:
2 1 0
```

---

### startPos

```cpp
startPos[col]
```

表示：

> 原矩阵第 `col` 列的元素，在转置后的三元组表中从哪个位置开始存放。

因为：

```text
原矩阵第 0 列
→ 转置后第 0 行

原矩阵第 1 列
→ 转置后第 1 行

原矩阵第 2 列
→ 转置后第 2 行
```

所以转置后的三元组表应该按原列号分组。

例如：

```text
colCount:
2 1 0
```

那么：

```text
startPos[0] = 0
startPos[1] = 2
startPos[2] = 3
```

也就是：

```text
第 0 列 → 位置 [0, 1]
第 1 列 → 位置 [2]
第 2 列 → 没有元素
```

---

## 6. startPos 怎么算？

第 0 列一定从 `0` 开始：

```cpp
startPos[0] = 0;
```

后面的列：

```cpp
startPos[col] =
    startPos[col - 1] + colCount[col - 1];
```

本质就是：

> 当前列的起点 = 前一列的起点 + 前一列有多少个元素

这其实就是一个前缀和。

---

## 7. 真正放置元素

假设当前三元组：

```text
(row, col, value)
```

它转置后应该变成：

```text
(col, row, value)
```

它属于转置后的第 `col` 组。

所以：

```cpp
pos = startPos[col];
result[pos] = {col, row, value};
startPos[col]++;
```

这里有一个非常重要的不变量：

> `startPos[col]` 始终指向“原矩阵第 col 列中，下一个还没放入结果的位置”。

所以每放一个元素：

```cpp
startPos[col]++;
```

---

## 8. 完整算法

可以把算法记成四步：

```text
1. 初始化 colCount
2. 扫描所有非零元素，统计每一列数量
3. 根据 colCount 计算 startPos
4. 再扫描所有非零元素，按照 startPos[col] 直接放入结果
```

伪代码：

```text
统计每列非零元素数量

startPos[0] = 0
for col = 1 ...:
    startPos[col] =
        startPos[col - 1] + colCount[col - 1]

for 每个非零元素 item:
    col = item.col
    pos = startPos[col]

    result[pos] = 转置后的 item

    startPos[col]++
```

---

## 9. 为什么这样能保证顺序？

原三元组不需要按照列排序。

因为 `startPos[col]` 已经提前给每一列划好了结果区域：

```text
col 0 → [startPos[0], ...]
col 1 → [startPos[1], ...]
col 2 → [startPos[2], ...]
...
```

所以无论原来的三元组以什么顺序出现：

```text
(2, 1, 5)
(0, 2, 3)
(1, 0, 4)
```

只要按照它们的 `col` 找对应区域，就能直接放进去。

---

## 10. 复杂度

设：

- `cols`：矩阵列数
- `terms`：非零元素数量

统计：

```text
O(terms)
```

计算起始位置：

```text
O(cols)
```

再次扫描并放置：

```text
O(terms)
```

总复杂度：

```text
O(terms + cols)
```

额外空间：

```text
O(cols)
```

如果结果三元组表本身不算额外辅助空间，则辅助数组就是 `colCount` 和 `startPos`。

---

## 11. 最容易错的地方

### 错误 1：把 row 和 col 搞反

原：

```text
(row, col, value)
```

转置：

```text
(col, row, value)
```

不是：

```text
(row, col, -value)
```

---

### 错误 2：忘记 startPos[col] 要递增

同一列可能有多个非零元素。

第一次：

```cpp
pos = startPos[col];
```

放完以后：

```cpp
startPos[col]++;
```

否则下一个元素会覆盖刚刚放进去的元素。

---

### 错误 3：把 colCount 当成位置

这两个数组含义完全不同：

```text
colCount[col]  = 有多少个

startPos[col]  = 从哪里开始放
```

---

### 错误 4：认为必须先排序

快速转置的意义就是：

> 不需要先对三元组排序，再做转置。

利用 `colCount + startPos` 可以直接确定位置。

---

## 12. 默写时只记这个

如果代码忘了，不要从代码硬背。

先问自己：

```text
当前元素属于原矩阵哪一列？
        ↓
这一列有多少个元素？
        ↓
这一列在结果中的起点在哪里？
        ↓
把元素放到这个位置
        ↓
这个位置向后移动
```

最核心的两个数组：

```text
colCount：每列有多少个

startPos：每列从哪里开始放
```

核心动作：

```cpp
pos = startPos[col];
result[pos] = ...
startPos[col]++;
```

---

## 13. 本模块练习目标

第一次学习：

- 能解释 `colCount` 和 `startPos`
- 能手算一个小矩阵的转置
- 能从四步流程重新写出代码

之后默写：

- 先看题意，不看 reference
- 写 `current.cpp`
- 运行 CTest
- 通过后再归档

它属于**经典技巧 / 次重点**，不需要像 KMP 一样高频重复默写。
