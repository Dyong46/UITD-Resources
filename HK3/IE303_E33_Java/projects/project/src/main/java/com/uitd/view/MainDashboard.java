package com.uitd.view;

import lombok.Getter;

import javax.swing.*;
import java.awt.*;

@Getter()
public class MainDashboard extends JFrame {
    private JPanel panel;
    private JLabel titleLabel;
    private JTextArea contentArea;

    public MainDashboard() {
        setTitle("Dashboard");
        setSize(500, 400);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        initUI();
    }

    private void initUI() {
        panel = new JPanel();
        panel.setLayout(new BorderLayout());

        titleLabel = new JLabel("Dashboard", SwingConstants.CENTER);
        titleLabel.setFont(new Font("Arial", Font.BOLD, 24));
        panel.add(titleLabel, BorderLayout.NORTH);

        contentArea = new JTextArea("This is the main dashboard content.");
        contentArea.setEditable(false);
        panel.add(contentArea, BorderLayout.CENTER);

        add(panel);
    }
}
