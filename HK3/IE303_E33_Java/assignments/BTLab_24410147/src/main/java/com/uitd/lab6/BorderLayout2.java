package com.uitd.lab6;

import javax.swing.*;
import java.awt.*;

public class BorderLayout2 extends JFrame {
    public BorderLayout2() {
        setTitle("BorderLayout");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(500, 500);
        setLayout(new BorderLayout(20, 15));
        setLocationRelativeTo(null);
        initUI();
    }

    private void initUI() {
        JButton btn1 = new JButton("NORTH");
        JButton btn2 = new JButton("SOUTH");
        JButton btn3 = new JButton("EAST");
        JButton btn4 = new JButton("WEST");
        JButton btn5 = new JButton("CENTER");

        this.add(btn1, BorderLayout.NORTH);
        this.add(btn2, BorderLayout.SOUTH);
        this.add(btn3, BorderLayout.EAST);
        this.add(btn4, BorderLayout.WEST);
        this.add(btn5, BorderLayout.CENTER);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            new BorderLayout2().setVisible(true);
        });
    }
}
