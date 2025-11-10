// childprocess.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>

int main(int argc, char* argv[])
{
    setlocale(0, "rus");
    wchar_t lpszAppName[] = L"C:\\Users\\st310-08\\Desktop\\Солихов\\systprakt9\\x64\\Debug\\childprocess.exe";
    STARTUPINFO si;
    PROCESS_INFORMATION piApp;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp)) {
        std::cout << "Процесс не запустился";
        _getch();
        return 0;
    }
    std::cout << "Процесс запустился" << std::endl;
    int i = 0;

    while (i < 10) {
        std::cout << i << std::endl;
        Sleep(1000);
        i++;
    }
    while (true) {
        char c;
        std::cout << "Введите букву t для завершения потока" << std::endl;
        std::cin >> c;
        if (c == 't') {
            TerminateProcess(piApp.hProcess, 1);
            break;
        }
    }

    WaitForSingleObject(piApp.hProcess, INFINITE);

    CloseHandle(piApp.hThread);
    CloseHandle(piApp.hProcess);
    return 0;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
