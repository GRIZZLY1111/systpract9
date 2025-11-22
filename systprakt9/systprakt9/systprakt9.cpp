// systprakt9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
volatile int x=0;

volatile int count;

DWORD WINAPI thread() {
    while (true) {
        count++;
        Sleep(1000);
        system("cls");
        std::cout << "Счетчик = " << count << std::endl;
        std::cout << "Выберите что вы хотите открыть\n1 - Microsoft Word \n2 - Microsoft Excel \n3 - Paint \n4 - Notepad\n5 - Microsoft Word \n6 - Microsoft Excel \n7 - Paint \n8 - Notepad  \n9 - закрыть приложение" << std::endl;
    }
    return 0;
}

int main()
{
    setlocale(0, "rus");
    int i = 0;

    HANDLE hThread, hInheritThread;
    DWORD IDThread;
    wchar_t cmd[255] = L"C:\\Users\\st310-08\\Desktop\\systpract9-main\\systprakt9\\x64\\Debug\\childprocess.exe ";
    wchar_t symHandle[255] = L"";
    wchar_t lpszAppNameP[] = L"C:\\WINDOWS\\system32\\mspaint.exe";
    wchar_t lpszAppNameE[] = L"C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE";
    wchar_t lpszAppNameW[] = L"C:\\Program Files\\Microsoft Office\\root\\Office16\\WINWORD.EXE";
    wchar_t lpszAppNameN[] = L"C:\\WINDOWS\\system32\\notepad.exe";
    STARTUPINFO si;
    PROCESS_INFORMATION piApp;

    hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, HANDLE_FLAG_INHERIT, &IDThread);
    
    if (hThread == NULL) {
        return GetLastError();
    }

    if (!SetHandleInformation(hThread, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT)) {
        return GetLastError();
    }

    if (!DuplicateHandle(GetCurrentProcess(), hThread, GetCurrentProcess(), &hInheritThread, 0, TRUE, DUPLICATE_SAME_ACCESS)) {
        std::cout << "У потока нет дубликата" << std::endl;
        _getch();
        return GetLastError();
    }

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    _itow_s((int)hInheritThread, symHandle, 10);

    wcscat_s(cmd, symHandle);

    if (!CreateProcess(NULL, cmd, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp)) {
        std::cout << "Не получается создать новый процесс" << std::endl;
        std::cout << "Нажмите на любую клавишу чтобы дойти до конца" << std::endl;
        _getch();
        return GetLastError();
    }
    STARTUPINFO siW;
    PROCESS_INFORMATION piAppW;
    STARTUPINFO siE;
    PROCESS_INFORMATION piAppE;
    STARTUPINFO siP;
    PROCESS_INFORMATION piAppP;
    STARTUPINFO siN;
    PROCESS_INFORMATION piAppN;
    piAppW.hProcess = NULL;
    piAppE.hProcess = NULL;
    piAppP.hProcess = NULL;
    piAppN.hProcess = NULL;
    while (true) {
        char x = _getch();
        switch (x) {
        case '1':
            ZeroMemory(&siW, sizeof(STARTUPINFO));
            siW.cb = sizeof(STARTUPINFO);

            if (!CreateProcess(lpszAppNameW, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siW, &piAppW)) {
                std::cout << "Процесс не запустился";
                _getch();
                return 0;
            }
            std::cout << "Процесс запустился" << std::endl;

            break;
        case '2':

            ZeroMemory(&siE, sizeof(STARTUPINFO));
            siE.cb = sizeof(STARTUPINFO);

            if (!CreateProcess(lpszAppNameE, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siE, &piAppE)) {
                std::cout << "Процесс не запустился";
                _getch();
                return 0;
            }
            std::cout << "Процесс запустился" << std::endl;

            break;
        case '3':

            ZeroMemory(&siP, sizeof(STARTUPINFO));
            siP.cb = sizeof(STARTUPINFO);

            if (!CreateProcess(lpszAppNameP, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siP, &piAppP)) {
                std::cout << "Процесс не запустился";
                _getch();
                return 0;
            }
            std::cout << "Процесс запустился" << std::endl;
            break;
        case '4':

            ZeroMemory(&siN, sizeof(STARTUPINFO));
            siN.cb = sizeof(STARTUPINFO);

            if (!CreateProcess(lpszAppNameN, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siN, &piAppN)) {
                std::cout << "Процесс не запустился";
                _getch();
                return 0;
            }
            std::cout << "Процесс запустился" << std::endl;
            break;
        case '5':
            if (piAppW.hProcess != NULL) {
                TerminateProcess(piAppW.hProcess, 0);
                CloseHandle(piAppW.hProcess);
                CloseHandle(piAppW.hThread);
                piAppW.hProcess = NULL;
            }
            break;
        case '6':
            if (piAppE.hProcess != NULL) {
                TerminateProcess(piAppE.hProcess, 0);
                CloseHandle(piAppE.hProcess);
                CloseHandle(piAppE.hThread);
                piAppE.hProcess = NULL;
            }
            break;
        case '7':
            if (piAppP.hProcess != NULL) {
                TerminateProcess(piAppP.hProcess, 0);
                CloseHandle(piAppP.hProcess);
                CloseHandle(piAppP.hThread);
                piAppP.hProcess = NULL;
            }
            break;
        case '8':
            if (piAppN.hProcess != NULL) {
                TerminateProcess(piAppN.hProcess, 0);
                CloseHandle(piAppN.hProcess);
                CloseHandle(piAppN.hThread);
                piAppN.hProcess = NULL;
            }
            break;
        case '9':
            ExitProcess(0);
            break;

        }
    }
        WaitForSingleObject(piApp.hThread, INFINITE);
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
