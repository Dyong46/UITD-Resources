class NhanVien:
    def __init__(self, ma_nv, ho_ten, luong_cb):
        self._ma_nv = ma_nv
        self._ho_ten = ho_ten
        self._luong_cb = luong_cb
        self._luong_ht = None

    def in_nv(self):
        print("NV: ", [self._ma_nv, self._ho_ten, self._luong_cb, self._luong_ht], end=" ")

class NVVanPhong(NhanVien):
    def __init__(self, ma_nv, ho_ten, luong_cb, so_ng):
        super().__init__(ma_nv, ho_ten, luong_cb)
        self.__so_ng = so_ng

    def in_nv(self):
        """Over right absolute"""
        print([self._ma_nv, self._ho_ten, self._luong_cb, self.__so_ng, self._luong_ht], end=" ")

    def in_nv_vp(self):
        print([self._ma_nv, self._ho_ten, self._luong_cb, self.__so_ng, self._luong_ht], end=" ")

    def tinh_luong_ht_nv_vp(self):
        self._luong_ht = self._luong_cb + self.__so_ng * 180_000
        return self._luong_ht
    
class NVBanHang(NhanVien):
    def __init__(self, ma_nv, ho_ten, luong_cb, so_sp):
        super().__init__(ma_nv, ho_ten, luong_cb)
        self.__so_sp = so_sp

    def in_nv(self):
        """Ghi de hoan toan"""
        print([self.__so_sp, self._luong_cb, self._luong_ht, self.__so_sp, self._luong_ht], end=" ")

    def in_nv_bh(self):
        print([self.__so_sp, self._luong_cb, self._luong_ht, self.__so_sp, self._luong_ht], end=" ")

    def tinh_luong_ht_nv_bh(self):
        self._luong_ht = self._luong_cb + self.__so_sp * 25_000

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
        for nv in self.__ds_nv:
            print(nv.in_nv())

    def tinh_luong_ht(self):
        for nv in self.__ds_nv:
            if isinstance(nv, NVVanPhong):
                nv.tinh_luong_ht_nv_vp()
            elif isinstance(nv, NVBanHang):
                nv.tinh_luong_ht_nv_bh()

    def tim_nv_theo_ma_nv(self, ma_nv):
        for nv in self.__ds_nv:
            if nv.ma_nv == ma_nv:
                return nv

        return None

