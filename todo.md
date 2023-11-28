First Contact:

- [ ] 多态包含哪些基本类型 int bool ?
- [ ] 有穷多个副本是什么
- [ ] 重复定义 同名不同类型函数和多态有什么区别
- [ ] 多态我们是用template\<typename T\> 还是 template\<class T\>
- [ ] do while， for ，while do ，local X in C这些要实现吗？
 
WhileF:

- [ ] ATTENTION: 目前的实现存在 2 Reduce/Reduce 冲突

- [ ] whileX语言设计的时候，对于赋值语句是定义为V=E,然而在阳历中给出的是 NT_EXPR TM_ASGNOP NT_EXPR

- [ ] 过程和函数有什么区别，proc和function中的 P(ARGS) F(ARGS)的P和F是如何定义，是否只需要定义成EXPR0,或者就是原生的EXPR即可（模仿上一个疑问）

- [ ] for(C;E;C){C} 和函数与过程调用， 这两个部分加在一起引起了 R/R 冲突，冲突的核心是分号，这个目前还没有解决，我在想。。。

关于R/R冲突的细节是这样的，当函数调用，过程调用,FOR这三个同时存在时，就会产生冲突，但是去掉任意一个，冲突就不会产生，真是绝了。

我大概知道了，例子是这样的。。。。

for(F();F();F();F())

R/R冲突就是，他不知道哪一个F是Cmd哪一个F是Expr，真是服了，有两种方法，把过程和函数分开，第二个，for里面的C是假C，不能引入额外分号的那啥。唉，到时候问下老师。

- [ ] 如下的函数定义是否要引入，目前是没有的捏。

int expr(args){
    C
}