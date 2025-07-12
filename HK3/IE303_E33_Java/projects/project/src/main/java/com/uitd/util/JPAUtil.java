package com.uitd.util;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import jakarta.persistence.Persistence;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class JPAUtil {
    private static final Logger logger = LogManager.getLogger(JPAUtil.class);
    private static EntityManagerFactory emf;

    public static void init() {
        try {
            emf = Persistence.createEntityManagerFactory("erpPU");
            logger.info("JPA initialized successfully.");
        } catch (Exception e) {
            logger.error("Failed to initialize JPA!", e);
            throw new RuntimeException("Could not initialize JPA", e);
        }
    }

    public static EntityManager getEntityManager() {
        if (emf == null) {
            throw new IllegalStateException("JPAUtil is not initialized. Call JPAUtil.init() first.");
        }
        return emf.createEntityManager();
    }

    public static void shutdown() {
        if (emf != null && emf.isOpen()) {
            emf.close();
        }
    }
}
