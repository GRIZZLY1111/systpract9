// systempract9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
volatile int x = 0;

volatile int count;

DWORD WINAPI thread() {
    while (true) {
        count++;
        Sleep(1000);
        system("cls");
        std::cout << "Счетчик = " << count << std::endl;
        std::cout << "Выберите что вы хотите открыть\n1 - Microsoft Word \n2 - Microsoft Excel \n3 - Paint \n4 - Notepad\n5 - Закрыть Microsoft Word \n6 - Закрыть Microsoft Excel \n7 - Закрыть Paint \n8 - Закрыть Notepad  \n9 - Закрыть приложение" << std::endl;
    }
    return 0;
}

int main()
{
    setlocale(0, "rus");
    int i = 0;

    HANDLE hThread, hInheritThread;
    DWORD IDThread;
    wchar_t cmd[255] = L"C:\\Users\\328-10\\Desktop\\systempract9\\Debug\\childprocess.exe ";
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
    STARTUPINFO siW[5];
    PROCESS_INFORMATION piAppW[5];
    int W = 0;
    STARTUPINFO siE;
    PROCESS_INFORMATION piAppE[5];
    int E = 0;
    STARTUPINFO siP;
    PROCESS_INFORMATION piAppP[5];
    int P = 0;
    STARTUPINFO siN;
    PROCESS_INFORMATION piAppN[5];
    int N = 0;
    piAppW[0].hProcess = NULL;
    piAppE[0].hProcess = NULL;
    piAppP[0].hProcess = NULL;
    piAppN[0].hProcess = NULL;
    while (true) {
        char x = _getch();
        switch (x) {
        case '1':

            ZeroMemory(&siW[W], sizeof(STARTUPINFO));
            siW[W].cb = sizeof(STARTUPINFO);

            if (!CreateProcess(lpszAppNameW, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siW[W], &piAppW[W])) {
                std::cout << "Процесс не запустился";
                _getch();
                return 0;
            }
            W++;
            std::cout << "Процесс запустился" << std::endl;

            break;
        case '2':

            ZeroMemory(&siE, sizeof(STARTUPINFO));
            siE.cb = sizeof(STARTUPINFO);

            if (!CreateProcess(lpszAppNameE, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siE, &piAppE[E])) {
                std::cout << "Процесс не запустился";
                _getch();
                return 0;
            }
            E++;
            std::cout << "Процесс запустился" << std::endl;

            break;
        case '3':

            ZeroMemory(&siP, sizeof(STARTUPINFO));
            siP.cb = sizeof(STARTUPINFO);

            if (!CreateProcess(lpszAppNameP, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siP, &piAppP[P])) {
                std::cout << "Процесс не запустился";
                _getch();
                return 0;
            }
            P++;
            std::cout << "Процесс запустился" << std::endl;
            break;
        case '4':

            ZeroMemory(&siN, sizeof(STARTUPINFO));
            siN.cb = sizeof(STARTUPINFO);

            if (!CreateProcess(lpszAppNameN, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siN, &piAppN[N])) {
                std::cout << "Процесс не запустился";
                _getch();
                return 0;
            }
            N++;
            std::cout << "Процесс запустился" << std::endl;
            break;
        case '5':
            if (W == 0) {
            }
            else if (piAppW[W-1].hProcess != NULL) {
                W--;
                TerminateProcess(piAppW[W].hProcess, 0);
                CloseHandle(piAppW[W].hProcess);
                CloseHandle(piAppW[W].hThread);
                piAppW[W].hProcess = NULL;

            }
            break;
        case '6':
            if (E == 0) {
            }
            else if (piAppE[E - 1].hProcess != NULL) {
                E = E - 1;
                TerminateProcess(piAppE[E].hProcess, 0);
                CloseHandle(piAppE[E].hProcess);
                CloseHandle(piAppE[E].hThread);
                piAppE[E].hProcess = NULL;
            }
            break;
        case '7':
            if (P == 0) {
            }
            else if (piAppP[P - 1].hProcess != NULL) {
                P--;
                TerminateProcess(piAppP[P].hProcess, 0);
                CloseHandle(piAppP[P].hProcess);
                CloseHandle(piAppP[P].hThread);
                piAppP[P].hProcess = NULL;
            }
            break;
        case '8':
            if (N == 0) {
            }
            else if (piAppN[N - 1].hProcess != NULL) {
                N--;
                TerminateProcess(piAppN[N].hProcess, 0);
                CloseHandle(piAppN[N].hProcess);
                CloseHandle(piAppN[N].hThread);
                piAppN[N].hProcess = NULL;
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
