#ifndef CTRLC_WIN32_HPP
#define CTRLC_WIN32_HPP

#include <windows.h>
#include <iostream>
#include "ctrlc_signal.hpp"

using namespace std;


BOOL WINAPI SignalHandler(DWORD dwCtrlEvent)
{
    if (dwCtrlEvent == CTRL_C_EVENT)
    {
        EXIT_PROGRAM = true;
        return TRUE;
    }
    return FALSE;
}


void set_signal_handler()
{
    cout << "win32 signal handler setted" << endl;
    SetConsoleCtrlHandler(SignalHandler, TRUE);
}

#endif // CTRLC_WIN32_HPP
