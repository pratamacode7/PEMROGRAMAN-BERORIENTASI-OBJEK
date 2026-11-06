#ifndef NILAIMK_H
#define NILAIMK_H

#include <string>
using namespace std;

class NilaiMK {
public:
    string nim;
    string kodeMK;
    double nilaiAngka;
    int semester;

    NilaiMK() {}
    NilaiMK(string n, string k, double na, int sem) 
        : nim(n), kodeMK(k), nilaiAngka(na), semester(sem) {}
    
    string getNilaiHuruf() {
        if (nilaiAngka >= 80) return "A";
        else if (nilaiAngka >= 75) return "AB";
        else if (nilaiAngka >= 70) return "B";
        else if (nilaiAngka >= 65) return "BC";
        else if (nilaiAngka >= 60) return "C";
        else if (nilaiAngka >= 50) return "D";
        else return "E";
    }

    double getBobot() {
        if (nilaiAngka >= 80) return 4.0;
        else if (nilaiAngka >= 75) return 3.5;
        else if (nilaiAngka >= 70) return 3.0;
        else if (nilaiAngka >= 65) return 2.5;
        else if (nilaiAngka >= 60) return 2.0;
        else if (nilaiAngka >= 50) return 1.0;
        else return 0.0;
    }
};

void simpanNilai(string nim, string kodeMK, double nilaiAngka, int semester);

#endif