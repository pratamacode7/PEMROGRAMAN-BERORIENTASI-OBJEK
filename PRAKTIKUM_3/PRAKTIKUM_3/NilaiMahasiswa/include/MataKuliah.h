#ifndef MATAKULIAH_H
#define MATAKULIAH_H

#include <string>
#include <vector>
using namespace std;

class MataKuliah {
public:
    string kodeMK;
    string namaMK;
    int sks;
    int semester;

    MataKuliah() {}
    MataKuliah(string k, string n, int s, int sem) 
        : kodeMK(k), namaMK(n), sks(s), semester(sem) {}
};

vector<MataKuliah> loadDataMataKuliah();
void tampilkanDaftarMK();
void tambahMataKuliah();

#endif