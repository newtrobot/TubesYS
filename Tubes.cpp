#include "Tubes.h"
#include <cstdlib>

void InsertNewFilm(List_child &LC, List_parent &LP)
/**
Nama : Yoga Ajitama
NIM :130117
**/
{
    film baru;
    cout<<"Judul : ";
    cin.ignore();
    getline(cin,baru.judul);
    cout<<"Genre : ";
    getline(cin,baru.genre);
    cout<<"Rating: ";
    cin>>baru.rating;
    insertLast(LC, alokasi(baru));
}

void ChangeFilm(List_child &LC, List_parent &LP)
/**
Nama : Nuurshadieq
NIM : 1301171087
**/
{
    cout<<"Pilih teater yang ingin diganti filmnya: "<<endl;
    printInfo(LP);
    cout<<"Teater pilihan anda: ";
    int tepil;
    cin>>tepil;
    cout<<endl;
    teater *tepill = findElm(LP, tepil);
    cout<<"Film yang tayang pada teater "<<tepil<<": "<<endl;
    printInfo(child(tepill));
    if (first(child(tepill)) == NULL)
    {
        cout<<"Film tidak tersedia"<<endl;
    }
    else
    {
        cout<<"Film yang tersedia :"<<endl;
        printInfo(LC);
        cout<<"Judul film yang ingin diganti: ";
        string juduldiganti;
        cin.ignore();
        getline(cin,juduldiganti);
        address_child filmdiganti = findElm(LC, juduldiganti);
        address_relasi alamatfilm = findElm(child(tepill), filmdiganti);
        cout<<"Film baru: ";
        string judulpengganti;
        cin.ignore();
        getline(cin,judulpengganti);
        address_child filmpengganti = findElm(LC, judulpengganti);
        alamatfilm->info = filmpengganti;
        printInfo(child(tepill));
    }
}

void NewTeater(List_parent &LP) //Yoga
{
    cout<<"Teater yang ada saat ini"<<endl;
    printInfo(LP);
    cout<<endl;
    int noteater;
    cout<<"Nomor teater baru: ";
    cin>>noteater;
    if (findElm(LP, noteater) == NULL)
    {
        teater* newteater = alokasi(noteater);
        InsertAndSort(LP, newteater);
        cout<<"Teater berhasil dibangun"<<endl;
    }
    else
    {
        cout<<"Duplikat Teater"<<endl;
    }
}

void DeleteFilm(List_child &LC,List_parent &LP)
{
    printInfo(LC);
    string judulfilm;
    cout<<"Judul film yang ingin dihapus: ";
    cin.ignore();
    getline(cin,judulfilm);
    address_child erasedfilm = findElm(LC, judulfilm);
    if (erasedfilm != NULL)
    {
        address_child filmbuangan;
        teater* P = first(LP);
        int i = 0;
        do
        {
            address_relasi Q = first(child(P));
            address_relasi R = findElm(child(P),erasedfilm);
            address_relasi S;
            if (R != NULL)
            {
                if (R == Q)
                    deleteFirst(child(P),S);
                else if (R != NULL)
                {
                    while (Q != NULL && info(next(Q)) != erasedfilm)
                        Q = next(Q);
                    if (Q != NULL)
                        deleteAfter(Q,S);
                }
                delete S;
            }
            i++;
            P = next(P);
        }while(P != first(LP));
        cout<<i<<endl;
        if (erasedfilm == first(LC))
            deleteFirst(LC,filmbuangan);
        else if(erasedfilm == last(LC))
            deleteLast(LC,filmbuangan);
        else
            deleteAfter(prev(erasedfilm), filmbuangan); //disini nih
        delete filmbuangan;
    }
}

void FilmToTeater(List_child &LC, List_parent &LP)
{
    printInfo(LC);
    string judulfilm;
    int noteater;
    cout<<"Judul film yang ingin ditambahkan: ";
    cin.ignore();
    getline(cin,judulfilm);
    if (findElm(LC, judulfilm) == NULL)
    {
        cout<<"Film tidak tersedia"<<endl;
    }
    else
    {
        printInfo(LP);
        cout<<"Teater yang diinginkan: ";
        cin>>noteater;
        address_child Q = findElm(LC, judulfilm);
        address_parent P= findElm(LP,noteater);
        if (!isConnected(P,Q)) {
            insertFirst(child(P), alokasi(Q));
            printInfo(child(P));
            cout<<endl;
            cout<<"Film berhasil ditambahkan ke teater "<<noteater<<endl;
        }
        else {
            cout<<"Film berjudul "<<judulfilm<<" telah tersedia di teater "<<noteater<<endl;
        }
    }
}

void DelTeater(List_child &LC, List_parent &LP) //Yoga
{
    cout<<"Teater yang tersedia: "<<endl;
    printInfo(LP);
    int tecur;
    cout<<"Teater yang ingin dihancurkan :";
    cin>>tecur;
    address_parent P = findElm(LP, tecur);
    address_parent R;
    address_parent S;
    address_relasi Q;
    if (P != NULL)
    {
        while (first(child(P)) != NULL)
        {
            deleteFirst(child(P),Q);
            delete Q;
        }
        if (P == first(LP))
        {
            deleteFirst(LP,S);
            cout<<"Teater berhasil dihancurkan"<<endl;
        }
        else
        {
            R = first(LP);
            while (next(R) != P)
            {
                R = next(R);
            }
            deleteAfter(LP,R,S);
            cout<<"Teater berhasil dihancurkan"<<endl;
        }
        delete S;
    }
    else
    {
        cout<<"Teater tidak ditemukan"<<endl;
    }
}

bool isConnected(address_parent P, address_child Q) {
    address_relasi R = findElm(child(P),Q);
    return (R != NULL);
}


void cekRelasi(List_child &LC, List_parent &LP) {
    int noteater;
    string judul;
    bool x = false;
    cout<<"Masukkan judul film: "<<endl;
    cin.ignore();
    getline(cin,judul);
    cout<<"Masukkan nomor teater : "<<endl;
    cin>>noteater;
    address_parent P = findElm(LP,noteater);
    address_child Q = findElm(LC,judul);
    if (P != NULL && Q != NULL) {
        x = isConnected(P,Q);
    }
    if (x == false) {
        cout<<"Teater dan film tidak terhubung"<<endl;
    }
    else {
        cout<<"Teater dan film terhubung"<<endl;
    }
}
