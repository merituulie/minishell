#!bin/bash

while TRUE
do
	echo "Checking for memory leaks ....."
	leaks minishell
	echo "*********************************************************"
	##lsof -c minishell
	sleep 3
done
