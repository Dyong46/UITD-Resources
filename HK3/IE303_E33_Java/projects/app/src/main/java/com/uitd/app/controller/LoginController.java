package com.uitd.app.controller;

import javafx.event.ActionEvent;

import java.util.logging.Logger;

public class LoginController {
    Logger logger = Logger.getLogger(LoginController.class.getName());
    public void handleLogin(ActionEvent actionEvent) {
        System.out.println(actionEvent);
    }
}
