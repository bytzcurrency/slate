#!/usr/bin/env bash
#
# Copyright (c) 2018 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C


#contrib/devtools/git-subtree-check.sh src/secp256k1
#contrib/devtools/git-subtree-check.sh src/univalue
#contrib/devtools/git-subtree-check.sh src/leveldb
#contrib/devtools/check-doc.py
test/lint/logprint-scanner.py

if [ "$TRAVIS_EVENT_TYPE" = "pull_request" ]; then
  test/lint/lint-whitespace.sh
fi
