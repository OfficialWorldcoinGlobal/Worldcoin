#!/usr/bin/env bash

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

WORLDCOIND=${WORLDCOIND:-$BINDIR/worldcoind}
WORLDCOINCLI=${WORLDCOINCLI:-$BINDIR/worldcoin-cli}
WORLDCOINTX=${WORLDCOINTX:-$BINDIR/worldcoin-tx}
WORLDCOINQT=${WORLDCOINQT:-$BINDIR/qt/worldcoin-qt}

[ ! -x $WORLDCOIND ] && echo "$WORLDCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
WDCVER=($($WORLDCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for worldcoind if --version-string is not set,
# but has different outcomes for worldcoin-qt and worldcoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$WORLDCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $WORLDCOIND $WORLDCOINCLI $WORLDCOINTX $WORLDCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${WDCVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${WDCVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
