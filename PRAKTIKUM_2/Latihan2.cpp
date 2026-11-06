#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


// ==========================================================
// KELAS MAHASISWA
// ==========================================================
class Mahasiswa {
// Atribut private untuk menyimpan data mahasiswa
private:
    string nim;
    string nama;
    string jurusan;

public:
// Method untuk input data mahasiswa
    void inputData() {
        cout << "NIM     : ";
        cin >> nim;
        cin.ignore();            

        cout << "Nama    : ";
        getline(cin, nama);

        cout << "Jurusan : ";
        getline(cin, jurusan);
    }

// Method untuk menampilkan data mahasiswa
    void tampilkanData() {
        cout << "NIM     : " << nim << endl;
        cout << "Nama    : " << nama << endl;
        cout << "Jurusan : " << jurusan << endl;
    }
};


// ==========================================================
// KELAS NILAI
// ==========================================================

class Nilai {
// Atribut private untuk menyimpan data nilai
private:
    string matakuliah;
    double nilaiTugas;
    double nilaiUTS;
    double nilaiUAS;

public:
    // Method untuk input nilai
    void inputNilai() {
        cout << "Mata Kuliah : ";
        getline(cin, matakuliah);    // tidak perlu cin.ignore()

        cout << "Nilai Tugas  : ";
        cin >> nilaiTugas;

        cout << "Nilai UTS    : ";
        cin >> nilaiUTS;

        cout << "Nilai UAS    : ";
        cin >> nilaiUAS;
    }

// Method untuk menghitung nilai akhir
    double hitungNilaiAkhir() {
        return (nilaiTugas * 0.3) + (nilaiUTS * 0.3) + (nilaiUAS * 0.4);
    }

// Method untuk menentukan grade berdasarkan nilai akhir
    char getGrade() {
        double na = hitungNilaiAkhir();

        if (na >= 85)
            return 'A';
        else if (na >= 70)
            return 'B';
        else if (na >= 60)
            return 'C';
        else if (na >= 50)
            return 'D';
        else
            return 'E';
    }

// Method untuk menampilkan nilai dan grade
    void tampilkanNilai() {
        cout << "Mata Kuliah : " << matakuliah << endl;
        cout << "Tugas       : " << nilaiTugas << endl;
        cout << "UTS         : " << nilaiUTS << endl;
        cout << "UAS         : " << nilaiUAS << endl;

        cout << "Nilai Akhir : "
            << fixed << setprecision(1)
            << hitungNilaiAkhir() << endl;

        cout << "Grade       : " << getGrade() << endl;
    }
};


// ==========================================================
// PROGRAM UTAMA
// ==========================================================
int main() {
// Buat objek Mahasiswa dan Nilai
    Mahasiswa mhs;
    Nilai nilai;

    // Input data mahasiswa
    cout << "=== INPUT DATA MAHASISWA ===" << endl;
    mhs.inputData();

    // Input nilai
    cout << "\n=== INPUT NILAI ===" << endl;
    nilai.inputNilai();

    // Tampilkan hasil
    cout << "\n=== HASIL ===" << endl;
    mhs.tampilkanData();

    cout << endl;

    nilai.tampilkanNilai();

    return 0;
}