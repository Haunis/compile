
echo "------1---------"

for str in 'this is a string'
do
	echo $str
done


echo "------2---------"

temp_array=( 1 2 3 4 ) #赋值时,等号两边不能有空格

for num in ${temp_array[*]} # *和@都行
do 

	echo $num
done



echo "------3---------"

for((i=0; i<4; i++))
do
        echo $i
done

