mkdir tmp
touch ./tmp/file1
touch ./tmp/file2
link ./tmp/file1 ./tmp/link1

# WARNING: compilation command depends on the system
# for me it was:
gcc -o ex4 ex4.c 
./ex4 >> ex4.txt
