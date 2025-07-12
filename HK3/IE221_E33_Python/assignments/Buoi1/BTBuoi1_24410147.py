import math


# Viết chương trình nhập vào 4 số nguyên a, b, c, d. Tính trung bình cộng của 4 số trên và in kết quả ra màn hình.
def average(a, b, c, d):
    return sum([a, b, c, d]) / 4

# Viết chương trình nhập vào 2 số nguyên a, b. Tính tổng, hiệu, tích, thình. K, chịa ây dp chia làm truy 2n 3 ủa 2 số râu dà in chết quả rau kết quả 3.333333 thì làm tròn 3.333).
def abc(a, b):
    sum = a + b
    sub = a - b
    mult = a * b
    div = a / b
    mod = a % b
    div_round = a // b
    return sum, sub, mult, div, mod, div_round


# Viết chương trình cho phép nhập vào số nguyên dương N có 2 chữ số. Xuất ra màn hình tổng các chữ số của N. Ví dụ: Nhập N=48, kết quả xuất ra màn hình là 4 + 8 = 12

# Viết chương trình cho phép nhập vào giờ, phút và giây (ví dụ 8 39 50). Hãy đổi ra giây và in kết quả ra màn hình.

# Viết chương trình nhập vào năm sinh, in ra tuổi. Ví dụ nhập 1988 in ra (giả sử năm hiện tại là 2023): Ban sinh nam 1988 vay ban 35 tuoi.


