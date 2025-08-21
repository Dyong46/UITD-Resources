class NhanVien:
    def __init__(self, ma_nv, ho_ten, luong_cb):
        self._ma_nv = ma_nv
        self._ho_ten = ho_ten
        self._luong_cb = luong_cb
        self._luong_ht = None

    def in_nv(self):
        print("NV: ", [self._ma_nv, self._ho_ten, self._luong_cb, self._luong_ht], end=" ")

    def tinh_luong_ht(self):
        pass


class NVVanPhong(NhanVien):
    def __init__(self, ma_nv, ho_ten, luong_cb, so_ng):
        super().__init__(ma_nv, ho_ten, luong_cb)
        self.__so_ng = so_ng

    def in_nv(self):
        """Over right absolute"""
        print([self._ma_nv, self._ho_ten, self._luong_cb, self.__so_ng, self._luong_ht], end=" ")

    def tinh_luong_ht(self):
        self._luong_ht = self._luong_cb + self.__so_ng * 180_000
        return self._luong_ht


class NVBanHang(NhanVien):
    def __init__(self, ma_nv, ho_ten, luong_cb, so_sp):
        super().__init__(ma_nv, ho_ten, luong_cb)
        self.__so_sp = so_sp

    def in_nv(self):
        print([self.__so_sp, self._luong_cb, self._luong_ht, self.__so_sp, self._luong_ht], end=" ")

    def tinh_luong_ht(self):
        self._luong_ht = self._luong_cb + self.__so_sp * 15_000


class CongTy:
    def __init__(self, ma_ct, ten_ct):
        self.__ma_ct = ma_ct
        self.__ten_ct = ten_ct
        self.__ds_nv = []

    def init_ds_nv(self):
        """1. Khoi tao du lieu cac nhan vien"""
        nv1 = NVVanPhong(123, 'Nguyen Van A', 6_000_000, 23)
        nv2 = NVBanHang(124, 'Nguyen Van B', 7_000_000, 256)

        self.__ds_nv.extend([nv1, nv2])
        self.__ds_nv.append(NVVanPhong(125, 'Nguyen Van C', 5_500_000, 25))

        return len(self.__ds_nv)

    def print_ds_nv(self):
        list(map(lambda nv: nv.in_nv(), self.__ds_nv))

    def tinh_luong_ht(self):
        list(map(lambda nv: nv.tinh_luong_ht(), self.__ds_nv))

    def tim_nv_theo_ma_nv(self, ma_nv):
        for nv in self.__ds_nv:
            if nv._ma_nv == ma_nv:
                return nv
        return None

    def tim_nv_theo_ma_nv_2(self, ma_nv):
        return list(filter(lambda nv: nv._ma_nv == ma_nv, self.__ds_nv))

    def tim_luong_ht_max(self):
        luong_ht_max = self.__ds_nv[0]
        for nv in self.__ds_nv:
            if nv.luong_cb > luong_ht_max:
                luong_ht_max = nv.luong_cb
        return luong_ht_max

    def tim_luong_ht_min(self):
        luong_ht_min = self.__ds_nv[0]
        for nv in self.__ds_nv:
            if nv.luong_cb < luong_ht_min:
                luong_ht_min = nv.luong_cb
        return luong_ht_min

if __name__ == '__main__':
    print("Test: 1. Khoi tao du lieu cac nhan vien")
    ct = CongTy('CITD', 'TT')
    so_nv = ct.init_ds_nv()
    print('\t+ Ket qua: ', so_nv, 'nhan vien')

    print("\tTest: 2. In ds nv trong ct:")
    ct.print_ds_nv()

    print("\tTest: 3. Tinh luong cac nhan vien:")
    ct.tinh_luong_ht()
    ct.print_ds_nv()

    print("\tTest: 4. Tim nhan vien theo ma nhan vien:")
    nv_test_4 = ct.tim_nv_theo_ma_nv_2(123)
    nv_test_4.in_nv()

    print("\tTest: 5. Tim nhan vien theo ma nv:")