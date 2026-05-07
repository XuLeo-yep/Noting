## Methods
##### Requesting Object Services

- Object's methods are regard as *services* that can be requested by the whole app.
- Signature: The specific vocabulary used to request a service.
  - 1. methods name
  - 2. parameters

Method  Header = Modifier + Return Type + Method Signature + Exception Declaration  

---

## Message Passing and Dot Notation

- Dot notation: invoking a method on that object's reference variable.

#### Obtaining Handles on Objects 

- The ways to A handle on B.
  - Object A might maintain a reference to B as one of A's attributes. (**Association**)
  - Object A may be handed a reference to B as an argument of one of A's methods.
  - B is globally available
  - A may have to explicitly request a handle to B By calling a method on some **third object C**


