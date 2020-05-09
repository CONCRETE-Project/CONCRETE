
Debian
====================
This directory contains files used to package concreted/concrete-qt
for Debian-based Linux systems. If you compile concreted/concrete-qt yourself, there are some useful files here.

## concrete: URI support ##


concrete-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install concrete-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your concrete-qt binary to `/usr/bin`
and the `../../share/pixmaps/concrete128.png` to `/usr/share/pixmaps`

concrete-qt.protocol (KDE)

