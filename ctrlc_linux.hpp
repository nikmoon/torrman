#ifndef CTRLC_LINUX_HPP
#define CTRLC_LINUX_HPP

#include <iostream>
#include <signal.h>
#include "ctrlc_signal.hpp"

using namespace std;


void ctrl_c_handler(int s)
{
    EXIT_PROGRAM = true;
}



void set_signal_handler()
{
    cout << "linux signal handler setted" << endl;

    struct sigaction sigHandler;
    sigHandler.sa_handler = ctrl_c_handler;
    sigaction(SIGINT, &sigHandler, NULL);
}

#endif // CTRLC_LINUX_HPP
