package com.uitd.lab5;

import javax.swing.*;
import java.awt.*;

public class JFrameExample extends JFrame {
    public JFrameExample() {
        setTitle("JFrame Example");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        initUI();
    }

    private void initUI() {
        setLayout(new FlowLayout());

        JLabel label = new JLabel("JFrame By Example");
        JButton button = new JButton("Button");

        add(label);
        add(button);
    }

    public static void main() {
        SwingUtilities.invokeLater(() -> new JFrameExample().setVisible(true));
    }
}
