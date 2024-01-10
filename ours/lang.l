%option noyywrap yylineno
%option outfile="lexer.c" header-file="lexer.h"
%{
#include "lang.h"
#include "parser.h"
%}

%%

0|[1-9][0-9]* {
    yylval.n = build_nat(yytext, yyleng);
    return TM_NAT;
}

"var" {
    return TM_VAR;
}

"func" {
    return TM_FUNC;
}

"int" {
    return TM_INTTYPE;
}

"void" {
    return TM_VOID;
}

"if" {
    return TM_IF;
}

"then" {
    return TM_THEN;
}

"else" {
    return TM_ELSE;
}

"while" {
    return TM_WHILE;
}

"do" {
    return TM_DO;
}

"for" {
    return TM_FOR;
}

"skip" {
    return TM_SKIP;
}

"continue" {
    return TM_CONTINUE;
}

"break" {
    return TM_BREAK;
}

"return" {
    return TM_RETURN;
}

"template" {
    return TM_TEMPLATE;
}

"typename" {
    return TM_TYPENAME;
}

[_A-Za-z][_A-Za-z0-9]* {
    // printf("A%dA",get_now_vtable()==NULL);
    // printf("%s %s %d\n",yytext,get_template_typename(),strcmp(yytext,get_template_typename()));
    if(strcmp(yytext,get_template_typename())==0){
        return TM_TEMPLATE_TYPENAME;
    }
    yylval.s = new_str(yytext, yyleng);
    struct vtable_item * res = vtable_find_char_now(get_now_vtable(),yytext);
    // printf("B%sB",yytext);
    // printf("C%sC\n",res->typename);
    
    /* Find the item(pointer of var_type) of given vtable using given name and only now_vtable. */
    if(res == NULL){
        res = vtable_find_char(get_now_vtable()->father_vtable);
        if(res == NULL){
            return TM_IDENT;
        }
        return TM_IDENT_VAR_NAME;
    }
    else{
        return TM_VAR_NAME;
    }
}

";" {
    return TM_SEMICOL;
    }


"," {
    return TM_COMMA;
    }

"(" {
    return TM_LEFT_PAREN;
    }

")" {
    return TM_RIGHT_PAREN;
    }

"{" {
    return TM_LEFT_BRACE;
    }

"}" {
    return TM_RIGHT_BRACE;
    }

"+" {
    return TM_PLUS;
    }

"-" {
    return TM_MINUS;
    }

"*" {
    return TM_MUL;
    }

"/" {
    return TM_DIV;
    }

"%" {
    return TM_MOD;
    }

"<" {
    return TM_LT;
    }

">" {
    return TM_GT;
    }

"<=" {
    return TM_LE;
    }

">=" {
    return TM_GE;
    }

"==" {
    return TM_EQ;
    }

"!=" {
    return TM_NE;
    }

"=" {
    return TM_ASGNOP;
    }

"&&" {
    return TM_AND;
    }

"||" {
    return TM_OR;
    }

"!" {
    return TM_NOT;
    }

"&" {
    return TM_ADDROF;
    }


[ \t\n\r]    { };

.   {printf("%s",yytext);
     return -1; }
%%
