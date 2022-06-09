user=$(whoami)
date=$(date +'%m/%d/%Y')
hour=$(date +'%r')
current_path=$(pwd) 
files=0

for i in *
do
files=$((files+1))
done

echo “User name: ${user}” >> data.txt
echo “Date: ${date}” >> data.txt
echo “Hour: ${hour}” >> data.txt
echo “Current path: ${path}” >> data.txt
echo “Files in pwd: ${files}” >> data.txt
