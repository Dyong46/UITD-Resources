package com.uitd.dao.impl;

import com.uitd.dao.UserDAO;
import com.uitd.entity.User;
import com.uitd.util.JPAUtil;
import jakarta.persistence.EntityManager;
import jakarta.persistence.NoResultException;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class UserDAOImpl extends GenericDAOImpl<User, Long> implements UserDAO {
    private static final Logger logger = LogManager.getLogger(UserDAOImpl.class);

    public UserDAOImpl() {
        super(User.class);
    }

    @Override
    public User findByUsername(String username) {
        EntityManager em = JPAUtil.getEntityManager();
        try {
            return em.createQuery("SELECT u FROM User u WHERE u.username = :username", User.class)
                    .setParameter("username", username)
                    .getSingleResult();
        } catch (NoResultException e) {
            logger.info("Username '{}' not found", username);
            return null;
        } catch (Exception e) {
            logger.error("Database error: {}", username, e);
            throw new RuntimeException(e);
        } finally {
            em.close();
        }
    }
}
