### 理论基础
#### 特点 
1. 内存地址连续 （java exception）
    1. 注意删除或增添元素后 其他元素是否要移动
2. 下标从0开始
3. 元素无法删除，只能用0覆盖实现，arry大小从声明时确定
---
##### 二分查找
###### prerequisite：sorted

core idea
1. 每次检查中间
2. 排除一半不可能区间
3. 时间复杂度 log n

### inclusive on both ends VS. left-inclusive and right-exclusive
1. 右边边界可以取到 故
```cpp
    int right = nums.size() - 1; // start with 0
    while(left <= right ){
        if(nums[middle] > target){
            right = middle - 1; //右边界可取的情况下，nums[middle]这个数明显大于right 舍弃
        }
    }
```
2. 右边界取不到
```cpp
    int right = nums.size(); // start with 0
    while(left < right ){
        if(nums[middle] > target){
            right = middle; //右边界不可取的情况下，即使nums[middle]这个数明显大于right，也不会进入下一次loop
        }
    }
```
### summary 

1. 注意边界值是否取到 三处不同 用边界值判断 右边界是否可取
   1. **根据查找区间的定义来作边界处理** 
2. 注意nums[middle] 与 target比较
3. middle = left + （right - left） /2；非负且防止溢出

---
##### element_remove
也就是实现库函数erase
1. 时间复杂度O(n)
2. 删除目标元素 且将后面的元素向前移动
3. 最后返回数组长度
##### double-pointer-solution O(n)
1. 快指针寻找新数组的元素
      1. 新数组就是不含目标元素的数组
2. 慢指针就是新数组的下标 最终返回慢指针就是返回数组长度
### summary
1. core idea： 将非目标值通过快指针赋值给慢指针，最终得到新数组
2. 条件 
   ```cpp
   if(nums[fastIndex] != val){
        nums[slowIndex++]=nums[fastIndex];
   }
```