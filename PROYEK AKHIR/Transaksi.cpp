#include "Transaksi.h"

#include <iomanip>
#include <iostream>

Transaksi::Transaksi(const std::string& idTransaksi,
                     const Pelanggan& pelanggan,
                     const Layanan& layanan,
                     double berat,
                     const std::string& tanggalTransaksi)
    : idTransaksi(idTransaksi),
      pelanggan(pelanggan),
      namaLayanan(layanan.getNamaLayanan()),
      hargaPerKg(layanan.getHargaPerKg()),
      berat(berat),
      totalHarga(layanan.hitungHarga(berat)),
      estimasi(layanan.getEstimasi()),
      rincianProses(layanan.getRincianProses()),
      status("Diproses"),
      tanggalTransaksi(tanggalTransaksi) {}

const std::string& Transaksi::getIdTransaksi() const {
    return idTransaksi;
}

const Pelanggan& Transaksi::getPelanggan() const {
    return pelanggan;
}

const std::string& Transaksi::getNamaLayanan() const {
    return namaLayanan;
}

long long Transaksi::getHargaPerKg() const {
    return hargaPerKg;
}

double Transaksi::getBerat() const {
    return berat;
}

long long Transaksi::getTotalHarga() const {
    return totalHarga;
}

const std::string& Transaksi::getEstimasi() const {
    return estimasi;
}

const std::string& Transaksi::getRincianProses() const {
    return rincianProses;
}

const std::string& Transaksi::getStatus() const {
    return status;
}

const std::string& Transaksi::getTanggalTransaksi() const {
    return tanggalTransaksi;
}

void Transaksi::tampilDetail() const {
    std::cout << "ID Transaksi     : " << idTransaksi << '\n'
              << "Pelanggan        : " << pelanggan.getNama() << '\n'
              << "No. HP           : " << pelanggan.getNoHP() << '\n'
              << "Layanan          : " << namaLayanan << '\n'
              << "Berat            : " << std::fixed << std::setprecision(2)
              << berat << " kg\n"
              << "Harga per kg     : Rp " << hargaPerKg << '\n'
              << "Total harga      : Rp " << totalHarga << '\n'
              << "Estimasi         : " << estimasi << '\n'
              << "Rincian proses   : " << rincianProses << '\n'
              << "Status           : " << status << '\n'
              << "Tanggal          : " << tanggalTransaksi << '\n';
}

void Transaksi::ubahStatus(const std::string& statusBaru) {
    if (statusBaru == "Diproses" || statusBaru == "Selesai") {
        status = statusBaru;
    }
}
