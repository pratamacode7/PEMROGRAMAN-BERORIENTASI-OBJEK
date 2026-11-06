#ifndef PELANGGAN_H
#define PELANGGAN_H

#include <string>

class Pelanggan {
private:
    std::string idPelanggan;
    std::string nama;
    std::string noHP;
    std::string alamat;

public:
    Pelanggan(const std::string& idPelanggan, const std::string& nama,
              const std::string& noHP, const std::string& alamat);

    const std::string& getIdPelanggan() const;
    const std::string& getNama() const;
    const std::string& getNoHP() const;
    const std::string& getAlamat() const;
    void tampilData() const;
};

#endif
