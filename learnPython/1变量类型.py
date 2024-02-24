#number 数字
#string 字符串
# list 列表
#tuple 元组
# Dictionary 字典
'''var1 =1
var2 =10
del var1#删除对象的引用
'''


#python支持的四种不同数字类型：
#int 
#long 
#float
#complex
'''
s="hahahahah...lalalala"
print(s)
'''

#如果你要实现从字符串中获取一段子字符串的话，
#可以使用 [头下标:尾下标] 来截取相应的字符串，
#其中下标是从 0 开始算起，可以是正数或负数，下标可以为空表示取到头或尾。
'''
print(s[3:9])

list = [ 'runoob', 786 , 2.23, 'john', 70.2 ]
tinylist = [123, 'john']

print (list)               # 输出完整列表
print (list[0])            # 输出列表的第一个元素
print (list[1:3])          # 输出第二个至第三个元素 
print (list[2:])           # 输出从第三个开始至列表末尾的所有元素
print (tinylist * 2)       # 输出列表两次
print (list + tinylist)    # 打印组合的列表
'''

'''元组是另一个数据类型，类似于 List（列表）。

元组用 () 标识。内部元素用逗号隔开。但是元组不能二次赋值，相当于只读列表。
'''
'''
tuple = ( 'runoob', 786 , 2.23, 'john', 70.2 )
tinytuple = (123, 'john')
 
print (tuple)              # 输出完整元组
print (tuple[0])            # 输出元组的第一个元素
print (tuple[1:3])          # 输出第二个至第四个（不包含）的元素 
print (tuple[2:])           # 输出从第三个开始至列表末尾的所有元素
print (tinytuple * 2)       # 输出元组两次
print (tuple + tinytuple)   # 打印组合的元组

'''

"""元组不允许更新，只读"""

#列表是有序的对象集合，字典是无序的对象集合。
'''哈希表？'''
'''
tinydict = {'Name': 'Zara', 'Age': 7, 'Class': 'First'}
 
print ("tinydict['Name']: ", tinydict['Name'])
print ("tinydict['Age']: ", tinydict['Age'])

'''

'''
就是键值对
'''



'''
Python 中的集合（Set）是一种无序、可变的数据类型，用于存储唯一的元素。

集合中的元素不会重复，并且可以进行交集、并集、差集等常见的集合操作。

在 Python 中，集合使用大括号 {} 表示，元素之间用逗号 , 分隔。

另外，也可以使用 set() 函数创建集合。

注意：创建一个空集合必须用 set() 而不是 { }，因为 { } 是用来创建一个空字典。
'''


'''
sites = {'Google', 'Taobao', 'Runoob', 'Facebook', 'Zhihu', 'Baidu'}

print(sites)   # 输出集合，重复的元素被自动去掉:q

if 'Google' in sites:
    print("google存在")
'''

a = set("hello myfriend")
b=set("fuck you!")
print(a)
print(b)

print(a-b) #差集
print(a|b) #并集