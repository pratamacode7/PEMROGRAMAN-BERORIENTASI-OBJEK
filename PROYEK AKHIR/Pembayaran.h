#ifndef PEMBAYARAN_H
#define PEMBAYARAN_H

#include <string>

class Pembayaran {
private:
    std::string idPembayaran;
    std::string idTransaksi;
    long long totalTagihan;
    long long jumlahBayar;
    long long kembalian;
    bool lunas;

public:
    Pembayaran(const std::string& idPembayaran,
               const std::string& idTransaksi, long long totalTagihan);
    bool prosesPembayaran(long long jumlahBayar);
    const std::string& getIdPembayaran() const;
    const std::string& getIdTransaksi() const;
    long long getTotalTagihan() const;
    long long getJumlahBayar() const;
    long long getKembalian() const;
    bool getLunas() const;
    void tampilPembayaran() const;
};

#endif
