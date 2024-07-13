## Firefox 128 esr for 11.3

### Notes

* There are no new dependencies for this release.

* On Solaris 11.3, the new ZSTD compression is raising an exception.
In the build from this repo, it has been disabled by default.

* Effective 128esr, Firefox Solaris identifies itself as 'Linux' via the
User-Agent request header.  See https://bugzilla.mozilla.org/show_bug.cgi?id=1861847

* If you are using GNOME 2 and want Firefox to detect your gtk3 theme,
specify in the environment `GTK_CSD=1` and `XDG_CURRENT_DESKTOP=MATE`.

### Screenshots

Using [slim-nimbus](https://github.com/RocketMan/solaris-ports/tree/master/components/look-and-feel/slim-nimbus)
and [firefox-nimbus-theme](https://github.com/RocketMan/firefox-nimbus-theme).
![screenshot](https://raw.githubusercontent.com/RocketMan/solaris-userland-legacy/master/components/desktop/firefox-128/screenshot.png "Firefox 128.0 esr")
