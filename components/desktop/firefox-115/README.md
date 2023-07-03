## Firefox 115 esr for 11.3

### Notes

* There are no new dependencies for this release.

* If you are using GNOME 2 and want Firefox to detect your gtk3 theme,
specify in the environment:

	XDG_CURRENT_DESKTOP=MATE

(It is no longer necessary to specify the GTK_CSD and GTK_THEME environment
variables.)

* EGL/glx probing seems to use a later version of EGL than we have, so
  falls back to libpci (part of pciutils) to detect the GPU.  This requires
  elevated priveges, which we really should not give to the browser.

  As a result, we disable GPU detection via PCI.  If you want to enable
  it anyway, launch firefox with the MOZ_USE_PCI=1 environment variable.

### Screenshots

Using [slim-nimbus](https://github.com/RocketMan/solaris-ports/tree/master/components/look-and-feel/slim-nimbus)
and [firefox-nimbus-theme](https://github.com/RocketMan/firefox-nimbus-theme).
![screenshot](https://raw.githubusercontent.com/RocketMan/solaris-userland-legacy/master/components/desktop/firefox-115/screenshot.png "Firefox 115.0 esr")
