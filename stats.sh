counter=1
circle=0
iterations=100
n=$1
while [ $counter -le $iterations ]
do
    temp=$(echo $n | ./a.out)
    echo $temp
    #((circle=circle+temp))
    ((counter += 1))
done
((circle=circle/iterations))
echo $circle
#counter=10

#while [ $counter -le 10000000 ]
#do
    #echo $counter | ./a.out
    #((counter *= 10))
#done
