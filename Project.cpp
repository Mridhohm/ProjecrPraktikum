#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int max_barang = 100;

struct Barang {
    int id;
    string nama;
    int jumlah;
};

void bubbleSort(Barang arr[], int n, int key, bool ascending) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            bool condition = false;
            switch (key) {
                case 1:
                    condition = ascending ? (arr[j].id > arr[j+1].id) : (arr[j].id < arr[j+1].id);
                    break;
                case 2:
                    condition = ascending ? (arr[j].nama > arr[j+1].nama) : (arr[j].nama < arr[j+1].nama);
                    break;
                case 3:
                    condition = ascending ? (arr[j].jumlah > arr[j+1].jumlah) : (arr[j].jumlah < arr[j+1].jumlah);
                    break;
            }
            if (condition) {
                Barang temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void saveToFile(Barang arr[], int n) {
    ofstream file("gudang.txt");
    if (!file) {
        cout << "Gagal membuka file untuk menyimpan data!" << endl;
        return;
    }
    file << n << endl;
    for (int i = 0; i < n; i++) {
        file << arr[i].id << endl;
        file << arr[i].nama << endl;
        file << arr[i].jumlah << endl;
    }
    file.close();
    cout << "Data berhasil disimpan ke file gudang.txt" << endl;
}

int loadFromFile(Barang arr[]) {
    ifstream file("gudang.txt");
    if (!file) {
        cout << "File gudang.txt tidak ditemukan, mulai dengan data kosong." << endl;
        return 0;
    }
    int n;
    file >> n;
    file.ignore();
    for (int i = 0; i < n; i++) {
        file >> arr[i].id;
        file.ignore();
        getline(file, arr[i].nama);
        file >> arr[i].jumlah;
        file.ignore();
    }
    file.close();
    cout << "Data berhasil dimuat dari file gudang.txt" << endl;
    return n;
}

void tampilkanBarang(Barang* arr, int n) {
    if (n == 0) {
        cout << "Tidak ada barang di gudang." << endl;
    } else {
        cout << "Daftar Barang di Gudang:" << endl;
        Barang* p = arr;
        for (int i = 0; i < n; i++, p++) {
            cout << "ID: " << p->id
                 << ", Nama: " << p->nama
                 << ", Jumlah: " << p->jumlah << endl;
        }
    }
}

int main() {
    Barang gudang[max_barang];
    int totalBarang = 0;
    int pilihan;

    totalBarang = loadFromFile(gudang);

    do {
        cout << "\nMenu Manajemen Gudang : "<< endl;
        cout << "1. Input Barang"<< endl;
        cout << "2. Tampilkan Barang Yang Sudah Di Input"<< endl;
        cout << "3. Sorting Data Barang"<< endl;
        cout << "4. Simpan ke File"<< endl;
        cout << "5. Muat dari File"<< endl;
        cout << "6. Keluar" << endl;
        cout << "Pilih opsi (1-6): ";
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
                tampilkanBarang(gudang, totalBarang);
                break;

            case 3: {
                if (totalBarang == 0) {
                    cout << "Data kosong, tidak bisa disorting." << endl;
                    break;
                }
                int sortPil, order;
                cout << "Sorting berdasarkan: \n1. ID\n2. Nama\n3. Jumlah\nPilih (1-3): ";
                cin >> sortPil;
                cout << "Urutan: \n1. Ascending\n2. Descending\nPilih (1-2): ";
                cin >> order;
                bubbleSort(gudang, totalBarang, sortPil, order == 1);
                cout << "Data berhasil disorting!" << endl;
                tampilkanBarang(gudang, totalBarang);
                break;
            }

            case 4:
                saveToFile(gudang, totalBarang);
                break;

            case 5:
                totalBarang = loadFromFile(gudang);
                break;

            case 6:
                cout << "Keluar dari program." << endl;
                break;

            default :
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 6);

    return 0;
}