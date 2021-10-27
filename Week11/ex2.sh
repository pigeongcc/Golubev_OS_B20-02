# please execute ex1.sh before running this script

sudo chmod 777 lofsdisk

# create the files in the created loopback FS (LOFS)
sudo touch lofsdisk/file1
sudo chmod 777 lofsdisk/file1
echo "Sergey" >> lofsdisk/file1
sudo touch lofsdisk/file2
sudo chmod 777 lofsdisk/file2
echo "Golubev" >> lofsdisk/file2

# compile the C program
gcc -o ex2.out ex2.c

# add commands to the LOFS
sudo mkdir lofsdisk/bin

sudo cp -R /bin/bash lofsdisk/bin
sudo cp -R /bin/cat lofsdisk/bin
sudo cp -R /bin/echo lofsdisk/bin
sudo cp -R /bin/ls lofsdisk/bin

# copy the shared libraries
sudo mkdir lofsdisk/lib
sudo mkdir lofsdisk/lib/x86_64-linux-gnu/
sudo mkdir lofsdisk/lib64

path='./lofsdisk'

# parse and copy the shared libraries for ls command
list="$(ldd /bin/ls | egrep -o '/lib.*\.[0-9]')"
for i in $list; do sudo cp  -v "$i" "${path}${i}"; done
list="$(ldd /bin/ls | egrep -o '/lib64.*\.[0-9]')"
for i in $list; do sudo cp  -v "$i" "${path}${i}"; done

# parse and copy the shared libraries for bash command
list="$(ldd /bin/bash | egrep -o '/lib.*\.[0-9]')"
for i in $list; do sudo cp  -v "$i" "${path}${i}"; done
list="$(ldd /bin/bash | egrep -o '/lib64.*\.[0-9]')"
for i in $list; do sudo cp  -v "$i" "${path}${i}"; done

# parse and copy the shared libraries for echo command
list="$(ldd /bin/echo | egrep -o '/lib.*\.[0-9]')"
for i in $list; do sudo cp  -v "$i" "${path}${i}"; done
list="$(ldd /bin/echo | egrep -o '/lib64.*\.[0-9]')"
for i in $list; do sudo cp  -v "$i" "${path}${i}"; done

# parse and copy the shared libraries for cat command
list="$(ldd /bin/cat | egrep -o '/lib.*\.[0-9]')"
for i in $list; do sudo cp  -v "$i" "${path}${i}"; done
list="$(ldd /bin/cat | egrep -o '/lib64.*\.[0-9]')"
for i in $list; do sudo cp  -v "$i" "${path}${i}"; done

# run the program ex2.out with the root directory changed to the mount point of the created LOFS
cd lofsdisk
gcc -o ex2.out ../ex2.c

echo "With chroot\n################################################\n" >> ../ex2.txt
sudo chroot . ./ex2.out >> ../ex2.txt

echo "\nWithout chroot\n################################################\n" >> ../ex2.txt

# run the program ex2.out as usual
./ex2.out >> ../ex2.txt
