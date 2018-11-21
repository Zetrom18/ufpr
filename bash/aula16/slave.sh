#!/bin/bash

error=$1
scriptDir="$(dirname "${BASH_SOURCE[0]}")"

count=$(xzcat $scriptDir/log-firewall.xz | grep -c $error)

if [ $count -ge 20000 ]
then
  echo "Error $error exceeded excpected ammount! - Total count: $count" | mail -s "Excessive error warning!" lrs13@inf.ufpr.br
fi
