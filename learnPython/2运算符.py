#!/usr/bin/python3
 
a = 21
b = 10
c = 0
 
c = a + b
print ("1 - c 的值为：", c)
 
c = a - b
print ("2 - c 的值为：", c)
 
c = a * b
print ("3 - c 的值为：", c)
 
c = a / b
print ("4 - c 的值为：", c)
 
c = a % b
print ("5 - c 的值为：", c)
 
# 修改变量 a 、b 、c
a = 2
b = 3
c = a**b #2的三次方
print ("6 - c 的值为：", c)
#除法 / 总是返回一个浮点数，
#如果只想得到整数的结果，丢弃可能的分数部分，可以使用运算符 // 
#
a = 10
b = 5
c = a//b 
print ("7 - c 的值为：", c)