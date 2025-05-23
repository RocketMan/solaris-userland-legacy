# Apache 2.4 with Debian-Style Configuration for Solaris

This project ports Debian's modular Apache configuration system to
Solaris Apache, enabling `a2enmod`, `a2dismod`, `a2ensite`, `a2dissite`,
`a2enconf`, and `a2disconf` utilities, along with the expected
directory layout (`mods-available`, `mods-enabled`, `sites-available`,
etc.).

## Why Use Debian's Configuration System?

Debian's approach to Apache configuration is widely regarded as more
modular and manageable than traditional monolithic `httpd.conf`
files. It separates concerns cleanly:

- **Modules** are enabled/disabled with simple symlinks via `a2enmod` and `a2dismod`;
- **Virtual hosts** are organized into `sites-available` and `sites-enabled`, making it easier to manage staging and production sites;
- **Snippets** and auxiliary configurations (`conf-available`, `conf-enabled`) allow for clean reuse and override patterns.

This makes configuration more readable, more maintainable, and easier
to automate or audit — especially in environments where configurations
need to be changed or deployed frequently.

## Getting Started

To use this system on Solaris:

1. Build and install apache-24 from this repo.
2. Begin managing your Apache setup with Debian-style tools:

```bash
a2enmod rewrite
a2dissite 000-default
a2ensite my-site
svcadm restart apache24
```

In addition to the core configuration framework, companion packages
such as php74, php82, and php84 built from this repository install
modular, Debian-style Apache configuration snippets.  This allows you
to manage PHP integration using the familiar a2enmod and a2enconf
tools.  For example, to use PHP 8.4 as an Apache module, simply run:

```bash
a2enmod php8.4
svcadm restart apache24
```

Or, to configure Apache to work with PHP 8.4 via FPM instead:

```bash
a2dismod php8.4
a2enconf php8.4-fpm
a2enmod proxy_fcgi
svcadm enable php-fpm-84
svcadm restart apache24
```

This modular setup makes it easy to switch between PHP versions and
handler modes without editing httpd.conf directly.

## Acknowledgements

This project is based on the modular Apache configuration system
developed and maintained by the Debian Project.  Special thanks
to **Stefan Fritsch** <sf@debian.org> and the
[Debian Apache Maintainers](https://tracker.debian.org/pkg/apache2)
team for their work on the architecture and related tooling that
laid the foundation for this port.
