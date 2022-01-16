#how to use:
#1 sudo chmod 777 s2.sh 
#2 ./s2.sh xiaoming
#or:bash s2.sh xiaoming

sex="me"

if [ "$sex" = "me" ]; then  #注意[]两边空格
	echo "you are female"
else
	echo "you are male"
fi


s=90
if [[ $s < 60 ]]; then
	echo "<60"        
elif [[ $s < 80 ]]; then
	echo "<80"        
else
	echo ">80"
fi
