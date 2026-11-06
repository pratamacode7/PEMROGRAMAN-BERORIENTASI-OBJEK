// src/NilaiMK.cpp
#include <iostream>
#include <fstream>
#include "../include/NilaiMK.h"

using namespace std;

void simpanNilai(string nim, string kodeMK, double nilaiAngka, int semester) {
    // Mode ios::app untuk menambahkan data di akhir file (tidak menimpa)
    ofstream file("data_nilai.csv", ios::app);
    
    if (file.is_open()) {
        file << nim << "," << kodeMK << "," << nilaiAngka << "," << semester << "\n";
        file.close();
        cout << "\n Nilai berhasil disimpan!" << endl;
    } else {
        cout << "\n Gagal membuka file data_nilai.csv" << endl;
    }
}