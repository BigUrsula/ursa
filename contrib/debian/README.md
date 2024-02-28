
Debian
====================
This directory contains files used to package ursad/ursa-qt
for Debian-based Linux systems. If you compile ursa/ursa-qt yourself, there are some useful files here.

## dash: URI support ##


ursa-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install ursa-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your dash-qt binary to `/usr/bin`
and the `../../share/pixmaps/ursa128.png` to `/usr/share/pixmaps`

ursa-qt.protocol (KDE)

