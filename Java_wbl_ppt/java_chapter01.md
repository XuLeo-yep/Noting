# Objects

## Behavior/Operations/Methods

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

## Declaration vs. Creation
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

- The keyword **new** trigger the creation of an actual instance in the Heap memory
- Then the JVM would find a free space in Memory , constructs the Student there, and return the reference via operator "=" to john variable.

    
