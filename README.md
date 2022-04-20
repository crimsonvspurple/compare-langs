# compare-langs
Compare `C`/`Java`/`Python` Performance in Matrix Multiplication

# Goals
- Implement matrix multiplication in C, Java and Python
  - For C, two versions
    -  Array + for loop
    -  Pointer arithmetics + for loop
  - For Java, three versions
    - Standard for loop
    - Stream (Parallel)
    - Without JIT
  - For Python, two versions
    - Standard for loop
    - Numpy

### Variations
`c-std`: Implementation in C using for loop and arrays (this should have been named `c-for` for coherence but too late)

`c-pointer`: Implementation in C using for loop and pointer arithmetics

`java-for`: Implementation in Java using for loop and arrays

`java-no-jit`: Same as above but disable JIT during runtime

`java-stream`: Implementation in Java using Parallel Streams (JDK8+) and arrays

`python-for`: Implementation in Python using for loop and arrays

`python-np`: Implementation in Python using numpy library


### Matrices
 - We'll be working with square matrices ranging from `16x16` to `1024x1024`. We'll focus more on matrices above `256x256`.
 - We'll only consider `int` types for simplicity

# Testing Methodology
- Only benchmark the matrix multiplication operation
  - Wont consider time taken for other actions such as I/O
- Use same matrices for all variations
  - Generate matrices on first run (Java) and save them to files
  - For all variations, read from file and execute
- Iterations
  - For each size, we will multiply `20` times and sum the durations to get larger duration results


For example, `python-np: 1024, 122.44` means, it took `122.44 seconds` to multiply `20` `1024x1024` matrices with `20` other corresponding `1024x1024` matrices in the `python` implementation using `numpy`.


# Test Setup

- CPU: Ryzen 3950x (16/32 Cores)
- RAM: 64GB
- GPU: N/A (Maybe in future, we can do CUDA)

# Implementation Procedure


# Expected Results (Based on common beliefs)
- `c-std`: C, being the low level system language with lowest overhead, will be fastest (well, 2nd most; see below).
- `c-pointer`: Using pointer arithmetics, we should be able to squeeze out a little more performance and should be fastest (faster than `c-std`).
- `java-for`: Java, being byte-code interpreted language during runtime, will be slower than C variations.
- `java-no-jit`: Without `JIT` optimization, Java will be extremely slow.
- `java-stream`: This should be really fast as Java will utilize multiple CPU cores but can it be faster than C?
- `python-for`: This is similar to `java-for` but should be even slower as Python's interpreter is much slower than Java.
- `python-np`: This should get us similar (but slightly slower) results to `c-std` as `numpy` is an extension module written in `C`.


# Actual Results

![image](https://user-images.githubusercontent.com/11375716/164284415-06043305-d99b-4fef-a514-75f1c27936fa.png)


The chart contains data `7x` data points for each variations and there are `7` variations as well. So we have `49` data points in total.

***NOTE***: We have ignored `three` data points in the above chart; namely `java-no-jit @ 1024`, `python-for @ 512` and `python-for @ 1024` as each of these took over ~500 seconds and made it harder to visualize other points of interest. We will talk about these values later.

# Observations

### Overall
- C is really fast for smaller dataset but is not performing as expected for larger datasets
- Java turned out to be much faster than expected
- Stock Python is many orders slow compared to everything else

We'll be explaining each of these shorty.

### 16x16 to 128x128
- Variations of C show absolute dominance.
- `java-stream` appears to be very slow.
- `python-for` is already slow compared to others (except `java-stream`)
- `python-np` closely follows `c-std` as predicted.

### 256x256
- Variations of `c` are closely holding up.
- `java` variations are slow (as expected) and `java-no-jit` is look really bad; amost as bad as `python-for`.
- `python-for`, is already showing the extremely lack of performance of python. `python-for 256, 86s` vs `python-np 256, 0.319s`. Just by replacing `for-loops` with `numpy`'s functions which execute using `c`, we are seeing insane amount of performance difference.
- `python-np` closely following `c-std` as before.

### 512x512 and 1024x1024
Things get really interesting here. Compared to other matrix sizes, these two are huge. The amount of mathematical operations is way higher and requires much more memory.

For example, mathematical operations for a matrix is `O(n^3)`.
- `256x256`: `16M`
- `512x512`: `134M` (8 times compared to `256x256`)
- `1024x1024`: `1B` (62 times compared to `256x256`)

- As expected of `c` variations, their times shot up due to huge number of operations increase.
- While `java-for` and `java-stream` were slower than variations of `c` before, they have turned it upside down and now are faster than `c` variations and in one particular case, _amazingly_ faster. We'll explain this below.
- `java-no-jit` is showing how useless Java is without JIT optimization and is only trailed by `python-for`.
- `python-for` is so 
