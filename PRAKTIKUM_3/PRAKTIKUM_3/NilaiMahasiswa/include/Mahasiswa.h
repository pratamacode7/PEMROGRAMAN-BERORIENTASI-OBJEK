// include/Mahasiswa.h
#ifndef MAHASISWA_H
#define MAHASISWA_H

#include <string>
#include <vector>
using namespace std;

class Mahasiswa {
public:
    string nim;
    string nama;
    string password;
    string jurusan;

    Mahasiswa() {}
    Mahasiswa(string n, string nm, string p, string j)
        : nim(n), nama(nm), password(p), jurusan(j) {}

    // Menampilkan form pembayaran dan memproses pembayaran uang kuliah.
    void bayarUangKuliah();
};

// Deklarasi fungsi
vector<Mahasiswa> loadDataMahasiswa();
bool loginMahasiswa(string inputNIM, string inputPass, Mahasiswa &hasilLogin);

#endif