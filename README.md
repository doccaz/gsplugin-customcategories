# Custom Categories Plugin

This plugin for GNOME Software creates adds programs with custom categories to the store.


## Installation

**Clone repo**

```bash
git clone git@github.com:doccaz/gsplugin-customcategories/gsplugin-customcategories.git
cd gsplugin-customcategories
```

**Configuration**

Constructing configuration and Makefiles

```bash
autoreconf -vfi
./configure
```

**Compiling/ Linking**

Compile and install the library to GNOME Software's default plugin directory (`/usr/lib64/gs-plugins-11`)

```bash
sudo make install
```


## Using the plugin

Just start gnome-software. You can check if it was loaded correctly by examining the output of `gnome-software -v`.

## Removing Clutter

You have to become root to cleanup, because `sudo make install` generates `src/.libs/*`.

```bash
sudo sh cleanup.sh
```

## Uninstalling the plugin

```bash
sudo make uninstall
```

