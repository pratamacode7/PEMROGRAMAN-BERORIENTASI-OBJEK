#ifndef STRUK_H
#define STRUK_H

#include "Pembayaran.h"
#include "Transaksi.h"

#include <string>

class Struk {
private:
    std::string nomorStruk;
    std::string idTransaksi;
    std::string tanggal;

public:
    Struk(const std::string& nomorStruk, const std::string& idTransaksi,
          const std::string& tanggal);
    void tampilStruk(const Transaksi& transaksi,
                     const Pembayaran& pembayaran) const;
    bool simpanStrukKeFile(const Transaksi& transaksi,
                           const Pembayaran& pembayaran) const;
};

#endif
