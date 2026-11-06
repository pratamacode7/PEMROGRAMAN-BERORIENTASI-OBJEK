#ifndef SISTEM_LAUNDRY_H
#define SISTEM_LAUNDRY_H

#include "Komplain.h"
#include "Layanan.h"
#include "Pembayaran.h"
#include "Struk.h"
#include "Transaksi.h"

#include <string>
#include <vector>

class SistemLaundry {
private:
    std::vector<Pelanggan> daftarPelanggan;
    std::vector<Transaksi> daftarTransaksi;
    std::vector<Pembayaran> daftarPembayaran;
    std::vector<Komplain> daftarKomplain;
    CuciKering cuciKering;
    CuciSetrika cuciSetrika;
    Express express;
    int counterPelanggan;
    int counterTransaksi;
    int counterPembayaran;
    int counterKomplain;

    std::string buatId(const std::string& awalan, int nomor) const;
    std::string tanggalHariIni() const;
    Pelanggan* cariPelanggan(const std::string& id);
    Transaksi* cariTransaksi(const std::string& id);
    Komplain* cariKomplain(const std::string& id);
    void menuPelanggan();
    void tambahPelanggan();
    void tampilDaftarPelanggan() const;
    void buatTransaksi();
    void tampilDaftarTransaksi() const;
    void ubahStatusLaundry();
    void menuPengambilan();
    void menuKomplain();
    void buatKomplain();
    void selesaikanKomplain();
    void tampilDaftarKomplain() const;
    void tampilLaporan() const;

public:
    SistemLaundry();
    void jalankan();
    void menuUtama() const;
};

#endif
