-- I. Ngôn ngữ định nghĩa dữ liệu (Data Definition Language):
-- 2.	Thêm vào thuộc tính GHICHU có kiểu dữ liệu varchar(20) cho quan hệ SANPHAM.
ALTER TABLE SANPHAM
    ADD GHICHU VARCHAR(20)
GO

-- 3.	Thêm vào thuộc tính LOAIKH có kiểu dữ liệu là tinyint cho quan hệ KHACHHANG.
ALTER TABLE KHACHHANG
    ADD LOAIKH TINYINT
GO

-- 4.	Sửa kiểu dữ liệu của thuộc tính GHICHU trong quan hệ SANPHAM thành varchar(100).
ALTER TABLE SANPHAM
    ALTER COLUMN GHICHU VARCHAR(100)
GO

-- 5.	Xóa thuộc tính GHICHU trong quan hệ SANPHAM.
ALTER TABLE SANPHAM
    DROP COLUMN GHICHU
GO

-- 6.	Làm thế nào để thuộc tính LOAIKH trong quan hệ KHACHHANG có thể lưu các giá trị là: “Vang lai”, “Thuong xuyen”, “Vip”, …
-- Thay kiểu dữ liệu của thuộc tính LOAIKH thành varchar
ALTER TABLE KHACHHANG
    ALTER COLUMN LOAIKH VARCHAR(100)
GO

-- 7.	Đơn vị tính của sản phẩm chỉ có thể là (“cay”,”hop”,”cai”,”quyen”,”chuc”)
ALTER TABLE SANPHAM
    ADD CONSTRAINT CK_DVT_CHECK
        CHECK (DVT IN ('cay', 'hop', 'cai', 'quyen', 'chuc'));
GO

-- 8.	Giá bán của sản phẩm từ 500 đồng trở lên.
ALTER TABLE SANPHAM
    ADD CONSTRAINT CK_GIA_MinValue
        CHECK (GIA >= 500);
GO

-- 9.	Mỗi lần mua hàng, khách hàng phải mua ít nhất 1 sản phẩm.
-- CREATE TRIGGER TRG_CHECK_QNT_SP
-- ON HOADON
-- AFTER INSERT
-- AS
--     BEGIN
--         IF EXISTS (
--                 SELECT 1
--                 FROM KHACHHANG
--                 WHERE NGDK <= NGSINH
--             )
--         BEGIN
--             ROLLBACK TRANSACTION
--             THROW 50000, 'Ngày đăng ký phải lớn hơn ngày sinh.', 1;
--     END
-- END;


-- 10.	Ngày khách hàng đăng ký là khách hàng thành viên phải lớn hơn ngày sinh của người đó.
-- CREATE TRIGGER TRG_CHECK_NGAYDK
-- ON KHACHHANG
-- AFTER INSERT, UPDATE AS
-- BEGIN
--     IF EXISTS (
--         SELECT 1
--         FROM KHACHHANG
--         WHERE NGDK <= NGSINH
--     )
-- END

-- 11.	Ngày mua hàng (NGHD) của một khách hàng thành viên sẽ lớn hơn hoặc bằng ngày khách hàng đó đăng ký thành viên (NGDK).
CREATE TRIGGER trg_CheckNGHD
ON HOADON
AFTER INSERT, UPDATE
AS
BEGIN
    -- Check if NGHD is less than NGDK for any customer
    IF EXISTS (
        SELECT 1
        FROM inserted i
        JOIN KHACHHANG k ON i.MAKH = k.MAKH
        WHERE i.NGHD < k.NGDK
    )
    BEGIN
        RAISERROR ('NGHD must be greater than or equal to NGDK for the customer.', 16, 1);
        ROLLBACK TRANSACTION;
    END
END;
GO


-- 12.	Ngày bán hàng (NGHD) của một nhân viên phải lớn hơn hoặc bằng ngày nhân viên đó vào làm.
CREATE TRIGGER trg_CheckSaleDate
ON HOADON
AFTER INSERT, UPDATE
AS
BEGIN
    -- Check if NGHD is less than NGVL for any employee
    IF EXISTS (
        SELECT 1
        FROM inserted i
        JOIN NHANVIEN n ON i.MANV = n.MANV
        WHERE i.NGHD < n.NGVL
    )
    BEGIN
        RAISERROR ('NGHD must be greater than or equal to NGVL for the employee.', 16, 1);
        ROLLBACK TRANSACTION;
    END
END;
GO

-- 13.	Mỗi một hóa đơn phải có ít nhất một chi tiết hóa đơn.
CREATE TRIGGER trg_EnsureInvoiceDetails
ON HOADON
AFTER INSERT, DELETE
AS
BEGIN
    -- Check if there are invoices without details
    IF EXISTS (
        SELECT 1
        FROM HOADON h
        LEFT JOIN CTHD c ON h.SOHD = c.SOHD
        WHERE c.SOHD IS NULL
    )
    BEGIN
        RAISERROR ('Every invoice must have at least one detail.', 16, 1);
        ROLLBACK TRANSACTION;
    END
END;
GO

-- 14.	Trị giá của một hóa đơn là tổng thành tiền (số lượng*đơn giá) của các chi tiết thuộc hóa đơn đó.
CREATE TRIGGER trg_UpdateInvoiceTotal
ON CTHD
AFTER INSERT, UPDATE, DELETE
AS
BEGIN
    -- Update the TRIGIA value in the HOADON table
    UPDATE HOADON
    SET TRIGIA = (
        SELECT SUM(c.SL * s.GIA) 
        FROM CTHD c
        JOIN SANPHAM s ON c.MASP = s.MASP
        WHERE c.SOHD = HOADON.SOHD
    )
    WHERE EXISTS (
        SELECT 1
        FROM CTHD
        WHERE CTHD.SOHD = HOADON.SOHD
    );
END;
GO

-- 15.	Doanh số của một khách hàng là tổng trị giá các hóa đơn mà khách hàng thành viên đó đã mua.
CREATE TRIGGER trg_UpdateCustomerSales
ON HOADON
AFTER INSERT, UPDATE, DELETE
AS
BEGIN
    -- Update the DOANHSO for all affected customers
    UPDATE KHACHHANG
    SET DOANHSO = (
        SELECT SUM(H.TRIGIA)
        FROM HOADON H
        WHERE H.MAKH = KHACHHANG.MAKH
    )
    WHERE EXISTS (
        SELECT 1
        FROM HOADON H
        WHERE H.MAKH = KHACHHANG.MAKH
    );
END;
GO

-- II. Ngôn ngữ thao tác dữ liệu (Data Manipulation Language):
-- 1.	Nhập dữ liệu cho các quan hệ trên.

-- 2.	Tạo quan hệ SANPHAM1 chứa toàn bộ dữ liệu của quan hệ SANPHAM. Tạo quan hệ KHACHHANG1 chứa toàn bộ dữ liệu của quan hệ KHACHHANG.
SELECT * INTO SANPHAM1
FROM SANPHAM;
GO

-- 3.	Cập nhật giá tăng 5% đối với những sản phẩm do “Thai Lan” sản xuất (cho quan hệ SANPHAM1)
UPDATE SANPHAM1
SET GIA = GIA * 1.5
WHERE NUOCSX = 'ThaiLan';
GO

-- 4.	Cập nhật giá giảm 5% đối với những sản phẩm do “Trung Quoc” sản xuất có giá từ 10.000 trở xuống (cho quan hệ SANPHAM1).
UPDATE SANPHAM1
SET GIA = GIA * 0.95
WHERE NUOCSX = 'TrungQuoc' AND GIA <= 10000
GO

-- 5.	Cập nhật giá trị LOAIKH là “Vip” đối với những khách hàng đăng ký thành viên trước ngày 1/1/2007 có doanh số từ 10.000.000 trở lên hoặc khách hàng đăng ký thành viên từ 1/1/2007 trở về sau có doanh số từ 2.000.000 trở lên (cho quan hệ KHACHHANG1).
UPDATE KHACHHANG1
SET LOAIKH = 'Vip'
WHERE (NGDK >= '2007-01-01' AND DOANHSO >= 10000000) OR (NGDK < '2007-01-01' AND DOANHSO >= 2000000)
GO

-- III. Ngôn ngữ truy vấn dữ liệu có cấu trúc:
-- 1.	In ra danh sách các sản phẩm (MASP,TENSP) do “Trung Quoc” sản xuất.
SELECT  MASP, TENSP FROM SANPHAM WHERE NUOCSX = 'Trung Quoc'
GO

-- 2.	In ra danh sách các sản phẩm (MASP, TENSP) có đơn vị tính là “cay”, ”quyen”.
SELECT MASP, TENSP, * FROM SANPHAM WHERE DVT = 'cay' OR DVT = 'quyen'
GO

-- 3.	In ra danh sách các sản phẩm (MASP,TENSP) có mã sản phẩm bắt đầu là “B” và kết thúc là “01”.
SELECT MASP, TENSP FROM SANPHAM WHERE MASP LIKE 'B%01'
GO

-- 4.	In ra danh sách các sản phẩm (MASP,TENSP) do “Trung Quốc” sản xuất có giá từ 30.000 đến 40.000.
SELECT MASP, TENSP, * FROM SANPHAM WHERE NUOCSX = 'Trung Quoc' AND GIA BETWEEN 30000 AND 40000
GO

-- 5.	In ra danh sách các sản phẩm (MASP,TENSP) do “Trung Quoc” hoặc “Thai Lan” sản xuất có giá từ 30.000 đến 40.000.
SELECT MASP, TENSP FROM SANPHAM WHERE NUOCSX = 'Trung Quoc' OR NUOCSX = 'Thai Lan' AND GIA BETWEEN 30000 AND 40000
GO

-- 6.	In ra các số hóa đơn, trị giá hóa đơn bán ra trong ngày 1/1/2007 và ngày 2/1/2007.
SELECT SOHD, TRIGIA  FROM HOADON WHERE NGHD BETWEEN '2007-01-01' AND '2007-01-02'
GO

-- 7.	In ra các số hóa đơn, trị giá hóa đơn trong tháng 1/2007, sắp xếp theo ngày (tăng dần) và trị giá của hóa đơn (giảm dần).
SELECT SOHD, TRIGIA
FROM HOADON 
WHERE NGHD >= '2007-01-01' AND NGHD < '2007-02-01' 
ORDER BY NGHD ASC, TRIGIA DESC;
GO

-- 8.	In ra danh sách các khách hàng (MAKH, HOTEN) đã mua hàng trong ngày 1/1/2007.
SELECT DISTINCT KH.MAKH, KH.HOTEN FROM KHACHHANG KH
INNER JOIN HOADON HD
ON KH.MAKH = HD.MAKH
WHERE HD.NGHD = '2007-01-01';
GO

-- 9.	In ra số hóa đơn, trị giá các hóa đơn do nhân viên có tên “Nguyen Van B” lập trong ngày 28/10/2006.
SELECT HD.SOHD, HD.TRIGIA FROM NHANVIEN NV
INNER JOIN HOADON HD
ON NV.MANV = HD.MANV
WHERE NV.HOTEN = 'Nguyen Van B'
AND NGHD = '2006-10-28'
GO

-- 10.	In ra danh sách các sản phẩm (MASP,TENSP) được khách hàng có tên “Nguyen Van A” mua trong tháng 10/2006.
SELECT DISTINCT SP.MASP, SP.TENSP FROM KHACHHANG KH
INNER JOIN HOADON HD
ON KH.MAKH = HD.MAKH
INNER JOIN CTHD CT
ON CT.SOHD = HD.SOHD
INNER JOIN SANPHAM SP
ON SP.MASP = CT.MASP
WHERE KH.HOTEN = 'Nguyen Van A'
AND NGHD >= '2006-10-01' AND NGHD < '2006-11-01'
GO

-- 11.	Tìm các số hóa đơn đã mua sản phẩm có mã số “BB01” hoặc “BB02”.
SELECT DISTINCT HD.SOHD
FROM HOADON HD
INNER JOIN CTHD CT 
ON HD.SOHD = CT.SOHD
WHERE CT.MASP = 'BB01' OR CT.MASP = 'BB02'
GO

-- 12.	Tìm các số hóa đơn đã mua sản phẩm có mã số “BB01” hoặc “BB02”, mỗi sản phẩm mua với số lượng từ 10 đến 20.
SELECT DISTINCT HD.SOHD
FROM HOADON HD 
INNER JOIN CTHD CT 
ON HD.SOHD = CT.SOHD
WHERE CT.SL BETWEEN 10 AND 20
GO

-- 13.	Tìm các số hóa đơn mua cùng lúc 2 sản phẩm có mã số “BB01” và “BB02”, mỗi sản phẩm mua với số lượng từ 10 đến 20.
SELECT SOHD
FROM CTHD CT 
WHERE (CT.MASP = 'BB01' AND CT.SL BETWEEN 10 AND 20) OR (CT.MASP = 'BB02' AND CT.SL BETWEEN 10 AND 20)
GROUP BY SOHD
HAVING COUNT(CASE WHEN CT.MASP IN ('BB01', 'BB02') THEN CT.MASP END) = 2;
GO

-- 14.	In ra danh sách các sản phẩm (MASP,TENSP) do “Trung Quoc” sản xuất hoặc các sản phẩm được bán ra trong ngày 1/1/2007.
SELECT DISTINCT SP.MASP, SP.TENSP
FROM SANPHAM SP
INNER JOIN CTHD CT
ON SP.MASP = CT.MASP
INNER JOIN HOADON HD
ON CT.SOHD = HD.SOHD
WHERE SP.NUOCSX = 'Trung Quoc' OR HD.NGHD = '2007-01-01'
GO

-- 15.	In ra danh sách các sản phẩm (MASP,TENSP) không bán được.
SELECT DISTINCT SP.MASP, SP.TENSP
FROM SANPHAM SP
LEFT JOIN CTHD CT
ON SP.MASP = CT.MASP
LEFT JOIN HOADON HD
ON CT.SOHD = HD.SOHD
WHERE CT.SOHD IS NULL
GO

-- 16.	In ra danh sách các sản phẩm (MASP,TENSP) không bán được trong năm 2006.
SELECT DISTINCT SP.MASP, SP.TENSP
FROM SANPHAM SP
WHERE SP.MASP NOT IN (
    SELECT DISTINCT CT.MASP
    FROM CTHD CT
    INNER JOIN HOADON HD
    ON CT.SOHD = HD.SOHD
    WHERE YEAR(HD.NGHD) = '2006'
)
GO

-- 17.	In ra danh sách các sản phẩm (MASP,TENSP) do “Trung Quoc” sản xuất không bán được trong năm 2006.
SELECT DISTINCT SP.MASP, SP.TENSP
FROM SANPHAM SP
WHERE SP.NUOCSX = 'Trung Quoc' AND SP.MASP NOT IN (
    SELECT DISTINCT CT.MASP
    FROM CTHD CT
    INNER JOIN HOADON HD
    ON CT.SOHD = HD.SOHD
    WHERE YEAR(HD.NGHD) = '2006'
)
GO

-- 18.	Tìm số hóa đơn đã mua tất cả các sản phẩm do Singapore sản xuất.
SELECT DISTINCT HD.SOHD
FROM HOADON HD
INNER JOIN CTHD CT
ON HD.SOHD = CT.SOHD
INNER JOIN SANPHAM SP
ON CT.MASP = SP.MASP
WHERE SP.NUOCSX = 'Singapore'
GO

-- 19.	Tìm số hóa đơn trong năm 2006 đã mua ít nhất tất cả các sản phẩm do Singapore sản xuất.
SELECT DISTINCT HD.SOHD
FROM HOADON HD
INNER JOIN CTHD CT
ON HD.SOHD = CT.SOHD
INNER JOIN SANPHAM SP
ON CT.MASP = SP.MASP
WHERE YEAR(HD.NGHD) = '2006' AND SP.NUOCSX = 'Singapore'
GROUP BY HD.SOHD
HAVING COUNT(CT.MASP) = (
    SELECT COUNT(SP.MASP) AS 'Total'
    FROM SANPHAM SP
    WHERE SP.NUOCSX = 'Singapore'
)
GO

-- 20.	Có bao nhiêu hóa đơn không phải của khách hàng đăng ký thành viên mua?
SELECT COUNT(SOHD) AS 'Total'
FROM HOADON
WHERE MAKH IS NULL
GO

-- 21.	Có bao nhiêu sản phẩm khác nhau được bán ra trong năm 2006.
SELECT COUNT(DISTINCT CT.MASP) AS 'Total'
FROM HOADON HD
INNER JOIN CTHD CT
ON HD.SOHD = CT.SOHD
WHERE YEAR(NGHD) = '2006'
GO

-- 22.	Cho biết trị giá hóa đơn cao nhất, thấp nhất là bao nhiêu ?
SELECT MAX(TRIGIA) AS 'Max', MIN(TRIGIA) AS 'Min'
FROM HOADON
GO

-- 23.	Trị giá trung bình của tất cả các hóa đơn được bán ra trong năm 2006 là bao nhiêu?
SELECT AVG(TRIGIA) AS 'Avg'
FROM HOADON
WHERE YEAR(NGHD) = '2006'
GO

-- 24.	Tính doanh thu bán hàng trong năm 2006.
SELECT SUM(TRIGIA) AS 'sum'
FROM HOADON
WHERE YEAR(NGHD) = '2006'
GO

-- 25.	Tìm số hóa đơn có trị giá cao nhất trong năm 2006.
SELECT MAX(TRIGIA) AS 'Max'
FROM HOADON
WHERE YEAR(NGHD) = '2006'
GO

-- 26.	Tìm họ tên khách hàng đã mua hóa đơn có trị giá cao nhất trong năm 2006.
SELECT TOP 1 KH.HOTEN
FROM KHACHHANG KH
INNER JOIN HOADON HD
ON KH.MAKH = HD.MAKH
WHERE YEAR(HD.NGHD) = '2006'
ORDER BY HD.TRIGIA DESC
GO

-- 27.	In ra danh sách 3 khách hàng (MAKH, HOTEN) có doanh số cao nhất.
SELECT TOP 3 KH.MAKH, KH.HOTEN, KH.DOANHSO
FROM KHACHHANG KH
ORDER BY KH.DOANHSO DESC

-- 28.	In ra danh sách các sản phẩm (MASP, TENSP) có giá bán bằng 1 trong 3 mức giá cao nhất.
SELECT SP.MASP, SP.TENSP, SP.GIA
FROM SANPHAM SP
WHERE SP.GIA IN (
    SELECT DISTINCT TOP 3  SP.GIA
    FROM SANPHAM SP
    ORDER BY SP.GIA DESC
)
GO

-- 29.	In ra danh sách các sản phẩm (MASP, TENSP) do “Thai Lan” sản xuất có giá bằng 1 trong 3 mức giá cao nhất (của tất cả các sản phẩm).
SELECT SP.MASP, SP.TENSP, SP.GIA
FROM SANPHAM SP
WHERE SP.NUOCSX = 'Thai Lan' AND SP.GIA IN (
    SELECT DISTINCT TOP 3  SP.GIA
    FROM SANPHAM SP
    ORDER BY SP.GIA DESC
)
GO

-- 30.	In ra danh sách các sản phẩm (MASP, TENSP) do “Trung Quoc” sản xuất có giá bằng 1 trong 3 mức giá cao nhất (của sản phẩm do “Trung Quoc” sản xuất).
SELECT SP.MASP, SP.TENSP, SP.GIA
FROM SANPHAM SP
WHERE SP.NUOCSX = 'Trung Quoc' AND SP.GIA IN (
    SELECT DISTINCT TOP 3  SP.GIA
    FROM SANPHAM SP
    WHERE SP.NUOCSX = 'Trung Quoc'
    ORDER BY SP.GIA DESC
)
GO

-- 31.  In ra danh sách 3 khách hàng có doanh số cao nhất (sắp xếp theo kiểu xếp hạng).
SELECT TOP 3 KH.MAKH, KH.HOTEN
FROM KHACHHANG KH
ORDER BY KH.DOANHSO DESC
GO

-- 32.	Tính tổng số sản phẩm do “Trung Quoc” sản xuất.
SELECT COUNT(SP.MASP) AS TOTAL
FROM SANPHAM SP
WHERE SP.NUOCSX = 'Trung Quoc'
GO

-- 33.	Tính tổng số sản phẩm của từng nước sản xuất.
SELECT COUNT(SP.MASP) AS TOTAL, SP.NUOCSX
FROM SANPHAM SP
GROUP BY SP.NUOCSX
ORDER BY TOTAL DESC
GO

-- 34.	Với từng nước sản xuất, tìm giá bán cao nhất, thấp nhất, trung bình của các sản phẩm.
SELECT SP.NUOCSX, MAX(SP.GIA) AS MAXPRICE, MIN(SP.GIA) AS MINPRICE, AVG(SP.GIA) AS AVGPRICE
FROM SANPHAM SP
GROUP BY SP.NUOCSX
GO

-- 35.	Tính doanh thu bán hàng mỗi ngày.
SELECT SUM(TRIGIA) AS 'DOANH THU', NGHD
FROM HOADON
GROUP BY NGHD
ORDER BY NGHD DESC
GO

-- 36.	Tính tổng số lượng của từng sản phẩm bán ra trong tháng 10/2006.
SELECT CT.MASP, SUM(CT.SL) AS TOTAL
FROM CTHD CT
INNER JOIN HOADON HD
ON CT.SOHD = HD.SOHD
WHERE MONTH(HD.NGHD) = '10' AND YEAR(HD.NGHD) = '2006'
GROUP BY CT.MASP
ORDER BY TOTAL DESC
GO

-- 37.	Tính doanh thu bán hàng của từng tháng trong năm 2006.
SELECT MONTH(HD.NGHD) AS MONTH, SUM(HD.TRIGIA) AS DOANHTHU
FROM HOADON HD
WHERE YEAR(HD.NGHD) = '2006'
GROUP BY MONTH(HD.NGHD)
ORDER BY MONTH ASC
GO

-- 38.	Tìm hóa đơn có mua ít nhất 4 sản phẩm khác nhau.
SELECT HD.SOHD
FROM HOADON HD
INNER JOIN CTHD CT
ON HD.SOHD = CT.SOHD
GROUP BY HD.SOHD
HAVING COUNT(DISTINCT CT.MASP) >= 4
GO

-- 39.	Tìm hóa đơn có mua 3 sản phẩm do “Viet Nam” sản xuất (3 sản phẩm khác nhau).
SELECT HD.SOHD, *
FROM HOADON HD
INNER JOIN CTHD CT
ON HD.SOHD = CT.SOHD
INNER JOIN SANPHAM SP
ON CT.MASP = SP.MASP
WHERE SP.NUOCSX = 'Viet Nam'
GROUP BY HD.SOHD
HAVING COUNT(DISTINCT CT.MASP) >= 3
GO

-- 40.	Tìm khách hàng (MAKH, HOTEN) có số lần mua hàng nhiều nhất. 
SELECT TOP 1 WITH TIES KH.MAKH, KH.HOTEN
FROM KHACHHANG KH
ORDER BY KH.DOANHSO DESC
GO

-- 41.	Tháng mấy trong năm 2006, doanh số bán hàng cao nhất ?
SELECT MONTH(HD.NGHD) AS MONTH, SUM(HD.TRIGIA) AS [TOTAL]
FROM HOADON HD
WHERE YEAR(HD.NGHD) = '2006'
GROUP BY MONTH(HD.NGHD)
ORDER BY [TOTAL] DESC
GO

-- 42.	Tìm sản phẩm (MASP, TENSP) có tổng số lượng bán ra thấp nhất trong năm 2006.
SELECT SP.MASP, SP.TENSP
FROM SANPHAM SP
INNER JOIN CTHD CT
ON SP.MASP = CT.MASP
INNER JOIN HOADON HD
ON HD.SOHD = CT.SOHD
WHERE YEAR(HD.NGHD) = '2006'
GROUP BY SP.MASP, SP.TENSP
HAVING SUM(CT.SL) = (
    SELECT TOP 1 SUM(CT.SL)
    FROM SANPHAM SP
    INNER JOIN CTHD CT
    ON SP.MASP = CT.MASP
    INNER JOIN HOADON HD
    ON HD.SOHD = CT.SOHD
    WHERE YEAR(HD.NGHD) = '2006'
    GROUP BY SP.MASP, SP.TENSP
    ORDER BY SUM(CT.SL) ASC
)
GO

SELECT TOP 1 WITH TIES SP.MASP, SP.TENSP, SUM(CT.SL)
FROM SANPHAM SP
INNER JOIN CTHD CT
ON SP.MASP = CT.MASP
INNER JOIN HOADON HD
ON HD.SOHD = CT.SOHD
WHERE YEAR(HD.NGHD) = '2006'
GROUP BY SP.MASP, SP.TENSP
ORDER BY SUM(CT.SL) ASC
GO

-- 43.	Mỗi nước sản xuất, tìm sản phẩm (MASP,TENSP) có giá bán cao nhất.
SELECT SP.MASP, SP.TENSP, SP.NUOCSX
FROM SANPHAM SP
INNER JOIN (
    SELECT SP.NUOCSX, MAX(SP.GIA) AS 'Max'
    FROM SANPHAM SP
    GROUP BY SP.NUOCSX
) MSP
ON SP.NUOCSX = MSP.NUOCSX AND SP.GIA = MSP.[Max]
GO

-- 44.	Tìm nước sản xuất sản xuất ít nhất 3 sản phẩm có giá bán khác nhau.
SELECT SP.NUOCSX
FROM SANPHAM SP
GROUP BY SP.NUOCSX
HAVING COUNT(DISTINCT SP.GIA) >= 3
GO

-- 45.	Trong 10 khách hàng có doanh số cao nhất, tìm khách hàng có số lần mua hàng nhiều nhất.
SELECT TOP 1 HD.MAKH, COUNT(HD.SOHD) AS 'SO LAN MUA HANG'
FROM HOADON HD
WHERE HD.MAKH IN (
    SELECT TOP 10 KH.MAKH
    FROM KHACHHANG KH
    ORDER BY KH.DOANHSO DESC
)
GROUP BY HD.MAKH
ORDER BY COUNT(HD.SOHD) DESC
GO

-- BAI TAP CUOI SLIDE CHUONG 4 -- PROCEDURE
-- 1.   Nhập vào MAKH,HOTEN,… kiểm tra xem đã tồn tại chưa, nếu có hãy thông báo lỗi, nếu không hãy thêm thông tin đó.
CREATE PROCEDURE check_info_customer 
    @MAKH CHAR(4),
    @HOTEN NVARCHAR(40), 
    @DCHI NVARCHAR(50), 
    @SODT NVARCHAR(20), 
    @NGSINH SMALLDATETIME,
    @NGDK SMALLDATETIME
AS
BEGIN
    BEGIN TRY
        IF EXISTS (SELECT 1 FROM KHACHHANG WHERE MAKH = @MAKH)
        BEGIN
            RAISERROR ('MAKH already exists.', 16, 1);
            RETURN;
        END

        INSERT INTO KHACHHANG (MAKH, HOTEN, DCHI, SODT, NGSINH, NGDK)
        VALUES (@MAKH, @HOTEN, @DCHI, @SODT, @NGSINH, @NGDK);
        
        PRINT 'Customer add successful';
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        SET @ErrorMessage = ERROR_MESSAGE();
        RAISERROR(@ErrorMessage, 16, 1);
    END CATCH
END
GO

EXEC check_info_customer 
    @MAKH = 'KH11', 
    @HOTEN = N'Tran Van B', 
    @DCHI = N'456 Đường XYZ, Quận 2, TP.HCM', 
    @SODT = '0912345678', 
    @NGSINH = '1995-05-15', 
    @NGDK = '2024-11-12';
GO

-- 2.   Nhập SOHD, NGHD,… kiểm tra xem hóa đơn này tồn tại chưa, kiểm ra mã KH, mã NV, nếu tồn tại thì thông báo lỗi, không thì hãy them thông tin vào bảng HOADON.
CREATE PROCEDURE check_info_order
    @SOHD INT,
    @NGHD SMALLDATETIME, 
    @MAKH CHAR(4), 
    @MANV CHAR(4)
AS
BEGIN
    BEGIN TRY
        IF EXISTS (SELECT 1 FROM HOADON WHERE SOHD = @SOHD)
        BEGIN
            RAISERROR ('SOHD is already exists.', 16, 1);
            RETURN;
        END

        IF NOT EXISTS (SELECT 1 FROM KHACHHANG WHERE MAKH = @MAKH)
        BEGIN
            RAISERROR ('MAKH is not exists.', 16, 1);
            RETURN;
        END

        IF NOT EXISTS (SELECT 1 FROM NHANVIEN WHERE MANV = MANV)
        BEGIN
            RAISERROR ('MANV is not exists.', 16, 1);
            RETURN;
        END

        INSERT INTO HOADON (SOHD, NGHD, MAKH, MANV)
        VALUES (@SOHD, @NGHD, @MAKH, @MANV);
        
        PRINT 'Order add successful';
    END TRY
    BEGIN CATCH
        DECLARE @ErrorMessage NVARCHAR(4000);
        SET @ErrorMessage = ERROR_MESSAGE();
        RAISERROR(@ErrorMessage, 16, 1);
    END CATCH
END
GO

EXEC check_info_order 
    @SOHD = '1024', 
    @NGHD = '2024-11-12', 
    @MAKH = 'KH01', 
    @MANV = 'NV01';
GO

-- 3.   Nhập vào MASP, hãy cho biết sản phẩm này được bán trong bao nhiêu hóa đơn rồi.
CREATE PROCEDURE count_product_in_order 
    @MASP CHAR(4)
AS
BEGIN
    SELECT COUNT(DISTINCT HD.SOHD) AS 'TOTALHOADON'
    FROM HOADON HD
    INNER JOIN CTHD CT
    ON HD.SOHD = CT.SOHD
    WHERE CT.MASP = @MASP
END
GO

EXEC count_product_in_order
    @MASP = 'TV02'
GO

-- 4.   Hãy thêm thông tin khách hàng mới là họ tên của bạn, những thông tin khác tùy ý, them dữ liệu cho các bảng HOADON, CTHD tương ứng. 
-- Sau đó viết procedure: Nhập vào MAKH (cái bạn vừa thêm) kiểm tra xem có tồn tại thì xóa thông tin khách hang đó và những dữ liệu liên quan, nếu không thì thông báo không có thông tin để xóa.
INSERT INTO KHACHHANG (MAKH, HOTEN, DCHI, SODT, NGSINH, NGDK, DOANHSO) VALUES
('KH99', 'Vu Thai Duong', 'Vinh Loc A, Binh Chanh, TPHCM', '0343338112', '1960-10-22', '2006-07-22', 13060000);
GO

INSERT INTO HOADON (SOHD, NGHD, MAKH, MANV, TRIGIA)
VALUES
(9999, '2024-11-12', 'KH99', 'NV01', 45000);
GO

INSERT INTO CTHD (SOHD, MASP, SL)
VALUES
    (9999, 'TV02', 10);
GO

CREATE PROCEDURE delete_cus_and_related_data
    @MAKH CHAR(4)
AS
BEGIN
    IF EXISTS (SELECT 1 FROM KHACHHANG WHERE MAKH = @MAKH)
    BEGIN
        DELETE FROM CTHD
        WHERE SOHD IN (SELECT SOHD FROM HOADON WHERE MAKH = @MAKH)

        DELETE FROM HOADON
        WHERE MAKH = @MAKH

        DELETE FROM KHACHHANG
        WHERE MAKH = @MAKH

        PRINT('Delete customer and related information are deleted')
    END
    ELSE
    BEGIN
        PRINT('There is no customer information to delete')
    END
END
GO

EXEC delete_cus_and_related_data
    @MAKH = 'KH99'
GO

-- 5.   Thêm 1 cột số lần mua hàng của khách hàng vào bảng KHACHHANG, bổ sung dữ liệu cột đó bằng procedure.
ALTER TABLE KHACHHANG
    ADD TOTALBUY INT
GO

CREATE PROCEDURE update_total_buy_customer
AS
BEGIN
    UPDATE KHACHHANG
    SET TOTALBUY = (
        SELECT COUNT(HD.SOHD)
        FROM HOADON HD
        WHERE HD.MAKH = KHACHHANG.MAKH
    )

    PRINT('Update total buy customer successful')
END

EXEC update_total_buy_customer
GO