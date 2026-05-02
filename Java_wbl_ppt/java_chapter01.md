# Objects

### Behavior/Operations/Methods

**Object behavior** includes:  
1. **accessing** its own attributes.
2. **modifying** its attributes.

- **Operations = Services**
- Operation are services accessible to clients, which is a manifestation for encapsulation. 

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


# Composition

### Advantages of Composition:

1. **Avoids** **Data** **Redundancy**:
If ten students choose the same professor, there is no need to duplicate the professor's data for each student. They simply share a reference.
2. **Maintains** **Data** **Integrity**:
If the professor's name changes, the update is automatically reflected for all students because the change happens in the single Professor object.
3. **Mechanism**:
The Student class contains a reference to the Professor class, which enables the student to access the professor's data directly.
    
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