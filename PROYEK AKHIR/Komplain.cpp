#include "Komplain.h"

#include <iostream>

Komplain::Komplain(const std::string& idKomplain,
                const std::string& idTransaksi,
                const std::string& jenisKomplain,
                const std::string& deskripsi)
    : idKomplain(idKomplain),
      idTransaksi(idTransaksi),
      jenisKomplain(jenisKomplain),
      deskripsi(deskripsi),
      status("Diproses"),
      nominalKompensasi(0) {}

const std::string& Komplain::getIdKomplain() const { return idKomplain; }
const std::string& Komplain::getIdTransaksi() const { return idTransaksi; }
const std::string& Komplain::getJenisKomplain() const { return jenisKomplain; }
const std::string& Komplain::getDeskripsi() const { return deskripsi; }
const std::string& Komplain::getStatus() const { return status; }
const std::string& Komplain::getSolusi() const { return solusi; }
long long Komplain::getNominalKompensasi() const { return nominalKompensasi; }

void Komplain::prosesKomplain() {
    status = "Diproses";
}

void Komplain::selesaikanKomplain(const std::string& solusiBaru,
                        long long kompensasi) {
    if (kompensasi < 0) {
        return;
    }
    solusi = solusiBaru;
    nominalKompensasi = kompensasi;
    status = "Selesai";
}

void Komplain::tampilKomplain() const {
std::cout   << "ID Komplain       : " << idKomplain << '\n'
            << "ID Transaksi      : " << idTransaksi << '\n'
            << "Jenis             : " << jenisKomplain << '\n'
            << "Deskripsi         : " << deskripsi << '\n'
            << "Status            : " << status << '\n'
            << "Solusi            : "
            << (solusi.empty() ? "-" : solusi) << '\n'
            << "Kompensasi        : Rp " << nominalKompensasi << '\n';
}
