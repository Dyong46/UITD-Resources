from Chuong9.QLNV_Luong import Luong


class View:
    @classmethod
    def print_ds_nv(cls, ds_nv: list):
        for ds in ds_nv:
            print(ds)

class Model:
    def __init__(self):
        self.luong = Luong()

    def conn_db_get_ds_nv(self):
        self.luong.init_ds_nv()

    def get_ds_nv(self):
        return self.luong.ds_nv

class Controller:
    def __init__(self, view: View, model: Model):
        self.view = view
        self.model = model

    # 1. conn_db 2. tinh_luong_ht 3. hien_thi_ds_nv
    def conn_db_tinh_luong_ht_hien_thi_ds_nv(self):
        self.model.conn_db_get_ds_nv()
        self.model.luong.tinh_luong_ht()
        self.view.print_ds_nv(self.model.luong.ds_nv)

if __name__ == '__main__':
    view = View()
    model = Model()
    controller = Controller(view, model)

    controller.conn_db_tinh_luong_ht_hien_thi_ds_nv()
