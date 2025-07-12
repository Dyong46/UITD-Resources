package com.uitd.lab1;

import java.util.Scanner;

public class Bai1 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Ho va ten: ");
        String name = scanner.nextLine();

        System.out.print("Diem TB: ");
        double avgScore = scanner.nextDouble();

        System.out.printf("%s %f diem", name, avgScore);
    }
}
