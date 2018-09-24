#!/bin/bash

error=$1
scriptDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

count=$(xzcat $scriptDir/log-firewall.xz | grep -c $error)

if [ $count -ge 20000 ]
then
  # todo - create real mail
  echo "Error $error exceeded excpected ammount!\nTotal count: $count" | mail -s "Excessive error warning!" lrs13@inf.ufpr.br
fi
