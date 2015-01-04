#
# spec file for package qwx
#
# Copyright (c) 2014 SUSE LINUX Products GmbH, Nuernberg, Germany.
# Copyright (c) 2014 hillwood <hillwood@opensuse.org>
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

%define qt5version 5.2

Name:           qwx
Summary:        WeChat for linux
Version:        0.0git20150104
Release:        1
License:        GPL-3.0
Url:            https://github.com/xiangzhai/qwx
Group:          Productivity/Networking/Instant Messenger
Source:        %{name}-%{version}.tar.bz2
%if 0%{?fedora}
BuildRequires:  qt5-qtbase-devel >= %{qt5version}
%endif
%if 0%{?suse_version}
BuildRequires:  libqt5-qtbase-common-devel >= %{qt5version}
%endif
BuildRequires:  pkgconfig(Qt5Xml) >= %{qt5version}
BuildRequires:  pkgconfig(Qt5Network) >= %{qt5version}
BuildRequires:  pkgconfig(Qt5QuickParticles) >= %{qt5version}
BuildRequires:  pkgconfig(Qt5Declarative) >= %{qt5version}
%if 0%{?suse_version}
Requires:       libqt5-qtquickcontrols >= %{qt5version}
%endif
%if 0%{?fedora}
Requires:       qt5-qtquickcontrols >= %{qt5version}
%endif
BuildRoot:      %{_tmppath}/%{name}-%{version}-build

%description
WeChat for linux, base with QT5.

%prep
%setup -q 

%build
qmake-qt5 QWX_DEBUG=ON
make

%install
mkdir -p %{buildroot}%{_bindir} 
install -D -m 0755 qwx %{buildroot}%{_bindir}/

%files 
%defattr(-, root, root, -)
%doc AUTHORS AUTHORS.md LICENSE
%{_bindir}/qwx

%changelog

