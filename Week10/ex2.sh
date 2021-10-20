mkdir ../week01
touch ../week01/file.txt
echo "Sergey Golubev ex2" >> file.txt
link ../week01/file.txt _ex2.txt
inodenumber=`ls -i ../week01/file.txt | awk '{print $1}'`
find ../ -inum "$inodenumber" >> ex2.txt
find ../ -inum "$inodenumber" -exec rm {} \; >> ex2.txt
