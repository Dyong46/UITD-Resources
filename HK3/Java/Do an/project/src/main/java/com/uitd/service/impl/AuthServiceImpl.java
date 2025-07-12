package com.uitd.service.impl;

import com.uitd.dao.UserDAO;
import com.uitd.dao.impl.UserDAOImpl;
import com.uitd.entity.User;
import com.uitd.service.AuthService;

public class AuthServiceImpl implements AuthService {
    private final UserDAO userDAO = new UserDAOImpl();

    @Override
    public boolean authenticate(String username, String password) {
        User user = userDAO.findByUsername(username);
        return user != null && user.getPassword().equals(password);
    }
}
