#include "SistemLaundry.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

namespace {
void bersihkanInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string bacaTeks(const std::string& label, bool wajib = true) {
    std::string nilai;
    do {
        std::cout << label;
        std::getline(std::cin, nilai);
        if (wajib && nilai.empty()) {
            std::cout << "Input tidak boleh kosong.\n";
        }
    } while (wajib && nilai.empty());
    return nilai;
}

long long bacaNominal(const std::string& label) {
    long long nilai;
    while (true) {
        std::cout << label;
        if (std::cin >> nilai && nilai >= 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return nilai;
        }
        std::cout << "Masukkan nominal bilangan bulat yang valid.\n";
        bersihkanInput();
    }
}

double bacaBerat() {
    double berat;
    while (true) {
        std::cout << "Berat pakaian (kg): ";
        if (std::cin >> berat && berat > 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return berat;
        }
        std::cout << "Berat harus berupa angka lebih dari 0.\n";
        bersihkanInput();
    }
}

bool konfirmasi(const std::string& pertanyaan) {
    std::string jawaban;
    while (true) {
        std::cout << pertanyaan << " (y/n): ";
        std::getline(std::cin, jawaban);
        if (jawaban == "y" || jawaban == "Y") {
            return true;
        }
        if (jawaban == "n" || jawaban == "N") {
            return false;
        }
        std::cout << "Jawab dengan y atau n.\n";
    }
}
}

SistemLaundry::SistemLaundry()
    : counterPelanggan(1),
      counterTransaksi(1),
      counterPembayaran(1),
      counterKomplain(1) {}

std::string SistemLaundry::buatId(const std::string& awalan, int nomor) const {
    std::ostringstream hasil;
    hasil << awalan << std::setfill('0') << std::setw(3) << nomor;
    return hasil.str();
}

std::string SistemLaundry::tanggalHariIni() const {
    const std::time_t sekarang = std::time(nullptr);
    std::tm waktu = {};
#ifdef _WIN32
    localtime_s(&waktu, &sekarang);
#else
    localtime_r(&sekarang, &waktu);
#endif
    std::ostringstream hasil;
    hasil << std::put_time(&waktu, "%d-%m-%Y");
    return hasil.str();
}

Pelanggan* SistemLaundry::cariPelanggan(const std::string& id) {
    for (Pelanggan& pelanggan : daftarPelanggan) {
        if (pelanggan.getIdPelanggan() == id) {
            return &pelanggan;
        }
    }
    return nullptr;
}

Transaksi* SistemLaundry::cariTransaksi(const std::string& id) {
    for (Transaksi& transaksi : daftarTransaksi) {
        if (transaksi.getIdTransaksi() == id) {
            return &transaksi;
        }
    }
    return nullptr;
}

Komplain* SistemLaundry::cariKomplain(const std::string& id) {
    for (Komplain& komplain : daftarKomplain) {
        if (komplain.getIdKomplain() == id) {
            return &komplain;
        }
    }
    return nullptr;
}

void SistemLaundry::menuUtama() const {
    std::cout << "\n========== SISTEM INFORMASI LAUNDRY ==========\n"
              << "1. Tambah pelanggan\n"
              << "2. Lihat daftar pelanggan\n"
              << "3. Buat transaksi laundry\n"
              << "4. Lihat riwayat transaksi\n"
              << "5. Ubah status laundry\n"
              << "6. Pengambilan laundry\n"
              << "7. Komplain\n"
              << "8. Laporan\n"
              << "0. Keluar\n"
              << "==============================================\n";
}

void SistemLaundry::jalankan() {
    int pilihan;
    do {
        menuUtama();
        std::cout << "Pilih menu: ";
        if (!(std::cin >> pilihan)) {
            std::cout << "Pilihan harus berupa angka.\n";
            bersihkanInput();
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (pilihan) {
        case 1: tambahPelanggan(); break;
        case 2: tampilDaftarPelanggan(); break;
        case 3: buatTransaksi(); break;
        case 4: tampilDaftarTransaksi(); break;
        case 5: ubahStatusLaundry(); break;
        case 6: menuPengambilan(); break;
        case 7: menuKomplain(); break;
        case 8: tampilLaporan(); break;
        case 0: std::cout << "Terima kasih.\n"; break;
        default: std::cout << "Menu tidak tersedia.\n";
        }
    } while (pilihan != 0);
}

void SistemLaundry::menuPelanggan() {
    std::cout << "\n1. Pilih pelanggan yang sudah ada\n"
              << "2. Input pelanggan baru\n";
}

void SistemLaundry::tambahPelanggan() {
    const std::string id = buatId("PLG", counterPelanggan++);
    const std::string nama = bacaTeks("Nama: ");
    const std::string noHP = bacaTeks("No. HP: ");
    const std::string alamat = bacaTeks("Alamat: ");
    daftarPelanggan.emplace_back(id, nama, noHP, alamat);
    std::cout << "Pelanggan berhasil ditambahkan dengan ID " << id << ".\n";
}

void SistemLaundry::tampilDaftarPelanggan() const {
    if (daftarPelanggan.empty()) {
        std::cout << "Belum ada data pelanggan.\n";
        return;
    }
    for (const Pelanggan& pelanggan : daftarPelanggan) {
        std::cout << "\n";
        pelanggan.tampilData();
    }
}

void SistemLaundry::buatTransaksi() {
    if (daftarPelanggan.empty()) {
        std::cout << "Belum ada pelanggan. Silakan input pelanggan baru.\n";
        tambahPelanggan();
    }

    menuPelanggan();
    int pilihanPelanggan;
    while (!(std::cin >> pilihanPelanggan) ||
           (pilihanPelanggan != 1 && pilihanPelanggan != 2)) {
        std::cout << "Pilih 1 atau 2: ";
        bersihkanInput();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Pelanggan* pelanggan = nullptr;
    if (pilihanPelanggan == 2) {
        tambahPelanggan();
        pelanggan = &daftarPelanggan.back();
    } else {
        tampilDaftarPelanggan();
        pelanggan = cariPelanggan(bacaTeks("Masukkan ID pelanggan: "));
        if (pelanggan == nullptr) {
            std::cout << "ID pelanggan tidak ditemukan.\n";
            return;
        }
    }

    std::cout << "\nPilihan layanan:\n";
    const Layanan* layananPilihan[] = {&cuciKering, &cuciSetrika, &express};
    for (int i = 0; i < 3; ++i) {
        std::cout << "\n" << i + 1 << ". ";
        layananPilihan[i]->tampilInfo();
    }
    int pilihanLayanan;
    while (!(std::cin >> pilihanLayanan) ||
           pilihanLayanan < 1 || pilihanLayanan > 3) {
        std::cout << "Pilih layanan 1 sampai 3: ";
        bersihkanInput();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    const Layanan& layanan = *layananPilihan[pilihanLayanan - 1];
    const double berat = bacaBerat();
    const long long total = layanan.hitungHarga(berat);

    std::cout << "\n========== RINGKASAN PESANAN ==========\n"
              << "Pelanggan : " << pelanggan->getNama() << '\n'
              << "Layanan   : " << layanan.getNamaLayanan() << '\n'
              << "Berat     : " << berat << " kg\n"
              << "Total     : Rp " << total << '\n';
    if (!konfirmasi("Konfirmasi pesanan")) {
        std::cout << "Pembuatan transaksi dibatalkan sebelum disimpan.\n";
        return;
    }

    Pembayaran pembayaran(buatId("PAY", counterPembayaran),
                          buatId("TR", counterTransaksi), total);
    while (true) {
        const long long jumlahBayar = bacaNominal("Jumlah pembayaran penuh: Rp ");
        if (pembayaran.prosesPembayaran(jumlahBayar)) {
            break;
        }
        std::cout << "Pembayaran kurang dari total tagihan. Silakan ulangi.\n";
    }
    if (!konfirmasi("Simpan transaksi dan pembayaran")) {
        std::cout << "Transaksi tidak disimpan.\n";
        return;
    }

    const std::string idTransaksi = buatId("TR", counterTransaksi++);
    ++counterPembayaran;
    daftarTransaksi.emplace_back(idTransaksi, *pelanggan, layanan, berat,
                                 tanggalHariIni());
    daftarPembayaran.push_back(pembayaran);
    Struk struk(idTransaksi, idTransaksi, tanggalHariIni());
    struk.tampilStruk(daftarTransaksi.back(), daftarPembayaran.back());
    if (struk.simpanStrukKeFile(daftarTransaksi.back(),
                                daftarPembayaran.back())) {
        std::cout << "Struk disimpan di folder struk.\n";
    }
}

void SistemLaundry::tampilDaftarTransaksi() const {
    if (daftarTransaksi.empty()) {
        std::cout << "Belum ada transaksi.\n";
        return;
    }
    for (const Transaksi& transaksi : daftarTransaksi) {
        std::cout << "\n";
        transaksi.tampilDetail();
    }
}

void SistemLaundry::ubahStatusLaundry() {
    Transaksi* transaksi = cariTransaksi(bacaTeks("ID transaksi: "));
    if (transaksi == nullptr) {
        std::cout << "ID transaksi tidak ditemukan.\n";
    } else if (transaksi->getStatus() == "Selesai") {
        std::cout << "Transaksi sudah berstatus Selesai.\n";
    } else {
        transaksi->ubahStatus("Selesai");
        std::cout << "Status laundry berhasil diubah menjadi Selesai.\n";
    }
}

void SistemLaundry::menuPengambilan() {
    if (!konfirmasi("Pastikan struk fisik asli sudah ditunjukkan pelanggan")) {
        std::cout << "Pengambilan ditolak karena struk fisik tidak ditunjukkan.\n";
        return;
    }
    Transaksi* transaksi = cariTransaksi(bacaTeks("ID transaksi pada struk: "));
    if (transaksi == nullptr) {
        std::cout << "Pengambilan ditolak: ID transaksi tidak ditemukan.\n";
    } else if (transaksi->getStatus() != "Selesai") {
        std::cout << "Laundry belum selesai dan belum boleh diserahkan.\n";
    } else {
        transaksi->tampilDetail();
        std::cout << "Pengambilan dapat dilanjutkan. Struk fisik ditahan admin.\n";
    }
}

void SistemLaundry::menuKomplain() {
    int pilihan;
    std::cout << "\n1. Buat komplain\n2. Selesaikan komplain\n"
              << "3. Lihat daftar komplain\n0. Kembali\nPilih: ";
    if (!(std::cin >> pilihan)) {
        bersihkanInput();
        std::cout << "Pilihan tidak valid.\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    switch (pilihan) {
    case 1: buatKomplain(); break;
    case 2: selesaikanKomplain(); break;
    case 3: tampilDaftarKomplain(); break;
    case 0: break;
    default: std::cout << "Pilihan tidak tersedia.\n";
    }
}

void SistemLaundry::buatKomplain() {
    const std::string idTransaksi = bacaTeks("ID transaksi: ");
    if (cariTransaksi(idTransaksi) == nullptr) {
        std::cout << "ID transaksi tidak ditemukan.\n";
        return;
    }
    int jenis;
    std::cout << "1. Barang Hilang\n2. Barang Tertukar\nPilih jenis: ";
    if (!(std::cin >> jenis) || (jenis != 1 && jenis != 2)) {
        bersihkanInput();
        std::cout << "Jenis komplain tidak valid.\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    const std::string namaJenis = jenis == 1 ? "Barang Hilang"
                                             : "Barang Tertukar";
    daftarKomplain.emplace_back(buatId("KMP", counterKomplain++), idTransaksi,
                                namaJenis, bacaTeks("Deskripsi: "));
    std::cout << "Komplain berhasil disimpan dengan status Diproses.\n";
}

void SistemLaundry::selesaikanKomplain() {
    Komplain* komplain = cariKomplain(bacaTeks("ID komplain: "));
    if (komplain == nullptr) {
        std::cout << "ID komplain tidak ditemukan.\n";
        return;
    }
    if (komplain->getStatus() == "Selesai") {
        std::cout << "Komplain sudah selesai.\n";
        return;
    }
    const std::string solusi = bacaTeks("Solusi: ");
    const long long kompensasi = bacaNominal("Nominal kompensasi (0 jika tidak ada): Rp ");
    komplain->selesaikanKomplain(solusi, kompensasi);
    std::cout << "Komplain berhasil diselesaikan.\n";
}

void SistemLaundry::tampilDaftarKomplain() const {
    if (daftarKomplain.empty()) {
        std::cout << "Belum ada komplain.\n";
        return;
    }
    for (const Komplain& komplain : daftarKomplain) {
        std::cout << '\n';
        komplain.tampilKomplain();
    }
}

void SistemLaundry::tampilLaporan() const {
    int diproses = 0;
    int selesai = 0;
    int komplainDiproses = 0;
    int komplainSelesai = 0;
    long long pendapatan = 0;
    for (const Transaksi& transaksi : daftarTransaksi) {
        if (transaksi.getStatus() == "Diproses") {
            ++diproses;
        } else {
            ++selesai;
        }
    }
    for (const Pembayaran& pembayaran : daftarPembayaran) {
        if (pembayaran.getLunas()) {
            pendapatan += pembayaran.getTotalTagihan();
        }
    }
    for (const Komplain& komplain : daftarKomplain) {
        if (komplain.getStatus() == "Diproses") {
            ++komplainDiproses;
        } else {
            ++komplainSelesai;
        }
    }
    std::cout << "\n================ LAPORAN ================\n"
              << "Jumlah pelanggan       : " << daftarPelanggan.size() << '\n'
              << "Jumlah transaksi       : " << daftarTransaksi.size() << '\n'
              << "Transaksi Diproses     : " << diproses << '\n'
              << "Transaksi Selesai      : " << selesai << '\n'
              << "Total pendapatan       : Rp " << pendapatan << '\n'
              << "Jumlah komplain        : " << daftarKomplain.size() << '\n'
              << "Komplain Diproses      : " << komplainDiproses << '\n'
              << "Komplain Selesai       : " << komplainSelesai << '\n';
}
