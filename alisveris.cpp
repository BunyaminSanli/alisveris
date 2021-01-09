
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void menuYazdir()   //geri deger dondurmeyen sadece menu yazdiran fonksiyon
{
    cout << "----------------------------------------------------" << endl;
    cout << "                      ANA MENU                      " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "|     1- A Marka Dizustu Bilgisayar :  2500 tl      |" << endl;
    cout << "|     2- B Marka Kulaklik :            500 tl       |" << endl;
    cout << "|     3- C Marka Klavye & Mouse seti : 250 tl       |" << endl;
    cout << "|     4- D Marka Monitor :             1500 tl      |" << endl;
    cout << "----------------------------------------------------" << endl;
}

int fiyatHesapla(int secim , int adet)  // secilen urun ve adedini paremetre olarak alip hesaplamayi yapan fonksiyon
{
    int hesap = 0;
    if (secim == 1)
    {
        hesap = 2500 * adet;
    }
    if (secim == 2)
    {
        hesap = 500 * adet;
    }
    if (secim == 3)
    {
        hesap = 250 * adet;
    }
    if (secim == 4)
    {
        hesap = 1500 * adet;
    }

    return hesap;
}

char menuKontrol(int menusecim) //menu secimi icin girdinin istenen tipte oldugunu kontrol eden fonksiyon
{
    char secim = menusecim;
    while (secim != 'e' && secim != 'E' && secim != 'h' && secim != 'H')
    {
        if (secim == 'e' || secim == 'E' || secim == 'h' || secim == 'H')
        {
            break;
        }
        else
        {
            cout << "gecersiz secim lutfen e,E,h,H karakterlerinden birini giriniz" << endl;
            cin >> secim;
        }
    }
    return secim;
}

int main()
{
    double taksittutari;
    string aylar[] = { "Ocak","Subat","Mart","Nisan","Mayis","Haziran","Temmuz","Agustos","Eylul","Ekim","Kasim","Aralik" };
    int taksitsayisi = 1;
    int secim, adet, toplamborc;
    string musteriAd;
    char menusecim;

    cout << "sakarya bilisim -> Hosgeldiniz\n--------------------------------------------" << endl;
    cout << "Lufen adinizi giriniz : " << endl;
    getline(cin, musteriAd);

    cout << "\nSayin " << musteriAd << " asagidaki listeden alisveris yapabilirsiniz..." << endl;
    menuYazdir();
    cout << "seciminiz : ";
    cin >> secim;
    cout << "adet sayisi giriniz : ";
    cin >> adet;
    toplamborc = fiyatHesapla(secim, adet);
    cout << "Su anki toplam borcunuz : " << toplamborc << endl;
    cout << "Alisverise devam etmek istiyor musunuz? (E/H)";
    cin >> menusecim;
    
    menusecim = menuKontrol(menusecim);     
    menuKontrol(menusecim);
    

    while (menusecim == 'e' || menusecim == 'E')    //e girildigi surece alisveris devam eder
    {
        menuYazdir();
        cout << "seciminiz : ";
        cin >> secim;
        cout << "adet sayisi giriniz : ";
        cin >> adet;
        toplamborc += fiyatHesapla(secim, adet);
        cout << "Su anki toplam borcunuz : " << toplamborc << endl;
        cout << "Alisverise devam etmek istiyor musunuz? (E/H)";
        cin >> menusecim;
        menusecim = menuKontrol(menusecim);
        menuKontrol(menusecim);
       
    }

    cout << "%18 kdv eklensin mi? (E/H)" << endl;   
    cin >> menusecim;
    menusecim = menuKontrol(menusecim);
    menuKontrol(menusecim);
    char kdvsecim = menusecim;

    if (menusecim == 'e' || menusecim == 'E')   //e girildigi zaman toplam paraya kdv eklenir
    {
        toplamborc = toplamborc + toplamborc * 18 / 100;
        cout << "Toplam Borcunuz = " << toplamborc << endl;
    }
    else
    {
        cout << "Toplam Borcunuz : " << toplamborc << "+kdv" << endl;
    }
    
    cout << "Taksitlendirmek istiyor musunuz? (E/H)" << endl;
    cin >> menusecim;
    menusecim = menuKontrol(menusecim);
    menuKontrol(menusecim);
   

    if (menusecim == 'e' || menusecim == 'E')   //e girildigi zaman toplam para taksit sayisina bolunur
    {
        cout << "Taksit sayisini giriniz (En fazla 12 taksit)" << endl;
        cin >> taksitsayisi;
        taksittutari = (double)(toplamborc) / taksitsayisi;
        cout << "\nAylik odeme tutariniz = " << taksittutari << " TL" << endl;
        cout << "Odeme cizelgeniz : \n--------------------------------" << endl;
        for (int i = 0; i < taksitsayisi; i++)
        {
            if (kdvsecim == 'h' || kdvsecim == 'H')     //onceki islemlerde kdv tercihine gore yazdirma islemi yapilir
            {
                cout << aylar[i] << " : " << taksittutari << " TL + kdv" << endl;
            }
            else
            {
                cout << aylar[i] << " : " << taksittutari << " TL" << endl;
            }
            
        }   
    }
    else if(menusecim == 'h' || menusecim == 'H')   //h girildiginde toplam borc taksittutarina esitlenir
    {
        taksittutari = toplamborc;
        cout << "Toplam Odenecek Tutar\n------------------------" << endl;
        
        if (kdvsecim == 'h' || kdvsecim == 'H')
        {
            cout << toplamborc << " TL + kdv" << endl;
        }
        else
        {
            cout << toplamborc << " TL " << endl;
        }
       
    }

    //dosya yazma islemi
    ofstream dosyaYaz;
    dosyaYaz.open("fatura.txt");
    if (dosyaYaz.is_open())
    {
        dosyaYaz << "Müşteri Adı \n" << musteriAd << "\n\nToplam Borç Tutar : " << toplamborc << "\n" << endl;
        dosyaYaz << "Ödeme Çizelgesi : \n------------------------------" << endl;
        for (int i = 0; i < taksitsayisi; i++)
        {
            if (kdvsecim == 'h' || kdvsecim == 'H')
            {
                dosyaYaz << aylar[i] << " : " << taksittutari << " TL + kdv" << endl;
            }
            else
            {
                dosyaYaz << aylar[i] << " : " << taksittutari << " TL" << endl;
            }

        }
        dosyaYaz.close();
    }
    system("pause");
}

