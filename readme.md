# RUBIRC


RUBIRC is an IRC client for Windows and UNIX-like operating systems.  
See [IRCHelp.org](http://irchelp.org) for information about IRC in general.  
For more information on RUBIRC please read our [documentation](https://rubirc.readthedocs.org/en/latest/index.html):
- [Downloads](http://rubirc.github.io/downloads.html)
- [FAQ](https://rubirc.readthedocs.org/en/latest/faq.html)
- [Changelog](https://rubirc.readthedocs.org/en/latest/changelog.html)
- [Python API](https://rubirc.readthedocs.org/en/latest/script_python.html)
- [Perl API](https://rubirc.readthedocs.org/en/latest/script_perl.html)

---

[IMG]https://github.com/hackdynamics/rubirc/blob/main/rubirc-linux.png?raw=true[/IMG]

Ubuntu make:

apt install meson libcanberra-dev libdbus-glib-1-dev libglib2.0-dev libgtk2.0-dev libluajit-5.1-dev libpci-dev libperl-dev libssl-dev python3-dev python3-cffi mono-devel desktop-file-utils

meson build

ninja -C build

ninja -C build install

<sub>
X-Chat ("xchat") Copyright (c) 1998-2010 By Peter Zelezny.  
HexChat ("hexchat") Copyright (c) 2009-2014 By Berke Viktor.
RUBIRC ("rubirc") Copyright (c) 2023-2026 By Alexey Kuleshov.
</sub>

<sub>
This program is released under the GPL v2 with the additional exemption
that compiling, linking, and/or using OpenSSL is allowed. You may
provide binary packages linked to the OpenSSL libraries, provided that
all other requirements of the GPL are met.
See file COPYING for details.
</sub>
