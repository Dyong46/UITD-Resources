def tinh(a: int, b: float) -> tuple:
    tong = a + b
    hieu = a - b
    tich = a * b

    return tong, hieu, tich

def none(a: int, b: float) -> None:
    tong = a + b
    hieu = a - b
    tich = a * b

    return tong, hieu, tich

if __name__ == "__main__":
    tg, h, tc = tinh(2, 3)
    print(tg)
    print(h)
    print(tc)

