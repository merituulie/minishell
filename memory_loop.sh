#!bin/bash

while TRUE
do
	echo "Checking for memory leaks ....."
	leaks minishell
	lsof -p 
	sleep 3
done
