# Khởi tạo nhân viên văn phòng
def tao_nv_vp(ma_nv, ho_ten, luong_cb, so_ngay):
    return {
        'loai': 'vp',
        'ma_nv': ma_nv,
        'ho_ten': ho_ten,
        'luong_cb': luong_cb,
        'so_ngay': so_ngay,
        'luong_ht': 0
    }


# Khởi tạo nhân viên bán hàng
def tao_nv_bh(ma_nv, ho_ten, luong_cb, so_sp):
    return {
        'loai': 'bh',
        'ma_nv': ma_nv,
        'ho_ten': ho_ten,
        'luong_cb': luong_cb,
        'so_sp': so_sp,
        'luong_ht': 0
    }


# 1. Khởi tạo danh sách nhân viên
def khoi_tao_ds():
    ds = []
    ds.append(tao_nv_vp('VP01', 'Nguyễn Văn A', 5000000, 22))
    ds.append(tao_nv_vp('VP02', 'Trần Thị B', 5500000, 25))
    ds.append(tao_nv_bh('BH01', 'Lê Văn C', 4500000, 150))
    ds.append(tao_nv_bh('BH02', 'Phạm Thị D', 6000000, 90))
    return ds


# 2. Xuất danh sách nhân viên
def xuat_ds(ds):
    for nv in ds:
        print(f"Mã: {nv['ma_nv']}, Họ tên: {nv['ho_ten']}, Lương CB: {nv['luong_cb']}, Lương HT: {nv['luong_ht']}")


# 3. Tính lương
def tinh_luong(ds):
    for nv in ds:
        if nv['loai'] == 'vp':
            nv['luong_ht'] = nv['luong_cb'] + nv['so_ngay'] * 150_000
        elif nv['loai'] == 'bh':
            nv['luong_ht'] = nv['luong_cb'] + nv['so_sp'] * 18_000


# 4. Tìm nhân viên theo mã
def tim_nv_theo_ma(ds, ma_nv):
    for nv in ds:
        if nv['ma_nv'] == ma_nv:
            print("Tìm thấy nhân viên:")
            print(f"Mã: {nv['ma_nv']}, Họ tên: {nv['ho_ten']}, Lương CB: {nv['luong_cb']}, Lương HT: {nv['luong_ht']}")
            return
    print("Không tìm thấy nhân viên.")


# 5. Tìm nhân viên có lương cao nhất
def nv_luong_cao_nhat(ds):
    if not ds:
        print("Danh sách rỗng.")
        return
    max_nv = ds[0]
    for nv in ds[1:]:
        if nv['luong_ht'] > max_nv['luong_ht']:
            max_nv = nv
    print("Nhân viên có lương cao nhất:")
    print(f"Mã: {max_nv['ma_nv']}, Họ tên: {max_nv['ho_ten']}, Lương HT: {max_nv['luong_ht']}")


# 6. Tìm nhân viên bán hàng có lương thấp nhất
def nv_bh_luong_thap_nhat(ds):
    bh_list = [nv for nv in ds if nv['loai'] == 'bh']
    if not bh_list:
        print("Không có nhân viên bán hàng.")
        return
    min_nv = bh_list[0]
    for nv in bh_list[1:]:
        if nv['luong_ht'] < min_nv['luong_ht']:
            min_nv = nv
    print("Nhân viên bán hàng có lương thấp nhất:")
    print(f"Mã: {min_nv['ma_nv']}, Họ tên: {min_nv['ho_ten']}, Lương HT: {min_nv['luong_ht']}")


# ===========================
# CHẠY CHƯƠNG TRÌNH CHÍNH
# ===========================
if __name__ == '__main__':
    ds_nv = khoi_tao_ds()
    tinh_luong(ds_nv)

    print("=== Danh sách nhân viên ===")
    xuat_ds(ds_nv)

    print("\n=== Tìm nhân viên theo mã 'VP02' ===")
    tim_nv_theo_ma(ds_nv, 'VP02')

    print("\n=== Nhân viên lương cao nhất ===")
    nv_luong_cao_nhat(ds_nv)

    print("\n=== Nhân viên bán hàng lương thấp nhất ===")
    nv_bh_luong_thap_nhat(ds_nv)
