-- I. Ngôn ngữ định nghĩa dữ liệu (Data Definition Language):
-- 1. Tạo quan hệ và khai báo tất cả các ràng buộc khóa chính, khóa ngoại. Thêm vào 3 thuộc tính GHICHU, DIEMTB, XEPLOAI cho quan hệ HOCVIEN.
ALTER TABLE HOCVIEN
ADD 
GHICHU VARCHAR(255),
DIEMTB FLOAT,
XEPLOAI VARCHAR(50)
GO

-- 2. Mã học viên là một chuỗi 5 ký tự, 3 ký tự đầu là mã lớp, 2 ký tự cuối cùng là số thứ tự học viên trong lớp. VD: “K1101”
CREATE TRIGGER TRG_CREATE_MAHV
ON HOCVIEN
INSTEAD OF INSERT
AS
BEGIN
    DECLARE @MALOP CHAR(3), @SO_THU_TU INT, @MAHV CHAR(5)

    SELECT @MALOP = MALOP 
    FROM INSERTED;

    SELECT @SO_THU_TU = COUNT(*) + 1
    FROM HOCVIEN
    WHERE MALOP = @MALOP;

    SET @MAHV = @MALOP + RIGHT('00' + CAST(@SO_THU_TU AS VARCHAR), 2);

    INSERT INTO HOCVIEN (MAHV, HO, TEN, NGSINH, GIOITINH, NOISINH, MALOP)
    SELECT @MAHV, HO, TEN, NGSINH, GIOITINH, NOISINH, MALOP
    FROM INSERTED;
END;
GO;

-- 3. Thuộc tính GIOITINH chỉ có giá trị là “Nam” hoặc “Nu”.
ALTER TABLE HOCVIEN
ADD CONSTRAINT CHK_GENDER
CHECK (GIOITINH IN ('Nam', 'Nu'))
GO;

-- 4. Điểm số của một lần thi có giá trị từ 0 đến 10 và cần lưu đến 2 số lẽ (VD: 6.22).
CREATE TRIGGER TRG_CHECK_DIEM
ON KETQUATHI
INSTEAD OF INSERT, UPDATE
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM INSERTED
        WHERE DIEM < 0 OR DIEM > 10
    )
    BEGIN
        RAISERROR ('DIEM phải nằm trong khoảng từ 0 đến 10.', 16, 1);
        ROLLBACK TRANSACTION;
    END

    IF EXISTS (
        SELECT 1 FROM INSERTED WHERE DIEM IS NOT NULL
    )
    BEGIN
        RAISERROR ('DIEM not null', 16, 1);
        ROLLBACK TRANSACTION;
    END

    INSERT INTO KETQUATHI (MAHV, MAMH, LANTHI, NGTHI, DIEM, KQUA)
    SELECT MAHV, MAMH, LANTHI, NGTHI, DIEM, KQUA
    FROM INSERTED;

END;
GO

-- 5. Kết quả thi là “Dat” nếu điểm từ 5 đến 10 và “Khong dat” nếu điểm nhỏ hơn 5.
CREATE TRIGGER trg_SetKqua
ON KETQUATHI
AFTER INSERT, UPDATE
AS
BEGIN
    UPDATE k
    SET KQUA = CASE
        WHEN i.DIEM >= 5 THEN 'Dat'
        ELSE 'Khong dat'
    END
    FROM KETQUATHI k
    INNER JOIN inserted i 
        ON k.MAHV = i.MAHV AND k.MAMH = i.MAMH AND k.LANTHI = i.LANTHI;
END;
GO

-- 6. Học viên thi một môn tối đa 3 lần.
CREATE TRIGGER trg_CheckMaxAttempts
ON KETQUATHI
AFTER INSERT
AS
BEGIN
    -- Check if the student has already attempted the subject 3 times
    DECLARE @MAHV CHAR(5), @MAMH VARCHAR(10);
    
    -- Get the student ID (MAHV) and subject code (MAMH) from the inserted record
    SELECT @MAHV = MAHV, @MAMH = MAMH
    FROM INSERTED;
    
    -- Check the count of attempts for this student and subject
    IF (SELECT COUNT(*) FROM KETQUATHI WHERE MAHV = @MAHV AND MAMH = @MAMH) > 3
    BEGIN
        -- If the student has already attempted the subject 3 times, roll back the insertion
        RAISERROR('Student %s has already attempted the subject %s 3 times.', 16, 1, @MAHV, @MAMH);
        ROLLBACK TRANSACTION;
    END
END
GO


-- 7. Học kỳ chỉ có giá trị từ 1 đến 3.
ALTER TABLE GIANGDAY
ADD CONSTRAINT chk_Hocky
CHECK (HOCKY BETWEEN 1 AND 3);
GO

-- 8. Học vị của giáo viên chỉ có thể là “CN”, “KS”, “Ths”, ”TS”, ”PTS”.
ALTER TABLE GIAOVIEN
ADD CONSTRAINT chk_Hocvi
CHECK (HOCVI IN ('CN', 'KS', 'Ths', 'TS', 'PTS'));
GO

-- 9. Lớp trưởng của một lớp phải là học viên của lớp đó.
CREATE TRIGGER trg_CheckClassLeader
ON LOP
AFTER INSERT, UPDATE
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM inserted i
        WHERE NOT EXISTS (
            SELECT 1
            FROM HOCVIEN h
            WHERE h.MAHV = i.MAGVCN AND h.MALOP = i.MALOP
        )
    )
    BEGIN
        RAISERROR('Class leader must be a student in the same class.', 16, 1);
        ROLLBACK TRANSACTION;
    END
END;
GO

-- 10. Trưởng khoa phải là giáo viên thuộc khoa và có học vị “TS” hoặc “PTS”.
CREATE TRIGGER trg_CheckDepartmentHead
ON KHOA
AFTER INSERT, UPDATE
AS
BEGIN
    -- Check if the department head (TRGKHOA) is a teacher (GIAOVIEN) in the same department (MAKHOA)
    -- and has the academic title "TS" or "PTS"
    IF EXISTS (
        SELECT 1
        FROM inserted i
        WHERE NOT EXISTS (
            SELECT 1
            FROM GIAOVIEN g
            WHERE g.MAGV = i.TRGKHOA
            AND g.MAKHOA = i.MAKHOA
            AND g.HOCVI IN ('TS', 'PTS')
        )
    )
    BEGIN
        -- If the conditions are not met, raise an error
        RAISERROR('Department head must be a teacher in the same department with academic title "TS" or "PTS".', 16, 1);
        ROLLBACK TRANSACTION;
    END
END;
GO

-- 11. Học viên ít nhất là 18 tuổi.
CREATE TRIGGER trg_CheckStudentAge
ON HOCVIEN
AFTER INSERT, UPDATE
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM inserted i
        WHERE DATEDIFF(YEAR, i.NGSINH, GETDATE()) < 18
            OR (DATEDIFF(YEAR, i.NGSINH, GETDATE()) = 18 AND MONTH(i.NGSINH) > MONTH(GETDATE()))
            OR (DATEDIFF(YEAR, i.NGSINH, GETDATE()) = 18 AND MONTH(i.NGSINH) = MONTH(GETDATE()) AND DAY(i.NGSINH) > DAY(GETDATE()))
    )
    BEGIN
        RAISERROR('Student must be at least 18 years old.', 16, 1);
        ROLLBACK TRANSACTION;
    END
END;
GO

-- 12. Giảng dạy một môn học ngày bắt đầu (TUNGAY) phải nhỏ hơn ngày kết thúc (DENNGAY).
CREATE TRIGGER trg_CheckTeachingDates
ON GIANGDAY
AFTER INSERT, UPDATE
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM inserted i
        WHERE i.TUNGAY >= i.DENNGAY
    )
    BEGIN
        RAISERROR('Start date (TUNGAY) must be earlier than end date (DENNGAY).', 16, 1);
        ROLLBACK TRANSACTION;  -- Rollback the transaction to prevent invalid data
    END
END;
GO

-- 13. Giáo viên khi vào làm ít nhất là 22 tuổi.
CREATE TRIGGER trg_CheckTeacherAge
ON GIAOVIEN
AFTER INSERT, UPDATE
AS
BEGIN
    DECLARE @CurrentDate DATE = GETDATE();

    IF EXISTS (
        SELECT 1
        FROM inserted i
        WHERE DATEDIFF(YEAR, i.NGSINH, @CurrentDate) < 22
           OR (MONTH(i.NGSINH) > MONTH(@CurrentDate) 
               OR (MONTH(i.NGSINH) = MONTH(@CurrentDate) AND DAY(i.NGSINH) > DAY(@CurrentDate)))
    )
    BEGIN
        RAISERROR('Teacher must be at least 22 years old when starting work.', 16, 1);
        ROLLBACK TRANSACTION;  -- Rollback the transaction to prevent invalid data
    END
END;
GO

-- 14. Tất cả các môn học đều có số tín chỉ lý thuyết và tín chỉ thực hành chênh lệch nhau không quá 3.
CREATE TRIGGER trg_CheckCreditDifference
ON MONHOC
AFTER INSERT, UPDATE
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM inserted i
        WHERE ABS(i.TCLT - i.TCTH) > 3
    )
    BEGIN
        RAISERROR('The difference between TCLT and TCTH must not exceed 3.', 16, 1);
        ROLLBACK TRANSACTION;  -- Rollback the transaction to prevent invalid data
    END
END;
GO

-- 15. Học viên chỉ được thi một môn học nào đó khi lớp của học viên đã học xong môn học này.
CREATE TRIGGER trg_HocVienThiMon
ON KETQUATHI
FOR INSERT
AS
BEGIN
    DECLARE @MAHV CHAR(5);
    DECLARE @MAMH VARCHAR(10);
    DECLARE @MALOP CHAR(3);

    SELECT @MAHV = MAHV, @MAMH = MAMH
    FROM inserted;

    SELECT @MALOP = MALOP
    FROM HOCVIEN
    WHERE MAHV = @MAHV;

    IF NOT EXISTS (
        SELECT 1
        FROM GIANGDAY
        WHERE MALOP = @MALOP
        AND MAMH = @MAMH
        AND DENNGAY IS NOT NULL
    )
    BEGIN
        RAISERROR('Student cannot take the exam for this course as the class has not completed it yet.', 16, 1);
        ROLLBACK TRANSACTION;
    END
END;
GO

-- 16. Mỗi học kỳ của một năm học, một lớp chỉ được học tối đa 3 môn.
CREATE TRIGGER trg_LopMax3Mon
ON GIANGDAY
FOR INSERT
AS
BEGIN
    DECLARE @MALOP CHAR(3);
    DECLARE @HOCKY TINYINT;
    DECLARE @NAM SMALLINT;

    SELECT @MALOP = MALOP, @HOCKY = HOCKY, @NAM = NAM
    FROM inserted;

    IF (SELECT COUNT(*) 
        FROM GIANGDAY
        WHERE MALOP = @MALOP
        AND HOCKY = @HOCKY
        AND NAM = @NAM) >= 3
    BEGIN
        RAISERROR('This class has already been assigned 3 courses for the semester.', 16, 1);
        ROLLBACK TRANSACTION;
    END
END;
GO

-- 17. Sỉ số của một lớp bằng với số lượng học viên thuộc lớp đó.
CREATE TRIGGER trg_UpdateSisoOnInsert
ON HOCVIEN
FOR INSERT
AS
BEGIN
    DECLARE @MALOP CHAR(3);
    
    -- Get the class ID of the newly inserted student
    SELECT @MALOP = MALOP
    FROM inserted;

    -- Update the class size (SISO) based on the number of students in the class
    UPDATE LOP
    SET SISO = (SELECT COUNT(*) FROM HOCVIEN WHERE MALOP = @MALOP)
    WHERE MALOP = @MALOP;
END;
GO

CREATE TRIGGER trg_UpdateSisoOnDelete
ON HOCVIEN
FOR DELETE
AS
BEGIN
    DECLARE @MALOP CHAR(3);
    
    -- Get the class ID of the student who was deleted
    SELECT @MALOP = MALOP
    FROM deleted;

    -- Update the class size (SISO) based on the number of students in the class
    UPDATE LOP
    SET SISO = (SELECT COUNT(*) FROM HOCVIEN WHERE MALOP = @MALOP)
    WHERE MALOP = @MALOP;
END;
GO

-- 18. Trong quan hệ DIEUKIEN giá trị của thuộc tính MAMH và MAMH_TRUOC trong cùng một bộ không được giống nhau (“A”,”A”) và cũng không tồn tại hai bộ (“A”,”B”) và (“B”,”A”).
CREATE TRIGGER trg_CheckDieukien
ON DIEUKIEN
FOR INSERT, UPDATE
AS
BEGIN
    IF EXISTS (SELECT 1 FROM inserted WHERE MAMH = MAMH_TRUOC)
    BEGIN
        RAISERROR('MAMH and MAMH_TRUOC cannot be the same.', 16, 1);
        ROLLBACK TRANSACTION;
    END

    IF EXISTS (SELECT 1 
               FROM inserted i1
               JOIN DIEUKIEN i2 
               ON i1.MAMH = i2.MAMH_TRUOC AND i1.MAMH_TRUOC = i2.MAMH)
    BEGIN
        RAISERROR('Cannot have reverse pairs of MAMH and MAMH_TRUOC (e.g., ("A", "B") and ("B", "A")).', 16, 1);
        ROLLBACK TRANSACTION;
    END
END;
GO

-- 19. Các giáo viên có cùng học vị, học hàm, hệ số lương thì mức lương bằng nhau.
CREATE TRIGGER trg_CheckLuongForSameTitle
ON GIAOVIEN
FOR INSERT, UPDATE
AS
BEGIN
    DECLARE @HOCVI VARCHAR(10), @HOCHAM VARCHAR(10), @HESO NUMERIC(4,2), @MUCLUONG MONEY;

    SELECT @HOCVI = HOCVI, @HOCHAM = HOCHAM, @HESO = HESO, @MUCLUONG = MUCLUONG
    FROM inserted;

    IF EXISTS (
        SELECT 1
        FROM GIAOVIEN
        WHERE HOCVI = @HOCVI
          AND HOCHAM = @HOCHAM
          AND HESO = @HESO
          AND MUCLUONG <> @MUCLUONG
    )
    BEGIN
        RAISERROR('Teachers with the same academic title, professional title, and salary coefficient must have the same salary.', 16, 1);
        ROLLBACK TRANSACTION;
    END
END;
GO

-- 20. Học viên chỉ được thi lại (lần thi >1) khi điểm của lần thi trước đó dưới 5.
CREATE TRIGGER trg_CheckRetakeConditions
ON KETQUATHI
FOR INSERT, UPDATE
AS
BEGIN
    DECLARE @MAHV CHAR(5), @MAMH VARCHAR(10), @LANTHI TINYINT, @DIEM NUMERIC(4,2);

    SELECT @MAHV = MAHV, @MAMH = MAMH, @LANTHI = LANTHI, @DIEM = DIEM
    FROM inserted;

    IF @LANTHI > 1
    BEGIN
        IF EXISTS (
            SELECT 1
            FROM KETQUATHI
            WHERE MAHV = @MAHV
              AND MAMH = @MAMH
              AND LANTHI = 1
              AND DIEM >= 5
        )
        BEGIN
            RAISERROR('A student can only retake the exam if the score of the previous attempt is below 5.', 16, 1);
            ROLLBACK TRANSACTION;
        END
    END
END;
GO

-- 21. Ngày thi của lần thi sau phải lớn hơn ngày thi của lần thi trước (cùng học viên, cùng môn học).
CREATE TRIGGER trg_CheckExamDateOrder
ON KETQUATHI
FOR INSERT, UPDATE
AS
BEGIN
    DECLARE @MAHV CHAR(5), @MAMH VARCHAR(10), @LANTHI TINYINT, @NGTHI SMALLDATETIME;

    SELECT @MAHV = MAHV, @MAMH = MAMH, @LANTHI = LANTHI, @NGTHI = NGTHI
    FROM inserted;

    IF @LANTHI > 1
    BEGIN
        IF EXISTS (
            SELECT 1
            FROM KETQUATHI
            WHERE MAHV = @MAHV
              AND MAMH = @MAMH
              AND LANTHI = 1
              AND NGTHI >= @NGTHI
        )
        BEGIN
            RAISERROR('The exam date of a retake must be later than the exam date of the previous attempt.', 16, 1);
            ROLLBACK TRANSACTION;
        END
    END
END;
GO

-- 22. Học viên chỉ được thi những môn mà lớp của học viên đó đã học xong.
-- Create a trigger to ensure a student can only take exams for completed courses
CREATE TRIGGER trg_CheckCourseCompletion
ON KETQUATHI
AFTER INSERT
AS
BEGIN
    -- Declare variables for student ID and course ID
    DECLARE @MAHV CHAR(5);
    DECLARE @MAMH VARCHAR(10);
    
    -- Get the student ID and course ID from the inserted record
    SELECT @MAHV = MAHV, @MAMH = MAMH
    FROM INSERTED;

    -- Check if the course is completed for the student's class
    IF NOT EXISTS (
        SELECT 1
        FROM HOCVIEN HV
        JOIN LOP L ON HV.MALOP = L.MALOP
        JOIN GIANGDAY GD ON L.MALOP = GD.MALOP
        WHERE HV.MAHV = @MAHV
          AND GD.MAMH = @MAMH
          AND GD.DENNGAY <= GETDATE() -- Ensure the course is completed (end date <= current date)
    )
    BEGIN
        -- If the course is not completed, raise an error and prevent the insert
        RAISERROR ('Student is not eligible to take the exam for this course because it has not been completed.', 16, 1);
        ROLLBACK; -- Rollback the transaction to prevent the insert
    END
END;
GO

-- 23. Khi phân công giảng dạy một môn học, phải xét đến thứ tự trước sau giữa các môn học (sau khi học xong những môn học phải học trước mới được học những môn liền sau).
-- Create a trigger to ensure that prerequisites are taught before assigning a course to a teacher
CREATE TRIGGER trg_CheckCoursePrerequisites
ON GIANGDAY
AFTER INSERT
AS
BEGIN
    -- Declare variables for the course ID and the class ID
    DECLARE @MAMH VARCHAR(10);
    DECLARE @MAGV CHAR(4);
    DECLARE @MALOP CHAR(3);

    -- Get the course ID, teacher ID, and class ID from the inserted record
    SELECT @MAMH = MAMH, @MAGV = MAGV, @MALOP = MALOP
    FROM INSERTED;

    -- Check if there are any prerequisite courses for the new course
    IF EXISTS (
        SELECT 1
        FROM DIEUKIEN D
        WHERE D.MAMH = @MAMH -- The current course
    )
    BEGIN
        -- Check if all prerequisite courses have been taught in the same class
        IF NOT EXISTS (
            SELECT 1
            FROM DIEUKIEN D
            JOIN GIANGDAY GD ON D.MAMH_TRUOC = GD.MAMH -- The prerequisite course
            WHERE D.MAMH = @MAMH
              AND GD.MALOP = @MALOP
              AND GD.DENNGAY <= GETDATE() -- Ensure the prerequisite course has been completed
        )
        BEGIN
            -- If any prerequisite course has not been completed, raise an error and prevent the insert
            RAISERROR ('Prerequisite course(s) not completed. Cannot assign teacher to this course.', 16, 1);
            ROLLBACK; -- Rollback the transaction to prevent the insert
        END
    END
END;
GO

-- 24. Giáo viên chỉ được phân công dạy những môn thuộc khoa giáo viên đó phụ trách.
-- Create a trigger to ensure a teacher is only assigned to teach courses in their department
CREATE TRIGGER trg_CheckTeacherDepartment
ON GIANGDAY
AFTER INSERT
AS
BEGIN
    -- Declare variables for course ID, teacher ID, and department
    DECLARE @MAMH VARCHAR(10);
    DECLARE @MAGV CHAR(4);
    DECLARE @MAKHOA_TEACHER VARCHAR(4);
    DECLARE @MAKHOA_COURSE VARCHAR(4);

    -- Get the course ID and teacher ID from the inserted record
    SELECT @MAMH = MAMH, @MAGV = MAGV
    FROM INSERTED;

    -- Get the department of the teacher from the GIAOVIEN table
    SELECT @MAKHOA_TEACHER = MAKHOA
    FROM GIAOVIEN
    WHERE MAGV = @MAGV;

    -- Get the department of the course from the MONHOC table
    SELECT @MAKHOA_COURSE = MAKHOA
    FROM MONHOC
    WHERE MAMH = @MAMH;

    -- Check if the teacher's department matches the department of the course
    IF @MAKHOA_TEACHER <> @MAKHOA_COURSE
    BEGIN
        -- If the departments do not match, raise an error and prevent the insert
        RAISERROR ('Teacher cannot be assigned to teach a course in a different department.', 16, 1);
        ROLLBACK; -- Rollback the transaction to prevent the insert
    END
END;
GO


-- II. Ngôn ngữ thao tác dữ liệu (Data Manipulation Language):
-- 1. Tăng hệ số lương thêm 0.2 cho những giáo viên là trưởng khoa.
UPDATE GIAOVIEN
SET HESO = HESO + 0.2
WHERE MAGV IN (
    SELECT TRGKHOA FROM KHOA
)

-- 2. Cập nhật giá trị điểm trung bình tất cả các môn học (DIEMTB) của mỗi học viên (tất cả các môn học đều có hệ số 1 và nếu học viên thi một môn nhiều lần, chỉ lấy điểm của lần thi sau cùng).
-- Update the average grade (DIEMTB) for each student
WITH LatestScores AS (
    -- Get the latest exam score for each student in each subject
    SELECT 
        MAHV, 
        MAMH, 
        MAX(LANTHI) AS LatestExam, -- Get the most recent exam attempt
        DIEM
    FROM KETQUATHI
    GROUP BY MAHV, MAMH
)
-- Update the DIEMTB for each student
UPDATE HOCVIEN
SET DIEMTB = (
    SELECT AVG(DIEM) -- Calculate the average of the latest scores for each student
    FROM LatestScores
    WHERE LatestScores.MAHV = HOCVIEN.MAHV
)
GO


-- 3. Cập nhật giá trị cho cột GHICHU là “Cam thi” đối với trường hợp: học viên có một môn bất kỳ thi lần thứ 3 dưới 5 điểm.
UPDATE HOCVIEN
SET GHICHU = 'Cam thi'
WHERE MAHV IN (
    SELECT MAHV
    FROM KETQUATHI
    WHERE LANTHI = 3
    AND DIEM < 5
)
GO


-- 4. Cập nhật giá trị cho cột XEPLOAI trong quan hệ HOCVIEN như sau:
-- o Nếu DIEMTB >= 9 thì XEPLOAI =”XS”
-- o Nếu 8 <= DIEMTB < 9 thì XEPLOAI = “G”
-- o Nếu 6.5 <= DIEMTB < 8 thì XEPLOAI = “K”
-- o Nếu 5 <= DIEMTB < 6.5 thì XEPLOAI = “TB”
-- o Nếu DIEMTB < 5 thì XEPLOAI = ”Y”
-- Update the XEPLOAI column based on DIEMTB value
UPDATE HOCVIEN
SET XEPLOAI = 
    CASE
        WHEN DIEMTB >= 9 THEN 'XS'
        WHEN DIEMTB >= 8 AND DIEMTB < 9 THEN 'G'
        WHEN DIEMTB >= 6.5 AND DIEMTB < 8 THEN 'K'
        WHEN DIEMTB >= 5 AND DIEMTB < 6.5 THEN 'TB'
        WHEN DIEMTB < 5 THEN 'Y'
    END
GO


-- III. Ngôn ngữ truy vấn dữ liệu:
-- 1. In ra danh sách (mã học viên, họ tên, ngày sinh, mã lớp) lớp trưởng của các lớp.
SELECT HV.MAHV, HV.HO + ' ' + HV.TEN AS 'HOTEN', HV.NGSINH, HV.MALOP
FROM HOCVIEN HV
INNER JOIN LOP CL
ON HV.MAHV = CL.TRGLOP

-- 2. In ra bảng điểm khi thi (mã học viên, họ tên , lần thi, điểm số) môn CTRR của lớp “K12”, sắp xếp theo tên, họ học viên.
SELECT HV.MAHV, HV.HO, HV.TEN, RS.LANTHI, RS.DIEM
FROM HOCVIEN HV
INNER JOIN KETQUATHI RS
ON HV.MAHV = RS.MAHV
WHERE HV.MALOP = 'K12' AND RS.MAMH = 'CTRR'
ORDER BY HV.TEN ASC, HV.HO ASC

-- 3. In ra danh sách những học viên (mã học viên, họ tên) và những môn học mà học viên đó thi lần thứ nhất đã đạt.
SELECT DISTINCT HV.MAHV, HV.HO, HV.TEN
FROM HOCVIEN HV
INNER JOIN KETQUATHI RS
ON HV.MAHV = RS.MAHV
WHERE RS.LANTHI = 1 AND RS.KQUA = 'Dat'

-- 4. In ra danh sách học viên (mã học viên, họ tên) của lớp “K11” thi môn CTRR không đạt (ở lần thi 1).
SELECT DISTINCT HV.MAHV, HV.HO, HV.TEN
FROM HOCVIEN HV
INNER JOIN KETQUATHI RS
ON HV.MAHV = RS.MAHV
WHERE 
    HV.MALOP = 'K11' AND 
    RS.LANTHI = 1 AND 
    RS.KQUA = 'Khong Dat' AND
    RS.MAMH = 'CTRR'

-- 5. * Danh sách học viên (mã học viên, họ tên) của lớp “K” thi môn CTRR không đạt (ở tất cả các lần thi).
SELECT DISTINCT HV.MAHV, CONCAT(HV.HO, ' ', HV.TEN) AS HOTEN
FROM HOCVIEN HV
INNER JOIN KETQUATHI RS
ON HV.MAHV = RS.MAHV
WHERE HV.MALOP LIKE 'K%' AND RS.MAMH = 'CTRR'
GROUP BY HV.MAHV, HV.HO, HV.TEN
HAVING MAX(RS.DIEM) < 5;

-- 6. Tìm tên những môn học mà giáo viên có tên “Tran Tam Thanh” dạy trong học kỳ 1 năm 2006.
SELECT DISTINCT MH.MAMH, MH.TENMH
FROM MONHOC MH
INNER JOIN GIANGDAY GD
ON MH.MAMH = GD.MAMH
INNER JOIN GIAOVIEN GV
ON GD.MAGV = GV.MAGV
WHERE 
    GV.HOTEN = 'Tran Tam Thanh' AND 
    GD.HOCKY = 1 AND
    GD.NAM = '2006'

-- 7. Tìm những môn học (mã môn học, tên môn học) mà giáo viên chủ nhiệm lớp “K11” dạy trong học kỳ 1 năm 2006.
SELECT DISTINCT MH.MAMH, MH.TENMH
FROM MONHOC MH
INNER JOIN GIANGDAY GD
ON MH.MAMH = GD.MAMH
INNER JOIN GIAOVIEN GV
ON GD.MAGV = GV.MAGV
WHERE 
    GD.HOCKY = 1 AND
    GD.NAM = '2006' AND
    GD.MAGV IN (
    SELECT CL.MAGVCN
    FROM LOP CL
    WHERE CL.MALOP = 'K11'
   )

-- 8. Tìm họ tên lớp trưởng của các lớp mà giáo viên có tên “Nguyen To Lan” dạy môn “Co So Du Lieu”.
SELECT CONCAT(HV.HO, ' ', HV.TEN) AS 'HOTEN'
FROM HOCVIEN HV
INNER JOIN LOP CL
ON HV.MAHV = CL.TRGLOP
INNER JOIN GIANGDAY GD
ON CL.MALOP = GD.MALOP
INNER JOIN MONHOC MH
ON MH.MAMH = GD.MAMH
INNER JOIN GIAOVIEN GV
ON GD.MAGV = GV.MAGV
WHERE GV.HOTEN = 'Nguyen To Lan' AND MH.TENMH = 'Co So Du Lieu'
GO

-- 9. In ra danh sách những môn học (mã môn học, tên môn học) phải học liền trước môn “Co So Du Lieu”.
SELECT DK.MAMH_TRUOC, MH.TENMH
FROM DIEUKIEN DK
JOIN MONHOC MH ON DK.MAMH_TRUOC = MH.MAMH
WHERE DK.MAMH = (
    SELECT MAMH
    FROM MONHOC
    WHERE TENMH = 'Co So Du Lieu'
);

-- 10. Môn “Cau Truc Roi Rac” là môn bắt buộc phải học liền trước những môn học (mã môn học, tên môn học) nào.
SELECT DK.MAMH_TRUOC, MH.TENMH
FROM DIEUKIEN DK
JOIN MONHOC MH ON DK.MAMH = MH.MAMH
WHERE DK.MAMH_TRUOC = (
    SELECT MAMH
    FROM MONHOC
    WHERE TENMH = 'Cau Truc Roi Rac'
);

-- 11. Tìm họ tên giáo viên dạy môn CTRR cho cả hai lớp “K11” và “K12” trong cùng học kỳ 1 năm 2006.
SELECT GV.HOTEN
FROM GIAOVIEN GV
INNER JOIN GIANGDAY GD
ON GV.MAGV = GD.MAGV
WHERE 
    GD.HOCKY = 1 AND
    GD.NAM = '2006' AND
    GD.MAMH = 'CTRR' AND
    GD.MALOP IN ('K11', 'K12')
GROUP BY GV.HOTEN
HAVING COUNT(GV.HOTEN) = 2

-- 12. Tìm những học viên (mã học viên, họ tên) thi không đạt môn CSDL ở lần thi thứ 1 nhưng chưa thi lại môn này.
SELECT HV.MAHV, CONCAT(HV.HO, ' ', HV.TEN)
FROM HOCVIEN HV
INNER JOIN KETQUATHI RS
ON HV.MAHV = RS.MAHV
WHERE 
    RS.MAMH = 'CSDL' AND
    RS.DIEM < 5
GROUP BY HV.MAHV, CONCAT(HV.HO, ' ', HV.TEN)
HAVING COUNT(HV.MAHV) = 1

-- 13. Tìm giáo viên (mã giáo viên, họ tên) không được phân công giảng dạy bất kỳ môn học nào.
SELECT GV.MAGV, GV.HOTEN
FROM GIAOVIEN GV
WHERE GV.MAGV NOT IN (
    SELECT DISTINCT GD.MAGV
    FROM GIANGDAY GD
)

-- 14. Tìm giáo viên (mã giáo viên, họ tên) không được phân công giảng dạy bất kỳ môn học nào thuộc khoa giáo viên đó phụ trách.
SELECT GV.MAGV, GV.HOTEN
FROM GIAOVIEN GV
WHERE NOT EXISTS (
    SELECT 1
    FROM GIANGDAY GD
    JOIN MONHOC MH ON GD.MAMH = MH.MAMH
    WHERE GD.MAGV = GV.MAGV
    AND MH.MAKHOA = GV.MAKHOA
);

-- 15. Tìm họ tên các học viên thuộc lớp “K11” thi một môn bất kỳ quá 3 lần vẫn “Khong dat” hoặc thi lần thứ 2 môn CTRR được 5 điểm.
SELECT DISTINCT HV.HO + ' ' + HV.TEN AS HOTEN
FROM HOCVIEN HV
JOIN LOP L ON HV.MALOP = L.MALOP
JOIN KETQUATHI KQ ON HV.MAHV = KQ.MAHV
WHERE L.MALOP = 'K11'
  AND KQ.DIEM < 5
  AND KQ.MAHV IN (
      SELECT MAHV
      FROM KETQUATHI
      WHERE DIEM < 5
      GROUP BY MAHV, MAMH
      HAVING COUNT(*) > 3
  )

UNION

-- Điều kiện 2: Thi lần thứ 2 môn CTRR được điểm 5
SELECT DISTINCT HV.MAHV, HV.HO + ' ' + HV.TEN AS HOTEN
FROM HOCVIEN HV
INNER JOIN KETQUATHI RS 
ON HV.MAHV = RS.MAHV
WHERE 
    HV.MALOP = 'K11' AND 
    RS.MAMH = 'CTRR' AND
    RS.LANTHI = 2 AND
    RS.DIEM = 5;
GO

-- 16. Tìm họ tên giáo viên dạy môn CTRR cho ít nhất hai lớp trong cùng một học kỳ của một năm học.
SELECT DISTINCT GV.HOTEN
FROM GIAOVIEN GV
JOIN GIANGDAY GD ON GV.MAGV = GD.MAGV
WHERE GD.MAMH =  'CTRR'
AND GD.MAGV IN (
    SELECT MAGV
    FROM GIANGDAY
    WHERE MAMH = 'CTRR'
    GROUP BY MAGV, HOCKY, NAM
    HAVING COUNT(DISTINCT MALOP) >= 2
);
GO

-- 17. Danh sách học viên và điểm thi môn CSDL (chỉ lấy điểm của lần thi sau cùng).
WITH LatestExam AS (
    SELECT MAHV, MAMH, MAX(LANTHI) AS LAST_LANTHI
    FROM KETQUATHI
    WHERE MAMH = 'CSDL'
    GROUP BY MAHV, MAMH
)

SELECT HV.MAHV, CONCAT(HV.HO, ' ', HV.TEN) AS HOTEN, KQ.DIEM
FROM LatestExam LE
INNER JOIN KETQUATHI KQ 
ON 
    LE.MAHV = KQ.MAHV AND
    LE.MAMH = KQ.MAMH AND
    LE.LAST_LANTHI = KQ.LANTHI
INNER JOIN HOCVIEN HV 
    ON LE.MAHV = HV.MAHV;

-- 18. Danh sách học viên và điểm thi môn “Co So Du Lieu” (chỉ lấy điểm cao nhất của các lần thi).
SELECT HV.MAHV, CONCAT(HV.HO, ' ', HV.TEN) AS HOTEN, MAX(RS.DIEM) AS DIEM
FROM HOCVIEN HV 
INNER JOIN KETQUATHI RS
ON HV.MAHV = RS.MAHV
INNER JOIN MONHOC MH
ON RS.MAMH = MH.MAMH
WHERE MH.TENMH = 'Co So Du Lieu'
GROUP BY HV.MAHV, HV.HO, HV.TEN, HV.MAHV

-- 19. Khoa nào (mã khoa, tên khoa) được thành lập sớm nhất.
SELECT TOP 1 WITH TIES MAKHOA, TENKHOA, NGTLAP
FROM KHOA
ORDER BY NGTLAP ASC

-- 20. Có bao nhiêu giáo viên có học hàm là “GS” hoặc “PGS”.
SELECT COUNT(*) AS 'SoLuongGiaoVien'
FROM GIAOVIEN
WHERE HOCHAM IN ('GS', 'PGS');

-- 21. Thống kê có bao nhiêu giáo viên có học vị là “CN”, “KS”, “Ths”, “TS”, “PTS” trong mỗi khoa.
SELECT HOCVI, MAKHOA, COUNT(MAGV) AS 'SoLuongGiaoVien'
FROM GIAOVIEN
WHERE HOCVI IN ('CN', 'KS', 'Ths', 'TS', 'PTS')
GROUP BY HOCVI, MAKHOA
ORDER BY COUNT(MAGV) DESC
GO

-- 22. Mỗi môn học thống kê số lượng học viên theo kết quả (đạt và không đạt).
SELECT MAMH, KQUA, COUNT(*) AS 'SoLuongHocVien'
FROM KETQUATHI
GROUP BY MAMH, KQUA
ORDER BY MAMH, KQUA;
GO

-- 23. Tìm giáo viên (mã giáo viên, họ tên) là giáo viên chủ nhiệm của một lớp, đồng thời dạy cho lớp đó ít nhất một môn học.
SELECT DISTINCT GV.MAGV, GV.HOTEN
FROM GIAOVIEN GV
INNER JOIN LOP L 
ON GV.MAGV = L.MAGVCN
INNER JOIN GIANGDAY GD 
ON GV.MAGV = GD.MAGV AND L.MALOP = GD.MALOP
WHERE GV.MAGV = L.MAGVCN;


-- 24. Tìm họ tên lớp trưởng của lớp có sỉ số cao nhất.
SELECT HV.HO + ' ' + HV.TEN AS HOTEN
FROM LOP L
INNER JOIN HOCVIEN HV ON L.TRGLOP = HV.MAHV
WHERE L.SISO = (
    SELECT MAX(SISO) FROM LOP
);
GO

-- 25. * Tìm họ tên những LOPTRG thi không đạt quá 3 môn (mỗi môn đều thi không đạt ở tất cả các lần thi).
SELECT HV.HO + ' ' + HV.TEN AS HOTEN
FROM  HOCVIEN HV
INNER JOIN LOP L ON HV.MAHV = L.TRGLOP
WHERE 
    (
        SELECT COUNT(DISTINCT KQ.MAMH)
        FROM KETQUATHI KQ
        WHERE KQ.MAHV = HV.MAHV
        AND KQ.KQUA = 'Không đạt'
    ) <= 3
AND NOT EXISTS 
    (
      SELECT 1
      FROM KETQUATHI KQ2
      WHERE KQ2.MAHV = HV.MAHV
        AND KQ2.KQUA != 'Không đạt'
    );
GO

-- 26. Tìm học viên (mã học viên, họ tên) có số môn đạt điểm 9,10 nhiều nhất.
SELECT TOP 1 WITH TIES
    HV.MAHV, 
    HV.HO + ' ' + HV.TEN AS HOTEN, 
    COUNT(*) AS SO_MON_DIEM_9_10
FROM 
    HOCVIEN HV
JOIN 
    KETQUATHI KQ ON HV.MAHV = KQ.MAHV
WHERE 
    KQ.DIEM BETWEEN 9 AND 10
GROUP BY 
    HV.MAHV, HV.HO, HV.TEN
ORDER BY 
    COUNT(*) DESC;

-- 27. Trong từng lớp, tìm học viên (mã học viên, họ tên) có số môn đạt điểm 9,10 nhiều nhất.
WITH HocVienDiemCao AS (
    SELECT 
        HV.MALOP, 
        HV.MAHV, 
        HV.HO + ' ' + HV.TEN AS HOTEN, 
        COUNT(*) AS SO_MON_DIEM_9_10
    FROM 
        HOCVIEN HV
    JOIN 
        KETQUATHI KQ ON HV.MAHV = KQ.MAHV
    WHERE 
        KQ.DIEM BETWEEN 9 AND 10
    GROUP BY 
        HV.MALOP, HV.MAHV, HV.HO, HV.TEN
),
MaxDiemMoiLop AS (
    SELECT 
        MALOP, 
        MAX(SO_MON_DIEM_9_10) AS MAX_DIEM
    FROM 
        HocVienDiemCao
    GROUP BY 
        MALOP
)
SELECT 
    HVD.MALOP, 
    HVD.MAHV, 
    HVD.HOTEN, 
    HVD.SO_MON_DIEM_9_10
FROM 
    HocVienDiemCao HVD
JOIN 
    MaxDiemMoiLop MDL ON HVD.MALOP = MDL.MALOP AND HVD.SO_MON_DIEM_9_10 = MDL.MAX_DIEM
ORDER BY 
    HVD.MALOP, HVD.MAHV;

-- 28. Trong từng học kỳ của từng năm, mỗi giáo viên phân công dạy bao nhiêu môn học, bao nhiêu lớp.
SELECT 
    GD.HOCKY, 
    GD.NAM, 
    GD.MAGV, 
    GV.HOTEN, 
    COUNT(DISTINCT GD.MAMH) AS SO_MON_DAY, 
    COUNT(DISTINCT GD.MALOP) AS SO_LOP_DAY
FROM 
    GIANGDAY GD
JOIN 
    GIAOVIEN GV ON GD.MAGV = GV.MAGV
GROUP BY 
    GD.HOCKY, GD.NAM, GD.MAGV, GV.HOTEN
ORDER BY 
    GD.NAM, GD.HOCKY, GD.MAGV;

-- 29. Trong từng học kỳ của từng năm, tìm giáo viên (mã giáo viên, họ tên) giảng dạy nhiều nhất.
WITH GiangDayCount AS (
    SELECT 
        GD.HOCKY, 
        GD.NAM, 
        GD.MAGV, 
        GV.HOTEN, 
        COUNT(DISTINCT GD.MAMH) AS SO_MON_DAY
    FROM 
        GIANGDAY GD
    JOIN 
        GIAOVIEN GV ON GD.MAGV = GV.MAGV
    GROUP BY 
        GD.HOCKY, GD.NAM, GD.MAGV, GV.HOTEN
),
MaxGiangDayCount AS (
    SELECT 
        HOCKY, 
        NAM, 
        MAX(SO_MON_DAY) AS MAX_MON_DAY
    FROM 
        GiangDayCount
    GROUP BY 
        HOCKY, NAM
)
SELECT 
    GDC.HOCKY, 
    GDC.NAM, 
    GDC.MAGV, 
    GDC.HOTEN, 
    GDC.SO_MON_DAY
FROM 
    GiangDayCount GDC
JOIN 
    MaxGiangDayCount MGC ON GDC.HOCKY = MGC.HOCKY AND GDC.NAM = MGC.NAM AND GDC.SO_MON_DAY = MGC.MAX_MON_DAY
ORDER BY 
    GDC.NAM, GDC.HOCKY;
GO

-- 30. Tìm môn học (mã môn học, tên môn học) có nhiều học viên thi không đạt (ở lần thi thứ 1) nhất.
SELECT 
    MH.MAMH, 
    MH.TENMH, 
    COUNT(KT.MAHV) AS SO_HV_KHONG_DAT
FROM 
    KETQUATHI KT
JOIN 
    MONHOC MH ON KT.MAMH = MH.MAMH
WHERE 
    KT.LANTHI = 1 
    AND KT.DIEM < 5
GROUP BY 
    MH.MAMH, MH.TENMH
ORDER BY 
    SO_HV_KHONG_DAT DESC

-- 31. Tìm học viên (mã học viên, họ tên) thi môn nào cũng đạt (chỉ xét lần thi thứ 1).
SELECT 
    HV.MAHV, 
    HV.HO + ' ' + HV.TEN AS HOTEN
FROM 
    HOCVIEN HV
JOIN 
    KETQUATHI KT ON HV.MAHV = KT.MAHV
WHERE 
    KT.LANTHI = 1
GROUP BY 
    HV.MAHV, HV.HO, HV.TEN
HAVING 
    COUNT(CASE WHEN KT.KQUA = 'Khong Dat' THEN 1 END) = 0;
GO

-- 32. * Tìm học viên (mã học viên, họ tên) thi môn nào cũng đạt (chỉ xét lần thi sau cùng).
WITH LastExamResults AS (
    SELECT 
        MAHV, 
        MAMH, 
        MAX(LANTHI) AS LATEST_LANTHI
    FROM 
        KETQUATHI
    GROUP BY 
        MAHV, MAMH
)
SELECT 
    HV.MAHV, 
    HV.HO + ' ' + HV.TEN AS HOTEN
FROM 
    HOCVIEN HV
JOIN 
    KETQUATHI KT ON HV.MAHV = KT.MAHV
JOIN 
    LastExamResults LER ON KT.MAHV = LER.MAHV AND KT.MAMH = LER.MAMH AND KT.LANTHI = LER.LATEST_LANTHI
WHERE 
    KT.KQUA = 'Dat'
GROUP BY 
    HV.MAHV, HV.HO, HV.TEN
HAVING 
    COUNT(CASE WHEN KT.KQUA = 'Khong Dat' THEN 1 END) = 0;

-- 33. * Tìm học viên (mã học viên, họ tên) đã thi tất cả các môn đều đạt (chỉ xét lần thi thứ 1).
WITH FirstExamResults AS (
    SELECT 
        MAHV, 
        MAMH, 
        LANTHI, 
        KQUA
    FROM 
        KETQUATHI
    WHERE 
        LANTHI = 1
)
SELECT 
    HV.MAHV, 
    HV.HO + ' ' + HV.TEN AS HOTEN
FROM 
    HOCVIEN HV
JOIN 
    FirstExamResults FER ON HV.MAHV = FER.MAHV
GROUP BY 
    HV.MAHV, HV.HO, HV.TEN
HAVING 
    COUNT(CASE WHEN FER.KQUA = 'Khong Dat' THEN 1 END) = 0
    AND COUNT(DISTINCT FER.MAMH) = (SELECT COUNT(DISTINCT MAMH) FROM MONHOC);

-- 34. * Tìm học viên (mã học viên, họ tên) đã thi tất cả các môn đều đạt (chỉ xét lần thi sau cùng).
WITH LastExamResults AS (
    SELECT 
        MAHV, 
        MAMH, 
        MAX(LANTHI) AS LATEST_LANTHI
    FROM 
        KETQUATHI
    GROUP BY 
        MAHV, MAMH
)
SELECT 
    HV.MAHV, 
    HV.HO + ' ' + HV.TEN AS HOTEN
FROM 
    HOCVIEN HV
JOIN 
    KETQUATHI KT ON HV.MAHV = KT.MAHV
JOIN 
    LastExamResults LER ON KT.MAHV = LER.MAHV AND KT.MAMH = LER.MAMH AND KT.LANTHI = LER.LATEST_LANTHI
WHERE 
    KT.KQUA = 'Đạt'
GROUP BY 
    HV.MAHV, HV.HO, HV.TEN
HAVING 
    COUNT(CASE WHEN KT.KQUA = 'Không đạt' THEN 1 END) = 0
    AND COUNT(DISTINCT KT.MAMH) = (SELECT COUNT(DISTINCT MAMH) FROM MONHOC);
GO

-- 35. ** Tìm học viên (mã học viên, họ tên) có điểm thi cao nhất trong từng môn (lấy điểm ở lần thi sau cùng).
WITH LastExamResults AS (
    SELECT 
        MAHV, 
        MAMH, 
        MAX(LANTHI) AS LATEST_LANTHI
    FROM 
        KETQUATHI
    GROUP BY 
        MAHV, MAMH
)
SELECT 
    HV.MAHV, 
    HV.HO + ' ' + HV.TEN AS HOTEN,
    KT.MAMH,
    KT.DIEM
FROM 
    HOCVIEN HV
JOIN 
    KETQUATHI KT ON HV.MAHV = KT.MAHV
JOIN 
    LastExamResults LER ON KT.MAHV = LER.MAHV AND KT.MAMH = LER.MAMH AND KT.LANTHI = LER.LATEST_LANTHI
WHERE 
    KT.DIEM = (
        SELECT MAX(DIEM)
        FROM KETQUATHI
        WHERE MAMH = KT.MAMH AND LANTHI = LER.LATEST_LANTHI
    )
ORDER BY 
    KT.MAMH, KT.DIEM DESC;
GO