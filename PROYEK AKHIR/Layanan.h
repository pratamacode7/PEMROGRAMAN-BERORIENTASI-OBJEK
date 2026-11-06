#ifndef LAYANAN_H
#define LAYANAN_H

#include <string>

class Layanan {
protected:
    std::string namaLayanan;
    long long hargaPerKg;
    std::string estimasi;
    std::string rincianProses;

public:
    virtual long long hitungHarga(double berat) const = 0;
    virtual void tampilInfo() const = 0;

    const std::string& getNamaLayanan() const;
    long long getHargaPerKg() const;
    const std::string& getEstimasi() const;
    const std::string& getRincianProses() const;
    virtual ~Layanan() = default;
};

class CuciKering : public Layanan {
public:
    CuciKering();
    long long hitungHarga(double berat) const override;
    void tampilInfo() const override;
};

class CuciSetrika : public Layanan {
public:
    CuciSetrika();
    long long hitungHarga(double berat) const override;
    void tampilInfo() const override;
};

class Express : public Layanan {
public:
    Express();
    long long hitungHarga(double berat) const override;
    void tampilInfo() const override;
};

#endif
