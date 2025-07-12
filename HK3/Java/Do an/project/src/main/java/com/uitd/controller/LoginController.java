package com.uitd.controller;

import com.uitd.dao.UserDAO;
import com.uitd.dao.impl.UserDAOImpl;
import com.uitd.entity.User;
import com.uitd.view.LoginView;
import com.uitd.view.MainDashboard;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import javax.swing.*;

public class LoginController {
    private final LoginView view;
    private final UserDAO userDAO;
    private static final Logger logger = LogManager.getLogger(LoginController.class);

    public LoginController(LoginView view) {
        this.view = view;
        this.userDAO = new UserDAOImpl();
        initListeners();
    }

    private void initListeners() {
        view.getLoginButton().addActionListener(e -> {
            String username = view.getUsernameField().getText().trim();
            String password = new String(view.getPasswordField().getPassword());
            JLabel messageLabel = view.getMessageLabel();
            System.out.println("[LoginController] Username: " + username);
            System.out.println("[LoginController] Password: " + password);
            System.out.println("[LoginController] Login button clicked");
            try {
                System.out.println("[LoginController] Attempting to log in user: " + username);
                User user = userDAO.findByUsername(username);
                if (user == null) {
                    messageLabel.setText("User not found!");
                    return;
                }

                if (!user.getPassword().equals(password)) {
                    messageLabel.setText("Invalid password!");
                    return;
                }

                messageLabel.setText("Login successful!");
                logger.info("User {} logged in successfully.", username);

                view.dispose();
                MainDashboard dashboard = new MainDashboard();
                new DashboardController(dashboard, user);
                dashboard.setVisible(true);
            } catch (Exception ex) {
                System.out.println("[LoginController] Error during login: " + ex.getMessage());
                messageLabel.setText("An error occurred during login. Please try again.");
                JOptionPane.showMessageDialog(view, "An error occurred during login: " + ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
                logger.error("Error during login", ex);
            }
        });
    }
}
