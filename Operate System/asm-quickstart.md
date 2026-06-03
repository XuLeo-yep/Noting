# 汇编快速入门：花半天搞懂 OS 需要的三件事

> 面向软件学院大一下学生 · 不追求精通，够用就行

---

## 0. 先搭环境

你需要能写、能跑汇编。推荐 **NASM + gcc**（Linux，或 WSL / 虚拟机）。

```bash
# Ubuntu / Debian
sudo apt install nasm gcc

# 写一个文件 test.s，然后：
nasm -f elf64 test.s -o test.o
gcc test.o -o test -no-pie
./test
```

> macOS 请用 `clang` 替代 gcc；Windows 建议装 WSL，别在原生 Windows 上折腾。

---

## 一、寄存器 —— CPU 里的临时小抽屉

### 1.1 什么是寄存器

寄存器是 CPU 内部**最快、最小**的存储单元。  
内存的速度很慢（百纳秒级），寄存器的速度就是一个时钟周期（纳秒级）。  
所以 CPU 算任何东西都必须先**把数据从内存搬到寄存器**，算完再写回去。

> **一句话：寄存器 ≈ CPU 的工作台，内存 ≈ 仓库。你不可能在仓库里干活。**

### 1.2 x86-64 常用寄存器一览

| 寄存器 | 用途 | 绰号 |
|--------|------|------|
| `rax` | 返回值 / 累加 | 返回值寄存器 |
| `rbx` | 备用存储 | 被调用者保存 |
| `rcx` | 循环计数 | 计数器 |
| `rdx` | 数据 / 乘法扩展 | 数据寄存器 |
| `rsi` | 源地址 | 源索引 |
| `rdi` | 目的地址 | 目标索引 |
| `rsp` | **栈顶指针** | 栈指针 |
| `rbp` | **栈底指针** | 基址指针 |
| `r8` – `r15` | 通用 | 扩展寄存器 |
| `rip` | **指向下一条指令** | 指令指针（不可直接修改） |
| `rflags` | 标志位（零、进位等） | 标志寄存器 |

### 1.3 寄存器的子集

x86-64 兼容 32/16/8 位操作：

```
| 64 位 | 32 位 | 16 位 | 8 位（低） | 8 位（高） |
|-------|-------|-------|----------|----------|
| rax   | eax   | ax    | al       | ah       |
| rbx   | ebx   | bx    | bl       | bh       |
| ...   | ...   | ...   | ...      | ...      |
```

### 1.4 实操：看寄存器

创建一个文件 `regs.s`：

```asm
section .text
global main

main:
    mov rax, 42        ; 把 42 放进 rax "抽屉"
    mov rbx, 58        ; 把 58 放进 rbx
    add rax, rbx       ; rax = rax + rbx = 100
    ; 此时 rax = 100（函数返回值）

    ret                ; 返回，rax 就是返回值
```

编译运行：

```bash
nasm -f elf64 regs.s -o regs.o
gcc regs.o -o regs -no-pie
./regs; echo $?    # $? 是上一个命令的退出码，输出 100
```

> **看，CPU 全程只在寄存器里倒腾，完全没碰内存。**

---

## 二、栈和栈帧 —— 函数调用时的内存布局

### 2.1 栈是什么

栈是内存里一块 **后进先出** 的区域。  
程序运行时，每个函数调用都会在栈上分配一块空间，叫 **栈帧**。  

栈帧存什么？
- **局部变量**（你的 `int x` 存在这里）
- **返回地址**（函数结束后回到哪）
- **上一个函数的栈帧基址**
- **参数**（传不下了才压栈）

### 2.2 栈的视觉印象

```
高地址                    低地址
┌─────────────────────────────┐
│   main 的局部变量            │  ← main 的栈帧
├─────────────────────────────┤
│   foo 的返回地址            │
│   foo 的局部变量            │  ← foo 的栈帧
├─────────────────────────────┤
│   bar 的返回地址            │
│   bar 的局部变量            │  ← bar 的栈帧（当前活动）
└─────────────────────────────┘
                              ↑ rsp（栈顶指针）
```

**栈向低地址增长**：`push` 使 rsp 减小，`pop` 使 rsp 增大。

### 2.3 栈帧的关键操作

| 指令 | 效果 |
|------|------|
| `push rax` | rsp -= 8，然后把 rax 写入 [rsp] |
| `pop rax` | 从 [rsp] 读出到 rax，然后 rsp += 8 |
| `call foo` | push 返回地址，然后 rip = foo 的地址 |
| `ret` | pop 出返回地址到 rip |

### 2.4 标准函数调用流程（C calling convention）

看一个 C 函数调用的汇编长什么样。

**C 代码：**
```c
int add(int a, int b) {
    int c = a + b;
    return c;
}

int main() {
    int x = add(1, 2);
    return x;
}
```

**对应的汇编（人工写，不是编译器输出）：**

```asm
section .text
global main

; int add(int a, int b)
add:
    push rbp          ; 保存 main 的 rbp
    mov  rbp, rsp      ; rbp = rsp（划定自己的栈帧）

    ; 参数已经由调用者放在 rdi (a=1), rsi (b=2)
    mov  rax, rdi      ; rax = a
    add  rax, rsi      ; rax += b → rax = 3

    ; 局部变量 c 其实就在 rax 里，不需要栈
    ; 但如果 c 需要存到栈上：
    ; mov  [rbp-8], rax

    mov  rsp, rbp      ; 恢复 rsp
    pop  rbp           ; 恢复 rbp
    ret                ; 返回，返回值在 rax

main:
    push rbp
    mov  rbp, rsp

    mov  rdi, 1        ; 第一个参数 → rdi
    mov  rsi, 2        ; 第二个参数 → rsi
    call add           ; push 返回地址，跳转到 add

    ; 此时 rax = 3
    ; 返回值已经在了，直接 return
    mov  rsp, rbp
    pop  rbp
    ret
```

编译运行：
```bash
nasm -f elf64 func.s -o func.o
gcc func.o -o func -no-pie
./func; echo $?    # 输出 3
```

### 2.5 关键记住

1. **rbp 是栈帧的"围栏"** —— rbp 固定，rsp 在函数内不断变化。用 rbp 定位局部变量最方便。
2. **参数传递**：前 6 个参数依次放在 `rdi, rsi, rdx, rcx, r8, r9`，再多才压栈。这比全压栈快得多。
3. **返回值永远在 rax**。

---

## 三、系统调用 —— 从用户态跳到内核态

### 3.1 为什么需要系统调用

你的程序运行在 **用户态**（ring 3），不能直接操作硬件、不能直接读写文件、不能直接分配内存。  
这些事只有 **内核态**（ring 0）才能做。

想从用户态进入内核态，必须通过 **系统调用指令**。

### 3.2 x86-64 的系统调用

在 64 位 Linux 上，系统调用用 `syscall` 指令。

**调用规则：**

| 做什么 | 放哪 |
|--------|------|
| 系统调用号 | rax |
| 参数 1 | rdi |
| 参数 2 | rsi |
| 参数 3 | rdx |
| 参数 4 | r10 |
| 参数 5 | r8 |
| 参数 6 | r9 |
| 返回值 | rax |
| 执行 | `syscall` |

### 3.3 常见系统调用号

| 名字 | 编号（rax） | 参数 |
|------|-----------|------|
| `write` | 1 | fd (rdi), buf (rsi), count (rdx) |
| `read` | 0 | fd (rdi), buf (rsi), count (rdx) |
| `exit` | 60 | code (rdi) |

> 全部列表：`/usr/include/asm/unistd_64.h`

### 3.4 完整例子：不用 C 库，直接打印 "Hello!"

```asm
section .data
    msg db 'Hello, OS!', 10    ; 字符串 + 换行符
    len equ $ - msg             ; 长度计算

section .text
global _start                  ; 程序入口，不用 C 库

_start:
    ; write(1, msg, len)
    mov rax, 1     ; 系统调用号 = write
    mov rdi, 1     ; fd = 1（stdout）
    mov rsi, msg   ; buf = 字符串地址
    mov rdx, len   ; count = 长度
    syscall         ; ⚡ 跳到内核态，内核执行 write

    ; exit(0)
    mov rax, 60    ; 系统调用号 = exit
    xor rdi, rdi   ; code = 0（xor 自身等于清零）
    syscall
```

编译运行（注意这里不用 gcc 链接，直接链接）：

```bash
nasm -f elf64 hello.s -o hello.o
ld hello.o -o hello
./hello    # 输出 Hello, OS!
```

> 这是**纯汇编**！你没有用任何 C 库，直接通过 `syscall` 让内核帮你写屏幕。

### 3.5 syscall 背后发生了什么（一句话）

```
用户态                   内核态
  │                       │
  │── syscall ──────────> │
  │                       │  切换到内核栈
  │                       │  查系统调用表
  │                       │  执行对应内核函数
  │<── 返回 ─────────────│  
  │                       │  切换回用户栈
用户态继续运行             
```

`syscall` 指令做了三件事：
1. 把返回地址存到 `rcx`
2. 把新的指令指针（内核入口）从 `MSR` 寄存器取出来装进 `rip`
3. 切换到内核栈

返回时用 `sysretq` 指令，它利用 `rcx` 里存的地址跳回来。

---

## 四、综合练习：把三件事串起来

写一个程序，调用一个函数，函数里做系统调用：

```asm
section .data
    msg db 'sum = '
    newline db 10

section .bss
    buf resb 4          ; 4 字节缓冲区

section .text
global _start

; 把 rax 里的数字转成十进制字符串写到 buf
; 返回写入的字节数
itoa:
    push rbp
    mov  rbp, rsp
    
    mov  rcx, buf + 3   ; 从末尾开始写
    mov  byte [rcx], 0   ; 末尾填 0
    
.loop:
    xor  rdx, rdx
    mov  rbx, 10
    div  rbx             ; rax = rax / 10, rdx = 余数
    add  dl, '0'         ; 数字 → ASCII
    dec  rcx
    mov  [rcx], dl
    test rax, rax
    jnz  .loop           ; rax != 0 则继续
    
    ; rcx 指向字符串开头
    mov  rax, rcx
    sub  rax, buf        ; rax = buf 地址偏移
    neg  rax             ; 变成正数
    add  rax, 3          ; 加 3 就是数字的字符数
    ; 其实直接算 buf+3 - rcx 更简单，这里为了方便理解
    
    mov  rsp, rbp
    pop  rbp
    ret

_start:
    ; 计算 1234 + 5678
    mov  rdi, 1234
    mov  rsi, 5678
    call add_func
    
    ; 把结果转成字符串
    call itoa
    
    ; write(1, msg, 6)     输出 "sum = "
    mov  rax, 1
    mov  rdi, 1
    mov  rsi, msg
    mov  rdx, 6
    syscall
    
    ; write(1, buf, len)
    mov  rax, 1
    mov  rdi, 1
    mov  rsi, buf
    mov  rdx, 4
    syscall
    
    ; write(1, newline, 1)
    mov  rax, 1
    mov  rdi, 1
    mov  rsi, newline
    mov  rdx, 1
    syscall
    
    ; exit(0)
    mov  rax, 60
    xor  rdi, rdi
    syscall

add_func:
    push rbp
    mov  rbp, rsp
    mov  rax, rdi
    add  rax, rsi       ; rax = 1234 + 5678 = 6912
    mov  rsp, rbp
    pop  rbp
    ret
```

> 这个程序用了 **寄存器**（rax, rdi, rsi...），**栈帧**（push/pop rbp），和 **系统调用**（write, exit）—— 你要学的三件事全了。

---

## 五、下一步学什么（半天不够就一天）

你已经会了 OS 需要的汇编基底，接下来：

1. **中断**（`int` 指令）—— 学 OS 迟早要碰
2. **特权级切换**（ring 0 vs ring 3）—— 彻底理解 syscall
3. **内联汇编** —— 在 C 里嵌入汇编（OS 内核源码常见）
   ```c
   __asm__ volatile("syscall" : "=a"(ret) : "a"(SYS_write), ...);
   ```
4. **GDB 调试汇编** —— `gdb ./prog`，`layout asm`，`stepi`
5. **阅读一个最小内核**（如 xv6）—— 你会发现自己能看懂一些了

---

## 六、速查卡

```
寄存器用途（OS 相关）:
  rax   → 返回值 + 系统调用号
  rdi   → 参数1 / syscall 参数1
  rsi   → 参数2 / syscall 参数2
  rdx   → 参数3 / syscall 参数3
  rsp   → 栈顶指针（永远指向栈顶）
  rbp   → 栈帧基址（围栏）
  rip   → 下一条指令地址

栈帧模板:
  push  rbp
  mov   rbp, rsp
  ...   干活 ...
  mov   rsp, rbp
  pop   rbp
  ret

系统调用模板:
  mov   rax, 系统调用号
  mov   rdi,  arg1
  mov   rsi,  arg2
  mov   rdx,  arg3
  syscall            ; 交内核
```

---

**好，花半天看完这个，你就能看懂一个最小 OS（比如 xv6）里大部分汇编代码了。够用了。**
