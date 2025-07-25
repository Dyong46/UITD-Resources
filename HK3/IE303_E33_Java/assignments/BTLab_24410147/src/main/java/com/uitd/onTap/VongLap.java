package com.uitd.onTap;

public class VongLap {
    public static void main(String[] args) {
        // Vòng lặp for
        for (int i = 0; i < 5; i++) {
            System.out.println("Vòng lặp for: " + i);
        }

        // Vòng lặp while
        int j = 0;
        while (j < 0) {
            System.out.println("Vòng lặp while: " + j);
            j++;
        }

        // Vòng lặp do-while
        int k = 0;
        do {
            System.out.println("Vòng lặp do-while: " + k);
            k++;
        } while (k < 0);
    }
}
