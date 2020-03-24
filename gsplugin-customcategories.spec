#
# spec file for package gsplugin-customcategories
#
# Copyright (c) 2020 SUSE LINUX GmbH, Nuernberg, Germany.
#
# All modifications and additions to the file contributed by third parties
# remain the property of their copyright owners, unless otherwise agreed
# upon. The license for this file, and modifications and additions to the
# file, is the same license as for the pristine package itself (unless the
# license for the pristine package is not an Open Source License, in which
# case the license is the MIT License). An "Open Source License" is a
# license that conforms to the Open Source Definition (Version 1.9)
# published by the Open Source Initiative.

# Please submit bugfixes or comments via http://bugs.opensuse.org/
#


Name:           gsplugin-customcategories
Version:        1.0
Release:        0
Summary:	Plugin that adds custom categories to GNOME Software
License:        MIT
Group:          System/GUI/GNOME
Url:            https://github.com/doccaz/gsplugin-customcategories.git
Source:         %{name}-%{version}.tar.xz
BuildRequires:  glibc-devel
BuildRequires:	autoconf
BuildRequires:	automake
BuildRoot:      %{_tmppath}/%{name}-%{version}-build

%description
This plugin adds custom categories to GNOME Software, based on specific non-standard desktop categories (e.g. "X-SuSE-YaST").

%prep
%setup -q

%build
autoreconf -vfi
%configure
make %{?_smp_mflags}

%install
%make_install

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%defattr(-,root,root)
%doc ChangeLog README README.md COPYING
%{_datadir}/pixmaps/*
%{_libdir}/*


%changelog

