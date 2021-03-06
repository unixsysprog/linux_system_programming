#!/bin/bash

#INFILE="infile$$"
#echo "$INFILE: $INFILE"
#echo INFILE quoted "$INFILE"
#
#catinto()
#{
#  cat > $INFILE
#  cat $INFILE
#  if [ -r $INFILE ]
#  then
#    echo -e "Reading is good!"
#  fi
#}
#
#vartest()
#{
#  cat $INFILE
#  if [ -r $INFILE ]
#  then
#    echo -e "Reading is good!"
#  else
#    echo -e "Readins is bad"
#  fi
#}

i=0
while IFS=$'\n' read -r line
do
  #readarray -d$'\t' -t rowarr$i <<< "$line"; declare -p "rowarr$i";
  readarray -d$'\t' -t rowarr$i < <(printf "%s" "$line") 
  declare -p "rowarr$i";
  ((i++))
done < "$1"
#
# This works:
echo "First row: ${rowarr0[@]}"
k=4
#var="rowarr$t[@]"
#echo "Row five: ${!var}"
c=4
var="rowarr$k[$c]"
echo "Row five, element 5: ${!var}"

for (( c = 0; c < 4; c++ ))
do
  for ((k = 0; k < 3; k++))
  do
    var="rowarr$k[$c]"
    echo "This is c: $c"
    echo "This is k: $k"
    rowvar="rowarr$k[@]"
    echo "this is row: ${!rowvar}" 
    echo "this is var: ${!var}" 
    #echo -e "${rowarr$k}"
    #echo -e "$rowarr${k}"
    #echo -e $rowarr${k}
    #echo -e $rowarr${$k}
    #echo -e "$rowarr${$k}"
    #echo -e "$rowarr$k"
    #echo -e $rowarr$k
    #echo -e "$rowarr$k"
    #echo -e ${!rowarr$k}
    #echo -e "${!rowarr$k}"
    #echo -e "${!rowarr$k}"
    #this works to show the entire array: 
    #...echo "${rowarr1}"
    #so does this: echo "${rowarr1[@]}"
    #so does this...
    #... ref=rowarr$k
    #.... echo ${!ref}
      #row="rowarr$k[index]"
     # declare -a row="rowarr$k"
      #index="$c"
      #ef=rowarr$k[$k]#index=1
      #echo ${!ref}
  #    row="rowarr$k[idx]"
      #echo ${!row[$c]}
  #    idx=${c} 
  #    echo -e ${!row} #[${idx}]}
  done
done

#echo "colsum: $colsum"  

#catinto
#vartest
