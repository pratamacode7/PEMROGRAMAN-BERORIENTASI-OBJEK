#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include "Layanan.h"
#include "Pelanggan.h"

#include <string>

class Transaksi {
private:
    std::string idTransaksi;
    Pelanggan pelanggan;
    std::string namaLayanan;
    long long hargaPerKg;
    double berat;
    long long totalHarga;
    std::string estimasi;
    std::string rincianProses;
    std::string status;
    std::string tanggalTransaksi;

public:
    Transaksi(const std::string& idTransaksi, const Pelanggan& pelanggan,
              const Layanan& layanan, double berat,
              const std::string& tanggalTransaksi);

    const std::string& getIdTransaksi() const;
    const Pelanggan& getPelanggan() const;
    const std::string& getNamaLayanan() const;
    long long getHargaPerKg() const;
    double getBerat() const;
    long long getTotalHarga() const;
    const std::string& getEstimasi() const;
    const std::string& getRincianProses() const;
    const std::string& getStatus() const;
    const std::string& getTanggalTransaksi() const;
    void tampilDetail() const;
    void ubahStatus(const std::string& statusBaru);
};

#endif
