/*
 * torrman.cpp
 * Copyright (C) 2017 nikbird <nikbird@server>
 *
 * Distributed under terms of the MIT license.
 */



#define BOOST_ASIO_SEPARATE_COMPILATION

#include <iostream>
#include <deque>
#include <time.h>

#include <libtorrent/session.hpp>
#include <libtorrent/torrent_info.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/alert_types.hpp>
#include "torrman.hpp"

namespace lt = libtorrent;
using namespace std;


int main(int argc, char *argv[])
{

    lt::session ses;
    ses.set_alert_mask(lt::alert::all_categories);
    lt::add_torrent_params atp;
    atp.ti = new lt::torrent_info("test.torrent");
    atp.save_path = "./downloads";
    ses.async_add_torrent(atp);

    std::deque<lt::alert*> alerts;
    for(;;)
    {
        ses.pop_alerts(&alerts);

        cout << "---------------------------------------------------------------------------------" << endl;
        cout << "Alerts count = " << alerts.size() << endl;

        std::deque<lt::alert*>::iterator it = alerts.begin();
        while (it != alerts.end())
        {
            cout << (*it)->message() << endl;
            it++;
        }

        ses.post_torrent_updates();
        sleep(3);
    }
    return 0;
}
