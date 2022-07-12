## Firefox 102 for 11.3 [Unstable]

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

[Edit: Marked 'Unstable', as too many random sites are crashing,
relative to Firefox 91.  Once upstream has migrated to 102, will
review and adjust the patches as needed.]

### Firefox 102 esr

Using [slim-nimbus](https://github.com/RocketMan/solaris-ports/tree/master/components/look-and-feel/slim-nimbus)
and [firefox-nimbus-theme](https://github.com/RocketMan/firefox-nimbus-theme).
![screenshot](https://raw.githubusercontent.com/RocketMan/solaris-userland-legacy/master/components/desktop/firefox-102/screenshot.png "Firefox 102.0 esr")
