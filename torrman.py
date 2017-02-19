#
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2017 nikbird <nikbird@server>
#
# Distributed under terms of the MIT license.

"""

"""
from __future__ import print_function
from __future__ import division

import libtorrent as lt
import time
import datetime as dt

KB = 1000
MB = KB * 1000
GB = MB * 1000

def print_info(s):
    #print(s.state, int(s.state) )
    #print('{} complete(down: {} kB/s up: {} kB/s peers: {}) {}'.format(s.progress * 100,
    #    s.download_rate / 1000, s.upload_rate / 1000, s.num_peers, states[s.state]))
    tpdMB = round(s.total_payload_download / MB, 2)
    tpdGB = round(s.total_payload_download / GB, 2)
    tpuMB = round(s.total_payload_upload / MB, 2)
    tpuGB = round(s.total_payload_upload / GB, 2)
    dr = round(s.download_rate / KB, 1)
    ur = round(s.upload_rate / KB, 1)
    print(dt.datetime.now().strftime('%d.%m.%y %H:%M:%S'), end=" ")
    print(u'{}, скачано: {} МБ ({} ГБ), отдано: {} МБ ({} ГБ), down {} КБ/с, up {} КБ/с, ps/ss: {}/{}'.format(s.state,
        tpdMB, tpdGB, tpuMB, tpuGB, dr, ur, s.num_peers, s.num_seeds))


session = lt.session()

session.set_alert_mask(lt.alert.category_t.all_categories ^ lt.alert.category_t.stats_notification)

session.listen_on(6892, 6902)

e = lt.bdecode(open('test.torrent', 'rb').read())
info = lt.torrent_info(e)


params = {
    'save_path': u'.',
    'storage_mode': lt.storage_mode_t.storage_mode_allocate,
    'ti': info
}

h = session.add_torrent(params)

while 1:
#    s = h.status()
#    session.post_torrent_updates()

    alerts = session.pop_alerts()
    if alerts:
        for alert in alerts:
            print(dt.datetime.now().strftime('%d.%m.%y %H:%M:%S'), end=" ")
            print(alert.message(), type(alert))
            if hasattr(alert, 'status'):
                for s in alert.status:
                    print_info(s)
#    else:
#        print(u'Состояние торрентов не изменилось')

#    print_info(s)
    time.sleep(2)
#    print(dt.datetime.now().strftime('%d.%m.%y %H:%M:%S'))



