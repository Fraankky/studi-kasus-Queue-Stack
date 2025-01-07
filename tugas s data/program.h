#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>

using namespace std;

// Struktur dan kelas
struct KTP {
    string nama;
    string nik;
};

struct user {
    KTP ktp;
    string password;
};

class LoginPage {
public:
    void login();
    void daftar();
    bool isLoggedIn() const;

private:
    user Users;
    bool loggedIn; // Status login
};

struct Pembeli {
    KTP ktp;
    string waktuKedatangan;
    string kodeItem;
};

class PembeliQueue {
private:
    queue<Pembeli> antrianPembeli;

public:
    void tambahPembeli(const Pembeli& pembeli);
    Pembeli layaniPembeli();
    void cetakAntrian();
};

struct Barang {
    string kodeItem;
    string tanggalMasuk;
};



// Implementasi LoginPage
void LoginPage::daftar() {
    cout << "Masukkan Nama: ";
    cin >> Users.ktp.nama;
    cout << "Masukkan NIK: ";
    cin >> Users.ktp.nik;
    cout << "Masukkan Password: ";
    cin >> Users.password;

    ofstream input("dataUser.txt", ios::app);
    if (!input.is_open()) {
        cout << "Gagal membuka file." << endl;
        return;
    }
    input << Users.ktp.nama << " " << Users.ktp.nik << " " << Users.password << endl;
    input.close();

    cout << "Pendaftaran berhasil!" << endl;
}

void LoginPage::login() {
    string username, password;
    cout << "Masukkan Username: ";
    cin >> username;
    cout << "Masukkan Password: ";
    cin >> password;

    ifstream input("dataUser.txt");
    if (!input.is_open()) {
        cout << "Gagal membuka file." << endl;
        return;
    }

    string nama, nik, pass;
    loggedIn = false;

    while (input >> nama >> nik >> pass) {
        if (username == nama && password == pass) {
            loggedIn = true;
            cout << "Login berhasil! Selamat datang, " << username << "!" << endl;
            return;
        }
    }
    input.close();

    if (!loggedIn) {
        cout << "Login gagal! Username atau password salah." << endl;
    }
}

bool LoginPage::isLoggedIn() const {
    return loggedIn;
}

// Implementasi PembeliQueue
void PembeliQueue::tambahPembeli(const Pembeli& pembeli) {
    antrianPembeli.push(pembeli);
}

Pembeli PembeliQueue::layaniPembeli() {
    if (antrianPembeli.empty()) {
        throw runtime_error("Tidak ada pembeli dalam antrian!");
    }
    Pembeli pembeli = antrianPembeli.front();
    antrianPembeli.pop();
    return pembeli;
}

void PembeliQueue::cetakAntrian() {
    queue<Pembeli> tempQueue = antrianPembeli;

    cout << "\nDaftar Antrian Pembeli:\n";
    while (!tempQueue.empty()) {
        Pembeli pembeli = tempQueue.front();
        tempQueue.pop();
        cout << "NIK: " << pembeli.ktp.nik << ", Waktu Kedatangan: " << pembeli.waktuKedatangan
             << ", Kode Item: " << pembeli.kodeItem << endl;
    }
}

// Implementasi Gudang

class Gudang {
private:
    stack<Barang> lifo;
    queue<Barang> fifo;

public:
    void tambahBarang(const Barang& barang);
    Barang jualBarangLIFO();
    Barang jualBarangFIFO();
    void cetakBarang();
   
};

void Gudang::tambahBarang(const Barang& barang) {
    lifo.push(barang);
    fifo.push(barang);
}

Barang Gudang::jualBarangLIFO() {
    if (lifo.isEmpty()) {
        throw runtime_error("Gudang kosong (LIFO)!");
    }
    Barang barang = lifo.top();
    lifo.pop();
    return barang;
}

Barang Gudang::jualBarangFIFO() {
    if (fifo.isEmpty()) {
        throw runtime_error("Gudang kosong (FIFO)!");
    }
    Barang barang = fifo.front();
    fifo.pop();
    return barang;
}

void Gudang::cetakBarang() {
    stack<Barang> tempLIFO = lifo;
    queue<Barang> tempFIFO = fifo;

    cout << "\nDaftar Barang (LIFO):\n";
    while (!tempLIFO.isEmpty()) {
        Barang barang = tempLIFO.top();
        tempLIFO.pop();
        cout << "Kode Item: " << barang.kodeItem << ", Tanggal Masuk: " << barang.tanggalMasuk << endl;
    }

    cout << "\nDaftar Barang (FIFO):\n";
    while (!tempFIFO.isEmpty()) {
        Barang barang = tempFIFO.front();
        tempFIFO.pop();
        cout << "Kode Item: " << barang.kodeItem << ", Tanggal Masuk: " << barang.tanggalMasuk << endl;
    }
}

#endif

