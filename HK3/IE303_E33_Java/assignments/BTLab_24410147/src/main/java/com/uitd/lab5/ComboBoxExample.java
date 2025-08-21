package com.uitd.lab5;

import javax.swing.*;
import java.awt.*;

public class ComboBoxExample extends JFrame {
    public ComboBoxExample() {
        setTitle("ComboBox Example");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        initUI();
    }

    private void initUI() {
        setLayout(new FlowLayout());

        String[] countries = {"India", "Aus", "U.S.A", "England", "Vietnam"};
        JComboBox<String> countryComboBox = new JComboBox<>(countries);

        add(countryComboBox);
    }

    public static void main() {
        SwingUtilities.invokeLater(() -> new ComboBoxExample().setVisible(true));
    }
}
