#include <iostream>
#include <string>
using namespace std;

// === Langkah 1: Membuat class
class Mahasiswa {
    public:
// === Langkah 2: Membuat atribut
    string nama;
    string nim;
// === Langkah 3: Membuat method
    void perkenalan() {
        cout << "Halo, Nama saya : " << nama 
        << ",dengan NIM : " << nim << endl;
    }
};  

// === Langkah 4: Membuat objek di dalam fungsi main
int main() {
    // Membuat objek dari class Mahasiswa
    Mahasiswa mhs1;
    // Mengisi atribut objek
    mhs1.nama = "Meilandri Salva Saputra Pratama";
    mhs1.nim = "25111024441302";
    // Memanggil method perkenalan
    mhs1.perkenalan();

    return 0;  

}