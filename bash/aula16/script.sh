#!/bin/bash

scriptDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

# xargs executes given program (last parameter) using the stdin as the programs parameter
# the options are used to indicate that the maximum number of threads possible is used and only one parameter is passed at a time
cat $scriptDir/tipos-bloqueios | xargs -P 0 -n 1 $scriptDir/slave.sh

# This section is a for with the intention to execute multiple processes at the same time
# for error in $(cat $scriptDir/tipos-bloqueios)
# do
# 	echo "$error: $(xzcat $scriptDir/log-firewall.xz | grep -c $error)" &
# done
#
# wait
