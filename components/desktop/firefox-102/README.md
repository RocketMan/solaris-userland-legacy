## Firefox 102 for 11.3

### Notes

* EGL/glx probing seems to use a later version of EGL than we have, so
  falls back to libpci (part of pciutils) to detect the GPU.  This requires
  elevated priveges, which we really should not give to the browser.

  As a result, we disable GPU detection via PCI.  If you want to enable
  it anyway, launch firefox with the MOZ_USE_PCI=1 environment variable.

* CSD and gtk3 theme are not being detected; if you want them, you will
  need to specify in the environment:

        GTK_CSD=1 GTK_THEME=slim-nimbus firefox

* During the build, it wants FFVPXRuntimeLinker.h, which
  is supplied in a later version of ffmpeg than the one we have (4.1.6).
  For now, we just disable this specific dependency.

* Relative to Firefox 91, you will need to upgrade the following
  dependencies:

  * **icu** 69.1 > **71.1**
  * **rustc, cargo** 1.51.0 -> **1.59.0** (for building only)
  * **cbindgen** 0.19.0 > **0.23.0** (for building only)

* **cups 1.6** or later is required at runtime for printing.  Firefox
  will build and run without this, but any attempt to print using an
  older CUPS will result in SIGSEGV.

### Firefox 102 esr

Using [slim-nimbus](https://github.com/RocketMan/solaris-ports/tree/master/components/look-and-feel/slim-nimbus)
and [firefox-nimbus-theme](https://github.com/RocketMan/firefox-nimbus-theme).
![screenshot](https://raw.githubusercontent.com/RocketMan/solaris-userland-legacy/master/components/desktop/firefox-102/screenshot.png "Firefox 102.0 esr")
