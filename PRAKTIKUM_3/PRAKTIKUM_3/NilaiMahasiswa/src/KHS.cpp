// src/KHS.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "../include/KHS.h"
#include "../include/MataKuliah.h"
#include "../include/NilaiMK.h"

using namespace std;

vector<string> bungkusTeksKHS(const string& teks, size_t lebar) {
    vector<string> hasil;
    string kata;
    string baris;
    stringstream ss(teks);

    while (ss >> kata) {
        if (kata.size() > lebar) {
            if (!baris.empty()) {
                hasil.push_back(baris);
                baris.clear();
            }
            for (size_t posisi = 0; posisi < kata.size(); posisi += lebar)
                hasil.push_back(kata.substr(posisi, lebar));
        } else if (baris.empty()) {
            baris = kata;
        } else if (baris.size() + 1 + kata.size() <= lebar) {
            baris += " " + kata;
        } else {
            hasil.push_back(baris);
            baris = kata;
        }
    }

    if (!baris.empty())
        hasil.push_back(baris);
    if (hasil.empty())
        hasil.push_back("");
    return hasil;
}

// Fungsi untuk membersihkan baris dari \r dan BOM
string bersihkanBaris(string baris) {
    // Hapus BOM UTF-8 di awal (ef bb bf)
    if (baris.size() >= 3 && 
        (unsigned char)baris[0] == 0xEF &&
        (unsigned char)baris[1] == 0xBB &&
        (unsigned char)baris[2] == 0xBF) {
        baris.erase(0, 3);
    }
    // Hapus \r di akhir (Windows line ending)
    if (!baris.empty() && baris.back() == '\r')
        baris.pop_back();
    return baris;
}

void cetakKHS(const string& nim, const string& nama, int semester) {
    vector<MataKuliah> daftarMK = loadDataMataKuliah();
    ifstream fileNilai("data_nilai.csv");
    string baris;

    double totalBobot = 0;
    int totalSKS = 0;
    bool adaData = false;

    cout << "\n" << string(85, '=') << endl;
    cout << "         KARTU HASIL STUDI (KHS)" << endl;
    cout << "         " << left << setw(9) << "Nama" << " : " << nama << endl;
    cout << "         " << left << setw(9) << "NIM" << " : " << nim << endl;
    cout << "         " << left << setw(9) << "Semester" << " : " << semester << endl;
    cout << string(85, '=') << endl;
    cout << left << setw(12) << "Kode" 
         << setw(42) << "Mata Kuliah" 
         << setw(5)  << "SKS" 
         << setw(8)  << "Nilai" 
         << setw(10) << "Ekivalen" 
         << setw(8)  << "Huruf" << endl;
    cout << string(85, '-') << endl;

    getline(fileNilai, baris); // Lewati header

    while (getline(fileNilai, baris)) {
        baris = bersihkanBaris(baris);
        if (baris.empty()) continue;

        stringstream ss(baris);
        string nMim, kode, nilaiStr, semStr;

        getline(ss, nMim, ',');
        getline(ss, kode, ',');
        getline(ss, nilaiStr, ',');
        getline(ss, semStr, ',');

        if (nMim != nim || kode.empty() || nilaiStr.empty() || semStr.empty())
            continue;

        try {
            int semesterData = stoi(semStr);
            double nilai = stod(nilaiStr);

            if (semesterData != semester)
                continue;

            NilaiMK n(nMim, kode, nilai, semesterData);
            
            string namaMK = "-";
            int sks = 0;
            for (MataKuliah mk : daftarMK) {
                if (mk.kodeMK == kode) {
                    namaMK = mk.namaMK;
                    sks = mk.sks;
                    break;
                }
            }

            vector<string> namaBaris = bungkusTeksKHS(namaMK, 40);
            for (size_t barisNama = 0; barisNama < namaBaris.size(); ++barisNama) {
                cout << left
                     << setw(12) << (barisNama == 0 ? kode : "")
                     << setw(42) << namaBaris[barisNama];

                if (barisNama == 0) {
                    cout << setw(5) << sks
                         << setw(8) << fixed << setprecision(2) << nilai
                         << setw(10) << fixed << setprecision(1) << n.getBobot()
                         << setw(8) << n.getNilaiHuruf();
                }

                cout << endl;
            }

            totalBobot += (sks * n.getBobot());
            totalSKS += sks;
            adaData = true;
        } catch (const exception&) {
            continue;
        }
    }
    fileNilai.close();

    cout << string(85, '-') << endl;
    if (adaData) {
        double ip = (totalSKS > 0) ? (totalBobot / totalSKS) : 0;
        cout << left << setw(12) << "Total SKS" << " : " << totalSKS << endl;
        cout << left << setw(12) << "IP Semester" << " : "
             << fixed << setprecision(2) << ip << endl;
    } else {
        cout << "Belum ada nilai untuk semester ini." << endl;
    }
    cout << string(85, '=') << endl;
}