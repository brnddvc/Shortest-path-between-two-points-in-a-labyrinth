#include "projekat3.h"

using namespace std;

int Projekat3::vrsta(char znak)
{
    ///engleski alfabet ima 26 slova
    int alfabet[26];
    alfabet[0]=0;
    for(int i=1; i<26; i++)
    {
        if(i%2==1)alfabet[i]=alfabet[i-1]+3;
        else alfabet[i]=alfabet[i-1]+1;
    }
    return alfabet[int(znak)-65];
}

void Projekat3::Zidovi()
{
    zidovi.resize(visina,vector<bool>(sirina));
    ///prvi i posljednji zid
    for(int i=0; i<sirina; i++)
    {
        zidovi[0][i]=true;
        zidovi[visina-1][i]=true;
    }
}

void Projekat3::Udaljenosti()
{
    ///postavljamo udaljenosti na neki random veliki broj tipa visina*sirina
    udaljenosti.resize(visina,vector<int>(sirina));
    for(int i=0; i<visina; i++)
    {
        for(int j=0; j<sirina; j++)
            udaljenosti[i][j]=visina*sirina;
    }
}

void Projekat3::popuni(int vrstaPocetak,int kolonaPocetak,int vrstaKraj,int kolonaKraj)
{
    int vrsta;
    Udaljenosti();
    if(vrstaPocetak%2==0)
    {
        ///popuni udaljenost susjeda po visini na 1 ako nisu prepreka
        if(kolonaPocetak!=0)
            if(zidovi[vrstaPocetak][kolonaPocetak-1]==false)udaljenosti[vrstaPocetak][kolonaPocetak-1]=1;
        if(kolonaPocetak!=sirina-1)
            if(zidovi[vrstaPocetak][kolonaPocetak+1]==false)udaljenosti[vrstaPocetak][kolonaPocetak+1]=1;
        ///popuni polje ispod sa 1
        udaljenosti[vrstaPocetak+1][kolonaPocetak]=1;
        ///popuni vrstu ispod
        for(int i=kolonaPocetak-1; i>=0; i--)
            ///lijevo od popunjenog polja sa vrijednostima susjeda desno +1
            udaljenosti[vrstaPocetak+1][i]=udaljenosti[vrstaPocetak+1][i+1]+1;
        for(int i=kolonaPocetak+1; i<sirina; i++)
            ///desno od popunjenog polja sa vrijednostima susjeda lijevo +1
            udaljenosti[vrstaPocetak+1][i]=udaljenosti[vrstaPocetak+1][i-1]+1;
        vrsta=vrstaPocetak+2;
    }
    else
    {
        ///popuni udaljenost susjeda po visini na 1 ako nisu prepreke
        if(kolonaPocetak!=0)
            if(zidovi[vrstaPocetak][kolonaPocetak-1]==false)udaljenosti[vrstaPocetak][kolonaPocetak-1]=1;
        if(kolonaPocetak!=sirina-1)
            if(zidovi[vrstaPocetak][kolonaPocetak+1]==false)udaljenosti[vrstaPocetak][kolonaPocetak+1]=1;
        ///popuni polje iznad sa 1
        udaljenosti[vrstaPocetak-1][kolonaPocetak]=1;
        ///popuni vrstu iznad
        for(int i=kolonaPocetak-1; i>=0; i--)
            ///lijevo od popunjenog polja sa vrijednostima susjeda desno +1
            udaljenosti[vrstaPocetak-1][i]=udaljenosti[vrstaPocetak-1][i+1]+1;
        for(int i=kolonaPocetak+1; i<sirina; i++)
            ///desno od popunjenog polja sa vrijednostima susjeda lijevo +1
            udaljenosti[vrstaPocetak-1][i]=udaljenosti[vrstaPocetak-1][i-1]+1;
        vrsta=vrstaPocetak+1;
    }
    if(vrstaPocetak==vrstaKraj)return;
    if(vrstaKraj%2==0)vrstaKraj+=2;
    ///popunjavanje reda sa slobodnim putem
    while(vrsta!=vrstaKraj)
    {
        ///prvu kolonu dolazimo odozgo
        if(zidovi[vrsta][0]==false)udaljenosti[vrsta][0]=udaljenosti[vrsta-1][0]+1;
        ///popuni sa lijeva na desno
        for(int i=1; i<sirina; i++)
        {
            ///dolazak odozgo ili sa lijeve strane - bira se manja udaljenost
            if(zidovi[vrsta][i]==false)udaljenosti[vrsta][i]=min(udaljenosti[vrsta][i],
                                                                 min(udaljenosti[vrsta-1][i]+1,udaljenosti[vrsta][i-1]+1));
        }
        ///popuni sa desna na lijevo
        for(int i=sirina-2; i>=0; i--)
        {
            ///dolazak sa desne strane ili vec obradjeno - bira se manja udaljenost
            if(zidovi[vrsta][i]==false)udaljenosti[vrsta][i]=min(udaljenosti[vrsta][i],udaljenosti[vrsta][i+1]+1);
        }
        vrsta++;
    }
}

Projekat3::Projekat3(string fajl)
{
    ifstream unos(fajl);
    unos>>visina;
    unos.get();
    unos>>sirina;
    unos.get();
    ///provjera visine i sirine
    if(visina<0 || visina>26 || visina%2==1)
        throw "Pogresan unos.";
    if(sirina<0)
        throw "Pogresan unos.";

    ///postavi visinu na duplu vrijednost
    visina*=2;
    Zidovi();

    for(int i=1; i<=(visina/2-2)/2; i++)
    {
        ///postavljanje unutrasnjih prepreka
        for(int j=0; j<sirina; j++)
        {
            zidovi[4*i-1][j]=true;
            zidovi[4*i][j]=true;
        }
        ///elemenat po elemenat iz fajla
        while(unos.peek()!='\n')
        {
            int slobodno;
            if(unos.eof())break;
            if(char(unos.peek())>='0' && char(unos.peek())<='9')
            {
                unos>>slobodno;
                if(slobodno<0 || slobodno>sirina) throw "Greska.";
                ///postavljanje slobodnog puta
                zidovi[4*i-1][slobodno-1]=false;
                zidovi[4*i][slobodno-1]=false;
            }
            else
                throw "Pogresan unos.";
            if(char(unos.peek()==','))unos.get();
        }
        unos.get();
    }
    unos.close();
}

int Projekat3::udaljenost(char prviZid, int pozicijaPrvog, char drugiZid,int pozicijaDrugog)
{
    ///konvertuj charove u brojeve
    int VrstaPocetak=vrsta(prviZid);
    int VrstaKraj=vrsta(drugiZid);
    ///smanji pozicije za jedan da bi u udaljenosti dobili njihove kolone
    pozicijaPrvog--;
    pozicijaDrugog--;

    ///provjera da li su tacke moguce za pocetak i kraj
    if(zidovi[VrstaPocetak][pozicijaPrvog]==false || zidovi[VrstaKraj][pozicijaDrugog]==false)
        throw "Pogresan unos tacki.";

    ///ako hocemo put odozdo prema gore
    if(VrstaPocetak>VrstaKraj)swap(VrstaPocetak,VrstaKraj);

    ///popunjavanje matrice
    popuni(VrstaPocetak,pozicijaPrvog,VrstaKraj,pozicijaDrugog);

    ///provjere vracanja udaljenosti u zavisnosti od krajnje vrste
    if(VrstaKraj==0)return udaljenosti[VrstaKraj+1][pozicijaDrugog];
    else if(VrstaKraj==visina-1)return udaljenosti[VrstaKraj-1][pozicijaDrugog];
    ///u zavisnosti od pozicije kraja
    else if(pozicijaDrugog==0)return min(udaljenosti[VrstaKraj][pozicijaDrugog+1],
                                         min(udaljenosti[VrstaKraj-1][pozicijaDrugog],udaljenosti[VrstaKraj+1][pozicijaDrugog]));
    else if(pozicijaDrugog==sirina-1)return min(udaljenosti[VrstaKraj][pozicijaDrugog-1],
                                                min(udaljenosti[VrstaKraj-1][pozicijaDrugog],udaljenosti[VrstaKraj+1][pozicijaDrugog]));
    else return min(min(udaljenosti[VrstaKraj][pozicijaDrugog-1],udaljenosti[VrstaKraj][pozicijaDrugog+1]),
                        min(udaljenosti[VrstaKraj-1][pozicijaDrugog],udaljenosti[VrstaKraj+1][pozicijaDrugog]));
}
