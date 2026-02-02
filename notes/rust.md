# Comprehensive Rust Notes (Deep Dive)

This document provides a deep dive into the Rust programming language, with extensive code examples for nearly every keyword and concept.

### 1. Rust Philosophy & Design Goals

- **Zero-cost abstractions**: You should not pay a performance penalty for high-level features. An abstraction should compile down to code that is as efficient as if you had written the low-level equivalent by hand.

  ```rust
  // This high-level, functional-style iterator...
  let numbers: Vec<i32> = (1..=100).collect();
  let sum_of_squares_of_evens: i32 = numbers
      .iter() // Borrow the vector and create an iterator
      .filter(|&&n| n % 2 == 0) // Filter for even numbers
      .map(|&n| n * n) // Square each number
      .sum(); // Sum the results

  // ...compiles down to machine code that is just as efficient as
  // a hand-written, low-level loop, with no runtime overhead.
  let mut sum = 0;
  for &num in &numbers {
      if num % 2 == 0 {
          sum += num * num;
      }
  }
  assert_eq!(sum_of_squares_of_evens, sum);
  ```

- **Memory safety without GC**: Rust's ownership, borrowing, and lifetime rules are a static analysis system enforced at compile time. This prevents entire classes of bugs (dangling pointers, data races, use-after-free) without the runtime overhead of a garbage collector (GC).
- **Fearless concurrency**: The compiler's type system includes `Send` and `Sync` marker traits that ensure types used across threads are safe to do so. If your concurrent code compiles, it is guaranteed to be free of data races.
- **Explicitness over magic**: Important operations are visible in the code. This makes code easier to reason about, debug, and maintain.
  - `mut`: Explicitly marks variables and references as mutable.
  - `Box`, `Vec`, `String`: Explicit heap allocations.
  - `Result<T, E>`: Explicit, type-checked error handling.
  - `unsafe`: Explicitly marks code that bypasses some of Rust's safety guarantees.
- **Compile-time correctness**: Rust's strict compiler catches a vast range of errors before the program runs. While this can feel like "fighting the borrow checker" for beginners, it leads to more robust software and fewer runtime panics.

---

### 2. Rust Compilation Model

- **Crate**: The smallest unit of compilation and linking. A crate can be a binary (`src/main.rs`) or a library (`src/lib.rs`).
- **Package**: A collection of one or more crates, described by a `Cargo.toml` file. A package can have at most one library crate, but many binary crates (e.g., in `src/bin/`).
- **`rustc`**: The Rust compiler. You rarely invoke it directly.
- **`cargo`**: Rust's build tool and package manager.
  - `cargo new my_project`: Creates a new binary package.
  - `cargo new my_lib --lib`: Creates a new library package.
  - `cargo build`: Compiles in debug mode (slow execution, fast compile).
  - `cargo build --release`: Compiles with optimizations (fast execution, slow compile).
  - `cargo run`: Builds and runs the main binary.
  - `cargo test`: Runs all tests.
  - `cargo check`: Quickly checks for errors without producing a binary.
- **Modules**: A system for organizing code into a hierarchy of crates and modules.

  ```rust
  // File: src/lib.rs
  // This declares a module named `network`. The compiler will look for
  // the code in `src/network.rs` or `src/network/mod.rs`.
  pub mod network;

  // File: src/network.rs
  // This declares a submodule named `server`.
  pub mod server {
      pub fn connect() {
          println!("Server connected.");
      }
  }

  // To use it from main.rs (assuming this is a library crate named `my_lib`):
  // File: src/main.rs
  // use my_lib::network::server;
  // server::connect();
  ```

- **Monomorphization**: The process of turning generic code into specific code at compile time.
- **Ahead-of-time (AOT) compilation**: Rust compiles directly to native machine code, resulting in fast startup and execution.
- **No runtime / minimal runtime**: The code that runs before your `main` function is extremely small. There is no virtual machine (VM) or large runtime system.

---

### 3. Primitive Data Types

- **Integers**: `i8` to `i128`, `u8` to `u128`, `isize`, `usize` (pointer-sized).
  - **Integer Overflow**: In debug builds, overflow will `panic`. In release builds, it performs two's complement wrapping.
  ```rust
  let mut i: u8 = 255;
  // In a debug build, this line would panic:
  // i += 1;
  // You can use checked operations to handle overflow explicitly.
  assert_eq!(i.checked_add(1), None);
  // Or wrapping operations if wrapping is the desired behavior.
  let j = i.wrapping_add(1);
  assert_eq!(j, 0);
  ```
- **Floating point**: `f32`, `f64`.
- **`bool`**: `true` or `false`.
- **`char`**: A 4-byte Unicode Scalar Value.
- **unit type `()`**: An empty tuple. It represents the absence of a value.
- **Type casting with `as`**: Rust requires explicit casting.
  ```rust
  let a: f32 = 10.5;
  let b: i32 = a as i32; // Truncates the float. b is 10.
  let c: u8 = b as u8;
  // Be careful: casting can lose information.
  let big_num: i32 = 1000;
  let small_num: u8 = big_num as u8; // small_num is 232 (1000 % 256)
  println!("{}", small_num);
  ```
- **Shadowing**: You can declare a new variable with the same name as a previous one.
  ```rust
  let x = 5;
  // The new `x` shadows the old one. It can even have a different type.
  let x = x + 1;
  let x = "a string now";
  println!("The value of x is: {}", x);
  ```

---

### 4. Ownership Model (CORE SECTION)

- **Ownership Rules**:
  1. Each value has one and only one owner.
  2. When the owner goes out of scope, the value is dropped.
  3. Ownership can be moved.
- **Move Semantics**: Default for heap-allocated types.
  ```rust
  // s1 is the owner of a String allocated on the heap.
  let s1 = String::from("hello");
  // Ownership of the String is moved to s2.
  // The pointer, length, and capacity are copied from s1's stack frame to s2's.
  // s1 is now considered uninitialized and cannot be used.
  let s2 = s1;
  // println!("{}", s1); // COMPILE ERROR: value borrowed here after move
  ```
- **Copy Types**: Implement the `Copy` trait. Stored entirely on the stack.
  ```rust
  // A custom struct that can be copied.
  // All its fields must also be `Copy`.
  #[derive(Debug, Copy, Clone)]
  struct Point {
      x: i32,
      y: i32,
  }
  let p1 = Point { x: 1, y: 2 };
  // The value of p1 is bit-for-bit copied to p2.
  // Both are independent instances on the stack.
  let p2 = p1;
  println!("p1: {:?}, p2: {:?}", p1, p2); // Both are valid.
  ```
- **Ownership and Functions**:

  ```rust
  fn takes_ownership(some_string: String) {
      println!("{}", some_string);
  } // `some_string` goes out of scope and `drop` is called. The memory is freed.

  fn makes_copy(some_integer: i32) {
      println!("{}", some_integer);
  } // `some_integer` goes out of scope. Nothing special happens.

  let s = String::from("hello");
  takes_ownership(s); // s's ownership is moved into the function.
  // println!("{}", s); // COMPILE ERROR

  let x = 5;
  makes_copy(x); // x is copied into the function.
  println!("{}", x); // x is still valid here.
  ```

- **`Drop` Trait**: For custom cleanup logic (RAII).
  ```rust
  struct FileHandle;
  impl Drop for FileHandle {
      fn drop(&mut self) {
          // Code to close the file would go here.
          println!("FileHandle dropped, resource released.");
      }
  }
  let fh = FileHandle; // Resource acquired.
  // `fh` is dropped at the end of the scope, automatically releasing the resource.
  ```

---

### 5. Borrowing & References

- **Borrowing**: Creating a reference (`&T`) to a value without taking ownership.
- **Borrow Checker Rules**: In a given scope, you can have either:
  - One mutable reference (`&mut T`), OR
  - Any number of immutable references (`&T`).
- **Dangling References**: The compiler guarantees this will never happen.
  ```rust
  /*
  fn dangle() -> &String { // dangle returns a reference to a String
      let s = String::from("hello"); // s is a new String
      &s // we return a reference to the String, s
  } // Here, s goes out of scope, and is dropped. Its memory is gone.
    // The reference would be pointing to invalid memory.
    // The compiler will reject this code with an error:
    // "missing lifetime specifier"
    // "this function's return type contains a borrowed value, but there is no value for it to be borrowed from"
  */
  ```
- **Non-Lexical Lifetimes (NLL)**: A borrow's lifetime lasts until its last use, not the end of its lexical scope.
  ```rust
  let mut s = String::from("hello");
  let r1 = &s;
  println!("r1: {}", r1);
  // The borrow for `r1` ends here because it's not used again.
  let r2 = &mut s; // This is now allowed.
  r2.push_str(", world");
  println!("r2: {}", r2);
  ```

---

### 6. Compound Data Types

- **`String`**: An owned, heap-allocated, growable, UTF-8 encoded string.
  ```rust
  let mut s = String::from("foo");
  s.push_str("bar"); // Appends a string slice
  s.push('!'); // Appends a char
  println!("{}", s); // "foobar!"
  let s2 = s.replace("foo", "baz"); // Returns a new String
  println!("{}", s2); // "bazbar!"
  ```
- **`&str` (string slice)**: A borrowed, immutable view into a `String` or a string literal.
- **`Vec<T>`**: A growable, heap-allocated vector.

  ```rust
  let mut v = vec![10, 20, 30];
  v.push(40);
  let third: &i32 = &v[2]; // Access with indexing (can panic)
  println!("The third element is {}", third);

  match v.get(2) { // Access with .get() (returns Option)
      Some(third) => println!("The third element is {}", third),
      None => println!("There is no third element."),
  }
  // A Vec has a length (number of elements) and a capacity (space allocated).
  println!("Length: {}, Capacity: {}", v.len(), v.capacity());
  ```

- **`HashMap<K, V>`**: A hash map.

  ```rust
  use std::collections::HashMap;
  let mut scores = HashMap::new();
  scores.insert("Blue", 10);
  scores.insert("Red", 50);

  // Using the entry API to insert only if the key has no value.
  scores.entry("Yellow").or_insert(30);
  scores.entry("Blue").or_insert(100); // Does nothing, "Blue" already exists.

  for (key, value) in &scores {
      println!("{}: {}", key, value);
  }
  ```

- **`BTreeMap<K, V>`**: A balanced tree map. Keys are always sorted. Slower than `HashMap` but predictable iteration order.

---

### 7. Structs

- **Named-field structs**:
  ```rust
  #[derive(Debug)]
  struct User {
      username: String,
      active: bool,
  }
  ```
- **Tuple structs**: Useful for creating new types around a primitive.
  ```rust
  struct Color(u8, u8, u8); // RGB color
  let black = Color(0, 0, 0);
  println!("First value: {}", black.0);
  ```
- **Unit-like structs**: Have no fields. Useful as markers.
  ```rust
  struct AlwaysEqual;
  // let subject = AlwaysEqual;
  // You might use this with a trait to mark something.
  ```
- **Methods and Associated Functions**:
  ```rust
  impl User {
      // Associated function (constructor)
      fn new(username: String) -> User {
          User { username, active: true }
      }
      // Method with immutable borrow of self
      fn get_username(&self) -> &str {
          &self.username
      }
      // Method with mutable borrow of self
      fn deactivate(&mut self) {
          self.active = false;
      }
      // Method that takes ownership of self
      fn into_username(self) -> String {
          self.username
      }
  }
  ```

---

### 8. Enums (Very Important)

- **Algebraic Data Types (ADTs)**: Each variant can hold different types and amounts of data.

  ```rust
  enum Message {
      Quit, // No data
      Move { x: i32, y: i32 }, // Anonymous struct
      Write(String), // A single String
      ChangeColor(u8, u8, u8), // A tuple
  }

  fn process_message(msg: Message) {
      match msg {
          Message::Quit => println!("Quit"),
          Message::Move { x, y } => {
              println!("Move to x: {}, y: {}", x, y);
          }
          Message::Write(text) => println!("Text message: {}", text),
          Message::ChangeColor(r, g, b) => {
              println!("Change color to R:{}, G:{}, B:{}", r, g, b);
          }
      }
  }
  ```

- **`Option<T>` and `Result<T, E>`** are just enums from the standard library.

---

### 9. Pattern Matching

- **`match`**: Must be exhaustive.
- **`if let` / `while let`**: For handling a single case.
- **Destructuring**:
- **`ref` and `ref mut`**: To get a reference to a value inside a pattern.
  ```rust
  let mut robot_name = Some(String::from("Bender"));
  match robot_name {
      // `ref mut name` borrows the String mutably instead of moving it.
      Some(ref mut name) => {
          *name = String::from("WALL-E");
      }
      None => {}
  }
  println!("Robot name: {:?}", robot_name); // robot_name is still valid
  ```

---

### 10. Traits

- **`trait`**: Defines shared behavior.
- **`impl Trait for Type`**: Implements the behavior for a type.
- **`derive` attribute**: A procedural macro that automatically generates `impl` blocks for common traits.
  ```rust
  // The compiler will generate impls for Debug, Clone, Copy, PartialEq, Eq
  #[derive(Debug, Clone, Copy, PartialEq, Eq)]
  struct Point { x: i32, y: i32 }
  ```
- **Orphan Rule**: You can implement a trait `T` for a type `U` only if either `T` or `U` is defined in your local crate. This prevents external crates from breaking each other's code.
- **Marker Traits**: Traits with no methods, used to give properties to types.
  - `Send`: Type is safe to move to another thread.
  - `Sync`: Type is safe to share between threads (`&T` is `Send`).
  - `Copy`: Type can be copied with a simple bit-wise copy.
  - `Sized`: Type has a known size at compile time. Most types are `Sized`. `?Sized` is used to opt-out for types like `[T]` or `str`.

---

### 11. Generics

- **`where` clauses**: For clarifying complex trait bounds.

  ```rust
  use std::fmt::{Debug, Display};
  // Without `where` clause (hard to read)
  fn some_function<T: Display + Clone, U: Clone + Debug>(t: &T, u: &U) {}

  // With `where` clause (much cleaner)
  fn some_function_where<T, U>(t: &T, u: &U)
  where
      T: Display + Clone,
      U: Clone + Debug,
  {
      // ...
  }
  ```

---

### 12. Error Handling

- **`panic!`**: For unrecoverable errors.
- **`Result<T, E>`**: For recoverable errors.

  ```rust
  use std::fs::File;
  use std::io::{self, Read};

  fn read_username_from_file() -> Result<String, io::Error> {
      let f = File::open("username.txt");

      let mut f = match f {
          Ok(file) => file,
          // Return early with the error if opening failed.
          Err(e) => return Err(e),
      };

      let mut s = String::new();

      match f.read_to_string(&mut s) {
          Ok(_) => Ok(s), // Return the string on success.
          Err(e) => Err(e), // Return the error on failure.
      }
  }
  // The `?` operator is syntactic sugar for this whole match block.
  fn read_username_with_q_mark() -> Result<String, io::Error> {
      let mut f = File::open("username.txt")?;
      let mut s = String::new();
      f.read_to_string(&mut s)?;
      Ok(s)
  }
  ```

---

### 13. Iterators & Functional Style

- **`iter()`**: Borrows and yields `&T`.
- **`into_iter()`**: Takes ownership and yields `T`.
- **`iter_mut()`**: Mutably borrows and yields `&mut T`.

  ```rust
  let mut names = vec![String::from("Alice"), String::from("Bob")];

  // `into_iter` moves the values out of the vector.
  // `names` cannot be used after this loop.
  for name in names.into_iter() {
      println!("Owned name: {}", name);
  }
  // println!("{:?}", names); // COMPILE ERROR

  let mut names = vec![String::from("Alice"), String::from("Bob")];
  // `iter_mut` allows modification of the values.
  for name in names.iter_mut() {
      name.push_str("!");
  }
  println!("{:?}", names); // ["Alice!", "Bob!"]
  ```

---

### 14. Memory Management Internals

- **`Box<T>`**: Single-owner heap pointer. Use for large objects on the stack or for recursive data structures.
  ```rust
  // A recursive type needs `Box` to have a known size.
  enum List {
      Cons(i32, Box<List>),
      Nil,
  }
  let list = List::Cons(1, Box::new(List::Cons(2, Box::new(List::Nil))));
  ```
- **`Rc<T>`**: Reference-counted pointer for multiple owners in a **single thread**.
  ```rust
  use std::rc::Rc;
  let data = Rc::new(String::from("shared data"));
  println!("Count after creation: {}", Rc::strong_count(&data)); // 1
  let owner1 = Rc::clone(&data);
  println!("Count after first clone: {}", Rc::strong_count(&data)); // 2
  {
      let owner2 = Rc::clone(&data);
      println!("Count inside scope: {}", Rc::strong_count(&data)); // 3
  } // owner2 is dropped
  println!("Count after scope: {}", Rc::strong_count(&data)); // 2
  ```
- **`Arc<T>`**: **A**tomically **R**eference-**C**ounted pointer for multiple owners across **multiple threads**. It's the thread-safe version of `Rc`.
- **`Cell<T>`**: Provides interior mutability for `Copy` types. The check is done at runtime, but it's just a simple value copy.
  ```rust
  use std::cell::Cell;
  let c = Cell::new(5);
  let five = c.get();
  c.set(10);
  println!("Cell value: {}", c.get()); // 10
  ```
- **`RefCell<T>`**: Provides interior mutability with runtime borrow checking. For non-`Copy` types. Panics if borrow rules are violated.
  ```rust
  use std::cell::RefCell;
  let rc = RefCell::new(String::from("hello"));
  // let mut borrow1 = rc.borrow_mut();
  // let mut borrow2 = rc.borrow_mut(); // This would panic at runtime!
  ```
- **`Mutex<T>`**: Mutual exclusion for shared state in multithreaded contexts. Blocks the thread until the lock is available.
- **`RwLock<T>`**: Allows multiple readers or one writer. More granular than a `Mutex`.

---

### 15. Concurrency & Thread Safety

- **`Arc<Mutex<T>>`**: The canonical way to share mutable state between threads. `Arc` allows multiple threads to own the `Mutex`, and `Mutex` ensures only one thread can access the data at a time.

  ```rust
  use std::sync::{Arc, Mutex};
  use std::thread;

  // Create a counter protected by Arc and Mutex.
  let counter = Arc::new(Mutex::new(0));
  let mut handles = vec![];

  for _ in 0..10 {
      let counter = Arc::clone(&counter);
      let handle = thread::spawn(move || {
          // Lock the mutex to get access to the data.
          // The lock is released when `num` goes out of scope.
          let mut num = counter.lock().unwrap();
          *num += 1;
      });
      handles.push(handle);
  }

  // Wait for all threads to finish.
  for handle in handles {
      handle.join().unwrap();
  }

  // Lock and print the final value.
  println!("Result: {}", *counter.lock().unwrap()); // 10
  ```

---

### 16. Unsafe Rust

- **`unsafe`**: An escape hatch to bypass some compiler guarantees.
- **Raw Pointers**: `*const T` and `*mut T`.
- **`union`**: Like a C union. Only safe to access one field at a time.
  ```rust
  union IntOrFloat {
      i: i32,
      f: f32,
  }
  let mut u = IntOrFloat { i: 1 };
  // Reading and writing to a union is unsafe.
  unsafe {
      u.i = 2;
      println!("u as integer: {}", u.i);
  }
  ```
- **Mutable static variables**: Can be changed by any thread at any time, causing data races. Accessing them is `unsafe`.
  ```rust
  static mut COUNTER: u32 = 0;
  fn add_to_count(inc: u32) {
      unsafe {
          COUNTER += inc;
      }
  }
  ```

---

### 17. Lifetimes in Practice

- **Structs with references**:
- **Methods on structs with lifetimes**:

  ```rust
  struct ImportantExcerpt<'a> {
      part: &'a str,
  }

  impl<'a> ImportantExcerpt<'a> {
      // The first elision rule applies: the lifetime of the input `&self`
      // is assigned to the output `&str`.
      fn announce_and_return_part(&self, announcement: &str) -> &str {
          println!("Attention please: {}", announcement);
          self.part
      }
  }
  ```

- **`'static` lifetime**: A reference that is valid for the entire program's duration.

---

### 18. Macros

- **Declarative Macros (`macro_rules!`)**:
- **Procedural Macros**:
  - **Custom `#[derive]`**:
    ```rust
    // In a separate crate with `proc-macro = true` in Cargo.toml
    // pub fn derive_hello_macro(input: TokenStream) -> TokenStream { ... }
    // Then in your main crate:
    // use hello_macro_derive::HelloMacro;
    // #[derive(HelloMacro)]
    // struct Pancakes;
    ```
  - **Attribute-like macros**: e.g., `#[tokio::main]`
  - **Function-like macros**: e.g., `sqlx::query!()`

---

### 19. Idiomatic Rust

- **Newtype Pattern**: Using a tuple struct to create a new type. This allows you to enforce invariants and implement traits on types you don't own.

  ```rust
  // We want to implement a trait for `Vec<String>`, but the orphan rule prevents it.
  // So we create a new type that wraps it.
  struct Wrapper(Vec<String>);

  impl std::fmt::Display for Wrapper {
      fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
          write!(f, "[{}]", self.0.join(", "))
      }
  }
  let w = Wrapper(vec![String::from("hello"), String::from("world")]);
  println!("w = {}", w); // w = [hello, world]
  ```

- **RAII (Resource Acquisition Is Initialization)**: Use the `Drop` trait to tie resource lifetimes to object lifetimes.

---

### 20. Performance Characteristics

- **Stack vs. Heap**: Accessing data on the stack is faster than the heap because it's just a pointer offset, whereas heap access involves following a pointer, potentially causing a CPU cache miss.
- **Inlining**: The compiler replaces calls to small functions with the function's body, eliminating function call overhead.
- **Monomorphization trade-off**: Fast execution at the cost of potentially larger binary sizes.

---

### 21. Common Pitfalls & Anti-Patterns

- **`&String` vs `&str` in function arguments**: Prefer `&str` as it's more general.
  ```rust
  fn takes_str_slice(s: &str) {}
  let owned_string = String::from("hello");
  let string_literal = "world";
  takes_str_slice(&owned_string); // Works
  takes_str_slice(string_literal); // Works
  ```
- **`panic!` in libraries**: Libraries should return `Result<T, E>` to let the calling application decide on the error handling strategy.
- **Unnecessary mutability**:
  ```rust
  // Bad: `v` is mutable but never changed.
  let mut v = vec![1, 2, 3];
  for x in &v {
      println!("{}", x);
  }
  // Good: `v` is immutable.
  let v = vec![1, 2, 3];
  for x in &v {
      println!("{}", x);
  }
  ```

---

### 22. Rust vs Other Languages

- **Rust `enum` vs. C++ `enum`**: Rust enums are powerful ADTs (sum types), while C++ enums are just named integers.
- **Rust `trait` vs. Java `interface`**: Similar, but Rust traits can also contain concrete methods and are used for compile-time generics (static dispatch), not just dynamic dispatch.
- **Rust error handling vs. Go error handling**: Both return errors as values, but Rust's `Result` enum and `?` operator are enforced by the type system, making it impossible to ignore an error accidentally.

---

### 23. Mental Models for Mastery

- **Ownership as a tree**: Every value has a root owner. Borrows are temporary read/write passes to sub-trees.
- **Borrow checker as a scheduler**: It schedules access to data, ensuring no write conflicts can occur.
- **`Send` and `Sync` as permissions**: `Send` is permission to move a value to another thread. `Sync` is permission to let multiple threads access it at once.
- **Lifetimes as contracts**: A function with a lifetime in its signature is making a contract with the caller about how long its references will be valid.
