# Minimal: load a UDataTable by path and print its row names
import unreal

DATA_TABLE_PATH = "/Game/ThirdParty/2D_Tools/SortingLayers/DT_SortingLayers.DT_SortingLayers"


def load_datatable(path):
    return unreal.EditorAssetLibrary.load_asset(path)


def print_row_names(path=DATA_TABLE_PATH):
    dt = load_datatable(path)
    if not dt:
        return
    names = dt.get_row_names() or []
    for n in names:
        try:
            s = n.get_name()
        except Exception:
            s = str(n)
        unreal.log(s)
        print(s)


if __name__ == '__main__':
    print_row_names()
