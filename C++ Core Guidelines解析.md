 关于C++的理念

 
 1.理念性规则（元规则）为具体规则提供理论依据。理想状态下，具体规则可以从理念性规则中推导出来。
 2.在代码中直接表达意图和思想。
 3.用ISO标准 C++编写代码，并使用支持库和辅助工具。
 4.一个程序应该是静态类型安全的，因此，应该可以在编译时进行检查。当这不可能时，要及早捕获运行期的错误。
 5.不要浪费资源，如空间或时间。
 6.将杂乱的构建封装在一个稳定的接口后面。

 关于接口的理念：接口是服务的提供者和使用者之间的契约。


 让接口易于正确使用，难以错误使用。

 
 1.不要使用全局变量。他们会引入隐藏的依赖。
 2.单例就是变相的全局变量。
 3.接口，尤其是函数，应该表达出意图。（应该写函数和接口的目的，而不是具体怎么做）
 4.接口应当是强类型的，而且应该只有几个不容易弄混的参数。
 5.不要按指针接受C数组，而应使用std::span。（C++20）
 6.如果你想要将类的使用和实现分开，请使用PImpl惯用法。
 



函数，编程中最为重要的部分


1.一个函数应该执行一个操作，要简短，并有一个精心选择的名字。
2.要把可以在编译期运行的函数实现为constexpr。
3.如果可能的话，将你的函数实现为纯函数。
4.区分一个函数的入、入/出和出参。对入参使用按值传递或按const引用传递。对入/出参使用按引用传递，对出参使用按值传递。
5.向函数传递参数涉及所有权语义的问题。按值传递使函数成为资源的独立所有者。按指针或者引用传递意味着函数只是借用了资源。std::unique_ptr 将所有权转移给函数，std::shared_ptr则使函数成为共享的所有者。
6.当你的函数需要接受任意数量的参数时，要使用变参模板而不是va_arg 参数。





类与类层次接口，类是一种用户自定义类型，程序员可以为其指定表示方法、操作、和接口。

类的层次结构被用来组织相关的结构。

1.尽量使用具体类型而不是类的层次结构。让你的具体类型成为规范类型。规范类型支持“六大”（默认构造函数、析构函数、拷贝和移动构造函数、拷贝和移动赋值运算符）、交换函数和相等运算符。
2。如果可能的话，就让编译期生产这“六大”。如果不能，就通过default请求所有这些特殊成员函数。 如果这也不行，就明确地实现所有这些函数，并给它们一个一致的设计。拷贝构造函数或拷贝赋值运算符应该拷贝。移动构造函数或移动赋值运算符应该移动。
3.构造函数应该返回一个完全初始化的对象。使用构造函数来建立不变式。不要使用构造函数来设置成员的默认值。尽量使用类内初始化减少重复。
4.如果你需要在对象销毁时进行清理动作，请事先析构函数。基类的析构函数应该要么是public且virtual，要么是protected且不是虚函数。
5.只对具有内在层次的结构使用类的层次结构来进行建模。如果基类作为一个接口使用，就让基类成为抽象类，以便分离接口的实现。一个抽象类应该只有一个预置的默认构造函数。
6.区分接口继承与实现继承。接口继承的目的是将用户与实现分隔开；实现继承是为了重用现有的实现。不要再一个类中混合这两个概念。
7.在一个有虚函数的类里，析构函数应该要么是public加virtual，要么是protected。对于一个虚函数，要使用virtual、override或finnal中的一个，不多也不少。
8.一个类的数据成员应该要么全部是public，要么全部private。如果类建立了一个不变式，将让他们全部private，并使用class。如果不是，就让它们public，并使用struct。
9.把单参数构造函数和转换运算符标为explicit。
10.使用联合体来节约内存，但不要使用裸联合体；尽量使用带标签联合体，如C++17中的std::variant。
