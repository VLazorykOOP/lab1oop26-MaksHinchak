#include <iostream>
#include <fstream>
#include <ios>
#include <array>
#include <time.h>

using namespace std;

int ConsoleInputSizeArray(const int sizeMax)
{
    int size = 0;
    do {
        cout << "Input size (0 < size < " << sizeMax << "): ";
        cin >> size;
    } while (size <= 0 || size >= sizeMax);
    return size;
}

int ConsoleInputArray(int sizeMax, double A[])
{
    int size = ConsoleInputSizeArray(sizeMax);
    for (int i = 0; i < size; i++) {
        cout << "A[" << i << "] = ";
        cin >> A[i];
    }
    return size;
}

int RndInputArray(int sizeMax, double A[])
{
    int size = ConsoleInputSizeArray(sizeMax);
    int r1 = 0, r2 = 0;
    srand(size);

    cout << "Random array:\n";
    for (int i = 0; i < size; i++) {
        r1 = rand();
        r2 = rand();
        A[i] = 100.0 * r1;
        A[i] = A[i] / (1.0 + r2);
        cout << A[i] << "   ";
    }
    cout << "\n";
    return size;
}

void WriteArrayTextFile(int n, double* arr, const char* fileName)
{
    ofstream fout(fileName);
    if (fout.fail()) return;

    fout << n << endl;
    for (int i = 0; i < n; i++)
        fout << arr[i] << "   ";
    fout.close();
}

int ReadArrayTextFile(int n, double* arr, const char* fileName)
{
    int size;
    ifstream fin(fileName);
    if (fin.fail()) return 0;

    fin >> size;
    if (size <= 0) return 0;
    if (size > n) size = n;

    for (int i = 0; i < size; i++)
        fin >> arr[i];

    fin.close();
    return size;
}

void WriteArrayBinFile(int n, double* arr, const char* fileName)
{
    ofstream bfout(fileName, ios_base::binary);
    if (bfout.fail()) return;

    bfout.write((const char*)&n, sizeof(int));
    bfout.write((const char*)arr, static_cast<std::streamsize>(n) * sizeof(double));
    bfout.close();
}

int ReadArrayBinFile(int n, double* arr, const char* fileName)
{
    int size = 0;
    ifstream bfin(fileName, ios_base::binary);
    if (bfin.fail()) return 0;

    bfin.read((char*)&size, sizeof(int));
    if (size <= 0) return 0;
    if (size > n) size = n;

    bfin.read((char*)arr, static_cast<std::streamsize>(size) * sizeof(double));
    bfin.close();
    return size;
}

// 3.1
void Lab_3_1_TextInputAndSave(const char* txtName)
{
    const int MAX = 560;
    double A[MAX];
    int n = ConsoleInputArray(MAX, A);
    WriteArrayTextFile(n, A, txtName);
    cout << "Saved: " << txtName << "\n";
}

// 3.2
void Lab_3_2_RandomAndSaveBin(const char* binName, const char* xTxtName, int needX)
{
    const int MAX = 560;
    double A[MAX];
    int n = RndInputArray(MAX, A);

    WriteArrayBinFile(n, A, binName);
    cout << "Saved: " << binName << "\n";

    if (needX) {
        double X;
        cout << "Input X: ";
        cin >> X;

        ofstream fout(xTxtName);
        if (!fout.fail()) {
            fout << X;
            fout.close();
            cout << "Saved: " << xTxtName << "\n";
        }
    }
}

// 3.4 (container: std::array)
void ReadTextToArrayAndPrint(const char* inTxt)
{
    const int MAX = 560;
    std::array<double, MAX> A{};

    int n = ReadArrayTextFile(MAX, A.data(), inTxt);
    if (n <= 0) { cout << "Error read: " << inTxt << "\n"; return; }

    cout << "Container(array) from " << inTxt << ":\n";
    for (int i = 0; i < n; i++) cout << A[i] << "   ";
    cout << "\n";
}

void ReadBinToArrayAndPrint(const char* inBin)
{
    const int MAX = 560;
    std::array<double, MAX> A{};

    int n = ReadArrayBinFile(MAX, A.data(), inBin);
    if (n <= 0) { cout << "Error read: " << inBin << "\n"; return; }

    cout << "Container(array) from " << inBin << ":\n";
    for (int i = 0; i < n; i++) cout << A[i] << "   ";
    cout << "\n";
}

// 3.3 задачі
void Solve_Task1_5_FromText_ToText(const char*, const char*) { cout << "TODO Task1#5\n"; }
void Solve_Task2_5_FromBinX_ToText(const char*, const char*, const char*) { cout << "TODO Task2#5\n"; }
void Solve_Task3_5_FromBin_ToText(const char*, const char*) { cout << "TODO Task3#5\n"; }

// menu
void ShowMainMenu()
{
    cout << "\n===== MENU (Variant 5) =====\n";
    cout << "1) 3.1 Console -> A1.txt\n";
    cout << "2) 3.2 Random -> A2.bin + X.txt\n";
    cout << "3) 3.2 Random -> A3.bin (2n)\n";
    cout << "4) 3.3 Solve Task1#5 (A1.txt -> B_no_zero.txt) [TODO]\n";
    cout << "5) 3.3 Solve Task2#5 (A2.bin + X.txt -> Result2_5.txt) [TODO]\n";
    cout << "6) 3.3 Solve Task3#5 (A3.bin -> Result3_5.txt) [TODO]\n";
    cout << "7) 3.4 Print container from A1.txt\n";
    cout << "8) 3.4 Print container from A2.bin\n";
    cout << "9) 3.4 Print container from A3.bin\n";
    cout << "0) Exit\n";
    cout << "Choice: ";
}

int main()
{
    char choice;

    while (true) {
        ShowMainMenu();
        cin >> choice;

        switch (choice) {
        case '1': Lab_3_1_TextInputAndSave("A1.txt"); break;
        case '2': Lab_3_2_RandomAndSaveBin("A2.bin", "X.txt", 1); break;
        case '3': Lab_3_2_RandomAndSaveBin("A3.bin", "X_unused.txt", 0); break;

        case '4': Solve_Task1_5_FromText_ToText("A1.txt", "B_no_zero.txt"); break;
        case '5': Solve_Task2_5_FromBinX_ToText("A2.bin", "X.txt", "Result2_5.txt"); break;
        case '6': Solve_Task3_5_FromBin_ToText("A3.bin", "Result3_5.txt"); break;

        case '7': ReadTextToArrayAndPrint("A1.txt"); break;
        case '8': ReadBinToArrayAndPrint("A2.bin"); break;
        case '9': ReadBinToArrayAndPrint("A3.bin"); break;

        case '0': return 0;
        default: cout << "Wrong choice\n";
        }
    }
}