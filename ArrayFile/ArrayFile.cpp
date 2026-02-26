#include <iostream>
#include <fstream>
#include <ios>
#include <array>
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
        A[i] = (2 * r1)-r2;
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
int ReadXandArrayFromText(const char* fileName, int maxN, double& X, double A[])
{
    ifstream fin(fileName);
    if (!fin) return 0;

    fin >> X;
    int n = 0;
    while (n < maxN && (fin >> A[n])) n++;

    fin.close();
    return n;
}

int ReadZFile(const char* fileName, int maxSize, int& n, double A[])
{
    ifstream fin(fileName);
    if (!fin) {
        cout << "Cannot open " << fileName << "\n";
        return 0;
    }

    fin >> n;

    int total = 2 * n;
    if (total > maxSize)
        total = maxSize;

    for (int i = 0; i < total; i++)
        fin >> A[i];

    fin.close();
    return total;
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
void Lab_3_2_RandomAndSaveBin(const char* binName)
{
    const int MAX = 560;
    double A[MAX];
    int n = RndInputArray(MAX, A);

    WriteArrayBinFile(n, A, binName);
    cout << "Saved: " << binName << "\n";
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
//  Task 1 №5
int Task1_5_RemoveZeros(int n, double* A, double*& B)
{
    int m = 0;
    for (int i = 0; i < n; i++)
        if (A[i] != 0.0) m++;

    B = new double[m];

    int j = 0;
    for (int i = 0; i < n; i++)
        if (A[i] != 0.0) B[j++] = A[i];

    return m;
}

void Solve_Task1_5_FromText_ToText(const char* inTxt, const char* outTxt)
{
    const int MAX = 560;
    double A[MAX];

    int n = ReadArrayTextFile(MAX, A, inTxt);
    if (n <= 0) { cout << "Error read: " << inTxt << "\n"; return; }

    double* B = nullptr;
    int m = Task1_5_RemoveZeros(n, A, B);

    if (m <= 0 || B == nullptr) {
        cout << "Task1#5: no data\n";
        return;
    }

    WriteArrayTextFile(m, B, outTxt);

    cout << "Task1#5 result (B without zeros), m=" << m << ":\n";
    for (int i = 0; i < m; i++) cout << B[i] << "   ";
    cout << "\n";

    cout << "Saved: " << outTxt << "\n";

    delete[] B;
}
// Task 2 №5
int Task2_5_MaxNegativeLessThanX(int n, double* A, double X, double& result)
{
    int found = 0;

    for (int i = 0; i < n; i++) {
        if (A[i] < 0 && A[i] < X) {
            if (!found) {
                result = A[i];
                found = 1;
            }
            else if (A[i] > result) {
                result = A[i];
            }
        }
    }
    return found;
}

void Solve_Task2_5_FromXFile_ToText(const char* inXTxt, const char* outTxt)
{
    const int MAX = 560;
    double A[MAX];
    double X;

    int n = ReadXandArrayFromText(inXTxt, MAX, X, A);

    cout << "X = " << X << "\n";
    cout << "A: ";
    for (int i = 0; i < n; i++) cout << A[i] << " ";
    cout << "\n";

    double ans = 0;
    int ok = Task2_5_MaxNegativeLessThanX(n, A, X, ans);

    ofstream fout(outTxt);
    if (!fout) {
        cout << "Error: cannot write " << outTxt << "\n";
        return;
    }

    if (ok) {
        fout << ans << "\n";
        cout << "Answer: " << ans << "\n";
    } else {
        fout << "No answer\n";
        cout << "No answer\n";
    }

    fout.close();
    cout << "Saved: " << outTxt << "\n";
}
void Task3_5(int n2, double* A, double& avg, double& sum)
{

    int n = n2 / 2;

    avg = 0.0;
    for (int i = 0; i < n; i++) avg += A[i];
    avg /= (double)n;

    sum = 0.0;
    for (int i = n; i < n2; i++)
        if (A[i] > avg) sum += A[i];

}

void Solve_Task3_5_FromZ_ToText(const char* inZTxt, const char* outTxt)
{
    const int MAX = 560;
    double A[MAX];
    int n = 0;

    int n2 = ReadZFile(inZTxt, MAX, n, A);
    if (n2 <= 0) { cout << "Error read: " << inZTxt << "\n"; return; }

    double avg = 0.0, sum = 0.0;
    Task3_5(n2, A, avg, sum);

    ofstream fout(outTxt);
    if (!fout) { cout << "Error write: " << outTxt << "\n"; return; }

        fout << "n=" << (n2 / 2) << "\n";
        fout << "avg=" << avg << "\n";
        fout << "sum=" << sum << "\n";

        cout << "Task3#5 result:\n";
        cout << "n = " << (n2 / 2) << "\n";
        cout << "avg(first half) = " << avg << "\n";
        cout << "sum(second half > avg) = " << sum << "\n";

    fout.close();
    cout << "Saved: " << outTxt << "\n";
}

// menu
void ShowMainMenu()
{
    cout << "\n===== MENU (Variant 5) =====\n";
    cout << "1) 3.1 Console -> ConsoleInput.txt\n";
    cout << "2) 3.2 Random -> RandomBIN.bin\n";
    cout << "3) 3.3 Solve Task1#5 (A1.txt -> B_no_zero.txt)\n";
    cout << "4) 3.3 Solve Task2#5 (X.txt -> Result2_5.txt)\n";
    cout << "5) 3.3 Solve Task3#5 (Z.txt -> Result3_5.txt)\n";
    cout << "6) 3.4 Print container from A1.txt\n";
    cout << "7) 3.4 Print container from RandomBIN.bin\n";
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
            case '1': Lab_3_1_TextInputAndSave("ConsoleInput.txt"); break;
            case '2': Lab_3_2_RandomAndSaveBin("RandomBIN.bin"); break;
            case '3': Solve_Task1_5_FromText_ToText("A1.txt", "B_no_zero.txt"); break;
            case '4': Solve_Task2_5_FromXFile_ToText("X.txt", "Result2_5.txt"); break;
            case '5': Solve_Task3_5_FromZ_ToText("Z.txt", "Result3_5.txt"); break;
            case '6': ReadTextToArrayAndPrint("A1.txt"); break;
            case '7': ReadBinToArrayAndPrint("RandomBIN.bin"); break;
            case '0': return 0;
            default: cout << "Wrong choice\n";
        }
    }
}