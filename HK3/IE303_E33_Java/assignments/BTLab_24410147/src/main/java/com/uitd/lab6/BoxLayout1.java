package com.uitd.lab6;

import javax.swing.*;
import java.awt.*;

public class BoxLayout1 extends JFrame {
    int TOTAL_BUTTONS = 5;
    JButton[] buttons;

    public BoxLayout1() {
        setTitle("BoxLayout 1");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(400, 400);
        setLocationRelativeTo(null);
        createUIComponents();
    }

    private void createUIComponents() {
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

        buttons = new JButton[TOTAL_BUTTONS];

        for (int i = 0; i < TOTAL_BUTTONS; i++) {
            buttons[i] = new JButton("Button " + (i + 1));
            buttons[i].setMaximumSize(new Dimension(Integer.MAX_VALUE, 60));
            buttons[i].setAlignmentX(Component.CENTER_ALIGNMENT);

            panel.add(buttons[i]);
        }

        this.setContentPane(panel);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new BoxLayout1().setVisible(true));
    }
}
