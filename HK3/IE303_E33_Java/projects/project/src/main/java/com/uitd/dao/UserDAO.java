package com.uitd.dao;

import com.uitd.entity.User;

public interface UserDAO extends GenericDAO<User, Long> {
    User findByUsername(String username);
}
