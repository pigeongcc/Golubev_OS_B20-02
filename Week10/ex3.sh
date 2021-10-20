touch _ex3.txt
echo "Sergey Golubev ex3" >> _ex3.txt

ls -l _ex3.txt >> ex3.txt

chmod a-x _ex3.txt
ls -l _ex3.txt >> ex3.txt

chmod ou+rwx _ex3.txt
ls -l _ex3.txt >> ex3.txt

chmod g=u _ex3.txt
ls -l _ex3.txt >> ex3.txt

echo "660 for ex3.txt means the following permissions: R,W for Owner; R,W for Group; nothing for Other." >> ex3.txt
echo "775 for ex3.txt means the following permissions: R,W,X for Owner; R,W,X for Group; R,X for Other." >> ex3.txt
echo "777 for ex3.txt means the following permissions: R,W,X for Owner; R,W,X for Group; R,W,X for Other." >> ex3.txt
