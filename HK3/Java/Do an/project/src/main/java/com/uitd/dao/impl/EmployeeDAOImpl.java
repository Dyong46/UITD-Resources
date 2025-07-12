package com.uitd.dao.impl;

import com.uitd.dao.EmployeeDAO;
import com.uitd.entity.Employee;
import com.uitd.util.JPAUtil;
import jakarta.persistence.EntityManager;

import java.util.List;

public class EmployeeDAOImpl implements EmployeeDAO {
    public void save(Employee emp) {
        EntityManager em = JPAUtil.getEntityManager();
        em.getTransaction().begin();
        em.persist(emp);
        em.getTransaction().commit();
        em.close();
    }

    public List<Employee> findAll() {
        EntityManager em = JPAUtil.getEntityManager();
        List<Employee> list = em.createQuery("SELECT e.id, e.firstName, e.lastName, e.email, e.position FROM Employee e", Employee.class)
                .getResultList();
        em.close();
        return list;
    }
}
