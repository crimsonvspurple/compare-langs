package com.crimson.net;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardOpenOption;

public class Main {

    public static void main(String[] args) {
        final int ITERATION = 100;                                    // iteration count per size
        final int[] SIZES = {16, 32, 64, 128, 256, 512, 1024};        // matrix sizes (square) to consider


        for (int size : SIZES) {                                // for each dimension sizes
            Matrix[] a = new Matrix[ITERATION];                 // array of a
            Matrix[] b = new Matrix[ITERATION];                 // array of b
            for (int i = 0; i < ITERATION; i++) {               // populate the arrays
                String sequence = String.format("%03d", i);         // make numbers at least 3 digit (for file name)
                a[i] = new Matrix(size);                            // init a with current size
                b[i] = new Matrix(size);                            // init b with current size
//                a[i].randomize();                                 // generate random matrix for a
//                a[i].write("a" + sequence);                       // write it to file for c/python versions
//                b[i].randomize();                                 // same for b
//                b[i].write("b" + sequence);
                a[i].read("a" + sequence);                  // read from file (can comment above four lines if files are already generated)
                b[i].read("b" + sequence);
//              a.print();                                          // print if needed
//              b.print();
            }
            long[] benchmark = new long[ITERATION];             // array for benchmark timings
            for (int i = 0; i < ITERATION; i++) {
                benchmark[i] = a[i].multiply(b[i]);                 // actual multiplication action
            }
            saveBenchmark(benchmark, size);                     // write all benchmark timings for this size
        }
        System.out.println("Check benchmark folder for logs.");
    }

    public static void saveBenchmark(long[] benchmark, int size) {
        long bestTime = Long.MAX_VALUE;
        long totalTime = 0;
        StringBuilder log = new StringBuilder();
        for (long l : benchmark) {
            if (bestTime > l) {
                bestTime = l;
            }
            totalTime += l;
            log.append(l);
            log.append("\n");
        }
        String dim = String.format("%03d", size);
        System.out.println("Best  Time for [" + dim + " x " + dim + "]: " + bestTime + "ns | " + (bestTime / 1000000.0) + "ms");
        System.out.println("Total Time for [" + dim + " x " + dim + "]: " + totalTime + "ns | " + (totalTime / 1000000.0) + "ms | " + (totalTime / 1000000000.0) + "s");
        try {
            File file = new File("../benchmark/java" + dim + ".log");
            // System.out.println("Saving to: " + file.getAbsolutePath());
            Files.writeString(file.toPath(), log.toString(), StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING);
        } catch (IOException ioe) {
            System.out.println("Cant read/write benchmark file");
            ioe.printStackTrace();
            System.exit(1);
        }
    }
}
