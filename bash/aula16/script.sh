#!/bin/bash

sourceDir="/home/bcc/lrs13/ufpr/bash/aula16"

for error in $(cat $sourceDir/tipos-bloqueios)
do
	echo "$error: $(xzcat $sourceDir/log-firewall.xz | grep -c $error)" &
done

wait
