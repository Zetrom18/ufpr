#!/bin/bash

error=$1
scriptDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

count=$(xzcat $scriptDir/log-firewall.xz | grep -c $error)

if [ $count -ge 20000 ]
then
  echo "over"
fi

echo "$error: $count"
