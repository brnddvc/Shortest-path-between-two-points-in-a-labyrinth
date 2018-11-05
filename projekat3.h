#ifndef PROJEKAT3_H
#define PROJEKAT3_H

#include<iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

class Projekat3 {
private:
    int visina;
    int sirina;
    vector<vector<bool>> zidovi;
    vector<vector<int>> udaljenosti;
    ////////////////////////////////
    int vrsta(char znak);
    void Zidovi();
    void Udaljenosti();
public:
    void popuni(int vrstaPocetak, int kolonaPocetak, int vrstaKraj, int kolonaKraj);
    Projekat3(string filename);
    int udaljenost(char prviZid, int pozicijaPrvog, char drugiZid,int pozicijaDrugog);
};

#endif
