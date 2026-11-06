#include "Struk.h"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace {
void tulisIsiStruk(std::ostream& output, const Transaksi& transaksi,
                   const Pembayaran& pembayaran, const std::string& nomorStruk) {
    const Pelanggan& pelanggan = transaksi.getPelanggan();
    output << "========================================\n"
           << "             LAUNDRY\n"
           << "========================================\n"
           << "Nomor struk     : " << nomorStruk << '\n'
           << "ID transaksi    : " << transaksi.getIdTransaksi() << '\n'
           << "Tanggal         : " << transaksi.getTanggalTransaksi() << '\n'
           << "Nama pelanggan  : " << pelanggan.getNama() << '\n'
           << "No. HP          : " << pelanggan.getNoHP() << '\n'
           << "Layanan         : " << transaksi.getNamaLayanan() << '\n'
           << "Berat           : " << std::fixed << std::setprecision(2)
           << transaksi.getBerat() << " kg\n"
           << "Harga per kg    : Rp " << transaksi.getHargaPerKg() << '\n'
           << "Total tagihan   : Rp " << pembayaran.getTotalTagihan() << '\n'
           << "Pembayaran      : Rp " << pembayaran.getJumlahBayar() << '\n'
           << "Kembalian       : Rp " << pembayaran.getKembalian() << '\n'
           << "Status bayar    : LUNAS\n"
           << "Status laundry  : " << transaksi.getStatus() << '\n'
           << "----------------------------------------\n"
           << "Simpan struk ini. Struk asli wajib\n"
           << "ditunjukkan saat pengambilan laundry.\n"
           << "========================================\n";
}
}

Struk::Struk(const std::string& nomorStruk, const std::string& idTransaksi,
             const std::string& tanggal)
    : nomorStruk(nomorStruk), idTransaksi(idTransaksi), tanggal(tanggal) {}

void Struk::tampilStruk(const Transaksi& transaksi,
                        const Pembayaran& pembayaran) const {
    tulisIsiStruk(std::cout, transaksi, pembayaran, nomorStruk);
}

bool Struk::simpanStrukKeFile(const Transaksi& transaksi,
                              const Pembayaran& pembayaran) const {
    std::error_code error;
    std::filesystem::create_directories("struk", error);
    if (error) {
        std::cerr << "Folder struk gagal dibuat: " << error.message() << '\n';
        return false;
    }

    std::ofstream file("struk/" + idTransaksi + ".txt");
    if (!file) {
        std::cerr << "File struk gagal dibuat.\n";
        return false;
    }
    tulisIsiStruk(file, transaksi, pembayaran, nomorStruk);
    return true;
}
