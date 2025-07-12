package com.uitd;

import com.uitd.controller.LoginController;
import com.uitd.util.JPAUtil;
import com.uitd.view.LoginView;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import javax.swing.*;

public class Main {
    private static final Logger logger = LogManager.getLogger(Main.class);

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            try {
                JPAUtil.init();
                UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
                LoginView loginView = new LoginView();
                new LoginController(loginView);
                loginView.setVisible(true);
            } catch (Exception e) {
                logger.error("Error init app: ", e);
                JOptionPane.showMessageDialog(null, "Failed to initialize the application: " + e.getMessage());
            }
        });
    }
}