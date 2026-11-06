// src/main.cpp
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include "../include/Mahasiswa.h"
#include "../include/MataKuliah.h"
#include "../include/NilaiMK.h"
#include "../include/KHS.h"
#include "../include/Pembayaran.h"

using namespace std;

vector<string> bungkusTeks(const string& teks, size_t lebar) {
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

// Menampilkan transkrip nilai seluruh semester mahasiswa.
void cetakTranskrip(const Mahasiswa& mhs) {
    vector<MataKuliah> daftarMK = loadDataMataKuliah();
    ifstream fileNilai("data_nilai.csv");

    if (!fileNilai.is_open()) {
        cout << "\n[X] Gagal membuka file data_nilai.csv" << endl;
        return;
    }

    struct DataTranskrip {
        string kode;
        string nama;
        double nilai;
        string huruf;
        double bobot;
        int sks;
        int semester;
    };

    vector<DataTranskrip> transkrip;
    string baris;

    // File data_nilai.csv pada versi ini memiliki header.
    getline(fileNilai, baris);

    while (getline(fileNilai, baris)) {
        if (!baris.empty() && baris.back() == '\r')
            baris.pop_back();

        // Hilangkan BOM UTF-8 jika muncul pada awal baris pertama.
        if (baris.size() >= 3 &&
            (unsigned char)baris[0] == 0xEF &&
            (unsigned char)baris[1] == 0xBB &&
            (unsigned char)baris[2] == 0xBF) {
            baris.erase(0, 3);
        }

        if (baris.empty())
            continue;

        stringstream ss(baris);
        string nim, kode, nilaiStr, semStr;

        getline(ss, nim, ',');
        getline(ss, kode, ',');
        getline(ss, nilaiStr, ',');
        getline(ss, semStr, ',');

        if (nim != mhs.nim || kode.empty() || nilaiStr.empty() || semStr.empty())
            continue;

        try {
            double nilai = stod(nilaiStr);
            int semester = stoi(semStr);

            NilaiMK n(mhs.nim, kode, nilai, semester);

            string namaMK = "Mata Kuliah Tidak Ditemukan";
            int sks = 0;

            for (const MataKuliah& mk : daftarMK) {
                if (mk.kodeMK == kode) {
                    namaMK = mk.namaMK;
                    sks = mk.sks;
                    break;
                }
            }

            if (sks > 0) {
                transkrip.push_back({
                    kode,
                    namaMK,
                    nilai,
                    n.getNilaiHuruf(),
                    n.getBobot(),
                    sks,
                    semester
                });
            }
        } catch (...) {
            // Abaikan baris CSV yang formatnya tidak valid.
        }
    }

    fileNilai.close();

    cout << "\n" << string(85, '=') << endl;
    cout << "                    TRANSKRIP NILAI" << endl;
    cout << string(85, '=') << endl;
    cout << left << setw(9) << "Nama" << " : " << mhs.nama << endl;
    cout << left << setw(9) << "NIM" << " : " << mhs.nim << endl;
    cout << left << setw(9) << "Jurusan" << " : " << mhs.jurusan << endl;
    cout << string(83, '-') << endl;

    if (transkrip.empty()) {
        cout << "Belum ada nilai yang tersimpan." << endl;
        cout << string(83, '=') << endl;
        return;
    }

    double totalBobot = 0.0;
    int totalSKS = 0;
    int semesterTerakhir = 0;

    // Data CSV tersimpan berdasarkan semester, sehingga kita kelompokkan
    // saat ditampilkan agar hasil transkrip lebih mudah dibaca.
    for (const DataTranskrip& data : transkrip) {
        if (data.semester > semesterTerakhir)
            semesterTerakhir = data.semester;
    }

    for (int sem = 1; sem <= semesterTerakhir; ++sem) {
        bool adaSemester = false;

        for (const DataTranskrip& data : transkrip) {
            if (data.semester == sem) {
                adaSemester = true;
                break;
            }
        }

        if (!adaSemester)
            continue;

        cout << "\nSEMESTER " << sem << endl;
        cout << left
            << setw(12) << "Kode"
            << setw(42) << "Mata Kuliah"
            << setw(5)  << "SKS"
            << setw(8)  << "Nilai"
            << setw(10) << "Ekivalen"
            << setw(8)  << "Huruf" << endl;
        cout << string(85, '-') << endl;

        double bobotSemester = 0.0;
        int sksSemester = 0;

        for (const DataTranskrip& data : transkrip) {
            if (data.semester != sem)
                continue;

            vector<string> namaBaris = bungkusTeks(data.nama, 40);
            for (size_t barisNama = 0; barisNama < namaBaris.size(); ++barisNama) {
                cout << left
                    << setw(12) << (barisNama == 0 ? data.kode : "")
                    << setw(42) << namaBaris[barisNama];

                if (barisNama == 0) {
                    cout << setw(5)  << data.sks
                        << setw(8)  << fixed << setprecision(2) << data.nilai
                        << setw(10) << fixed << setprecision(1) << data.bobot
                        << setw(8)  << data.huruf;
                }

                cout << endl;
            }

            bobotSemester += data.sks * data.bobot;
            sksSemester += data.sks;

            totalBobot += data.sks * data.bobot;
            totalSKS += data.sks;
        }

        double ipSemester = (sksSemester > 0) ? bobotSemester / sksSemester : 0.0;

    cout << string(85, '-') << endl;
    cout << left << setw(21) << "Total SKS Semester" << " : " << sksSemester << endl;
    cout << left << setw(21) << "IP Semester" << " : "
        << fixed << setprecision(2) << ipSemester << endl;
    }

    double ipk = (totalSKS > 0) ? totalBobot / totalSKS : 0.0;

    cout << "\n" << string(85, '=') << endl;
    cout << "RINGKASAN TRANSKRIP" << endl;
    cout << left << setw(21) << "Total SKS Keseluruhan" << " : " << totalSKS << endl;
    cout << left << setw(21) << "IPK" << " : "
        << fixed << setprecision(2) << ipk << endl;
    cout << string(85, '=') << endl;
}

void menuMahasiswa(Mahasiswa mhs) {
    int pilihan;

    do {
        cout << "\n========================================" << endl;
        cout << "   MENU MAHASISWA - " << mhs.nama << endl;
        cout << "========================================" << endl;
        cout << "1. Lihat Daftar Mata Kuliah" << endl;
        cout << "2. Input Nilai" << endl;
        cout << "3. Cetak KHS" << endl;
        cout << "4. Cetak Transkrip Nilai" << endl;
        cout << "5. Tambah Mata Kuliah Baru" << endl;
        cout << "6. Bayar Uang Kuliah" << endl;
        cout << "7. Riwayat Pembayaran" << endl;
        cout << "0. Logout" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nPilihan harus berupa angka!" << endl;
            continue;
        }

        switch (pilihan) {
            case 1:
                tampilkanDaftarMK();
                break;

            case 2: {
                string kodeMK;
                double nilai;
                int semester;

                tampilkanDaftarMK();

                cout << "\n--- INPUT NILAI ---" << endl;
                cout << "Masukkan Kode MK : ";
                cin >> kodeMK;
                cout << "Masukkan Nilai   : ";
                cin >> nilai;
                cout << "Masukkan Semester: ";
                cin >> semester;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n[!] Input nilai/semester tidak valid." << endl;
                    break;
                }

                simpanNilai(mhs.nim, kodeMK, nilai, semester);
                break;
            }

            case 3: {
                int sem;
                cout << "\nMasukkan Semester yang ingin dicetak: ";
                cin >> sem;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n[!] Semester tidak valid." << endl;
                    break;
                }

                cetakKHS(mhs.nim, mhs.nama, sem);
                break;
            }

            case 4:
                cetakTranskrip(mhs);
                break;

            case 5:
                tambahMataKuliah();
                break;

            case 6:
                try {
                    mhs.bayarUangKuliah();
                } catch (const NominalTidakValidException& e) {
                    cout << "\n[X] " << e.what() << endl;
                } catch (const exception& e) {
                    cout << "\n[X] Kesalahan sistem: " << e.what() << endl;
                }
                break;

            case 7:
                Pembayaran::tampilkanRiwayat(mhs.nim);
                break;

            case 0:
                cout << "\nLogout berhasil. Sampai jumpa, " << mhs.nama << "!" << endl;
                break;

            default:
                cout << "\nPilihan tidak valid!" << endl;
        }

    } while (pilihan != 0);
}

int main() {
    string nim, pass;
    Mahasiswa mhsLogin;

    cout << "=== LOGIN MAHASISWA ===" << endl;
    cout << "Masukkan NIM      : ";
    cin >> nim;
    cout << "Masukkan Password : ";
    cin >> pass;

    if (loginMahasiswa(nim, pass, mhsLogin)) {
        cout << "\nLogin Berhasil!" << endl;
        cout << "Selamat datang, " << mhsLogin.nama << endl;
        menuMahasiswa(mhsLogin);
    } else {
        cout << "\nLogin Gagal! NIM atau Password salah." << endl;
    }

    return 0;
}
