package com.uitd.lab6;

import javax.swing.*;
import java.awt.*;

public class GridLayout2 extends JFrame {
    JButton[] buttons;
    int TOTAL_BUTTONS = 9;

    GridLayout2() {
        setTitle("GridLayout");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setSize(400, 400);
        initUI();
        setLayout(new GridLayout(3, 3, 20, 25));
    }

    private void initUI() {
        buttons = new JButton[TOTAL_BUTTONS];
        for (int i = 0; i < TOTAL_BUTTONS; i++) {
            buttons[i] = new JButton("" + (i + 1));
            this.add(buttons[i]);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new GridLayout2().setVisible(true));
    }
}
