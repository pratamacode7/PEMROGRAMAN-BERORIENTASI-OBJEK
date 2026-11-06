#ifndef PEMBAYARAN_H
#define PEMBAYARAN_H

#include <stdexcept>
#include <string>

// Exception khusus ketika NIM belum memiliki data tagihan.
class NIMTidakDitemukanException : public std::runtime_error {
public:
    explicit NIMTidakDitemukanException(const std::string& nim)
        : std::runtime_error("NIM '" + nim + "' tidak terdaftar pada data tagihan.") {}
};

// Exception untuk nominal yang bukan angka, nol, negatif, atau di bawah minimum.
class NominalTidakValidException : public std::runtime_error {
public:
    explicit NominalTidakValidException(const std::string& pesan)
        : std::runtime_error("Nominal tidak valid: " + pesan) {}
};

// Exception ketika nominal pembayaran lebih besar daripada sisa tagihan.
class PembayaranMelebihiTagihanException : public std::runtime_error {
private:
    double sisa;

public:
    PembayaranMelebihiTagihanException(double nominal, double sisaTagihan)
        : std::runtime_error("Nominal melebihi sisa tagihan."), sisa(sisaTagihan) {
        (void)nominal; // Parameter dipertahankan sesuai rancangan pada materi praktikum.
    }

    double getSisa() const { return sisa; }
};

class Pembayaran {
public:
    static double getSisaTagihan(const std::string& nim);
    static double prosesPembayaran(const std::string& nim, double nominal);
    static void tampilkanRiwayat(const std::string& nim);
};

#endif
