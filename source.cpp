//Michał Sałęga
#include <iostream>
using namespace std;

long pow(int x, int y){
    long sum = 1;
    for(int i = 0; i < y; i++){
        sum *= x;
    }
    return sum;
}

long long determ(long long a[][32], int n) {
    long long p, h, k, i, j, temp[32][32];
    long long det = 0;

    if(n==1) {
        return a[0][0];
    } else if(n==2) {
        det=(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
        return det;
    } else {
        for(p=0;p<n;p++) {
            h = 0;
            k = 0;
            for(i=1;i<n;i++) {
                for( j=0;j<n;j++) {
                    if(j==p) {
                        continue;
                    }
                    temp[h][k] = a[i][j];
                    k++;
                    if(k==n-1) {
                        h++;
                        k = 0;
                    }
                }
            }
            det=det+a[0][p]*pow(-1,p)*determ(temp,n-1);
        }
        return det;
    }
}

int main() {
    int szescian[32][32][32];
    int szescianBok;
    int poziomWierzcholka;
    int pionWierzcholka;
    int panelWierzcholka;
    int wysProsto;
    int szerProsto;
    int glebProsto;
    int dlugoscKr;

    char kodOperacji;
    cin >> szescianBok;
    int srodekSzescianu = szescianBok/2;
    for(int i = 0; i < szescianBok; i++){
        for(int j = 0; j < szescianBok; j++){
            for(int k = 0; k < szescianBok; k++){
                cin >> szescian[j][k][i];
            }
        }
    }

    while(kodOperacji != 'E'){
        cin >> kodOperacji;

        if(kodOperacji == 'C'){
            cin >> poziomWierzcholka >> pionWierzcholka >> panelWierzcholka >> wysProsto >> szerProsto >> glebProsto;

            int zwrotX = 1;
            int zwrotY = 1;
            int zwrotZ = 1;
            if(poziomWierzcholka < 0){
                wysProsto += poziomWierzcholka;
                poziomWierzcholka = 0;
            }
            if(pionWierzcholka < 0){
                szerProsto += pionWierzcholka;
                pionWierzcholka = 0;
            }
            if(panelWierzcholka < 0){
                glebProsto += panelWierzcholka;
                panelWierzcholka = 0;
            }

            if(poziomWierzcholka >= srodekSzescianu){
                zwrotX = -1;
            }
            if(pionWierzcholka >= srodekSzescianu){
                zwrotY = -1;
            }
            if(panelWierzcholka >= srodekSzescianu){
                zwrotZ = -1;
            }

            long int suma = 0;
            if(wysProsto >= szescianBok){
                wysProsto = szescianBok - 1;
            }
            if(glebProsto >= szescianBok){
                glebProsto = szescianBok - 1;
            }
            if(szerProsto >= szescianBok){
                szerProsto = szescianBok - 1;
            }

            for(int i = 0; i <= wysProsto; i++){
                for(int j = 0; j <= glebProsto; j++){
                    for(int k = 0; k <= szerProsto; k++){
                        suma += szescian[poziomWierzcholka + (i*zwrotX)][pionWierzcholka + (k*zwrotY)][panelWierzcholka + (j*zwrotZ)];
                    }
                }
            }


            cout << suma << endl;
        }

        if(kodOperacji == 'T'){
            cin >> poziomWierzcholka >> pionWierzcholka >> panelWierzcholka >> dlugoscKr;

            int zwrotX = 1;
            int zwrotY = 1;
            int zwrotZ = 1;

            if(poziomWierzcholka >= srodekSzescianu){
                zwrotX = -1;
            }
            if(pionWierzcholka >= srodekSzescianu){
                zwrotY = -1;
            }
            if(panelWierzcholka >= srodekSzescianu){
                zwrotZ = -1;
            }

            if(poziomWierzcholka < 0){
                dlugoscKr += poziomWierzcholka;
                poziomWierzcholka = 0;
            }
            if(pionWierzcholka < 0){
                dlugoscKr += pionWierzcholka;
                pionWierzcholka = 0;
            }
            if(panelWierzcholka < 0){
                dlugoscKr += panelWierzcholka;
                panelWierzcholka = 0;
            }

            long int suma = 0;
            if(dlugoscKr > 0){
                for(int i = poziomWierzcholka; (i < 32) && (i >= 0); i+=zwrotX){
                    for(int j = pionWierzcholka; (j < 32) && (j >= 0); j+=zwrotY){
                        for(int k = panelWierzcholka; (k < 32) && (k >= 0); k+=zwrotZ){
                            int ex = poziomWierzcholka - i;
                            int ey = pionWierzcholka - j;
                            int ez = panelWierzcholka - k;
                            if(ex < 0){
                                ex = -ex;
                            }
                            if(ey < 0){
                                ey = -ey;
                            }
                            if(ez < 0){
                                ez = -ez;
                            }

                            if(ex + ey + ez <= dlugoscKr) {
                                suma += szescian[i][j][k];
                            }
                        }
                    }
                }
            }else if(dlugoscKr == 0){
                suma += szescian[poziomWierzcholka][pionWierzcholka][panelWierzcholka];
            }
            cout << suma << endl;
        }
        if(kodOperacji == 'D'){
            char pOrPOrP;
            int indeks;
            cin >> pOrPOrP >> indeks;

            if(pOrPOrP == 'l'){
                long long tab[32][32];
                long long det = 0;
                for(int i = 0; i < szescianBok;i++){
                    for(int j = 0; j < szescianBok; j++){
                        tab[i][j] = szescian[indeks][i][j];
                    }
                }

                bool trojkatUp = true;
                bool trojkatDown = true;

                for(int i = 0; i < szescianBok-1; i++){
                    for(int j = i+1; j < szescianBok; j++){
                        if(tab[i][j] != 0){
                            trojkatUp = false;
                        }
                    }
                }
                for(int i = 1; i < szescianBok; i++){
                    for(int j = 0; j < i; j++){
                        if(tab[i][j] != 0){
                            trojkatDown = false;
                        }
                    }
                }
                if((trojkatDown == true) || (trojkatUp == true)){
                    for(int i = 0; i < szescianBok; i++){
                        for(int j = 0; j < szescianBok; j++){
                            if(i == j){
                                det *= tab[i][j];
                            }
                        }
                    }
                    cout << det << endl;
                }else{
                    cout << determ(tab, szescianBok) << endl;
                }

            }else if(pOrPOrP == 'v'){
                long long tab[32][32];
                long long det = 0;
                for(int i = 0; i < szescianBok;i++){
                    for(int j = 0; j < szescianBok; j++){
                        tab[i][j] = szescian[i][indeks][j];
                    }
                }
                bool trojkatUp = true;
                bool trojkatDown = true;
                for(int i = 0; i < szescianBok-1; i++){
                    for(int j = i+1; j < szescianBok; j++){
                        if(tab[i][j] != 0){
                            trojkatUp = false;
                        }
                    }
                }
                for(int i = 1; i < szescianBok; i++){
                    for(int j = 0; j < i; j++){
                        if(tab[i][j] != 0){
                            trojkatDown = false;
                        }
                    }
                }
                if((trojkatDown == true) || (trojkatUp == true)){
                    for(int i = 0; i < szescianBok; i++){
                        for(int j = 0; j < szescianBok; j++){
                            if(i == j){
                                det *= tab[i][j];
                            }
                        }
                    }
                    cout << det << endl;
                }else{
                    cout << determ(tab, szescianBok) << endl;
                }
            }else if(pOrPOrP == 'p'){
                long long tab[32][32];
                long long det = 1;
                for(int i = 0; i < szescianBok;i++){
                    for(int j = 0; j < szescianBok; j++){
                        tab[i][j] = szescian[i][j][indeks];
                    }
                }
                bool trojkatUp = true;
                bool trojkatDown = true;
                for(int i = 0; i < szescianBok-1; i++){
                    for(int j = i+1; j < szescianBok; j++){
                        if(tab[i][j] != 0){
                            trojkatUp = false;
                        }
                    }
                }
                for(int i = 1; i < szescianBok; i++){
                    for(int j = 0; j < i; j++){
                        if(tab[i][j] != 0){
                            trojkatDown = false;
                        }
                    }
                }
                if((trojkatDown == true) || (trojkatUp == true)){
                    for(int i = 0; i < szescianBok; i++){
                        for(int j = 0; j < szescianBok; j++){
                            if(i == j){
                                det *= tab[i][j];
                            }
                        }
                    }
                    cout << det << endl;
                }else{
                    cout << determ(tab, szescianBok) << endl;
                }
            }
        }
        if(kodOperacji == 'O'){
            int promien;
            cin >> poziomWierzcholka >> pionWierzcholka >> panelWierzcholka >> promien;

            int zwrotX = 1;
            int zwrotY = 1;
            int zwrotZ = 1;

            if(poziomWierzcholka >= srodekSzescianu){
                zwrotX = -1;
            }
            if(pionWierzcholka >= srodekSzescianu){
                zwrotY = -1;
            }
            if(panelWierzcholka >= srodekSzescianu){
                zwrotZ = -1;
            }

//            if((poziomWierzcholka < 0) && (pionWierzcholka < 0) && (panelWierzcholka < 0)){
//                if(poziomWierzcholka <= pionWierzcholka){
//                    if(poziomWierzcholka <= panelWierzcholka){
//                        promien += poziomWierzcholka;
//                    }else{
//                        promien += panelWierzcholka;
//                    }
//                }else{
//                    if(pionWierzcholka <= panelWierzcholka){
//                        promien += pionWierzcholka;
//                    }
//                }
//                promien += poziomWierzcholka;
//                poziomWierzcholka = 0;
//                pionWierzcholka = 0;
//                panelWierzcholka = 0;
//            }
//            if(poziomWierzcholka < 0){
//                promien += poziomWierzcholka;
//                poziomWierzcholka = 0;
//            }
//            if(pionWierzcholka < 0){
//                promien += pionWierzcholka;
//                pionWierzcholka = 0;
//            }
//            if(panelWierzcholka < 0){
//                promien += panelWierzcholka;
//                panelWierzcholka = 0;
//            }

            long int suma = 0;
            if(promien > 0){
                for(int i = poziomWierzcholka; (i < 32) && ((i >= 0) || (i >= poziomWierzcholka)); i+=zwrotX){
                    for(int j = pionWierzcholka; (j < 32) && ((j >= 0) || (j >= pionWierzcholka)); j+=zwrotY){
                        for(int k = panelWierzcholka; (k < 32) && ((k >= 0) || (k >= panelWierzcholka)); k+=zwrotZ){
                            if((i >= 0) && (j >= 0) && (k >= 0)){
                                int ex = poziomWierzcholka - i;
                                int ey = pionWierzcholka - j;
                                int ez = panelWierzcholka - k;
                                if(ex < 0){
                                    ex = -ex;
                                }
                                if(ey < 0){
                                    ey = -ey;
                                }
                                if(ez < 0){
                                    ez = -ez;
                                }

                                if(((ex*ex)+(ey*ey)+(ez*ez)) <= promien*promien) {
                                    suma += szescian[i][j][k];
                                }
                            }
                        }
                    }
                }
            }else if(promien == 0){
                suma += szescian[poziomWierzcholka][pionWierzcholka][panelWierzcholka];
            }
            cout << suma << endl;
        }
    }

    return 0;
}
