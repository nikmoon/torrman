#! /usr/bin/python2
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2017 nikbird <nikbird@server>
#
# Distributed under terms of the MIT license.

from __future__ import print_function

"""

"""
import libtorrent as lt
import os
import os.path as path
import shutil
import sys

torrentsDir = u'/home/nikbird/.config/deluge/state'

torrent_names = []


def get_torrents(dirPath):
    torrents = []
    for fileName in os.listdir(dirPath):
        if fileName.endswith(u'.torrent'):
            filePath = path.join(dirPath, fileName)
            torrents.append(filePath)
    return torrents
            


def save_by_name(torrents, destDir):
    for filePath in torrents:
        newFileName = lt.torrent_info(filePath).name().decode('utf-8') + u'.torrent'
        newFilePath = path.join(destDir, newFileName)
        if not path.exists(newFilePath):
            shutil.copyfile(filePath, newFilePath)


if __name__ == '__main__':

    if len(sys.argv) < 2:
        print(u'Укажите каталог назначения')
        sys.exit()

    destDir = sys.argv[1].decode('utf-8')
    if not path.exists(destDir):
        print(u'Такого каталога не существует')
        sys.exit()

    torrents = get_torrents(torrentsDir)
    save_by_name(torrents, destDir)


