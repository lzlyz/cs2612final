# 函数指针与多态函数 小组

### 题目:

【前端实现】带函数指针与类型多态的程序语言的词法分析、语法分析与类型多态展开

这个任务中，你需要在 WhileF 语言中加入函数指针、基本类型系统与类型多态。该语言的类型包括整数类型、某类型的指针类型与基于特定参数与返回值类型的函数指针类型，声明变量时需要使用 var 关键字 + 类型 + 变量名，类型多态使用类似 C++ 语言中 template 的语法表示。

要求 1：在 WhileF 语言中加入函数指针与基本类型系统，并完成词法分析、语法分析与语法树输出。

要求 2：进一步加入类型多态，并完成词法分析、语法分析与语法树输出。

要求 3：实现类型检查，根据 main 函数的需要，将类型多态展开，不能展开成为有穷多个副本的，产生报错信息。

### 调用:

我们调用了一个由N. Devillard制作的dictionary的实现，该dictionary利用字符串作为key，找到一个相应的指针。

该dictionary实现其实非常简单，它的本质只是一个结构体数组，并没有用到字典树，红黑树等查询复杂度为O(logN)的数据结构，具体只使用了哈希函数来辅助字符串比对。

为了方便我们依然使用了这个实现，具体文件为ours文件夹下的dictionary.h和dictionary.c。

### 约定:

1. 由于没有数组，我们禁止了函数指针进行二元运算。由于多态函数可以传入指针作为类型，对于多态类型，我们也禁止了其进行二元运算。更进一步，还禁用了解引用。
2. 不考虑函数重载。具体实现中，禁止了函数重载。
3. 声明方式：
```
函数指针、指针、变量：
var TYPENAME RIGHT_TYPE_EXPR;
函数:
func TYPENAME RIGHT_TYPE_EXPR;
过程:
func void RIGHT_TYPE_EXPR
多态函数:
template <typename NEW_TYPENAME> TYPENAME RIGHT_TYPE_EXPR
 
其中：
TYPENAME->NEW_TYPENAME, TYPENAME->INT
``` 
考虑到多态过程没有什么意义，

4. 函数原型仅能声明一次。
5. 多态函数实例化必须使用`POLYMORPHIC_FUNCTION< TYPENAME ANNON_TYPE_EXPR >`，这个会被看作一个实例化后的普通函数，在这个函数上再进行函数调用`(ARGUMENTS)`。
6. 我们约定函数调用会被看作为一个expr，过程调用会被看作为一个cmd。
7. 我们修改了一点点原有的WhileF语法。原有的WhileF语法要求cmd之间用分号`;`进行分开，但是这个在实际写代码的时候有些反直觉，所以在我们的实现中，用分号`;`表示cmd的结尾，包括函数声明。
8. 使用函数指针对应的函数前必须Derefrence。

### 关键实现方式:
要求 1：基本没什么难点，理解flex和bison后，按照要求加入对应语法即可。

要求 2：我们利用var_type(见lang.h)来储存一个变量及其数据类型、或是一种数据类型。由于原来作业(struct&union&enumration)中，对于以函数的指针作为返回值的函数的指针的语法树输出不正确，我们重写了RIGHT_TYPE_EXPR(在代码中是var_decl_expr，见lang.h)的相关代码，让函数指针的定义符合要求。然后，我们加入了按照语法加入了类型多态。

要求 3：要求3相比要求1、2难度大很多，主要分为两点

要求 3.1: 类型检查。

要求 3.2: 类型多态展开。

### 怎么使用:
1. 在./ours下 make
2. 运行编译得到的 main(on Linux) 或 main.exe (on Windows)。需要参数，参数为同文件夹下的文件名。如
```shell
main.exe s0.jtl
```
```powershell
.\main.exe s0.jtl
```

