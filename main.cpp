#include <iostream>

#include "projekat3.h"

using namespace std;

int main()
{
    cout<<"PROJEKAT 3\n";
    Projekat3 projekat3("projekat3.txt");
    cout<<"Najmanja udaljenost od polja A9 do polja J8 je: "<<projekat3.udaljenost('A',9,'J',8);
    return 0;
}
