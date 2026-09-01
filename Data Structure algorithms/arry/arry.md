### 理论基础
#### 特点 
1. 内存地址连续 （java exception）
    1. 注意删除或增添元素后 其他元素是否要移动
2. 下标从0开始
3. 元素无法删除，只能用0覆盖实现，arry大小从声明时确定

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
1. 二分查找 
   1. 注意边界值是否取到 三处不同 用边界值判断 右边界是否可取
         1. **根据查找区间的定义来作边界处理** 
   2. 注意nums[middle] 与 target比较
   3. middle = left + （right - left） /2；非负且防止溢出