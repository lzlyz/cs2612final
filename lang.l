%option noyywrap yylineno
%option outfile="lexer.c" header-file="lexer.h"
%{
#include "lang.h"
#include "parser.h"
#include "lib.h"
%}

%%


"struct" {
    return TM_STRUCT;
}

"union" {
    return TM_UNION;
}

"enum" {
    return TM_ENUM;
}

"typedef" {
    return TM_TYPEDEF;
}


"int" {
    return TM_INTTYPE;
}

"char" {
    return TM_CHARTYPE;
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

"[" {
    return TM_LEFT_BRACKET;
}

"]" {
    return TM_RIGHT_BRACKET;
}


"{" {
    return TM_LEFT_BRACE;
    }

"}" {
    return TM_RIGHT_BRACE;
    }

"*" {
    return TM_POINTER;
    }

0|[1-9][0-9]* {
    yylval.n = build_nat(yytext, yyleng);
    return TM_NAT;
}

 [_A-Za-z][_A-Za-z0-9]*  {
    yylval.i = new_str(yytext, yyleng);
    return TM_IDENT;
}



[ \t\n\r]    { };

.   {printf("%s",yytext);
     return -1; }
%%
