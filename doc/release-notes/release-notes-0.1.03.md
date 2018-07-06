SLATE Core version *0.1.03* is now available from:

  <https://github.com/slatecurrency/slate/releases/tag/v0.1.0>

This is the first major version release, including new features, various
bugfixes and performance improvements, as well as updated translations.

Please report bugs using the issue tracker at GitHub:

  <https://github.com/slatecurrency/slate/issues>

How to Upgrade
==============

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes for older versions), then run the
installer (on Windows) or just copy over `/Applications/SLATE-Qt` (on Mac)
or `slated`/`slate-qt` (on Linux).

Compatibility
==============

SLATE Core is extensively tested on multiple operating systems using
the Linux kernel, macOS 10.8+, and Windows Vista and later. Windows XP is not supported.

SLATE Core should also work on most other Unix-like systems but is not
frequently tested on them.

Notable changes
===============

Do not allow generation of stakes with not enough coins
-------------------------------------------------------

Protections were in place to guard against stakes with more coins than the
expected amount, update this to also guard against stakes with less coins than
the expected amounts.

0.1.3 Change log
=================

- `18aba2b` Add new main and testnet checkpoints
- `b4d918d` Add new DNS seeders: US, EU, ASIA and AUSTRALIA
- `6a9b586` Update hardcoded nodes for main and testnet
- `3390460` Delete nodes_main.txt and nodes_test.txt
- `2cb84d3` Mark out check-doc.py for passing travis build checks
- `c38e98d` Bump version and updated documentatoin for master branch
- `b6d430c` Update release documentation v0.1.03

Credits
=======

Thanks to everyone who directly (or indirectly through cherry-picks) contributed
to this release:

- blockcig
- Cory Fields
- Fuzzbawls
- Gediminas
- gpdionisio
- Mrs-X
- presstab
- SHTDJ
- Slate Random Dev

As well as everyone that helped translating on Transifex.
