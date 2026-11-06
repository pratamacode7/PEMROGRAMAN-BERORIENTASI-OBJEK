# Praktikum 3 - Nilai Mahasiswa dengan Exception Handling

Proyek ini merupakan pengembangan dari sistem nilai mahasiswa yang sudah ada. Fitur sebelumnya tetap dipertahankan dan ditambahkan fitur pembayaran uang kuliah serta penanganan kesalahan menggunakan custom exception.

## Fitur tambahan

- Melihat sisa tagihan berdasarkan NIM yang sedang login.
- Membayar uang kuliah dengan nominal minimal Rp1.000.
- Menolak nominal yang bukan angka, nol, negatif, atau melebihi sisa tagihan.
- Menampilkan riwayat transaksi pembayaran berdasarkan NIM.
- Menggunakan tiga custom exception: `NIMTidakDitemukanException`, `NominalTidakValidException`, dan `PembayaranMelebihiTagihanException`.

## File pembayaran

- `data_tagihan.csv`: menyimpan sisa tagihan setiap mahasiswa.
- `data_pembayaran.csv`: menyimpan riwayat nominal dan tanggal pembayaran.

Nominal awal di `data_tagihan.csv` adalah data contoh agar fitur bisa langsung diuji. Silakan sesuaikan kolom `TotalTagihan` dengan data praktikum yang diberikan dosen.

## Menjalankan di VS Code (Windows / MinGW)

Buka folder `PRAKTIKUM_3` atau langsung `PRAKTIKUM_3/NilaiMahasiswa` di VS Code, lalu jalankan build task atau tekan `Ctrl+Shift+B`.

Jika terminal sedang berada di folder `NilaiMahasiswa`, perintah manualnya:

```bash
g++ -std=c++17 -Wall -Wextra src/main.cpp src/Mahasiswa.cpp src/MataKuliah.cpp src/NilaiMK.cpp src/KHS.cpp src/Pembayaran.cpp -Iinclude -o NilaiMahasiswa.exe
.\\NilaiMahasiswa.exe
```

Pastikan program dijalankan dengan working directory `NilaiMahasiswa` karena file CSV dibaca dari folder tersebut.

## Akun contoh

- NIM: `2511102441302`
- Password: `pass302`

Akun dan password lain dapat dilihat di `data_mahasiswa.csv`.
