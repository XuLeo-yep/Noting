# Lecture 2 学习笔记：Recursion（第 49–69 页 + 附录练习 70–73）

> 来源：`Lecture2_ArraysLinkedLists.pdf`
> 适用范围：第 49 页「Recursion」目录 ～ 第 69 页「Recursion Summary」；附录补充第 70–73 页（整讲总结与递归编程练习）
> 结构：Linear Recursion（线性递归）→ Binary Recursion（二分递归）→ Multiple Recursion（多重递归）
>
> ⚠️ 说明：第 51、52、54、61、67 等页在 PDF 中为**图片/动画帧**，无文字可提取；这些页笔记按该课件常见演示逻辑转述，请以课上实际画面为准。

---

## 0. 本部分主线

> **什么是递归 → 阶乘经典例子 → 线性递归（两条规则）→ 递归的参数设计 → 尾递归 → 二分递归（分治）→ 多重递归（枚举）→ 总结**

核心英文词：**recursion**（递归）、**base case**（基本情况/递归出口）、**recursive call**（递归调用）、**linear / binary / multiple recursion**（线性/二分/多重递归）、**tail recursion**（尾递归）、**divide and conquer**（分治）、**run-time stack**（运行时调用栈）。

---

## 1. 第 49 页：章节目录（Recursion）

本讲递归部分三个主题：

- **Linear Recursion** —— 线性递归：每次调用只产生**一个**递归调用
- **Binary Recursion** —— 二分递归：每次调用产生**两个**递归调用（分治）
- **Multiple Recursion** —— 多重递归：每次调用产生**多个**递归调用（枚举）

> 术语：**linear** 线性的 / **binary** 二分的、两路的 / **multiple** 多重的。老师口中的 "We will look at three types of recursion."

---

## 2. 第 50 页：Recursion Pattern（递归模式）—— 阶乘

### 定义
> **Recursion: when a method calls itself** —— 递归：方法调用它自身。

### 经典例子：阶乘函数（factorial function）
$$n! = 1 \times 2 \times 3 \times 4 \times \cdots \times (n-1) \times n$$

**递归定义（recursive definition）** —— 把"大问题"拆成"更小的同类型问题"：

$$n! = \begin{cases} 1, & n = 0 \quad (\text{base case 基本情形})\\ n \times (n-1)!, & n > 0 \quad (\text{recursive case 递归情形})\end{cases}$$

### 讲解要点
1. 阶乘有两个"分支"：
   - **base case（基本情形）**：$n=0$ 时直接得 $0! = 1$，**不再调用自己** —— 递归必须有的"出口"；
   - **recursive case（递归情形）**：$n! = n \times (n-1)!$，问题规模从 $n$ 缩小到 $n-1$。
2. 这正是递归的通用套路：**把问题化成更小的同类问题，直到小到可以直接回答**。

> 术语：**factorial** 阶乘 / **recursive definition** 递归定义 / **base case** 基本情形 / **recursive case** 递归情形 / **pattern** 模式、套路。

---

## 3. 第 51–54 页：动画演示（图片帧，含 "// Base case" 与 Integer division）

> ⚠️ 这 4 页文字几乎提取不到（纯动画画面），内容按常规演示转述，请对照课堂确认。

### 动画演示的内容通常包括

**① Java 阶乘代码（对应 "// Base case" 标注）：**

```java
public static int factorial(int n) {
    if (n == 0) {          // Base case：递归出口
        return 1;
    } else {               // Recursive case：问题规模变小
        return n * factorial(n - 1);
    }
}
```

**② 递归调用链（recursion trace）演示**，例如求 `factorial(4)`：

```
factorial(4) = 4 * factorial(3)
             = 4 * (3 * factorial(2))
             = 4 * (3 * (2 * factorial(1)))
             = 4 * (3 * (2 * (1 * factorial(0))))
             = 4 * (3 * (2 * (1 * 1)))      ← 到达 base case 后逐层返回（unwinding）
             = 24
```

每调用一次，JVM 就在 **run-time stack（运行时调用栈）** 上压入一个 **stack frame（栈帧）**，到达 base case 后逐层弹栈返回。

**③ Integer division（整数除法）**：Java 中两个 `int` 相除结果仍是 `int`（小数部分被丢弃，向零取整），如 `7 / 2 = 3`、`5 / 2 = 2`。它在递归里非常重要——很多递归通过 `n / 2` 把问题规模**减半**（下一页例题就会用到）。

> 术语：**run-time stack / call stack** 调用栈 / **stack frame** 栈帧 / **push / pop** 压栈/弹栈 / **recursion trace** 递归轨迹 / **unwinding** 逐层返回 / **integer division** 整数除法。

---

## 4. 第 55–56 页：Printing integer as text（用递归输出整数）

### 题目原文（PPT 文字）
假设有一个**正整数 n**，要把它**打印出来**；我们的方法叫 `printOut(n)`。可用的 I/O 只能一次**输出一位数字**（方法 `printDigit`），例如 `printDigit(4)` 会在终端输出一个 4。

> 注：页标题写的是 "(binary representation) as text"（按二进制表示输出），但正文文字与经典教材（Weiss《Data Structures and Algorithm Analysis in Java》）的"打印十进制整数"例题一致，课堂演示时请以画面为准。下面给出两种版本思路。

### 经典解法思路
要打印整个数 n，只需两步：
1. 先递归打印"去掉最后一位"的部分（高位）；
2. 再打印最后一位：`n % 10`（十进制）或 `n % 2`（二进制）。

**十进制版本（Weiss 经典例题）：**

```java
public static void printOut(int n) {
    if (n >= 10) {          // 还有多位：先打印高位
        printOut(n / 10);
    }
    printDigit(n % 10);     // 再打印最低一位
}
```

例如 `printOut(529)`：先 `printOut(52)` → 再 `printOut(5)` → `printDigit(5)` → `printDigit(2)` → `printDigit(9)`，得到 "529"。

**二进制版本（按页标题）：**

```java
public static void printBinary(int n) {
    if (n > 1) {            // 先打印高位部分
        printBinary(n / 2);
    }
    printDigit(n % 2);      // 再打印最低一位（0 或 1）
}
```

### 讲解要点
- **base case**：n 只剩一位时（`n < 10` 或 `n <= 1`）不再递归，直接 `printDigit`。
- 关键：递归发生在 **printDigit 之前** → 先处理高位，保证输出顺序正确（先高位后低位）。

> 术语：**positive integer** 正整数 / **single-digit** 单个数字 / **base 10 / base 2** 十进制/二进制 / **most significant digit / least significant digit** 最高位/最低位。

---

## 5. 第 57–59 页：Linear Recursion（线性递归）与两条规则

### 规则一（第 57 页）：测试基本情形 Test for base cases
- 先检查**一组 base cases** —— **至少有一个（at least one）**；
- **每一条可能的递归调用链最终都必须到达某个 base case**（否则就是无限递归 infinite recursion）；
- 每个 base case 的处理**不应该再使用递归**。

### 规则二（第 58–59 页）：只做一次递归调用 + 必须向 base case 推进
- **Perform a single recursive call** —— 线性递归每次只产生一个递归调用；
- **每个递归调用都必须让问题"更接近" base case（makes progress towards a base case）** —— 即参数向出口方向变化（变小/减半/区间收缩）。

### 课堂代码（第 58–59 页，老师问 "Can you spot any bug?"）

```java
public void recursiveMethod(int n) {
    if (n <= 0) {               // base case
        return 0;
    } else if (n % 2 == 0) {    // 偶数：减半
        return 1 + recursiveMethod(n / 2);
    } else {                    // 奇数：减 1
        return 1 + recursiveMethod(n - 1);
    }
}
```

**思考题答案提示（你能发现的 bug）：**
1. **终止性 bug（关键）**：当 n 为负数时可能**永远到不了 base case**。以 `n = -1` 为例：`-1 % 2 != 0` → 走 `n-1 = -2` → `-2 % 2 == 0` → 走 `n/2 = -1` → 又回到 `-1`… 在 `-1` 和 `-2` 之间死循环 → 栈无限增长 → **StackOverflowError**。
   > 原因：Java 中负数取模结果也是负数（`-1 % 2 == -1`），不会等于 0；base case 只写了 `n <= 0`，却没让"奇数负数"路径收敛。
2. **编译问题（视课件原码而定）**：方法声明为 `void` 却 `return 0; return 1 + ...`，若原码确为 `void` 则无法编译，应为 `int`。

> 术语：**infinite recursion** 无限递归 / **stack overflow** 栈溢出 / **termination** 终止性 / **even / odd** 偶数/奇数 / **modulo（%）** 取模、求余 / **makes progress** 向出口推进。

---

## 6. 第 60–61 页：Example: ReverseArray（递归反转数组）

### 代码（PPT 原文）

```java
public void ReverseArray(int[] A, int i, int j) {
    if (i < j) {                // base case：i >= j 时停止（空转或已交换完）
        int tmp = A[i];
        A[i] = A[j];
        A[j] = tmp;
        ReverseArray(A, i + 1, j - 1);   // 一次递归调用，区间向中间收缩
    }
}
```

### 讲解要点
- 思路：**交换两端** `A[i]` 与 `A[j]`，然后递归处理**更小的区间** `[i+1, j-1]`；
- **base case**：当 `i >= j`（两指针相遇或越过）时不再递归；
- 每次调用区间长度减 2 → **向 base case 推进** ✓（线性递归，只有一次递归调用）；
- 复杂度：交换约 n/2 次，时间 **O(n)**；递归深度 **O(n)**（调用栈里最多约 n/2 个栈帧）；
- 第 61 页为递归过程演示图（追踪 i、j 指针如何从两端向中间移动并交换）。

> 术语：**swap** 交换 / **temporary variable (tmp)** 临时变量 / **two pointers** 双指针 / **shrink the range** 收缩区间。

---

## 7. 第 62–63 页：Defining Arguments for Recursion（递归的参数设计）

### 为什么是 ReverseArray(A, i, j) 而不是 ReverseArray(A)？
- **递归方法往往需要和非递归版本不同的参数（different arguments）**，常常要多传几个参数；
- 反转整个数组这个任务本身只需要数组 A，但**递归子问题需要知道"这一次处理哪一段区间"**，所以要额外传 `i`（左端点）和 `j`（右端点）——子问题 = 反转 `A[i..j]`。

### 递归中信息的传递方式（第 63 页）
1. **Operands are passed forward via parameters** —— 要处理的数据靠**参数**传给下一次调用（向下传）；
2. **Simple case：结果通过 return 传回** —— 例如阶乘 `return n * factorial(n-1)`（向上返回）；
3. **其它情况：目标对象也作为参数传入** —— 例如反转数组时，递归调用共享同一个数组对象 A：
   - 子调用修改的**是同一个数组**（affect the target object）；
   - 部分结果仍可能通过 return 传回。

> 术语：**parameter / argument** 形参/实参 / **pass forward** 向下传递 / **return value** 返回值 / **target object** 目标对象 / **shared object** 共享对象。

---

## 8. 第 64–65 页：Tail Recursion（尾递归）

### 定义
> **Tail recursion occurs when a linearly recursive method makes its recursive call as its last step.**
> 尾递归：线性递归方法中，**递归调用是方法执行的最后一个动作**（调用完之后没有别的计算，直接返回）。

→ 由于递归调用后无事可做，**可以很容易改写成迭代（iterative）形式**。

### 页面对比代码

```java
// 尾递归版
public void ReverseArray(int[] A, int i, int j) {
    if (i < j) {
        int tmp = A[i];
        A[i] = A[j];
        A[j] = tmp;
        ReverseArray(A, i + 1, j - 1);   // ← 最后一步就是递归调用（尾递归）
    }
}
```

```java
// 迭代版（等价）
public void ReverseArray2(int[] A, int i, int j) {
    while (i < j) {
        int tmp = A[i];
        A[i] = A[j];
        A[j] = tmp;
        i += 1;
        j -= 1;
    }
}
```

### 第 65 页的问题：哪个更高效？(is there even a difference?)
- 渐进复杂度相同：都是 **O(n)** 时间；
- 差别在**空间与常数开销**：递归版每层调用占用一个**栈帧**（保存参数、返回地址等），深度 O(n)；迭代版只用常数个变量，**O(1) 额外空间**；
- 理论上尾递归可被编译器优化成循环（**tail-call optimization, TCO**），但 **Java 通常不保证做这种优化**，所以 Java 里写迭代版更省栈、更稳妥；
- 结论：`ReverseArray2`（迭代版）更高效、无栈溢出风险；但二者思路一一对应。

> 术语：**last step** 最后一步 / **tail-call optimization (TCO)** 尾调用优化 / **iterative form** 迭代形式 / **overhead** 开销 / **equivalent** 等价的。老师常问：*"Can this tail recursion be rewritten as a loop?"* → 答 *"Yes, because the recursive call is the last operation, so nothing needs to be remembered after it."*

---

## 9. 第 66–67 页：Binary Recursion（二分递归）—— 分治求数组和

### 定义
> **Binary recursion occurs whenever there are two calls for each non-base case.**
> 二分递归：每个**非 base case** 都产生**两个递归调用** → 典型的 **divide and conquer（分治）**。

### 代码（PPT 原文）：BinarySum —— 递归求数组子段之和

```java
public int BinarySum(int[] A, int i, int len) {
    if (len == 1) {              // base case：只剩一个元素
        return A[i];
    } else {                     // 分成两半，分别求和，再相加
        return BinarySum(A, i, len / 2)
             + BinarySum(A, i + len / 2, len / 2);
    }
}
```

调用示例：`BinarySum(A, 0, n)`，前提 n 取 2 的幂，每段不断对半分。

### 讲解要点
- **如何分**：区间 `[i, i+len)` 分成左半 `[i, len/2)` 与右半 `[i+len/2, len/2)`，两半各自递归求和；
- **base case**：`len == 1` 时直接返回 `A[i]`；
- 第 67 页是**递归树（recursion tree）**示意图：像一棵二叉树一样逐层分裂，最终叶子就是每个元素；
- **复杂度**：总共仍要做 n-1 次加法，时间 **O(n)**；但递归深度只有 **O(log n)**（比线性递归的 O(n) 浅很多）——这是"分治"的一大好处。

> 术语：**divide and conquer** 分治 / **split in half** 对半分 / **recursion tree** 递归树 / **depth**（递归）深度 / **logarithmic** 对数的。

---

## 10. 第 68 页：Multiple Recursion（多重递归）—— 枚举所有组合

### 定义
> **Multiple recursion makes potentially many recursive calls — not just one or two.**
> 多重递归：每个非 base case 可能产生**多个（三个以上甚至循环内无数次）递归调用**。

### 用途
> **Multiple recursion is a way of enumerating all possible combinations of a set of elements.**
> 多重递归常用于**枚举一个元素集合的所有可能组合**（如生成子集、DNA k-mer、排列、迷宫/数独类搜索）。

典型结构：递归体里有一个**循环**，对每个可选元素各调用一次自身（例如第 71 页练习的 DNA k-mer 生成：对 A/C/G/T 每个字符递归接一个字符）。

> 术语：**enumerate** 枚举 / **combinations** 组合 / **all possibilities** 所有可能情况 / **loop inside recursion** 递归内的循环 / **exhaustive search** 穷举搜索。

---

## 11. 第 69 页：Recursion Summary（递归总结）

- **Linear Recursion（线性递归）**
  - 每次只做一个递归调用；
  - **Tail Recursion 可以很容易改写成迭代算法**（尾递归 → while 循环）。
- **Binary Recursion（二分递归）**
  - 方法里包含**两个递归调用** → **divide and conquer（分治）**；
  - 代表例子：BinarySum。
- **Multiple Recursion（多重递归）**
  - 一次产生多个递归调用；
  - 用于**枚举组合 / 穷举所有可能性**。

### 三种递归对比表

| 类型 | 每次递归调用数 | 代表例子 | 递归深度 | 时间 |
|---|---|---|---|---|
| Linear | 1 | factorial、ReverseArray、printOut | O(n) | 视问题而定 |
| Binary | 2 | BinarySum | O(log n) | O(n)（求和） |
| Multiple | 多个（常在循环里） | DNA k-mer 枚举、子集生成 | O(k)（k=长度） | 指数级（穷举，如 4³=64） |

---

## 12. 附录 A：第 70 页 Lecture Summary（整讲总结，涉及递归部分）

整讲三大主题收尾（数组 / 链表 / 递归）：
- **Arrays**：访问快，扩容慢（需要 copy）；
- **Linked lists**：访问 head/tail 快，随机访问慢；
- **Recursion**：三种递归形态 —— 线性（尾递归可转迭代）、二分（分治）、多重（枚举）。

---

## 13. 附录 B：第 71–73 页 编程练习（Feel Like Programming?）

### 练习 1（第 71 页）：输出所有 DNA k-mer（k = 3）

> 字符集 **ACGT**，长度为 3 的 k-mer 形如：AAA, AAC, AAG, AAT, ACA, ACC, …, ATC, ATG, ATT, CAA, …, TTA, TTC, TTG, TTT。
> 提示：假设你已经会生成所有长度为 n-1 的 k-mer，再在其后追加一个字符。
> 要求：**用 Java 实现**。

- 本质：**多重递归枚举**，长度 3 → 每个位置 4 种选择，共 $4^3 = 64$ 个；
- 递归思路：方法接收"当前前缀 prefix"和"剩余长度 k"；k == 0 时输出 prefix（base case）；否则对 A、C、G、T 四个字符各递归一次 `k-1`。

```java
public static void kmers(String prefix, int k) {
    if (k == 0) {                       // base case：长度凑够，输出
        System.out.println(prefix);
        return;
    }
    char[] bases = {'A', 'C', 'G', 'T'};
    for (char c : bases) {              // 多重递归：循环内 4 次调用
        kmers(prefix + c, k - 1);
    }
}
// 调用：kmers("", 3);
```

### 练习 2（第 72 页）：判断数组中是否存在"某元素 = 它前面两元素之和"

> 描述一个**递归算法**：检查整数数组 A 中是否存在某个 `A[i]`，等于**它之前**出现的两个不同整数之和：`A[i] = A[j] + A[k]`，其中 `j, k < i` 且 `j != k`。用 Java 实现。

### 练习 2 的解法大纲（第 73 页原文，逐条翻译）

1. **Base Case（基本情形）**
   - 如果数组**少于 3 个元素**，返回 `false` —— 因为不可能存在"某元素等于前面两个不同元素之和"。
2. **Recursive Case（递归情形）**
   - 从**最后一个元素** `A[i]` 开始：检查是否存在两个不同的 `A[j]`、`A[k]`（`j < k < i`）使 `A[i] = A[j] + A[k]`；
   - 若存在 → 返回 `true`；
   - 若不存在 → 递归处理**去掉最后一个元素的子数组** `A[0...i-1]`（问题规模减 1）。

参考实现：

```java
// hasSum(A, i) 表示：在 A[0..i] 中是否存在满足条件的 A[i']
public static boolean hasSum(int[] A, int i) {
    if (i < 2) return false;                 // base case：少于 3 个元素
    for (int j = 0; j < i; j++) {            // 检查 A[i] 本身
        for (int k = j + 1; k < i; k++) {
            if (A[i] == A[j] + A[k]) return true;
        }
    }
    return hasSum(A, i - 1);                 // 递归：去掉最后一个元素
}
// 调用：hasSum(A, A.length - 1);
```

---

## 14. 重点英文词汇总表

| English | 中文 | 出现页 |
|---|---|---|
| recursion | 递归 | 49–50 |
| a method calls itself | 方法调用自身 | 50 |
| base case | 基本情形 / 递归出口 | 50, 57, 60, 66, 73 |
| recursive case | 递归情形 | 50 |
| factorial | 阶乘 | 50 |
| recursive definition | 递归定义 | 50 |
| recursion trace | 递归轨迹（追踪图） | 51–54, 61 |
| run-time stack / call stack | 运行时调用栈 | 51–54 |
| stack frame | 栈帧 | 51–54 |
| stack overflow | 栈溢出 | 58–59 |
| infinite recursion | 无限递归 | 57, 58–59 |
| integer division | 整数除法 | 54, 58 |
| modulo（%） | 取模 / 求余 | 58 |
| linear recursion | 线性递归 | 57–59 |
| single recursive call | 单次递归调用 | 58 |
| makes progress towards a base case | 向基本情形推进 | 58 |
| termination | 终止性 | 57, 58–59 |
| swap | 交换 | 60 |
| arguments / parameters | 实参 / 形参 | 62–63 |
| pass forward via parameters | 通过参数向下传递 | 63 |
| return value | 返回值 | 63 |
| tail recursion | 尾递归 | 64–65 |
| last step | 最后一步 | 64 |
| iterative | 迭代的 | 64 |
| tail-call optimization (TCO) | 尾调用优化 | 65 |
| binary recursion | 二分递归 | 66–67 |
| two recursive calls | 两个递归调用 | 66 |
| divide and conquer | 分治 | 66, 69 |
| recursion tree | 递归树 | 67 |
| multiple recursion | 多重递归 | 68 |
| enumerate | 枚举 | 68 |
| combinations | 组合 | 68 |
| subset | 子集 | 71 |
| k-mer | k 长度序列片段（DNA） | 71 |
| unwinding | 逐层返回（回溯展开） | 51–54 |

---

## 15. 外教课堂常用句型

- *"What is recursion?"* → Recursion is when a method calls itself.
- *"What is the base case?"* → The case where the method stops and does not call itself again; every recursive call must eventually reach it.
- *"Why do we need a base case?"* → To avoid infinite recursion and stack overflow.
- *"What is tail recursion?"* → A linear recursion where the recursive call is the last step, so it can be rewritten as a loop.
- *"What is binary recursion?"* → A recursion with two recursive calls per non-base case, e.g., divide and conquer.
- *"What is the time complexity / recursion depth of BinarySum?"* → Time O(n), depth O(log n).
- 高频口语：**base case**（出口）、**make progress**（逐步缩小）、**call itself**（调用自身）、**blow the stack**（把栈撑爆 = stack overflow）、**trade-off**（权衡）。

---

## 16. 一句话总结

> **递归 = base case（出口）+ recursive case（向出口推进的自调用）**
> 线性递归（1 次调用）常可转迭代；二分递归（2 次调用）即分治，深度只有 O(log n)；多重递归（多次调用）用于穷举枚举。
> 写递归先问三句英文：*Is there a base case? Does every call make progress? Is it the last step (tail)?*

---

*说明：本笔记基于对 PDF 第 49–73 页的逐页文本核对编写；第 51、52、54、61、67 等页为嵌入图片的动画/示意图帧，其内容按课件常见演示逻辑转述，请以课堂画面为准。代码中除注明"PPT 原文"外，为便于理解给出的标准示范实现。*
