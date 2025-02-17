#include <iostream>
#include <string>
using namespace std;

const int max_barang = 100;

struct Barang {
    int id;
    string nama;
    int jumlah;
};

int main() {
    Barang gudang[max_barang];
    int totalBarang = 0;
    int pilihan;

    do {
        cout << "\nMenu Manajemen Gudang : "<< endl;
        cout << "1. Input Barang"<< endl;
        cout << "2. Tampilkan Barang Yang Sudah Di Input"<< endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih opsi (1-3): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: 
                if (totalBarang < max_barang){
                    cout << "Masukkan Nomor Barang: ";
                    cin >> gudang[totalBarang].id;
                    cout << "Masukkan Nama Barang: ";
                    cin.ignore(); 
                     getline(cin, gudang[totalBarang].nama);
                    cout << "Masukkan Jumlah Barang : ";
                    cin >> gudang[totalBarang].jumlah;
                    totalBarang++;
                    cout << "Barang berhasil ditambahkan!" << endl;
                } else {
                    cout << "Gudang sudah penuh!" << endl;
                }
                break;
            
            case 2:
                if (totalBarang == 0) {
                    cout << "Tidak ada barang di gudang." << endl;
                } else {
                    cout << "Daftar Barang di Gudang:" << endl;
                    for (int i = 0; i < totalBarang; i++) {
                        cout << "ID: " << gudang[i].id 
                             << ", Nama: " << gudang[i].nama 
                             << ", Jumlah: " << gudang[i].jumlah << endl;
                    }
                }
                break;
            
            case 3:
                cout << "Keluar dari program." << endl;
                break;

            default :
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 3);

    return 0;
}
