#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include "../include/Pembayaran.h"

using namespace std;

namespace {
    string bersihkanBaris(string baris) {
        // Menghapus BOM UTF-8 jika file CSV disimpan dari aplikasi spreadsheet.
        if (baris.size() >= 3 &&
            (unsigned char)baris[0] == 0xEF &&
            (unsigned char)baris[1] == 0xBB &&
            (unsigned char)baris[2] == 0xBF) {
            baris.erase(0, 3);
        }

        // Menghapus carriage return dari format baris Windows.
        if (!baris.empty() && baris.back() == '\r') {
            baris.pop_back();
        }
        return baris;
    }

    string tanggalHariIni() {
        time_t sekarang = time(nullptr);
        tm* waktu = localtime(&sekarang);
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", waktu);
        return string(buffer);
    }

    void bacaSemuaTagihan(vector<pair<string, double> >& data) {
        data.clear();
        ifstream file("data_tagihan.csv");
        if (!file.is_open()) {
            throw runtime_error("Gagal membuka data_tagihan.csv.");
        }

        string baris;
        getline(file, baris); // Lewati header.

        while (getline(file, baris)) {
            baris = bersihkanBaris(baris);
            if (baris.empty()) continue;

            stringstream ss(baris);
            string nim, tagihanStr;
            getline(ss, nim, ',');
            getline(ss, tagihanStr, ',');

            if (nim.empty() || tagihanStr.empty()) continue;

            try {
                size_t posisiAkhir = 0;
                double tagihan = stod(tagihanStr, &posisiAkhir);
                if (posisiAkhir != tagihanStr.size() || !isfinite(tagihan) || tagihan < 0) {
                    continue;
                }
                data.push_back(make_pair(nim, tagihan));
            } catch (const exception&) {
                // Baris CSV yang format angkanya tidak benar dilewati.
                continue;
            }
        }
        file.close();
    }

    void tulisSemuaTagihan(const vector<pair<string, double> >& data) {
        ofstream file("data_tagihan.csv", ios::trunc);
        if (!file.is_open()) {
            throw runtime_error("Gagal memperbarui data_tagihan.csv.");
        }

        file << "NIM,TotalTagihan\n";
        for (size_t i = 0; i < data.size(); ++i) {
            file << data[i].first << "," << fixed << setprecision(0)
                 << data[i].second << "\n";
        }
        file.close();

        if (!file) {
            throw runtime_error("Gagal menyimpan perubahan data_tagihan.csv.");
        }
    }

    void pastikanFileRiwayatAda() {
        ifstream cek("data_pembayaran.csv");
        if (cek.good()) {
            cek.close();
            return;
        }

        ofstream buat("data_pembayaran.csv");
        if (!buat.is_open()) {
            throw runtime_error("Gagal membuat data_pembayaran.csv.");
        }
        buat << "NIM,Nominal,Tanggal\n";
    }
}

double Pembayaran::getSisaTagihan(const string& nim) {
    vector<pair<string, double> > data;
    bacaSemuaTagihan(data);

    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i].first == nim) {
            return data[i].second;
        }
    }

    throw NIMTidakDitemukanException(nim);
}

double Pembayaran::prosesPembayaran(const string& nim, double nominal) {
    if (!isfinite(nominal) || nominal <= 0) {
        throw NominalTidakValidException("harus berupa angka lebih dari 0.");
    }
    if (nominal < 1000) {
        throw NominalTidakValidException("minimal pembayaran adalah Rp1.000.");
    }

    vector<pair<string, double> > data;
    bacaSemuaTagihan(data);

    int index = -1;
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i].first == nim) {
            index = static_cast<int>(i);
            break;
        }
    }

    if (index == -1) {
        throw NIMTidakDitemukanException(nim);
    }

    const double sisa = data[index].second;
    if (nominal > sisa) {
        throw PembayaranMelebihiTagihanException(nominal, sisa);
    }

    // Pastikan file riwayat dapat ditulis sebelum mengubah sisa tagihan.
    pastikanFileRiwayatAda();
    ofstream riwayat("data_pembayaran.csv", ios::app);
    if (!riwayat.is_open()) {
        throw runtime_error("Gagal membuka data_pembayaran.csv.");
    }

    data[index].second = sisa - nominal;
    tulisSemuaTagihan(data);

    riwayat << nim << "," << fixed << setprecision(0) << nominal
            << "," << tanggalHariIni() << "\n";
    riwayat.close();

    if (!riwayat) {
        throw runtime_error("Pembayaran tersimpan, tetapi riwayat gagal ditulis.");
    }

    return data[index].second;
}

void Pembayaran::tampilkanRiwayat(const string& nim) {
    ifstream file("data_pembayaran.csv");
    if (!file.is_open()) {
        cout << "\nBelum ada riwayat pembayaran." << endl;
        return;
    }

    string baris;
    getline(file, baris); // Lewati header.

    bool ada = false;
    double total = 0;
    int nomor = 1;

    cout << "\n========================================================" << endl;
    cout << " RIWAYAT PEMBAYARAN - NIM " << nim << endl;
    cout << "========================================================" << endl;
    cout << left << setw(6) << "No"
         << setw(16) << "Tanggal"
         << right << setw(20) << "Nominal (Rp)" << endl;
    cout << string(42, '-') << endl;

    while (getline(file, baris)) {
        baris = bersihkanBaris(baris);
        if (baris.empty()) continue;

        stringstream ss(baris);
        string nimData, nominalStr, tanggal;
        getline(ss, nimData, ',');
        getline(ss, nominalStr, ',');
        getline(ss, tanggal, ',');

        if (nimData != nim) continue;

        try {
            double nominal = stod(nominalStr);
            cout << left << setw(6) << nomor++
                 << setw(16) << tanggal
                 << right << setw(20) << fixed << setprecision(0) << nominal
                 << endl;
            total += nominal;
            ada = true;
        } catch (const exception&) {
            // Abaikan baris riwayat yang tidak valid.
            continue;
        }
    }

    file.close();
    cout << string(42, '-') << endl;
    if (ada) {
        cout << left << setw(22) << "TOTAL DIBAYAR"
             << right << setw(20) << fixed << setprecision(0) << total << endl;
    } else {
        cout << "Belum ada pembayaran untuk NIM ini." << endl;
    }
    cout << "========================================================" << endl;
}
