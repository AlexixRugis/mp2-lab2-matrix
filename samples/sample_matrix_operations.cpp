#include <iostream>
#include "tmatrix.h"

using namespace std;

int main()
{
    size_t m_size;

    cout << "Welcome to matrix calculator app!\n";

    cout << "Enter matrix size: ";
    cin >> m_size;

    TDynamicMatrix<int> a(m_size);

    cout << "Enter matrix (" << m_size << "x" << m_size << "):\n";
    cin >> a;

    int choice;
    cout << "Select operation:\n1 - Matrix addition\n2 - Matrix multiplication\n3 - Matrix-scalar multiplication\n4 - Matrix-vector multiplication\nYour choice: ";
    cin >> choice;

    if (choice == 1)
    {
        TDynamicMatrix<int> b(m_size);
        cout << "Enter second matrix (" << m_size << "x" << m_size << "):\n";
        cin >> b;
        cout << "Result:\n" << a + b;
    } else if (choice == 2)
    {
        TDynamicMatrix<int> b(m_size);
        cout << "Enter second matrix (" << m_size << "x" << m_size << "):\n";
        cin >> b;
        cout << "Result:\n" << a * b;
    } else if (choice == 3)
    {
        int m;
        cout << "Enter multiplicand: ";
        cin >> m;
        cout << "Result:\n" << a * m;
    } else if (choice == 4)
    {
        TDynamicVector<int> v(m_size);
        cout << "Enter " << m_size << "-dimensional vector:\n";
        cin >> v;
        cout << "Result:\n" << a * v;
    } else
    {
        cout << "Incorrect choice.\n";
    }

    return 0;
}
