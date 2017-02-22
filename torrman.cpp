/*
 * torrman.cpp
 * Copyright (C) 2017 nikbird <nikbird@server>
 *
 * Distributed under terms of the MIT license.
 */



#define BOOST_ASIO_SEPARATE_COMPILATION


#include <iostream>
#include <chrono>
#include <thread>
#include <deque>

#include <libtorrent/session.hpp>
#include <libtorrent/torrent_info.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/alert_types.hpp>

#include "ctrlc_signal.hpp"
#include "torrman.hpp"

namespace lt = libtorrent;
using namespace std;


int main(int argc, char *argv[])
{
    argc, argv;

    // настраиваем корректное завершение программы по Ctrl-C
    set_signal_handler();

    while (true)
    {
        this_thread::sleep_for(chrono::seconds(5));
        if (EXIT_PROGRAM) {
            break;
        }
    }
    cout << "Correct exit" << endl;
    return 0;

    lt::session ses;
//    ses.set_alert_mask(lt::alert::status_notification);
    ses.set_alert_mask(lt::alert::all_categories);
    lt::add_torrent_params atp;
    atp.ti = new lt::torrent_info("test.torrent");
    atp.save_path = "downloads";
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
//        sleep(5);
        this_thread::sleep_for(chrono::seconds(2));
//        if (EXIT_PROGRAM) {
//            break;
//        }
//        break;
    }
    cout << "Завершаем программу" << endl;
    return 0;
}
