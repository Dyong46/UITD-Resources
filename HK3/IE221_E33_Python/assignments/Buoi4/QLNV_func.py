def init_vp(ma_nv, ho_ten, luong_cb, so_ng):
    return {
        'ma_nv': ma_nv,
        'ho_ten': ho_ten,
        'luong_cb': luong_cb,
        'so_ng': so_ng
    }

def init_bh(ma_nv, ho_ten, luong_cb, so_sp):
    return {
        'ma_nv': ma_nv,
        'ho_ten': ho_ten,
        'luong_cb': luong_cb,
        'so_sp': so_sp,
        'luong_ht': 0
    }

def init_data_dsnv(ds):
    """tao danh sach chua nhan vien"""
    ds.append(init_vp(123, "", 5_000_000, 23))
    ds.append(init_vp(123, "", 5_000_000, 567))

def print_ds_nv(ds):
    for d in ds:
        print(list(d.values()))

if __name__ == '__main__':
    ds = []
    init_data_dsnv(ds)

    print_ds_nv(ds)