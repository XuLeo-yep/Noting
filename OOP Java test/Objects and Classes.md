# Object
the specific material that can be perceived by the senses

1. Attributes
    2. put attributes together -> state
2. Behavior 
   - to access or modify the attribute values
   - as services for its clients
---
# Class 
the models of real-world entities.

1. data structure
  - name
  - type
2. operation  
---
# Declaration vs. Creation
1. 
```java 
Student john;
```
- It is a step to declaring a  **reference variable** ,in the Stack, which is a container capable of holding the memory address of "Student".

- At this stage, the variable is null before using constructor.
  
2. 
```java
john = new student( );
john = new student( );
```

- The keyword **new** triggers the creation of an actual instance in the Heap memory
- Then the JVM would find a free space in Memory , constructs the Student there, and return the reference via operator "=" to john variable.
---
# Composition
["composition" in previous note](Association.md#compositionstrong-the-part-can-not-exists-without-the-whole)

### Advantages of Composition:

1. **Avoids** **Data** **Redundancy**:
If ten students choose the same professor, there is no need to duplicate the professor's data for each student. They simply share a reference.
1. **Maintains Data Integrity**:
If the professor's name changes, the update is automatically reflected for all students because the change happens in the single Professor object.

  -   **Mechanism** ：
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

## The Wrapper Classes
classes that mimic the primitives
- java.lang.Byte -> byte
---
    
  - respecting case means 遵从大小写规则