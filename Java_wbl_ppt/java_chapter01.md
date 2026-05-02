# Objects

### Behavior/Operations/Methods

**Object behavior** includes:  
1. **accessing** its own attributes.
2. **modifying** its attributes.

- **Operations = Services**
- Operation are services accessible to clients, which is a manifestation for encapsulation. 

---

# Class

- class is an abstract collection of objects sharing common attributes and behaviors.

- class = model
- object = example
> An object is an instance of a class.

### Declaration vs. Creation
e.g. 
```java 
Student john;
```
- It is a step to declaring a  **reference variable** which is a container capable of holding the memory address of "Student".

- At this stage, the variable is null before using constructor.
  
e.g.
```java
john = new student( );
john = new student( );
```

- The keyword **new** triggers the creation of an actual instance in the Heap memory
- Then the JVM would find a free space in Memory , constructs the Student there, and return the reference via operator "=" to john variable.

---

# Composition

### Advantages of Composition:

1. **Avoids** **Data** **Redundancy**:
If ten students choose the same professor, there is no need to duplicate the professor's data for each student. They simply share a reference.
2. **Maintains** **Data** **Integrity**:
If the professor's name changes, the update is automatically reflected for all students because the change happens in the single Professor object.
3. **Mechanism**:
The Student class contains a reference to the Professor class, which enables the student to access the professor's data directly.

---

# API

API represents an extensive Java library.

e.g.
```java
import java.util.StringTokenizer;

String s = "Hello,World;Java";

StringTokenizer st = 
new StringTokenizer(s,",;")'
// for iterating thr String.
```

- **java.lang** is the only package imported implicitly into every Java program.

---

# **Summary**

- **Object** is the material which could be perceived by our senses.
- object behaviors: 
    - 1. accessing to the data;
    - 2. modifying the data;
- operation = service (for the user) 
---
- **Class** is the abstraction of some objects sharing the same attributes and operation.
---
- **Composition**
- advantages: 
  - 1. avoids data redundancy 
  - 2. maintain data integrity
- mechanism: we are passing the **reference** of the source object to the target object, allowing the latter to resolve and access the former's data.
---
# creation vs. declaration
- 1. After declaration, reference variable is null in the Heap memory.
- 2. Creation : The keyword **new** triggers the constructor of the specific class, and return the reference address to the variable via operator " = "
---
# API
- represents an extensive Java library.
- **java.lang** is the only package imported implicitly into every Java projects.