
Debian
====================
This directory contains files used to package chipod/chipo-qt
for Debian-based Linux systems. If you compile chipod/chipo-qt yourself, there are some useful files here.

## chipo: URI support ##


chipo-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install chipo-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your chipo-qt binary to `/usr/bin`
and the `../../share/pixmaps/chipo128.png` to `/usr/share/pixmaps`

chipo-qt.protocol (KDE)

