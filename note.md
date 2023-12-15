赋值语句修改:
不改了

定义方式修改:
不改了

定义函数的时候解析函数类型和函数参数，语法上允许定义出一个函数指针来，解析的时候给他error掉


函数指针声明方式  
CMD -> var int DECL_RIGHT_EXPR

DECL_RIGHT_EXPR
    -> IDENT
    -> * DECL_RIGHT_EXPR
    -> DECL_RIGHT_EXPR ( DECL_ARGS )
    -> DECL_RIGHT_EXPR ()
    -> (DECL_RIGHT_EXPR)

DECL_ARGS
    -> int ANNON_RIGHT_EXPR, DECL_ARGS
    -> int ANNON_RIGHT_EXPR
    -> int
    -> int, DECL_ARGS

ANNON_RIGHT_EXPR:
    -> *
    -> ()
    -> * ANNON_RIGHT_EXPR
    -> ANNON_RIGHT_EXPR()
    -> ANNON_RIGHT_EXPR(DECL_ARGS)
    -> (ANNON_RIGHT_EXPR)
    -> (DECL_ARGS)


多态声明方式：  
CMD -> tempalte < typename IDENT > var int TEMPLATE_DECL_RIGHT_EXPR
CMD -> tempalte < typename IDENT > var IDENT TEMPLATE_DECL_RIGHT_EXPR

TEMPLATE_DECL_RIGHT_EXPR
    -> IDENT
    -> * DECL_RIGHT_EXPR
    -> DECL_RIGHT_EXPR ( TEMPLATE_DECL_ARGS )
    -> DECL_RIGHT_EXPR ()
    -> (DECL_RIGHT_EXPR)

TEMPALTE_DECL_ARGS
    -> int ANNON_RIGHT_EXPR, TEMPLATE_DECL_ARGS
    -> int ANNON_RIGHT_EXPR
    -> int
    -> int, TEMPLATE_DECL_ARGS
    -> IDENT ANNON_RIGHT_EXPR, TEMPLATE_DECL_ARGS
    -> IDENT ANNON_RIGHT_EXPR
    -> IDENT
    -> IDENT, TEMPLATE_DECL_ARGS

TEMPLATE_ANNON_RIGHT_EXPR:
    -> *
    -> ()
    -> * TEMPLATE_ANNON_RIGHT_EXPR
    -> TEMPLATE_ANNON_RIGHT_EXPR()
    -> TEMPLATE_ANNON_RIGHT_EXPR(TEMPLATE_DECL_ARGS)
    -> (TEMPLATE_ANNON_RIGHT_EXPR)
    -> (TEMPLATE_DECL_ARGS)

多态的实例化：  
如何声明函数过程：

func int(args){CMD}

func void IDENT(args){CMD}