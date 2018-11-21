#!/bin/bash

scriptDir="$(dirname "${BASH_SOURCE[0]}")"

# xargs executes given program (last parameter) using the stdin as the programs parameter
# the options are used to indicate that the maximum number of threads possible is used and only one parameter is passed at a time
cat $scriptDir/tipos-bloqueios | xargs -P 0 -n 1 $scriptDir/slave.sh

