
Debian
====================
This directory contains files used to package slated/slate-qt
for Debian-based Linux systems. If you compile slated/slate-qt yourself, there are some useful files here.

## slate: URI support ##


slate-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install slate-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your slateqt binary to `/usr/bin`
and the `../../share/pixmaps/slate128.png` to `/usr/share/pixmaps`

slate-qt.protocol (KDE)

