#include <iostream>
#include "program.h"

using namespace std;

void menuUtama(Gudang& gudang, PembeliQueue& pembeliQueue, LoginPage& loginPage) {
    int pilihan;

    do {
        cout << "\n========== Login user  ==========" << endl;
        cout << "1. Login" << endl;
        cout << "2. Daftar" << endl;
        cout << "============ Menu utama  =========="<<endl;
        cout << "3. Tambah Barang" << endl;
        cout << "4. Jual Barang (LIFO)" << endl;
        cout << "5. Jual Barang (FIFO)" << endl;
        cout << "6. Tambah Pembeli" << endl;
        cout << "7. Cetak Barang" << endl;
        cout << "8. Cetak Antrian Pembeli" << endl;
        cout << "9. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan >= 3 && pilihan <= 8 && !loginPage.isLoggedIn()) {
            cout << "Silakan login terlebih dahulu untuk mengakses menu ini." << endl;
            continue;
        }

        switch (pilihan) {
        case 1:
            loginPage.login();
            break;
        case 2:
            loginPage.daftar();
            break;
        case 3: {
            Barang barang;
            cout << "Masukkan Kode Item: ";
            cin >> barang.kodeItem;
            cout << "Masukkan Tanggal Masuk: ";
            cin >> barang.tanggalMasuk;
            gudang.tambahBarang(barang);
            cout << "Barang berhasil ditambahkan!" << endl;
            break;
        }
        case 4: {
              if (gudang.isEmpty()) {
                cout << "Gudang kosong, tidak ada barang yang dapat dijual." << endl;
            } else {
                Barang barang = gudang.jualBarangLIFO();
                cout << "Barang LIFO terjual: Kode Item: " << barang.kodeItem << ", Tanggal Masuk: " << barang.tanggalMasuk << endl;
            }
            break;
        }
        case 5: {
              if (gudang.isEmpty()) {
                cout << "Gudang kosong, tidak ada barang yang dapat dijual." << endl;
            } else {
                Barang barang = gudang.jualBarangFIFO();
                cout << "Barang FIFO terjual: Kode Item: " << barang.kodeItem << ", Tanggal Masuk: " << barang.tanggalMasuk << endl;
            }
            break;
        }
        case 6: {
            Pembeli pembeli;
            cout << "Masukkan Nama Pembeli: ";
            cin >> pembeli.ktp.nama;
            cout << "Masukkan NIK Pembeli: ";
            cin >> pembeli.ktp.nik;
            cout << "Masukkan Waktu Kedatangan: ";
            cin >> pembeli.waktuKedatangan;
            cout << "Masukkan Kode Item: ";
            cin >> pembeli.kodeItem;
            pembeliQueue.tambahPembeli(pembeli);
            cout << "Pembeli berhasil ditambahkan ke antrian!" << endl;
            break;
        }
        case 7:
            gudang.cetakBarang();
            break;
        case 8:
            pembeliQueue.cetakAntrian();
            break;
        case 9:
            cout << "Keluar dari program." << endl;
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
            break;
        }
    } while (pilihan != 9);
}

int main() {
    Gudang gudang;
    PembeliQueue pembeliQueue;
    LoginPage loginPage;

    menuUtama(gudang, pembeliQueue, loginPage);

    return 0;
}

