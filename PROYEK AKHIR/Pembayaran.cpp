#include "Pembayaran.h"

#include <iostream>

Pembayaran::Pembayaran(const std::string& idPembayaran,
                       const std::string& idTransaksi,
                       long long totalTagihan)
    : idPembayaran(idPembayaran),
      idTransaksi(idTransaksi),
      totalTagihan(totalTagihan),
      jumlahBayar(0),
      kembalian(0),
      lunas(false) {}

bool Pembayaran::prosesPembayaran(long long jumlahBayarBaru) {
    if (jumlahBayarBaru < totalTagihan) {
        return false;
    }
    jumlahBayar = jumlahBayarBaru;
    kembalian = jumlahBayar - totalTagihan;
    lunas = true;
    return true;
}

const std::string& Pembayaran::getIdPembayaran() const { return idPembayaran; }
const std::string& Pembayaran::getIdTransaksi() const { return idTransaksi; }
long long Pembayaran::getTotalTagihan() const { return totalTagihan; }
long long Pembayaran::getJumlahBayar() const { return jumlahBayar; }
long long Pembayaran::getKembalian() const { return kembalian; }
bool Pembayaran::getLunas() const { return lunas; }

void Pembayaran::tampilPembayaran() const {
    std::cout << "ID Pembayaran : " << idPembayaran << '\n'
              << "Total tagihan : Rp " << totalTagihan << '\n'
              << "Jumlah bayar  : Rp " << jumlahBayar << '\n'
              << "Kembalian     : Rp " << kembalian << '\n'
              << "Status        : " << (lunas ? "LUNAS" : "BELUM LUNAS")
              << '\n';
}
