# Guarantee all files are new
rm /home/bcc/lrs13/bash/aula11/counts/*

counts="/home/bcc/lrs13/bash/aula11/counts"
dir="/home/bcc/lrs13/nobackup/DadosMatricula"
re='^[0-9]+$'
arr=()

for discip in $(ls $dir/)
do
	for perio in $(ls $dir/$discip)
	do
		file=$(echo $perio | sed "s/\..*//g")
		touch $counts/$file
		arr=($(cat $counts/$file))
		grrList=$(cat $dir/$discip/$perio | cut -f 2 -d ':')
		for grr in $grrList
		do
			if [[ $grr =~ $re ]]
			then
				found=false
				for ra in ${arr[@]}
				do
					if [[ $ra = $grr ]]
					then
						found=true
						break
					fi
				done
				if [[ $found =  false ]]
				then
					arr=("${arr[@]}" "$grr")
				fi
			fi
		done
		echo ${arr[@]} > $counts/$file
	done
done

for perio in $(ls $counts/)
do
	echo "$perio:$(cat $counts/$perio | wc -w)"
done

