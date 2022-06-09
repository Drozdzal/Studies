!#/bin/bash

folders=["file1","file2","file3","file4"]
items=["item1.txt", "item2.txt", "item3.txt", "item4.txt"]

for i in ${folders}
do
mkdir ${i}
cd ${i}
for j in ${items}
touch {j}
done
cd ..
done

echo "Everyting is done"


