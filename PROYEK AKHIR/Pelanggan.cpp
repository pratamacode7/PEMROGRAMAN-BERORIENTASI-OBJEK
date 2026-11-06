#include "Pelanggan.h"

#include <iostream>

Pelanggan::Pelanggan(const std::string& idPelanggan,
                     const std::string& nama,
                     const std::string& noHP,
                     const std::string& alamat)
    : idPelanggan(idPelanggan), nama(nama), noHP(noHP), alamat(alamat) {}

const std::string& Pelanggan::getIdPelanggan() const {
    return idPelanggan;
}

const std::string& Pelanggan::getNama() const {
    return nama;
}

const std::string& Pelanggan::getNoHP() const {
    return noHP;
}

const std::string& Pelanggan::getAlamat() const {
    return alamat;
}

void Pelanggan::tampilData() const {
    std::cout << "ID Pelanggan : " << idPelanggan << '\n'
              << "Nama         : " << nama << '\n'
              << "No. HP       : " << noHP << '\n'
              << "Alamat       : " << alamat << '\n';
}
