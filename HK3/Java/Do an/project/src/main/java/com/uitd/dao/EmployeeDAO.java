package com.uitd.dao;

import com.uitd.entity.Employee;

import java.util.List;

public interface EmployeeDAO {
    void save(Employee emp);

    List<Employee> findAll();
}
