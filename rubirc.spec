%define _unpackaged_files_terminate_build 1
%define _stripped_files_terminate_build 1
%set_verify_elf_method strict,unresolved=relaxed

Summary: A popular and easy to use graphical IRC (chat) client
Name: rubirc
Version: 3.16.4
Release: alt2
License: GPLv2+
Group: Networking/IRC
Url: http://rubirc.net
VCS: https://github.com/hackdynamics/rubirc.git
Source: %name-%version.tar

BuildRequires(pre): rpm-build-python3
BuildRequires: meson
BuildRequires: pkgconfig(glib-2.0)
BuildRequires: pkgconfig(gtk+-2.0)
BuildRequires: pkgconfig(dbus-glib-1)
BuildRequires: pkgconfig(libcanberra)
BuildRequires: pkgconfig(libnotify)
BuildRequires: pkgconfig(libproxy-1.0)
BuildRequires: pkgconfig(iso-codes)
BuildRequires: pkgconfig(openssl)
BuildRequires: pkgconfig(python3)
BuildRequires: pkgconfig(libpci)
BuildRequires: pkgconfig(lua)
BuildRequires: perl-devel perl(ExtUtils/Embed.pm)
BuildRequires: python3(cffi)
BuildRequires: python3(setuptools)

Requires: enchant2

Provides: xchat = %EVR
Obsoletes: xchat
Provides: xchat2 = %EVR
Obsoletes: xchat2

%add_python3_path %_libdir/rubirc/python

%add_python3_req_skip _rubirc_embedded

%description
RUBIRC is an easy to use graphical IRC chat client for the X Window System.
It allows you to join multiple IRC channels (chat rooms) at the same time,
talk publicly, private one-on-one conversations etc. Even file transfers
are possible.

%package devel
Summary: Development files for %name
Group: Development/C++
Requires: %name = %EVR

%description devel
This package contains the development files for %name.

%prep
%setup

%build
%meson -Dwith-lua=lua
%meson_build

%install
%meson_install

%find_lang %name

%files -f %name.lang
%doc COPYING readme.md
%_bindir/rubirc
%dir %_libdir/rubirc
%dir %_libdir/rubirc/plugins
%_libdir/rubirc/plugins/checksum.so
%_libdir/rubirc/plugins/fishlim.so
%_libdir/rubirc/plugins/lua.so
%_libdir/rubirc/plugins/sysinfo.so
%_libdir/rubirc/plugins/perl.so
%_libdir/rubirc/plugins/python.so
%_libdir/rubirc/python
%_desktopdir/*.desktop
%_iconsdir//hicolor/*/apps/*
%_datadir/metainfo/*.appdata.xml
%_datadir/dbus-1/services/org.rubirc.service.service
%_man1dir/*

%files devel
%_includedir/*
%_pkgconfigdir/*

%changelog

