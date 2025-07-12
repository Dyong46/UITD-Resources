USE master
GO

IF EXISTS (SELECT name FROM sys.databases WHERE name = 'Store')
BEGIN
    DROP DATABASE Store;
END
GO

CREATE DATABASE Store;
GO

USE Store;
GO

-- Drop constraints and tables if they already exist
IF EXISTS (SELECT 1 FROM sys.sysobjects WHERE name = 'FK_HOADON_KHACHHANG' AND xtype = 'F')
    ALTER TABLE HOADON DROP CONSTRAINT FK_HOADON_KHACHHANG;
GO

IF EXISTS (SELECT 1 FROM sys.sysobjects WHERE name = 'FK_HOADON_NHANVIEN' AND xtype = 'F')
    ALTER TABLE HOADON DROP CONSTRAINT FK_HOADON_NHANVIEN;
GO

IF EXISTS (SELECT 1 FROM sys.sysobjects WHERE name = 'FK_CTHD_HOADON' AND xtype = 'F')
    ALTER TABLE CTHD DROP CONSTRAINT FK_CTHD_HOADON;
GO

IF EXISTS (SELECT 1 FROM sys.sysobjects WHERE name = 'FK_CTHD_SANPHAM' AND xtype = 'F')
    ALTER TABLE CTHD DROP CONSTRAINT FK_CTHD_SANPHAM;
GO

IF EXISTS (SELECT 1 FROM sys.sysobjects WHERE id = OBJECT_ID('CTHD') AND xtype = 'U')
    DROP TABLE CTHD;
GO

IF EXISTS (SELECT 1 FROM sys.sysobjects WHERE id = OBJECT_ID('HOADON') AND xtype = 'U')
    DROP TABLE HOADON;
GO

IF EXISTS (SELECT 1 FROM sys.sysobjects WHERE id = OBJECT_ID('SANPHAM') AND xtype = 'U')
    DROP TABLE SANPHAM;
GO

IF EXISTS (SELECT 1 FROM sys.sysobjects WHERE id = OBJECT_ID('NHANVIEN') AND xtype = 'U')
    DROP TABLE NHANVIEN;
GO

IF EXISTS (SELECT 1 FROM sys.sysobjects WHERE id = OBJECT_ID('KHACHHANG') AND xtype = 'U')
    DROP TABLE KHACHHANG;
GO

-- Create the KHACHHANG table
CREATE TABLE KHACHHANG (
    MAKH CHAR(4) PRIMARY KEY,         -- Customer ID
    HOTEN NVARCHAR(40) NOT NULL,      -- Full Name
    DCHI NVARCHAR(50),                -- Address
    SODT NVARCHAR(20),                -- Phone Number
    NGSINH SMALLDATETIME,             -- Date of Birth
    NGDK SMALLDATETIME,               -- Registration Date
    DOANHSO MONEY                     -- Total sales of invoices
);
GO

-- Create the NHANVIEN table
CREATE TABLE NHANVIEN (
    MANV CHAR(4) PRIMARY KEY,         -- Employee ID
    HOTEN NVARCHAR(40) NOT NULL,      -- Full Name
    SODT NVARCHAR(20),                -- Phone Number
    NGVL SMALLDATETIME                -- Date of Hire
);
GO

-- Create the SANPHAM table
CREATE TABLE SANPHAM (
    MASP CHAR(4) PRIMARY KEY,         -- Product ID
    TENSP NVARCHAR(40) NOT NULL,      -- Product Name
    DVT NVARCHAR(20),                 -- Unit of Measurement
    NUOCSX NVARCHAR(40),              -- Country of Origin
    GIA MONEY                         -- Price
);
GO

-- Create the HOADON table
CREATE TABLE HOADON (
    SOHD INT PRIMARY KEY,             -- Invoice Number
    NGHD SMALLDATETIME NOT NULL,      -- Purchase Date
    MAKH CHAR(4),                     -- Customer ID
    MANV CHAR(4) NOT NULL,            -- Employee ID
    TRIGIA MONEY                      -- Invoice Value
);
GO

-- Create the CTHD table
CREATE TABLE CTHD (
    SOHD INT,                         -- Invoice Number
    MASP CHAR(4),                     -- Product ID
    SL INT NOT NULL,                  -- Quantity
    PRIMARY KEY (SOHD, MASP)          -- Composite Primary Key
);
GO

-- Add foreign key constraints
ALTER TABLE HOADON
    ADD CONSTRAINT FK_HOADON_KHACHHANG FOREIGN KEY (MAKH) REFERENCES KHACHHANG(MAKH);
GO

ALTER TABLE KHACHHANG
    ADD CONSTRAINT DF_NGDK DEFAULT GETDATE() FOR NGDK;
GO

ALTER TABLE HOADON
    ADD CONSTRAINT FK_HOADON_NHANVIEN FOREIGN KEY (MANV) REFERENCES NHANVIEN(MANV);
GO

ALTER TABLE CTHD
    ADD CONSTRAINT FK_CTHD_HOADON FOREIGN KEY (SOHD) REFERENCES HOADON(SOHD);
GO

ALTER TABLE CTHD
    ADD CONSTRAINT FK_CTHD_SANPHAM FOREIGN KEY (MASP) REFERENCES SANPHAM(MASP);
GO
