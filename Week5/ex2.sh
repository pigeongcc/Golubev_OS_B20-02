file="ex2.txt"	# file with numbers
lock="$file.lock"	# lock file

# check if file exists
if [ ! -f $file ] 	# if doesn't exist
then
	echo 0 > $file	# then create a file with 0
fi

# check if another process is using this file
while [ -f $lock ]	# while lock file exists
do
	:	# just wait
done

for i in {1..100}
do
	ln $file $lock
	LASTNUM=`tail -1 $file`
	NEXTNUM=`expr 1 + $LASTNUM`
	echo ${NEXTNUM} >> $file
	rm $lock
done
