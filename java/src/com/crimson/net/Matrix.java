package com.crimson.net;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardOpenOption;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.stream.IntStream;

public class Matrix {
    public final int size;
    public final int[][] data;
    private final Random random = new Random();

    public Matrix(int size) {
        this.size = size;
        data = new int[size][size];
    }

    /**
     *  This function multiplies current with param | (this.data * m.data)
     * @param m Matrix to be multiplied
     * @return benchmark time
     */
    long multiply(Matrix m) {
        // this * m // assuming same square dimensions
        Matrix c = new Matrix(size);
        int[][] a = data;
        int[][] b = m.data;
        long start = System.nanoTime();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int x = 0; x < size; x++) {
                    c.data[i][j] += a[i][x] * b[x][j];
                }
            }
        }
//        IntStream.range(0, size).parallel().forEach(i -> {
//            IntStream.range(0, size).parallel().forEach(j -> {
//                IntStream.range(0, size).parallel().forEach(x -> {
//                    c.data[i][j] += a[i][x] * b[x][j];
//                });
//            });
//        });

        long end = System.nanoTime();
        // c.print();
        // System.out.println("Start: " + start);
        // System.out.println("End: " + end);
        // System.out.println("Time taken: " + (end - start) + "ns");
        return (end - start);
    }

    void randomize() {
        for (int i = 0; i < data.length; i++) {
            for (int j = 0; j < data[i].length; j++) {
                data[i][j] = random.nextInt(10);    // keeping this small so we don't overflow
            }
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < data.length; i++) {
            for (int j = 0; j < data[i].length; j++) {
                sb.append(data[i][j]);
                sb.append(' ');
            }
            sb.append("\n");
        }
        return sb.toString();
    }

    void print() {
        System.out.println(this);
    }

    /**
     * Given a sequence x, it writes current matrix to ./matrices/{size}/{a|b}{XXX}.matrix.txt
     * @param sequence should be {a|b}{000-999}
     */
    void write(String sequence) {
        try {
            File file = getFile(sequence);
            // System.out.println("Saving to: " + file.getAbsolutePath());
            Files.writeString(file.toPath(), this.toString(), StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING);
        } catch (IOException ioe) {
            System.out.println("Cant write file");
            ioe.printStackTrace();
            System.exit(1);
        }
    }

    /**
     * Given a sequence x, it reads ./matrices/{size}/{a|b}{XXX}.matrix.txt and regenerates a matrix
     * @param sequence should be {a|b}{000-999}
     */
    void read(String sequence) {
        try {
            File file = getFile(sequence);
            // System.out.println("Reading from: " + file.toPath());
            List<String> lines = Files.readAllLines(file.toPath());

            for (int i = 0; i < lines.size(); i++) {
                String[] row = lines.get(i).split(" ");
                for (int j = 0; j < row.length; j++) {
                    data[i][j] = Integer.parseInt(row[j]);
                }
            }
        } catch (IOException ioe) {
            System.out.println("Cant read file");
            ioe.printStackTrace();
            System.exit(1);
        }
    }

    /**
     * Given a sequence x, it returns corresponding matrix path
     * @param sequence  matrix sequence to load
     * @return  path of that matrix
     */
    private File getFile(String sequence) {
        return new File("../matrices/" + size + "/" + sequence + ".matrix.txt");
    }
}
