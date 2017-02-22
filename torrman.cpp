/*
 * torrman.cpp
 * Copyright (C) 2017 nikbird <nikbird@server>
 *
 * Distributed under terms of the MIT license.
 */



#define BOOST_ASIO_SEPARATE_COMPILATION

#include <iostream>
#include <ctime>
#include <deque>
#include <signal.h>
#include <cstdlib>

#include <libtorrent/session.hpp>
#include <libtorrent/torrent_info.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/alert_types.hpp>
#include "torrman.hpp"

namespace lt = libtorrent;
using namespace std;

bool EXIT_PROGRAM = false;


void ctrl_c_handler(int s)
{
    EXIT_PROGRAM = true;
}


int main(int argc, char *argv[])
{
    // настраиваем корректное завершение программы по Ctrl-C
    struct sigaction sigHandler;
    sigHandler.sa_handler = ctrl_c_handler;
    sigaction(SIGINT, &sigHandler, NULL);

    lt::session ses;
    ses.set_alert_mask(lt::alert::status_notification);
    lt::add_torrent_params atp;
    atp.ti = new lt::torrent_info("test.torrent");
    atp.save_path = "./downloads";
    ses.async_add_torrent(atp);

    std::deque<lt::alert*> alerts;
    for(;;)
    {
        ses.pop_alerts(&alerts);

//        cout << "Alerts count = " << alerts.size() << endl;

        for(const auto *alert: alerts)
        {
            cout << "message: \"" << alert->message() << "\"  ";
            cout << "type: \"" << alert->what() << "\"" << endl;
//            if (alert->type() == lt::state_changed_alert::alert_type)
//            {
//                cout << alert->message() << endl;
//            }
        }
//        std::deque<lt::alert*>::iterator it = alerts.begin();
//        while (it != alerts.end())
//        {
//            cout << (*it)->message() << endl;
//            it++;
//        }

//        ses.post_torrent_updates();
        sleep(5);
        if (EXIT_PROGRAM) {
            break;
        }
    }
    cout << "Завершаем программу" << endl;
    return 0;
}
