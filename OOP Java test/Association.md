# one-to-many

- java.lang is the only auto-imported package.
- " call " means " 调用 "
- " instantiated " means " 实例化 "
###### —— vs ——>
- In UML class diagrams, a solid line with an arrow indicates a unidirectional association where only the source class holds a reference to the target, whereas a plain line without an arrow signifies a bidirectional association implying that both classes hold references to each other.
  
  
1. 
``` java
import java.util.ArrayList

public class Order {
    private ArrayList<OrderItem> orders;

    public Order(){
        this.orders = new ArrayList<>();
    }
}
```
- 勤汉  Prefer initializing in the Constructor instead of  at the declaration.
- Always initialize collections.

2. In the UML diagram, one-to-many association will be represented by a line labeled " - has".

# has-many

**Aggregation vs Composition**
1. #### Aggregation(**weak**): the part still exists even the whole is destroyed.
###### UML表示：**空心**菱形 + 实线（菱形靠近“整体”那一端）。

```java
// 聚合：Department 聚合了 Employee
public class Department {
    private List<Employee> employees;

    // 员工在外部创建，传进来
    public Department(List<Employee> employees) {
        this.employees = employees;
    }
}
```

2. #### Composition(**strong**): the part can not exists without the whole.
###### UML表示：**实心**菱形 + 实线（菱形靠近“整体”那一端）。

```java
// 组合：House 组合了 Room
public class House {
    private Room livingRoom;

    public House() {
        // Room 的生命周期完全由 House 控制
        this.livingRoom = new Room("Living Room");
    }
}
```
- Objects as Attributes