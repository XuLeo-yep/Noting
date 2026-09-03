# Lecture 2 学习笔记：Arrays（第 1–30 页，截至 Arrays Summary）

> 来源：`Lecture2_ArraysLinkedLists.pdf`
> 适用范围：第 1 页 ～ 第 30 页「Arrays Summary」
> 本讲完整标题：*Arrays, Linked Lists and Recursion*（数组、链表与递归）—— 但本次只覆盖 **Arrays（数组）** 部分，Linked Lists 和 Recursion 在后面。

---

## 0. 整体主线（建议先读）

> **定义 → Java 里数组到底是什么样（内存图）→ 连续存储带来的好处和代价 → 用"有序插入"的例子体会代价 → 总结（优点/缺点）**

核心英文词：**array**（数组）、**element**（元素）、**index / indexing**（下标/按下标访问）、**contiguous**（连续的）、**storage**（存储）、**insert**（插入）、**resize**（扩容）。

---

## 1. 第 1 页：标题页（Title slide）

- *Arrays, Linked Lists and Recursion* — 数组、链表与递归
- *Algorithms and Data Structures* — 算法与数据结构

| English | 中文 |
|---|---|
| algorithm | 算法 |
| data structure | 数据结构 |

---

## 2. 第 2 页：数组的定义（What is an Array?）

PPT 给出了三个定义要点：

### ① 一组元素 + 一个名字 + 按下标访问
> *"A data structure consisting of a group of elements having a single name that are accessed by indexing."*

- **a group of elements** — 一组元素
- **a single name** — 一个数组名（`array` 这一个名字代表整组数据）
- **accessed by indexing** — 通过 `array[i]` 下标访问 → 即后面的 **random access（随机访问）**

### ② 占据连续存储区
> *"It occupies a contiguous area of storage."*

- **contiguous** — 连续、紧挨着；数组在内存中是一排连续"房间"
- 这是数组最重要的物理特征，也是 O(1) 访问的来源

### ③ 元素类型相同
> *"Each element has the same data type."* —— 限定在 **statically typed programming languages（静态类型语言）**，如 Java、C/C++。

> 对比：Python 这类动态类型语言，列表可以混装不同类型 → 所以老师特别加了 *statically typed* 这个限定。
> 注意：这里讲的是**计算机科学意义上的数组**，和后面自定义的 `Array` 类不是一回事。

---

## 3. 第 3–7 页：Java Example 1 —— int 数组（存"值"）

> 这几页是同一段代码 + 动画逐帧截图（PDF 每页 = 动画一帧）。

```java
public class Example1 {
    public static void main(String[] args) {
        int[] array = new int[4];   // 声明并创建长度为 4 的 int 数组
        array[0] = 255;             // 把 255 存到下标 0 的位置
    }
}
```

动画标注的关键标签：

- **Array size**：长度 = 4
- **Array storage**：连续存储空间，4 格各占 4 字节（int），共 16 字节连续排布
- **`array[0]`**：按下标 0 访问第一格，直接写入 255

### 讲解要点
1. `int[]` 每格存的是 **primitive value（基本类型的值本身）** —— 255 直接躺在格子里，不指向别处。
2. 下标从 **0** 开始（**zero-based indexing**）：`array[0]` 第一格，`array[3]` 最后一格。
3. 访问原理：`第 i 个元素地址 = 起始地址 + i × 元素大小` → 一步算出 → **constant time（常数时间）**。

| English | 中文 |
|---|---|
| declare | 声明 |
| allocate（new） | 分配内存 |
| array length | 数组长度 |
| element size | 元素大小 |
| byte | 字节 |
| base address | 起始地址 |
| zero-based indexing | 从 0 开始的下标 |

---

## 4. 第 8–13 页：Java Example 2 —— String 数组（存"引用"）

```java
public class Example2 {
    public static void main(String[] args) {
        String[] array = new String[4];
        array[0] = new String("Hello world");
        System.out.println(array[0]);
    }
}
```

动画标注的关键词：**Dynamically allocated**（动态分配）、**Reference**（引用）。

### 讲解要点（中国学生最容易懵的地方）
1. `String` 是**对象类型（reference type）**；数组每个格子存的是一个 **reference（引用）** —— 可理解成"指向对象的门牌号/地址"。
2. 真正的字符串对象 `"Hello world"` 被 `new` 出来放在**堆内存（heap）**里的其它位置，`array[0]` 的格子里只存着指向它的箭头/地址。
3. `array` 和 `String` 对象都是 **dynamically allocated**（运行时用 `new` 向堆申请）。
4. 两种数组结构相同（都是连续格子），区别只在**格子里装的是数值还是地址**。

| English | 中文 |
|---|---|
| reference type | 引用类型 |
| reference / pointer | 引用 / 指针 |
| heap | 堆（动态内存区） |
| dynamically allocated | 动态分配 |
| object | 对象 |
| address | 地址 |

---

## 5. 第 14–20 页：Java Example 3 —— 自己封装一个 Array 类

```java
public class Array {
    private Object[] data;          // 内部用一个 Object 数组存数据

    public Array() {                // 默认构造器
        this.data = new Object[4];
    }

    public static void main(String[] args) {
        Array arrayObject = new Array();
    }
}
```

动画标注：`arrayObject: null`（未指向任何对象）→ `arrayObject: 0xFFFC`（教学用假地址，表示已指向一个对象）。

### 讲解要点
1. 演示"**对象里套数组**"的内存图（引用链）：
   `arrayObject → Array 对象 → Object[] 数组`
2. `arrayObject` 是指向 `Array` 对象的引用；对象内部的字段（field）`data` 又指向 `Object[4]`。
3. 为什么用 `Object[]`？因为 **Object 是所有类的父类**，`Object[]` 每格都能放任意对象的引用 → 为以后写通用容器（如 `ArrayList` 的原理）做准备。

| English | 中文 |
|---|---|
| class / instance / object | 类 / 实例 / 对象 |
| field | 字段 |
| constructor | 构造器 |
| wrapping / wrapper | 包装 |
| null | 空引用 |
| reference chain | 引用链 |

---

## 6. 第 21 页：Contiguous Uniform Storage（连续、统一的存储）

过渡页，抛出两个问题：
- **What does it get us?**（它给我们带来什么好处？）
- **What does it cost us?**（我们付出什么代价？）

| 好处（what it gets us） | 代价（what it costs us） |
|---|---|
| **Constant-time / O(1) random access**：`array[i]` 一步定位（base + i × size） | **Fixed size**：长度创建时定死，满了要扩容 |
| 内存局部性好，**cache friendly** | **中间插入/删除代价高**：后面元素要整体搬动，O(n) |
| 结构简单、开销小 | 需要**提前知道最多存多少个元素** |

**术语**：**trade-off**（权衡，老师口头禅）、**random access**（随机访问）、**fixed size**（固定大小）、**in the middle**（在中间位置）。

---

## 7. 第 22–29 页：Arrays (insert) —— "有序数组插入"动画

> 注意：第 24–28 页在 PDF 中是纯动画图片、无文字，以下为该演示所表达的内容（课上你会看到一步步的画面）。

演示内容：
- 数组存着**按字母序排好的首都城市名单（sorted capital cities）**（澳大利亚各州首府，如 Adelaide, Brisbane, Darwin, Hobart…）。
- 突然发现——**"Oops, we forgot Canberra, let's fix it"**（忘了首都堪培拉，把它补进去）。
- 问题：Canberra 按字母序应插在 **Brisbane 和 Darwin 之间**，但数组无法"就地塞入"：

1. 元素只能占自己那一格 → 硬插就必须把**后面的元素一个个往后挪（shift / move right）**腾出空位；
2. 若数组已**满员（full）**，连挪的地方都没有 → 先**申请更大的新数组并复制全部元素（resize）**，再腾位插入。

### 真实成本
| 操作 | 复杂度 |
|---|---|
| 末尾追加（空间够） | O(1) |
| 中间插入 | O(n)（要把插入点之后的元素逐个 shift） |
| 扩容复制 | O(n)（复制 n 个旧元素到新数组） |

**术语**：**sorted**（有序的）、**insertion point**（插入位置）、**shift to the right**（向右挪）、**make room**（腾位置）、**full**（满了）、**resize**（扩容）、**copy**（复制）、**alphabetical order**（字母顺序）。

外教句式：*"Inserting into a sorted array is expensive because we have to shift elements."*

---

## 8. 第 30 页：Arrays Summary（数组总结）★ 复习终点页

### Pros（优点）
- **Constant time access to indexed memory location**
  对"按下标定位的内存单元"的访问是常数时间的 → `array[i]` 是 **O(1) 随机访问**，与数组大小无关。

### Cons（缺点）
- **Fixed size** —— 大小固定
- **Resizing requires copying all existing values to a new array**
  扩容必须把所有元素复制到新数组（O(n)）
- **Sorted insert**（向有序数组插入）
  - **Best case constant**：最好情况 O(1) —— 新元素比所有元素都大，直接追加末尾，无需搬动；
  - **Worst case, must shuffle entire array of n elements**：最坏情况 O(n) —— 新元素最小、要插到最前面，整组 n 个元素全部搬动一遍。

---

## 9. 复杂度速记表（老师最爱问）

| 操作 (operation) | 英文说法 | 复杂度 |
|---|---|---|
| 按下标访问 `array[i]` | random access | **O(1)** |
| 末尾追加（空间够） | append at the end | O(1) |
| 中间/开头插入 | insert in the middle | **O(n)**（要 shift） |
| 中间删除 | delete / remove | **O(n)**（要 shift 补空位） |
| 扩容复制 | resize / grow the array | **O(n)**（copy） |

> 一句话背下来：**"Access is O(1); insertion and deletion are O(n)."** —— 足够回答外教提问。

---

## 10. 重点英文词汇总表

| English | 中文 | 所在页 |
|---|---|---|
| data structure | 数据结构 | 1 |
| array | 数组 | 2 |
| element | 元素 | 2 |
| index / indexing | 下标 / 按下标访问 | 2 |
| contiguous storage | 连续存储 | 2 |
| data type | 数据类型 | 2 |
| statically typed language | 静态类型语言 | 2 |
| allocate / new | 分配内存 | 3–20 |
| dynamically allocated | 动态分配 | 8–13 |
| reference / pointer | 引用 / 指针 | 8–13 |
| heap | 堆 | 8–13 |
| object / instance | 对象 / 实例 | 14–20 |
| field | 字段 | 14–20 |
| constructor | 构造器 | 17 |
| fixed size | 固定大小 | 30 |
| resize | 扩容 | 30 |
| copy | 复制 | 30 |
| random access | 随机访问 | 21, 30 |
| constant time (O(1)) | 常数时间 | 30 |
| sorted insert | 有序插入 | 30 |
| best case / worst case | 最好 / 最坏情况 | 30 |
| shift / shuffle | 平移 / 挪动整组 | 22–29 |
| pros and cons | 优点和缺点 | 30 |
| summary | 总结 | 30 |

---

## 11. 外教课堂常用句型

- *"What is the definition of an array?"* → 数组的定义
- *"Why can we access array elements in constant time?"* → 内存连续，`base + i × size` 一步算出地址
- *"What are the pros and cons of arrays?"* → 优点 O(1) 访问；缺点大小固定、插入/扩容要 O(n)
- *"Inserting into a sorted array — what is the best case? What about the worst case?"*
  → Best case: append at the end, O(1)；Worst case: insert at the front, shift all n elements, O(n)
- 高频口语词：**trade-off**（权衡）、**under the hood**（底层/内部实现）、**roughly**（大概）、**in the worst case**（最坏情况下）

---

## 12. 一句话总结

**数组 = 连续(contiguous) + 类型统一(uniform) + 按下标访问(indexing)**
→ 换来 **O(1) 随机访问**
→ 代价是 **大小固定(fixed size)、中间插入和扩容都要 O(n) 搬运**

下次 Linked Lists（链表）正好是"反过来的特性"：插入 O(1)、按下标访问 O(n)——可与本页 Arrays Summary 对照记忆。

---

*说明：本笔记基于对 PDF 第 1–30 页的逐页文本核对编写；第 24–28 页为嵌入图片的动画帧，其内容按课件常见演示逻辑转述。*
