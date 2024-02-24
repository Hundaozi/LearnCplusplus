"""
while 判断条件(condition)：
    执行语句(statements)……
"""

#经典高斯。。
'''
n = 100

sum = 0
counter = 1
while counter <= n:
    sum = sum + counter
    counter += 1
 
print("1 到 %d 之和为: %d" % (n,sum))
'''

"""
while <expr>:
    <statement(s)>
else:
    <additional_statement(s)>
"""

'''
count = 0
while count < 5:
   print (count, " 小于 5")
   count = count + 1
else:
   print (count, " 大于或等于 5")

'''

"""
for <variable> in <sequence>:
    <statements>
else:
    <statements>

    Python for 循环可以遍历任何可迭代对象，如一个列表或者一个字符串。
"""
'''
sites = ["Baidu", "Google","Runoob","Taobao"]
for site in sites:
    print(site)
'''
#在 Python 中，for...else 语句用于在循环结束后执行一段代码。
'''
for x in range(6):
    print(x)
else:
    print("Finally finished!")
'''

#break 语句可以跳出 for 和 while 的循环体。如果你从 for 或 while 循环中终止，任何对应的循环 else 块将不执行。

#continue 语句被用来告诉 Python 跳过当前循环块中的剩余语句，然后继续进行下一轮循环。
'''
n = 5
while n > 0:
    n -= 1
    if n == 2:
        #break
        continue#2就没输出了，4 3 1 0
    print(n)
print('循环结束。')
'''
"""
pass 语句
Python pass是空语句，是为了保持程序结构的完整性。
"""
'''
for letter in 'Runoob': 
   if letter == 'o':
      pass #pass就是跳过的意思
      print ('执行 pass 块')
   print ('当前字母 :', letter)
 
print ("Good bye!")
'''