#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const long long MAX_BARANG = 99999;
struct BARANG
{
    int id;
    string nama;
    string kategori;
    int harga;
    int total;
};

int pilih;

BARANG dataBarang[MAX_BARANG];
int jumlahBarang = 0;

BARANG* cariBarang(int idCari)
{
    for (int i = 0; i < jumlahBarang; i++)
    {
        if (dataBarang[i].id == idCari)
        {
            return &dataBarang[i]; 
        }
    }
    return nullptr; 
}

void buatheaderfile()
{
    ifstream test("DATA_GUDANG.txt");
    if (!test.good())
    {
        ofstream file("DATA_GUDANG.txt");
        file << "DATA GUDANG\n";
        file << left
             << setw(5)  << "NO"
             << setw(20) << "NAMA"
             << setw(20) << "ID BARANG"
             << setw(20) << "KATEGORI"
             << setw(15) << "HARGA"
             << setw(15) << "TOTAL" << endl;
        file << string(95, '=') << endl;
        file.close();
    }
}

void loadDataFromFile()
{
    ifstream file("DATA_GUDANG.txt");
    jumlahBarang = 0;

    if (file.is_open())
    {
        string line;
        getline(file, line); 
        getline(file, line); 
        getline(file, line); 

        while (getline(file, line) && jumlahBarang < MAX_BARANG)
        {
            if (line.empty() || line.find_first_not_of(" \t") == string::npos)
                continue;

            istringstream iss(line);
            int no;
            iss >> no
                >> dataBarang[jumlahBarang].nama
                >> dataBarang[jumlahBarang].id
                >> dataBarang[jumlahBarang].kategori
                >> dataBarang[jumlahBarang].harga
                >> dataBarang[jumlahBarang].total;

            if (!iss.fail())
                jumlahBarang++;
        }

        file.close();
    }
}

void saveDataToFile()
{
    ofstream file("DATA_GUDANG.txt");

    file << "DATA GUDANG\n";
    file << left
         << setw(5)  << "NO"
         << setw(20) << "NAMA"
         << setw(20) << "ID BARANG"
         << setw(20) << "KATEGORI"
         << setw(15) << "HARGA"
         << setw(15) << "TOTAL" << endl;

    file << string(95, '=') << endl;

    for (int i = 0; i < jumlahBarang; i++)
    {
        file << left
             << setw(5)  << (i + 1)
             << setw(20) << dataBarang[i].nama
             << setw(20) << dataBarang[i].id
             << setw(20) << dataBarang[i].kategori
             << setw(15) << dataBarang[i].harga
             << setw(15) << dataBarang[i].total
             << endl;
    }

    file.close();
}


void inputbarang()
{
    loadDataFromFile(); 
    system("CLS");
    cout << "================================\n";
    cout << "=         INPUT ITEM           =\n";
    cout << "================================\n";
    cout << "MASUKKAN JUMLAT ITEM :  ";
    cin >> pilih;

    if (jumlahBarang + pilih > MAX_BARANG)
    {
        cout << "KAPASITAS ITEM PENUH! " << (MAX_BARANG - jumlahBarang) << endl;
        return;
    }

    for (int i = 0; i < pilih; i++)
    {
        cout << "\nINPUT DATA BARANG KE- " << (i + 1) << ":\n";

        BARANG b;
        
        do {
            cout << "ID BARANG : ";
            cin >> b.id;

            if (cariBarang(b.id) != nullptr)
                cout << "ID SUDAH DIGUNAKAN! COBA LAGI.\n";

        } while (cariBarang(b.id) != nullptr);

        cout << "NAMA BARANG : ";
        cin >> b.nama;

        cout << "KATEGORI : ";
        cin >> b.kategori;

        do {
            cout << "HARGA : ";
            cin >> b.harga;
            if (b.harga < 0) cout << "HARGA TIDAK BOLEH NEGATIF!\n";
        } while (b.harga < 0);

        do {
            cout << "TOTAL : ";
            cin >> b.total;
            if (b.total < 0) cout << "TOTAL TIDAK BOLEH NEGATIF!\n";
        } while (b.total < 0);

        // Simpan ke array
        dataBarang[jumlahBarang] = b;
        jumlahBarang++;
    }

    saveDataToFile(); 
    cout << "\nDATA BERHASIL DISIMPAN. TOTAL DATA SEKARANG: " << jumlahBarang << endl;
}

void listbarang()
{
    loadDataFromFile(); 

    if (jumlahBarang == 0)
    {
        cout << "ANDA BELUM MENGINPUT BARANG APAPUN\n";
        return;
    }

    cout << left
         << setw(5)  << "NO"
         << setw(20) << "NAMA"
         << setw(20) << "ID BARANG"
         << setw(20) << "KATEGORI"
         << setw(15) << "HARGA"
         << setw(15) << "TOTAL" << endl;
    cout << string(95, '=') << endl;

    for (int i = 0; i < jumlahBarang; i++)
    {
        cout << left
             << setw(5)  << (i + 1)
             << setw(20) << dataBarang[i].nama
             << setw(20) << dataBarang[i].id
             << setw(20) << dataBarang[i].kategori
             << setw(15) << dataBarang[i].harga
             << setw(15) << dataBarang[i].total << endl;
    }
}


void caribarang()
{
    loadDataFromFile();

    if (jumlahBarang == 0)
    {
        cout << "TIDAK ADA DATA UNTUK DICARI\n";
        return;
    }

    int idCari;
    cout << "MASUKKAN ID BARANG YANG DICARI: ";
    cin >> idCari;

    BARANG* b = cariBarang(idCari);

    if (b != nullptr)
    {
        cout << "\n==== BARANG DITEMUKAN ====\n";
        cout << "NAMA     : " << b->nama << endl;
        cout << "ID       : " << b->id << endl;
        cout << "KATEGORI : " << b->kategori << endl;
        cout << "HARGA    : " << b->harga << endl;
        cout << "TOTAL    : " << b->total << endl;
    }
    else
    {
        cout << "BARANG DENGAN ID " << idCari << " TIDAK DITEMUKAN\n";
    }
}


void merge(BARANG arr[], int l, int m, int r, int field)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    BARANG L[100], R[100];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        bool condition = false;

        switch (field)
        {
        case 1:
            condition = L[i].nama > R[j].nama;
            break;
        case 2:
            condition = L[i].id > R[j].id;
            break;
        case 3:
            condition = L[i].kategori > R[j].kategori;
            break;
        case 4:
            condition = L[i].harga > R[j].harga;
            break;
        case 5:
            condition = L[i].total > R[j].total;
            break;
        }

        if (condition)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(BARANG arr[], int l, int r, int field)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, field);
        mergeSort(arr, m + 1, r, field);
        merge(arr, l, m, r, field);
    }
}
void sortingbarang()
{
    if (jumlahBarang == 0)
    {
        cout << "TIDAK ADA DATA UNTUK DISORTIR\n";
        return;
    }

    int metode, field;
    cout << "=== PILIH METODE SORTING ===\n";
    cout << "1. ASCENDING (Bubble Sort)\n";
    cout << "2. DESCENDING (Merge Sort)\n";
    cout << "PILIH : ";
    cin >> metode;

    cout << "\n=== SORTING BERDASARKAN APA? ===\n";
    cout << "1. NAMA\n";
    cout << "2. ID BARANG\n";
    cout << "3. KATEGORI\n";
    cout << "4. HARGA\n";
    cout << "5. TOTAL\n";
    cout << "PILIH : ";
    cin >> field;

    if (metode == 1) 
    {
        for (int i = 0; i < jumlahBarang - 1; i++)
        {
            for (int j = 0; j < jumlahBarang - i - 1; j++)
            {
                bool condition = false;

                switch (field)
                {
                case 1:
                    condition = dataBarang[j].nama > dataBarang[j + 1].nama;
                    break;
                case 2:
                    condition = dataBarang[j].id > dataBarang[j + 1].id;
                    break;
                case 3:
                    condition = dataBarang[j].kategori > dataBarang[j + 1].kategori;
                    break;
                case 4:
                    condition = dataBarang[j].harga > dataBarang[j + 1].harga;
                    break;
                case 5:
                    condition = dataBarang[j].total > dataBarang[j + 1].total;
                    break;
                }

                if (condition)
                    swap(dataBarang[j], dataBarang[j + 1]);
            }
        }
    }
    else if (metode == 2) 
    {
        mergeSort(dataBarang, 0, jumlahBarang - 1, field);
    }
    else
    {
        cout << "METODE SORTING TIDAK VALID\n";
        return;
    }

    
    cout << "\nHASIL SORTING:\n";
    cout << left
         << setw(5)  << "NO"
         << setw(20) << "NAMA"
         << setw(20) << "ID BARANG"
         << setw(20) << "KATEGORI"
         << setw(15) << "HARGA"
         << setw(15) << "TOTAL" << endl;
    cout << string(95, '=') << endl;

    for (int i = 0; i < jumlahBarang; i++)
    {
        cout << left
             << setw(5)  << (i + 1)
             << setw(20) << dataBarang[i].nama
             << setw(20) << dataBarang[i].id
             << setw(20) << dataBarang[i].kategori
             << setw(15) << dataBarang[i].harga
             << setw(15) << dataBarang[i].total << endl;
    }
}


void updatebarang()
{
    int idUpdate;
    cout << "MASUKKAN ID BARANG YANG AKAN DIUPDATE: ";
    cin >> idUpdate;

    BARANG* b = cariBarang(idUpdate);
    if (b != nullptr)
    {
        cout << "MASUKKAN INFORMASI BARANG BARU:\n";
        cout << "NAMA BARANG: ";
        cin >> b->nama;
        cout << "KATEGORI: ";
        cin >> b->kategori;
        cout << "HARGA: ";
        cin >> b->harga;
        cout << "TOTAL: ";
        cin >> b->total;
        saveDataToFile(); 
        cout << "INFORMASI BARANG BERHASIL DIUPDATE\n";
    }
    else
    {
        cout << "BARANG TIDAK DITEMUKAN\n";
    }
}

void hapusbarang()
{
    int idHapus;
    cout << "MASUKKAN ID BARANG YANG AKAN DIHAPUS: ";
    cin >> idHapus;

    for (int i = 0; i < jumlahBarang; i++)
    {
        if (dataBarang[i].id == idHapus)
        {
            
            for (int j = i; j < jumlahBarang - 1; j++)
            {
                dataBarang[j] = dataBarang[j + 1];
            }
            jumlahBarang--; 
            saveDataToFile(); 
            cout << "BARANG BERHASIL DIHAPUS\n";
            return;
        }
    }
    cout << "BARANG TIDAK DITEMUKAN\n";
}

int main()
{
    buatheaderfile(); 
    loadDataFromFile(); 

    int pilih;
    do
    {
        cout << "================================\n";
        cout << "=   PROGRAM MANAJEMEN GUDANG   =\n";
        cout << "================================\n";
        cout << "1. INPUT BARANG\n";
        cout << "2. LIST BARANG\n";
        cout << "3. CARI BARANG\n";
        cout << "4. SORTING BARANG\n";
        cout << "5. UPDATE BARANG\n";
        cout << "6. HAPUS BARANG\n";
        cout << "7. EXIT\n";
        cout << "PILIH MENU : ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            inputbarang();
            break;
        case 2:
            listbarang();
            break;
        case 3:
            caribarang();
            break;
        case 4:
            sortingbarang();
            break;
        case 5:
            updatebarang();
            break;
        case 6:
            hapusbarang();
            break;
        case 7:
            cout << "TERIMA KASIH\n";
            break;
        default:
            cout << "PILIHAN TIDAK VALID\n";
            break;
        }
        system("PAUSE");
        system("CLS");
    } while (pilih != 7);

    return 0;
}
