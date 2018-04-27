#!/bin/bash

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

SLATED=${SLATED:-$BINDIR/slated}
SLATECLI=${SLATECLI:-$BINDIR/slate-cli}
SLATETX=${SLATETX:-$BINDIR/slate-tx}
SLATEQT=${SLATEQT:-$BINDIR/qt/slate-qt}

[ ! -x $SLATED ] && echo "$SLATED not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
SLXVER=($($SLATECLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for slated if --version-string is not set,
# but has different outcomes for slate-qt and slate-cli.
echo "[COPYRIGHT]" > footer.h2m
$SLATED --version | sed -n '1!p' >> footer.h2m

for cmd in $SLATED $SLATECLI $SLATETX $SLATEQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${SLXVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${SLXVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
