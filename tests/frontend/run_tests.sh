#!/bin/bash

#Navigate to source folder to build application
cd ../../srcFront
make
#Renavigate back to frontend test folder
cd ../tests/frontend

#Remove old test outputs if exists
if [ -d "./outputs/" ] 
then
    rm -r outputs
fi

#Remove old output comparisons if exists
if [ -d "./comparison" ] 
then
    rm -r comparison
fi

#Make directories for output and comparisons
mkdir outputs
mkdir comparison

#Loop across all test input files
for test in input/*;do
	#Copy user account and avialble items file from the default folder
	#This will setup th test enviroment with correct users and items
	cp ./default/UserAccountsFile.txt ./default/AvailableItemsFile.txt .

	#cutting off 'input/' from variable 'test'
	test=$(echo $test | cut -c7-)
	echo "Running test: $test"

	#Run executeable with input from test file
	#Take executeable terminal outputs and append to output folder
	#in file with same name as test variable
	../../srcFront/main UserAccountsFile.txt AvailableItemsFile.txt DailyTransactionFile.txt < "input/$test" > outputs/"$test"
	
	#Remove '.txt' from 'test' variable
	test=${test::-4}
	
	#Add the contents of dailytransactionfile to new file in outputs folder
	#new file is the same as test variable but with _FILE.txt added to the end
	cat DailyTransactionFile.txt >> outputs/"${test}_FILE.txt"
	#Clears Daily transaction file for next test
	> DailyTransactionFile.txt
	rm ./UserAccountsFile.txt ./AvailableItemsFile.txt
done


#Change directory to outputs folder
cd outputs
#loop across all files in outputs folder
for output in *;do
	echo "Validating test: $output"
	DIFF=$(diff $output ../expected_output/$output) 
	if [ "$DIFF" != "" ];then
   		echo "FAIL: "
		echo $DIFF
		read -n 1 -s -r -p "Press any key to continue"
	else
		echo "PASS"
	fi
done
