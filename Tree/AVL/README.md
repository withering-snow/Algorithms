# AVL Tree

## 作用

AVL 是自平衡二叉搜索树。

对于任意节点：

balance = height(left) - height(right)

满足：

|balance| <= 1

因此查找、插入、删除的树高保持 O(log n)。

---

## 设计上的选择

此版本以 [洛谷 P3369](https://www.luogu.com.cn/problem/P3369) 模板题为依据进行设计，对于具体实现的选择如下：

- 对于 `insert` `remove` 等需要 **保留历史路径** 的函数，采用 **递归** 实现
- 对于 `rank` `kth` 等只进行 **搜索遍历** 的函数，采用 **循环** 实现
- 此外，此版本在基础的 `AVL` 之外增加了 `size` `count` 信息，实现了对数据的顺序统计
- 此版本实现的是单向 `node` 结构，不维护 `parent` 指针

---

## Node 维护的信息

```cpp
val
count
height
size
left
right
```

- `count`：该值出现次数
- `height`：以当前节点为根的子树高度
- `size`：子树中元素总数，包含重复元素

本实现约定：

```text
height(nullptr) = 0
height(leaf) = 1
```

更新：

```text
height = max(leftHeight, rightHeight) + 1

size = leftSize + rightSize + count
```

---

## Balance

```text
balance = leftHeight - rightHeight
```

失衡：

```text
balance > 1
→ 左边过高

balance < -1
→ 右边过高
```

四种情况：

```text
LL → 右旋

RR → 左旋

LR → 左孩子先左旋，再右旋

RL → 右孩子先右旋，再左旋
```

核心原则：

```text
修改子树
→ updateInfo
→ rebalance
→ 返回新的子树根
```

因此 insert/remove 最后都可以：

```cpp
return rebalance(node);
```

---

## Insert

本质：

```text
BST 插入
→ 重复值 count++
→ 递归返回时 rebalance
```

---

## Remove

本质：

```text
BST 删除
→ 递归返回时 rebalance
```

找到节点后：

```text
count > 1
→ count--

count == 1:
    无左孩子 → 返回右孩子
    无右孩子 → 返回左孩子
    两个孩子 → 用前驱或后继替换，再删除原前驱/后继
```

若替代节点有多个相同值：

```text
把 val 和 count 全部搬到当前节点
把 target->count 临时设为 1
再递归删除 target
```

这样保证相同值仍只占一个 TreeNode。

---

## Rank

`rank(x)`：

```text
比 x 小的元素数量 + 1
```

往右走时：

```text
smaller += leftSize + count
```

---

## kth

寻找第 k 小。

当前节点中：

```text
[ 左子树 ][ 当前值 count 次 ][ 右子树 ]
```

- `k <= leftSize` → 左
- `k <= leftSize + count` → 当前值
- 否则：
  ```text
  k -= leftSize + count
  ```
  去右边

---

## prev / next

`prev(x)`：

```text
严格小于 x 的最大值
```

`next(x)`：

```text
严格大于 x 的最小值
```

都是普通 BST 搜索，同时维护候选答案。

---

## 易错点

- `height` 是 `max + 1`
- `size` 是 `left + right + count`
- 旋转后必须先更新旧根，再更新新根
- `rebalance` 的返回值不能丢
- 两孩子删除时是复制 target 的数据，不是 `node = target`
- 搬运重复值时必须一起搬 `count`
- 搬完后还要把原 target 从子树真正删除
