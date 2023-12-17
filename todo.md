### First Contact:

- [x] 多态包含哪些基本类型 int bool ?
```只包含bool```
- [x] 有穷多个副本是什么
```不能展开为指针的指针的。。。。指针的int```
- [x] 重复定义 同名不同类型函数和多态有什么区别
```前者是函数重载，不考虑```
- [x] 多态我们是用template\<typename T\> 还是 template\<class T\>
```Only typename```
- [x] do while， for ，while do ，local X in C这些要实现吗？
```要，老师说whileF很简单的```

### WhileF:

- [ ] 不是很理解为什么expr要归约到expr1之后再加入NOT EXPR,有没有董哥细说一下。
(这边也不是很懂，但是可以确定的是要避免一些冲突，修改位置后都会发生conflict...)
- [x] ATTENTION: 目前的实现存在 2 Reduce/Reduce 冲突

- [ ] whileX语言设计的时候，对于赋值语句是定义为V=E,然而在阳历中给出的是 NT_EXPR TM_ASGNOP NT_EXPR

- [ ] 过程和函数有什么区别，proc和function中的 P(ARGS) F(ARGS)的P和F是如何定义，是否只需要定义成EXPR0,或者就是原生的EXPR即可（模仿上一个疑问）—— EXPR0 会产生冲突，此外还有不能是 NAT 的问题，但是重新定义一个 EXPR 也会有冲突...

- [x] for(C;E;C){C} 和函数与过程调用， 这两个部分加在一起引起了 R/R 冲突，冲突的核心是分号，这个目前还没有解决，我在想。。。(cwx:就用simple方法打了个补丁)

```
关于R/R冲突的细节是这样的，当函数调用，过程调用,FOR这三个同时存在时，就会产生冲突，但是去掉任意一个，冲突就不会产生，真是绝了。

我大概知道了，例子是这样的。。。。

for(F();F();F();F())   simple_command

R/R冲突就是，他不知道哪一个F是Cmd哪一个F是Expr，真是服了，有两种方法，把过程和函数分开，第二个，for里面的C是假C，不能引入额外分号的那啥。唉，到时候问下老师。

现在的问题是没有冲突了，但是 for 不能 print 出来（之前也不可以）
```

- [ ] 如下的函数定义是否要引入，目前是没有的捏。好像不用？

```
int expr(args){
    C
}
```

### 函数指针：

- [x] 很多新的NT,TM符我都没写priority，有没有好心人帮忙检查一下。

### 指针多态:

- [ ] 什么是类型检查? 比如 `template <typename T> int (* f)(T,C);` 是不是合法的，类型检查是不是这个
赋值、计算的类型检查

- [ ] 函数进行实例化的时候，c++中可以省略实例化参数交由编译器自行判断，这个怎么说。
```cpp
template<typename T,typename C> T max(T a, T b,C c=0){
    return a?a>b:b;
} 

//调用
max<int,int>(10,20,10);
max<int>(10,20,10);
max(10,20,10)
```

- [x] 形如`template <> int a;`是否需要特判中空。目前已特判 —— exactly one
- [ ] 多态声明的情况是否应该都改为函数体？实例化的时候要构建一个数据类型(int,int*)的语法树？

- [ ] 目前的想法有点赘余，记录在note.md中，有没有董哥优化一下？

### 类型检查:

- [ ] 如下

```cpp
//没有template，单纯无限递归，不也会导致程序无法终止？不是很理解
template <typename T> T sjtu(T a){
	sjtu<T *>(&a);
}

int sjtu(int a);
int * sjtu(int * a);
int ** sjtu
int ****
 ******
*********

int sjtu(int a){
    sjtu(a);
}
```

- [] 及其弱智的一个 R/R冲突：
有
expr

expr < IDENT > ( IDEN)


expr < expr > expr


expr < NT_TYPENAME annoy_right_expr > (args);

NT_INT,TM_TYPE_NAME

(* a)(int, int *);

func int (*a(int a,int b ,int c))(int,int)

template <typename C> func int a(T b, T c);

complex_decl_expr_list
-> annoy, named


- [] 关于局部变量的处理
我们建立一个字典链表，首先，在bison初始化一个全局字典，
在FOR,WHILE,DOWHILE,FUNC语句的时候，创建子字典，指向父字典，查询时，逐步查询，创建时，优先在子创建，子查询。