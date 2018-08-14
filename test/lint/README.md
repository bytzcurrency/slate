This folder contains lint scripts.

check-doc.py
============
Check for missing documentation of command line options.

logprint-scanner.py
===================
LogPrint and LogPrintf are known to throw exceptions when the number of arguments supplied to the
LogPrint(f) function is not the same as the number of format specifiers.

Ideally, the presentation of this mismatch would be at compile-time, but instead it is at run-time.

This script scans the src/ directory recursively and looks in each .cpp/.h file and identifies all
errorneous LogPrint(f) calls where the number of arguments do not match.

The filename and line number of the errorneous occurence is given.

The script returns with the number of erroneous occurences as an error code to help facilitate
integration with a continuous integration system.

The script can be ran from any working directory inside the git repository.

lint-all.sh
===========
Calls other scripts with the `lint-` prefix.
