#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#define NOMINMAX
#include <Windows.h>
using namespace std;

double F(double x, double a, double b, double c) {
    if (x < 0 and b != 0) {
        return a * x * x + b;
    }
    else if (x > 0 and b == 0) {
        return (x - a) / (x - c);
    }
    else {
        return x / c;
    }
}
bool powoftwo(int num) {
    return (num > 0) && (num & (num - 1)) == 0;
}

void printTable(double arr1[], double arr2[], double x1, double x2, int size) {

    cout << "Первый массив:" << endl;
    cout << string(25, '-') << endl;
    cout << "|" << setw(6) << "x" << setw(7) << "|" << setw(6) << "F" << setw(5) << "|" << endl;
    cout << string(25, '-') << endl;

    for (int i = 0; i < size; ++i) {
        double x = x1 + (x2 - x1) * i / (size - 1);
        cout << "| " << setw(10) << x << " | "
            << setw(8) << arr1[i] << " |" << endl;
    }

    cout << string(25, '-') << endl;

    cout << "Второй массив:" << endl;
    cout << string(25, '-') << endl;
    cout << "|" << setw(6) << "x" << setw(7) << "|" << setw(6) << "F" << setw(5) << "|" << endl;
    cout << string(25, '-') << endl;

    for (int i = 0; i < size; ++i) {
        double x = -x2 + (x2 - x1) * i / (size - 1);
        cout << "| " << setw(10) << x << " | "
            << setw(8) << arr2[i] << " |" << endl;
    }

    cout << string(25, '-') << endl;
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "");

    bool isHuman = false;
    if (argc <= 1 || strcmp(argv[1], "false") != 0)
    {
        isHuman = true;
    }

    if (isHuman) {
        cout << "Введите пять действительных чисел (x1, x2, a, b, c):" << endl;
    }
    double x1, x2, a, b, c;
    cin >> x1 >> x2 >> a >> b >> c;
    const int size = 15;
    double arr1[size], arr2[size];
    double step = (x2 - x1) / (size - 1);

    for (int i = 0; i < size; ++i) {
        double x = x1 + i * step;
        arr1[i] = F(x, a, b, c);
    }

    for (int i = 0; i < size; ++i) {
        double x = -x2 + i * step;
        arr2[i] = F(x, a, b, c);
    }
    int a_int = static_cast<int>(a);
    int b_int = static_cast<int>(b);
    int c_int = static_cast<int>(c);

    if (((a_int | b_int) & (a_int | c_int)) == 0) {
        for (int i = 0; i < 15; ++i) {
            arr1[i] = round(arr1[i]);
            arr2[i] = round(arr2[i]);
        }
    }
    else {
        for (int i = 0; i < 15; ++i) {
            arr1[i] = round(arr1[i] * 100) / 100.0;
            arr2[i] = round(arr2[i] * 100) / 100.0;
        }
    }

    if (isHuman) {
        printTable(arr1, arr2, x1, x2, size);
    }

    else {
        for (int i = 0; i < size - 1; ++i) {
            cout << arr1[i] << " ";
        }
        cout << arr1[14] << endl;
        for (int i = 0; i < size - 1; ++i) {
            cout << arr2[i] << " ";
        }
        cout << arr2[14] << endl;
    }

    if (isHuman) {
        cout << "Минимумы пятерок первого массива:" << endl;
    }
    for (int i = 0; i < 14; i += 5) {
        double min_val = min({ arr1[i], arr1[i + 1], arr1[i + 2], arr1[i + 3], arr1[i + 4] });
        cout << min_val << endl;
    }
    
    int index = -1;
    
    for (int i = 0; i < 15; i++) {
        int ch = 0;
        if (powoftwo(static_cast<int>(arr1[i])) and (arr1[i] < arr1[i+1])) {
            for (int j = i + 1; j < 15; ++j) {
                if (!powoftwo(static_cast<int>(arr1[j]))) {
                    ch++;
                }
            }
            if (ch != 0) {
                index = i;
            }
        }
    }
    double sort_arr1[15];
    for (int i = 0; i < 15; ++i) {
        sort_arr1[i] = arr1[i];
    }
    for (int i = 1; i < 15; ++i)
    {
        for (int r = 0; r < 15 - i; r++)
        {
            if (sort_arr1[r] > sort_arr1[r + 1])
            {
                double temp = sort_arr1[r];
                sort_arr1[r] = sort_arr1[r + 1];
                sort_arr1[r + 1] = temp;
            }
        }
    }
    if (isHuman) {
        cout << "Элементы первого массива упорядоченные по возрастанию:" << endl;
    }
    for (int i = 0; i < size - 1; ++i) {
        cout << sort_arr1[i] << " ";
    }
    cout << sort_arr1[14] << endl;
    
    bool counted[15] = { false };
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (counted[i]) continue;
        int occ = 0;
        for (int j = 0; j < size; j++) {
            if (arr1[i] == arr1[j]) {
                occ++;
            }
        }
        if (occ > 1) {
            count++;
        }
        for (int j = 0; j < size; ++j) {
            if (arr1[i] == arr1[j]) {
                counted[j] = true;
            }
        }
    }
    if (isHuman) {
        cout << "Количество значений, встречающихся в массиве более одного раза:" << endl;
    }
    cout << count << endl;
     
    if (isHuman) {
        cout << "Номер элемента, начиная с которого в массиве непрерывно размещаются степени числа 2 в порядке возрастания:" << endl;
    }
    cout << index << endl;

    double pol[15], otr[15];
    int p = 0, o = 0;

    for (int i = 0; i < 15; ++i) {
        if (arr1[i] > 0) {
            pol[p++] = arr1[i];
            arr1[i] = 0;
        }
        
    }
  
    for (int i = 0; i < 15; ++i) {
        if (arr2[i] < 0) {
            otr[o++] = arr2[i];
            arr2[i] = 0;
        }

    }

    o = 0;
    p = 0;

    for (int i = 0; i < 15; ++i) {
        if (arr1[i] == 0) {
            arr1[i] = otr[o];
            o++;
        }
    }
    for (int i = 0; i < 15; ++i) {
        if (arr2[i] == 0) {
            arr2[i] = pol[p];
            p++;
        }
    }

    if (isHuman) {
        cout << "Перераспределенные массивы:" << endl;
    }
    for (int i = 0; i < size - 1; ++i) {
        cout << arr1[i] << " ";
    }
    cout << arr1[14] << endl;

    for (int i = 0; i < size - 1; ++i) {
        cout << arr2[i] << " ";
    }
    cout << arr2[14] << endl;

    return 0;
}