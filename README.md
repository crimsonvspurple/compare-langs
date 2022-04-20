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

# Variations
`c-std`: Implementation in C using for loop and arrays

`c-pointer`: Implementation in C using for loop and pointer arithmetics

`java-for`: Implementation in Java using for loop and arrays

`java-no-jit`: Same as above but disable JIT during runtime

`java-stream`: Implementation in Java using Parallel Streams (JDK8+) and arrays

`python-for`: Implementation in Python using for loop and arrays

`python-np`: Implementation in Python using numpy library


# Matrix Sizes
We'll be working with square matrices ranging from `16x16` to `1024x1024`. We'll focus more on matrices above `256x256`.

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
- RAM: 64GM
- GPU: N/A (Maybe in future, we can do CUDA)

# Implementation Procedure
