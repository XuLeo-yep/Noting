# the Heart of the Java platform
- semi-compiled
  - Java source code(.java) -javac-> Java bytecode(.class)
- semi-interpreted
  - Java bytecode -Just In Time c-> Machine code
- Java virtual machine

### JVM
- following major subsystems
 - class loader
 - execution engine
 - runtime data area

## all above are designed for implementing **Write Once Run Anywhere**
---
- JDK -> Java Development Kit
 - JRE -> Java Runtime Environment
  - JVM
  - class libraries 
 - API -> Application Programming Interface
---
# Compile and Run Java src through CLI
- Compile 
  - javac HelloWorld.java
- Run
  - java HelloWorld
---
#  Language Basics
1. naming: only letters , digits , $ and _
2. Data type
   - primitive types
    - boolean  
   - reference types
    - String
   1. An integer literal is of type long if it ends with the letter **L or l**; otherwise it is of type int.
   2. A floating-point literal is of type float if it ends with the letter **F or f**; otherwise its type is double and it can optionally end with the letter D or d. 
