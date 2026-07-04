# Methods


```java
public class BankAccount{
    private int balance;

    public void deposit(int amount){//header
        int newBalance = this.balance + amount;//newBalance-> local variable; amount -> parameter;
        this.balance = newBalance;
    }
}
```

- argument means "实参"

## Passing Primitive Types
- Arguments are passed to a method using the **pass-by-value** scheme
    - Changes made to the parameters will not affect the value of corresponding arguments.

## Passing Objects as Parameters
- Arguments are passed to a method using the **pass-by-reference** scheme
    - When methods returns, parameters disappear.Objects has been changed.

# Message Passing & Dot Notation
- think of the notation **x.** as "talking to object x".

# Obtaining Handles on Objects
- ###### the ways of A handle on B
    - A maintain a reference to B as one of A's attributes
    - A reference to B may be made " globally available"
    - A may be handed a reference to B as an argument of one of A's methods.
    - A may have to explicitly request a handle to B by calling a method on some third object C.(admin)
  
    ```java
     public void startReading(Librarian librarianC) {
        // 【关键点】：Student(A) 不能直接变出 Book(B)
        // Student(A) 必须调用 Librarian(C) 的方法
        // 这里的 librarianC 就是 PPT 里的 "third object C"
        
        this.myReadingBook = librarianC.getBookRequest(); 
        
        System.out.println("拿到了书的引用，开始阅读！");
    }
    ```
    ---