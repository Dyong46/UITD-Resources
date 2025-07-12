package com.uitd.controller;

import com.uitd.entity.User;
import com.uitd.view.MainDashboard;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class DashboardController {
    private final MainDashboard view;
    private final User loggedUser;
    private static Logger logger = LogManager.getLogger(DashboardController.class);

    public DashboardController(MainDashboard view, User user) {
        this.view = view;
        this.loggedUser = user;
        init();
    }

    private void init() {
        System.out.println("Người dùng hiện tại: " + loggedUser.getUsername());
    }
}
