#Temporary fix to correct windows bug that puts \r at the end of some of files, for some reason.

let i=0;

mkdir -p tester/tests
for FILE in tester/bugged_tests/*; do
	((i+=1))
	new_file_name=tester/tests/$(readlink -f $FILE | cut -d'/' -f7-)
	echo "correcting $new_file_name" 
	sed $'s/\r$//' $FILE > $new_file_name 
done