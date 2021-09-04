#include <iostream>

using namespace std;

const int standart_lenght = 100;

class subvector
{
private:
    int *trash;
    int l; //указвает на первую незаполненую €чейку
    int available; //на последнюю доступную

public:
    subvector (int n){ //кол-во элементов
        if(n == 0) n = standart_lenght;

        trash = new int[n];
        l = n;
        available = n - 1;
    }

    subvector (int n, int a) : subvector(n) { //n одинаковых элементов a
        for(int i = 0; i < n; i++) trash[i] = a;
    }

   subvector (int *massiv, int n) { //передаетс€ указатель / сколько оттуда копировать
        delete[] trash;

        trash = massiv;
        l = n;
        available = n - 1;
    }

    subvector operator = (subvector const a){
        delete[] trash;

        trash = new int[a.available + 1];

        for(int i = 0; i <= a.available; i++) trash[i] = (a.trash)[i];
        l = a.l;
        available = a.available;
    }

    subvector operator += (subvector const a){ //поэлементное сложение (если один больше, другого, то копирование недостающих €чеек)
        if(a.l <= l)
        {
            for(int i = 0; i < a.l; i++) //a.l - свободна€ €чейка, поэтому, до неЄ Ќ≈ включительно
                trash[i] += (a.trash)[i];
        }
        else
        {
            int *New = new int[a.l];

            for(int i = 0; i < l; i++) New[i] = trash[i] + (a.trash)[i];

            for(int i = l; i < a.l; i++) New[i] = (a.trash)[i];

            delete[] trash;
            trash = New;
            l = a.l;
            available = a.l - 1;
        }
    }

    int Size() {return l;}

    void Push_back(int a){
        if(l != available + 1) {trash[l] = a; l++;}
        else
        {
            int new_lenght = available ? (available+1)*2 : standart_lenght;

            int* New = new int[new_lenght];

            for(int i = 0; i <= available; i++) New[i] = trash[i];
            delete[] trash;
            trash = New;

            trash[available + 1] = a;
            available = new_lenght - 1;
            l++;
        }
    }

    int& Position(int n) {if(0 <= n && n <= available) return trash[n];}
};

int main()
{
    subvector b(3, 1);
    subvector a(4, 2);

    for(int i = 0; i < a.Size(); i++) cout << a.Position(i) << " ";
    cout << "   /   ";
    for(int i = 0; i < b.Size(); i++) cout << b.Position(i) << " "; cout << endl;

    a += b;

    for(int i = 0; i < a.Size(); i++) cout << a.Position(i) << " ";
    cout << " /   ";
    for(int i = 0; i < b.Size(); i++) cout << b.Position(i) << " ";

    return 0;
}
