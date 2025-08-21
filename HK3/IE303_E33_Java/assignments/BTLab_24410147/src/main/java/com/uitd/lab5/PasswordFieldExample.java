package com.uitd.lab5;

import javax.swing.*;
import java.awt.*;

public class PasswordFieldExample extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JLabel messageLabel;

    public PasswordFieldExample() {
        setTitle("Password Field Example");
        setSize(300, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        initUI();
    }

    private void initUI() {
        // Use layout
        setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(8, 8, 8, 8);
        gbc.anchor = GridBagConstraints.WEST;

        // Username
        gbc.gridx = 0; gbc.gridy = 0;
        add(new JLabel("Username:"), gbc);

        gbc.gridx = 1;
        usernameField = new JTextField(10);
        add(usernameField, gbc);

        // Password
        gbc.gridx = 0; gbc.gridy = 1;
        add(new JLabel("Password:"), gbc);

        gbc.gridx = 1;
        passwordField = new JPasswordField(10);
        add(passwordField, gbc);

        // Login Button
        gbc.gridx = 1; gbc.gridy = 2;
        JButton loginButton = new JButton("Login");
        add(loginButton, gbc);

        // Message Label
        gbc.gridx = 0; gbc.gridy = 3; gbc.gridwidth = 2;
        messageLabel = new JLabel("");
        add(messageLabel, gbc);

        loginButton.addActionListener(_ -> {
            String username = usernameField.getText();
            String password = new String(passwordField.getPassword());
            messageLabel.setText("Username: " + username + ", Password: " + password);
        });
    }

    public static void main() {
        SwingUtilities.invokeLater(() -> new PasswordFieldExample().setVisible(true));
    }
}
