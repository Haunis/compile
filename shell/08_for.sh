
for str in 'this is a string'
do
	echo $str
done


echo "---------------"

temp_array=( 1 2 3 4 ) #赋值时,等号两边不能有空格

for num in ${temp_array[*]} # *和@都行
do 

	echo $num
done
