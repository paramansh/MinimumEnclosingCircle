# Calculates the average number of points outside the circle
# That is the number of times circle expanded
counter=1
circle=0
iterations=100
n=$1
while [ $counter -le $iterations ]
do
    temp=$(echo $n $counter| ./mic_stats)
    #echo $temp
    ((circle=circle+temp))
    ((counter += 1))
done
((circle=circle/iterations))
echo $circle
