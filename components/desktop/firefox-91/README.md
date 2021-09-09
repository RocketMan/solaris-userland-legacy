## Firefox 91 for 11.3

### Notes

* EGL/glx probing seems to use a later version of EGL than we have, so
  falls back to libpci (part of pciutils) to detect the GPU.  This requires
  elevated priveges, which we really should not give to the browser.

  **WORKAROUND:**

  Launch firefox with the locally added MOZ_AVOID_PCI_SCAN env variable:
  
        MOZ_AVOID_PCI_SCAN=1 firefox

  This lets it get past the PCI scan; it then seems to continue OK;
  one can successfuly run the WebAssembly tanks demo, for example.
  
* CSD and gtk3 theme are not being detected; if you want them, you will
  need to specify in the environment:

        GTK_CSD=1 GTK_THEME=slim-nimbus MOZ_AVOID_PCI_SCAN=1 firefox

* By default, Firefox 91 uses a non-native theme, which displays Adwaita-
  like scrollbars, etc.  You can disable this in about:config by changing
  the property `widget.non-native-theme.enabled` to `false`.

* During the build, it wants FFVPXRuntimeLinker.h, which
  is supplied in a later version of ffmpeg than the one we have (4.1.6).
  For now, we just disable this specific dependency.

* Relative to Firefox 78, you will need to upgrade the following
  dependencies:

  * **icu** 67.1 > **69.1** (see note below)
  * **pixman** 0.34.0 > **0.38.4**
  * **rustc, cargo** 1.45.0 -> **1.51.0** (for building only)
  * **cbindgen** 0.14.4 > **0.19.0** (for building only)

  NOTE: The icu upgrade to 69.1 breaks ABI compatibility
  in some other applications such as Thunderbird 78.  Rebuilding
  those with the updated icu should clear any problem.

* **cups 1.6** or later is required at runtime for printing.  Firefox
  will build and run without this, but any attempt to print using an
  older CUPS will result in SIGSEGV.

### Firefox 91 esr

Using [slim-nimbus](https://github.com/RocketMan/solaris-ports/tree/master/components/look-and-feel/slim-nimbus)
and [firefox-nimbus-theme](https://github.com/RocketMan/firefox-nimbus-theme).
![screenshot](https://raw.githubusercontent.com/RocketMan/solaris-userland-legacy/master/components/desktop/firefox-91/screenshot.png "Firefox 91.0.1 esr")
