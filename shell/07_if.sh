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


