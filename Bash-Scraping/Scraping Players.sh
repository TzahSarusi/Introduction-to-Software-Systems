#!/bin/bash
# counts how many players we have with the "Midfielder" role.
rm player_results.csv
wget https://www.premierleague.com/players
grep -Eo "players\/[0-9]+\/[a-zA-Z]+\-*[a-zA-Z]+\-*[a-zA-Z]+/overview" players > playersname.txt
grep -P -v "[\x80-\xFF]" playersname.txt > urls.txt
sed -i "s/players/https:\/\/www\.premierleague\.com\/players/" urls.txt

totalplayers=$(grep -c ".*" urls.txt)
echo "Total Players: $totalplayers" >> player_results.csv

for urlline in $(cat "urls.txt"); do
		wget -O tmp "$urlline"
		midfieldcount=$(grep -cE "[M|m](idfielder)" tmp)
		if [[ $midfieldcount -gt 0 ]]
		then
		echo "$urlline, Midfielder, $midfieldcount" >> player_results.csv
		
		fi

done

rm players*
rm tmp*
rm urls.txt
