import numpy as np
from typing import *
import time


def readMatrix(i: int, size: int, var: str) -> np.ndarray:
    iterString: str = "%04d" % i
    path: str = f"../matrices/{size}/{var}{iterString}.matrix.txt"
    # print(f"Path is: {path}")
    return np.genfromtxt(path, dtype="int", delimiter=" ")


def saveBenchmark(benchmark: list[float], size: int):
    print(f"[{size}x{size}]: Best Time: {min(benchmark)}s | Total Time: {sum(benchmark)}s")
    # print("\n".join(iter(map(str, benchmark))))
    file = open(f"../benchmark/python{size}.log", "w")
    file.write("\n".join(iter(map(str, benchmark))))
    file.close()


if __name__ == '__main__':
    ITERATION: Final[int] = 20
    # sizes: list[int] = [128]
    sizes: list[int] = [16, 32, 64, 128, 256, 512, 1024]

    for size in sizes:
        benchmark: list[float] = list()
        for i in range(ITERATION):
            # read matrices
            a: np.ndarray = readMatrix(i, size, "a")
            b: np.ndarray = readMatrix(i, size, "b")

            # benchmark
            start: float = time.time()

            # multiply
            c: np.ndarray = np.dot(a, b)

            end: float = time.time()
            # print(f"{end - start} seconds")
            benchmark.append((end - start))
        saveBenchmark(benchmark, size)
