// systprakt9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
volatile int x=0;

volatile int count;

void thread() {
    while (x!='5') {
        count++;
        Sleep(1000);
        system("cls");
        std::cout << "Счетчик = " << count << std::endl;
        std::cout << "Выберите что вы хотите открыть\n1 - Microsoft Word \n2 - Microsoft Excel \n3 - Paint \n4 - Notepad \n5 - закрыть приложение" << std::endl;
        if (_kbhit()) {
            x = (int)_getch();
        }
        else {
        }
    }
}

int main()
{
    setlocale(0, "rus");
    int i = 0;

    wchar_t cmd[255] = L"C:\\Users\\admin\\OneDrive\\Рабочий стол\\Системное программирование\\systpract9-main\\systprakt9\\x64\\Debug\\childprocess.exe ";
    wchar_t symHandle[20];
    wchar_t lpszAppNameP[] = L"C:\\WINDOWS\\system32\\mspaint.exe";
    wchar_t lpszAppNameE[] = L"C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE";
    wchar_t lpszAppNameW[] = L"C:\\Program Files\\Microsoft Office\\root\\Office16\\WINWORD.EXE";
    wchar_t lpszAppNameN[] = L"C:\\WINDOWS\\system32\\notepad.exe";
    STARTUPINFO si;
    PROCESS_INFORMATION piApp;

    HANDLE hThread, hInheritThread;
    DWORD IDThread;

    hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0, NULL);
    
    if (hThread == NULL) {
        return GetLastError();
    }

    if (!DuplicateHandle(GetCurrentProcess(), hThread, GetCurrentProcess(), &hInheritThread, 0, TRUE, DUPLICATE_SAME_ACCESS)) {
        std::cout << "У потока нет дубликата" << std::endl;
        _getch();
        return GetLastError();
    }

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    _itow_s((int)hInheritThread, symHandle, 20);

    wcscat_s(cmd, symHandle);

    if (!CreateProcess(NULL, cmd, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp)) {
        std::cout << "Не получается создать новый процесс" << std::endl;
        std::cout << "Нажмите на любую клавишу чтобы дойти до конца" << std::endl;
        _getch();
        return GetLastError();
    }

    while (x != '5') {
        switch (x) {
        case 1:
            STARTUPINFO siW;
            PROCESS_INFORMATION piAppW;

            ZeroMemory(&siW, sizeof(STARTUPINFO));
            siW.cb = sizeof(STARTUPINFO);

            if (!CreateProcess(lpszAppNameW, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siW, &piAppW)) {
                std::cout << "Процесс не запустился";
                _getch();
                return 0;
            }
            std::cout << "Процесс запустился" << std::endl;

            WaitForSingleObject(piAppW.hProcess, INFINITE);

            CloseHandle(piAppW.hThread);
            CloseHandle(piAppW.hProcess);
            break;
        case 2:
            STARTUPINFO siE;
            PROCESS_INFORMATION piAppE;

            ZeroMemory(&siE, sizeof(STARTUPINFO));
            siE.cb = sizeof(STARTUPINFO);

            if (!CreateProcess(lpszAppNameE, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siE, &piAppE)) {
                std::cout << "Процесс не запустился";
                _getch();
                return 0;
            }
            std::cout << "Процесс запустился" << std::endl;

            WaitForSingleObject(piAppE.hProcess, INFINITE);

            CloseHandle(piAppE.hThread);
            CloseHandle(piAppE.hProcess);
            break;
        case 3:
            STARTUPINFO siP;
            PROCESS_INFORMATION piAppP;

            ZeroMemory(&siP, sizeof(STARTUPINFO));
            siP.cb = sizeof(STARTUPINFO);

            if (!CreateProcess(lpszAppNameP, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siP, &piAppP)) {
                std::cout << "Процесс не запустился";
                _getch();
                return 0;
            }
            std::cout << "Процесс запустился" << std::endl;

            WaitForSingleObject(piAppP.hProcess, INFINITE);

            CloseHandle(piAppP.hThread);
            CloseHandle(piAppP.hProcess);
            break;
        case 4:
            STARTUPINFO siN;
            PROCESS_INFORMATION piAppN;

            ZeroMemory(&siN, sizeof(STARTUPINFO));
            siN.cb = sizeof(STARTUPINFO);

            if (!CreateProcess(lpszAppNameN, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siN, &piAppN)) {
                std::cout << "Процесс не запустился";
                _getch();
                return 0;
            }
            std::cout << "Процесс запустился" << std::endl;

            WaitForSingleObject(piAppN.hProcess, INFINITE);

            CloseHandle(piAppN.hThread);
            CloseHandle(piAppN.hProcess);
            break;
        }
        WaitForSingleObject(piApp.hThread, INFINITE);
        CloseHandle(piApp.hProcess);
        CloseHandle(piApp.hThread);
        CloseHandle(hThread);
        return 0;
    }
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
