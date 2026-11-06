#ifndef KOMPLAIN_H
#define KOMPLAIN_H

#include <string>

class Komplain {
private:
    std::string idKomplain;
    std::string idTransaksi;
    std::string jenisKomplain;
    std::string deskripsi;
    std::string status;
    std::string solusi;
    long long nominalKompensasi;

public:
    Komplain(const std::string& idKomplain, const std::string& idTransaksi,
             const std::string& jenisKomplain, const std::string& deskripsi);
    const std::string& getIdKomplain() const;
    const std::string& getIdTransaksi() const;
    const std::string& getJenisKomplain() const;
    const std::string& getDeskripsi() const;
    const std::string& getStatus() const;
    const std::string& getSolusi() const;
    long long getNominalKompensasi() const;
    void prosesKomplain();
    void selesaikanKomplain(const std::string& solusi,
                            long long kompensasi = 0);
    void tampilKomplain() const;
};

#endif
