// src/MataKuliah.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "../include/MataKuliah.h"

using namespace std;

vector<MataKuliah> loadDataMataKuliah() {
    vector<MataKuliah> daftarMK;
    ifstream file("data_matakuliah.csv");
    string baris;

    getline(file, baris); // Lewati header

    while (getline(file, baris)) {
        if (!baris.empty() && baris.back() == '\r')
            baris.pop_back();

        stringstream ss(baris);
        string kode, nama, sksStr, semStr;

        getline(ss, kode, ',');
        getline(ss, nama, ',');
        getline(ss, sksStr, ',');
        getline(ss, semStr, ',');

        if (kode.empty()) continue;

        daftarMK.push_back(MataKuliah(kode, nama, stoi(sksStr), stoi(semStr)));
    }
    file.close();
    return daftarMK;
}

void tampilkanDaftarMK() {
    vector<MataKuliah> daftar = loadDataMataKuliah();
    cout << "\n=== DAFTAR MATA KULIAH ===" << endl;
    cout << left << setw(10) << "Kode" 
         << setw(30) << "Nama MK" 
         << setw(5) << "SKS" 
         << setw(10) << "Semester" << endl;
    cout << string(55, '-') << endl;
    
    for (MataKuliah mk : daftar) {
        cout << left << setw(10) << mk.kodeMK 
             << setw(30) << mk.namaMK 
             << setw(5) << mk.sks 
             << setw(10) << mk.semester << endl;
    }
}

void tambahMataKuliah() {
    string kode, nama;
    int sks, semester;

    cout << "\n--- TAMBAH MATA KULIAH BARU ---" << endl;
    cout << "Masukkan Kode MK     : ";
    cin >> kode;
    cin.ignore();
    cout << "Masukkan Nama MK     : ";
    getline(cin, nama);
    cout << "Masukkan SKS         : ";
    cin >> sks;
    cout << "Masukkan Semester    : ";
    cin >> semester;

    vector<MataKuliah> daftar = loadDataMataKuliah();
    for (MataKuliah mk : daftar) {
        if (mk.kodeMK == kode) {
            cout << "\n[!] Kode MK '" << kode << "' sudah ada!" << endl;
            return;
        }
    }

    ofstream file("data_matakuliah.csv", ios::app);
    if (file.is_open()) {
        file << kode << "," << nama << "," << sks << "," << semester << "\n";
        file.close();
        cout << "\n[OK] Mata kuliah berhasil ditambahkan!" << endl;
    } else {
        cout << "\n[X] Gagal membuka file data_matakuliah.csv" << endl;
    }
}