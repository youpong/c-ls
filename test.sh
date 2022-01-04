#!/bin/bash

set -o nounset

program_name=$0

prog=./ls

tmpfile1=/tmp/${program_name##*/}1-$$
tmpfile2=/tmp/${program_name##*/}2-$$
tmpfile3=/tmp/${program_name##*/}3-$$
tmpfile4=/tmp/${program_name##*/}4-$$

function error() {
    echo "$@" >&2
    exit 1
}

#
# normal cases...
#

#
# return value checks
#
$prog             >/dev/null           || error "$LINENO: must return 0"
$prog .           >/dev/null           || error "$LINENO: must return 0"
$prog $prog       >/dev/null           || error "$LINENO: must return 0"
$prog ''          >/dev/null 2>&1      && error "$LINENO: must return 2"
$prog .     .     >/dev/null           || error "$LINENO: must return 0"
$prog .     $prog >/dev/null           || error "$LINENO: must return 0"
$prog $prog $prog >/dev/null           || error "$LINENO: must return 0"
$prog .     ''    >/dev/null 2>&1      && error "$LINENO: must return 2"

# compare output
cmp <($prog)             <(\ls -1)              || error "differ in $LINENO"

cmp <($prog .)           <(\ls -1 .)            || error "differ in $LINENO"
cmp <($prog $prog)       <(\ls -1 $prog)        || error "differ in $LINENO"

cmp <($prog . .)         <(\ls -1 . .)          || error "differ in $LINENO"
cmp <($prog . $prog)     <(\ls -1 . $prog)      || error "differ in $LINENO"
cmp <($prog $prog .)     <(\ls -1 $prog .)      || error "differ in $LINENO"
cmp <($prog $prog $prog) <(\ls -1 $prog $prog)  || error "differ in $LINENO"


#
# irregular cases...
#

# file not found
$prog '' 2>&1 | sed 's/^..//' > $tmpfile1
LANG=C \ls -1 '' 2>&1 | cmp - $tmpfile1         || error "differ in $LINENO"

# file, not found and dir
$prog '' . >$tmpfile1 2>$tmpfile2
sed -i 's/^..//' $tmpfile2
LANG=C \ls -1 '' . >$tmpfile3 2>$tmpfile4
cmp $tmpfile1 $tmpfile3                         || error "differ in $LINENO"
cmp $tmpfile2 $tmpfile4                         || error "differ in $LINENO"

# delete temporary files.
rm -f $tmpfile1 $tmpfile2 $tmpfile3 $tmpfile4    

echo "Ok."
