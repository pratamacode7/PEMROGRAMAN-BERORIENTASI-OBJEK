#include "Layanan.h"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
long long hitungHargaDasar(long long hargaPerKg, double berat) {
    return static_cast<long long>(std::llround(berat * hargaPerKg));
}

void tampilkanInfoLayanan(const Layanan& layanan) {
    std::cout << "Layanan          : " << layanan.getNamaLayanan() << '\n'
              << "Harga per kg     : Rp " << layanan.getHargaPerKg() << '\n'
              << "Estimasi         : " << layanan.getEstimasi() << '\n'
              << "Rincian proses   : " << layanan.getRincianProses() << '\n';
}
}

const std::string& Layanan::getNamaLayanan() const {
    return namaLayanan;
}

long long Layanan::getHargaPerKg() const {
    return hargaPerKg;
}

const std::string& Layanan::getEstimasi() const {
    return estimasi;
}

const std::string& Layanan::getRincianProses() const {
    return rincianProses;
}

CuciKering::CuciKering() {
    namaLayanan = "Cuci Kering";
    hargaPerKg = 7000;
    estimasi = "2-3 hari";
    rincianProses = "Cuci + Kering + Lipat";
}

long long CuciKering::hitungHarga(double berat) const {
    return hitungHargaDasar(hargaPerKg, berat);
}

void CuciKering::tampilInfo() const {
    tampilkanInfoLayanan(*this);
}

CuciSetrika::CuciSetrika() {
    namaLayanan = "Cuci Setrika";
    hargaPerKg = 10000;
    estimasi = "2-3 hari";
    rincianProses = "Cuci + Kering + Setrika + Lipat";
}

long long CuciSetrika::hitungHarga(double berat) const {
    return hitungHargaDasar(hargaPerKg, berat);
}

void CuciSetrika::tampilInfo() const {
    tampilkanInfoLayanan(*this);
}

Express::Express() {
    namaLayanan = "Express";
    hargaPerKg = 15000;
    estimasi = "1 hari";
    rincianProses = "Cuci + Kering + Setrika + Lipat (prioritas)";
}

long long Express::hitungHarga(double berat) const {
    return hitungHargaDasar(hargaPerKg, berat);
}

void Express::tampilInfo() const {
    tampilkanInfoLayanan(*this);
}
