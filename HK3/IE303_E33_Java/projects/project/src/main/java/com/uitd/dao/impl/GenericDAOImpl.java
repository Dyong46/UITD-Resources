package com.uitd.dao.impl;

import com.uitd.dao.GenericDAO;
import com.uitd.util.JPAUtil;
import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityTransaction;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.List;

public class GenericDAOImpl<T, ID> implements GenericDAO<T, ID> {
    private static final Logger logger = LogManager.getLogger(GenericDAOImpl.class);

    protected final Class<T> clazz;

    public GenericDAOImpl(Class<T> clazz) {
        this.clazz = clazz;
    }

    @Override
    public T findById(ID id) {
        EntityManager em = JPAUtil.getEntityManager();
        try {
            return em.find(clazz, id);
        } catch (Exception e) {
            logger.error("Error finding entity by ID: {}", id, e);
            throw new RuntimeException(e);
        } finally {
            em.close();
        }
    }

    @Override
    public List<T> findAll() {
        EntityManager em = JPAUtil.getEntityManager();
        try {
            String query = "SELECT e FROM " + clazz.getSimpleName() + " e";
            return em.createQuery(query, clazz).getResultList();
        } catch (Exception e) {
            logger.error("Error finding all entities", e);
            throw new RuntimeException(e);
        } finally {
            em.close();
        }
    }

    @Override
    public boolean save(T entity) {
        EntityManager em = JPAUtil.getEntityManager();
        EntityTransaction tx = em.getTransaction();
        try {
            tx.begin();
            em.persist(entity);
            tx.commit();
            logger.info("Saved entity: {}", entity);
            return true;
        } catch (Exception e) {
            if (tx.isActive()) tx.rollback();
            logger.error("Error saving entity", e);
            return false;
        } finally {
            em.close();
        }
    }

    @Override
    public boolean update(T entity) {
        EntityManager em = JPAUtil.getEntityManager();
        EntityTransaction tx = em.getTransaction();
        try {
            tx.begin();
            em.merge(entity);
            tx.commit();
            logger.info("Updated entity: {}", entity);
            return true;
        } catch (Exception e) {
            if (tx.isActive()) tx.rollback();
            logger.error("Error updating entity", e);
            return false;
        } finally {
            em.close();
        }
    }

    @Override
    public boolean delete(ID id) {
        EntityManager em = JPAUtil.getEntityManager();
        EntityTransaction tx = em.getTransaction();
        try {
            T entity = em.find(clazz, id);
            if (entity == null) {
                logger.warn("Entity with ID {} not found for deletion", id);
                return false;
            }

            tx.begin();
            em.remove(entity);
            tx.commit();
            logger.info("Deleted entity with ID: {}", id);
            return true;
        } catch (Exception e) {
            if (tx.isActive()) tx.rollback();
            logger.error("Error deleting entity", e);
            return false;
        } finally {
            em.close();
        }
    }
}
