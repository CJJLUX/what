#!/bin/sh

#a=10
#b=20
#
#val=`expr $a + $b`
#echo "a + b : $val"
name="yrx"
#算数比较 [ $var -eq 0 ]
#文件属性测试，比如一个文件是否存在，[ -e $var ] ,目录[ -d $var ]
#字符串比较，[[ $var1 = $var0 ]]
while :
do
    echo -n "please input your best love:"
    read the_name
    if [[ $the_name = $name ]]
    then
        echo "This is the best answer!"
    else
        echo "you are stupid!!"
    fi
done

