// src/Mahasiswa.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <limits>
#include "../include/Mahasiswa.h"
#include "../include/Pembayaran.h"

using namespace std;

vector<Mahasiswa> loadDataMahasiswa() {
    vector<Mahasiswa> daftarMahasiswa;
    ifstream file("data_mahasiswa.csv");
    string baris;

    if (!file.is_open()) {
        return daftarMahasiswa;
    }

    // Lewati baris pertama (header).
    getline(file, baris);

    while (getline(file, baris)) {
        if (baris.size() >= 3 &&
            (unsigned char)baris[0] == 0xEF &&
            (unsigned char)baris[1] == 0xBB &&
            (unsigned char)baris[2] == 0xBF) {
            baris.erase(0, 3);
        }
        if (!baris.empty() && baris.back() == '\r') {
            baris.pop_back();
        }
        if (baris.empty()) continue;

        stringstream ss(baris);
        string nim, nama, password, jurusan;

        getline(ss, nim, ',');
        getline(ss, nama, ',');
        getline(ss, password, ',');
        getline(ss, jurusan, ',');

        if (!nim.empty()) {
            daftarMahasiswa.push_back(Mahasiswa(nim, nama, password, jurusan));
        }
    }
    file.close();
    return daftarMahasiswa;
}

bool loginMahasiswa(string inputNIM, string inputPass, Mahasiswa &hasilLogin) {
    vector<Mahasiswa> daftar = loadDataMahasiswa();

    for (const Mahasiswa& m : daftar) {
        if (m.nim == inputNIM && m.password == inputPass) {
            hasilLogin = m;
            return true;
        }
    }
    return false;
}

void Mahasiswa::bayarUangKuliah() {
    cout << "\n--- PEMBAYARAN UANG KULIAH ---" << endl;

    double sisa = 0;
    try {
        sisa = Pembayaran::getSisaTagihan(nim);
    } catch (const NIMTidakDitemukanException& e) {
        cout << "[X] " << e.what() << endl;
        return;
    } catch (const exception& e) {
        cout << "[X] Kesalahan sistem: " << e.what() << endl;
        return;
    }

    cout << "NIM          : " << nim << endl;
    cout << "Nama         : " << nama << endl;
    cout << "Sisa Tagihan : Rp" << fixed << setprecision(0) << sisa << endl;

    if (sisa <= 0) {
        cout << "[OK] Tagihan Anda sudah LUNAS." << endl;
        return;
    }

    cout << "\nMasukkan nominal pembayaran (Rp): ";
    double nominal;
    if (!(cin >> nominal)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw NominalTidakValidException("input bukan angka.");
    }

    try {
        double sisaBaru = Pembayaran::prosesPembayaran(nim, nominal);
        cout << "\n[OK] PEMBAYARAN BERHASIL" << endl;
        cout << "Dibayar        : Rp" << fixed << setprecision(0) << nominal << endl;
        cout << "Sisa tagihan   : Rp" << sisaBaru << endl;
        cout << "Status         : " << (sisaBaru == 0 ? "LUNAS" : "BELUM LUNAS") << endl;
    } catch (const PembayaranMelebihiTagihanException& e) {
        cout << "\n[X] " << e.what() << endl;
        cout << "Sisa tagihan Anda: Rp" << fixed << setprecision(0)
             << e.getSisa() << endl;
    } catch (const NominalTidakValidException& e) {
        cout << "\n[X] " << e.what() << endl;
    } catch (const exception& e) {
        cout << "\n[X] Kesalahan sistem: " << e.what() << endl;
    }
}
