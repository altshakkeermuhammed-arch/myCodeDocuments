#!/bin/bash
# Print Hello world message
echo "Hello World!started  my program in shell script"
echo 'Enter the score'
read x

if [[ $x -ge  70 ]]; then
 echo 'Good job, you passed!'
else
 echo 'sorry you failed' 
fi

echo 'Please Enter your user_id'
read user_id
echo 'Please Enter your tag_no'
read tag_id

if [[ ($user_id -eq 100  && $tag_id -eq 1980) ]];
then
  echo “Login successful”
else
  echo “Login failure”
fi  

# A simple while loop
counter=1
while [ $counter -le 10 ]
 do
echo $counter
 ((counter++))
done

# Specify range in a for loop
for num in {10..20}
do
  echo $num
done

# bash positional paramters
echo "The name of the script is: " $0
echo "My first name is: " $1
echo "My second name is: " $2

# storing command in variable
mydatecommand=$(date)
echo "Todays Data is"
echo "$mydatecommand"
