%option noyywrap yylineno
%option outfile="lexer.c" header-file="lexer.h"
%{
#include "lang.h"
#include "parser.h"
#include "lib.h"
%}

%%

"var" {
    return TM_VAR;
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


"int" {
    return TM_INTTYPE;
}

"char" {
    return TM_CHARTYPE;
}

"while" {
    return TM_WHILE;
}

"DO" {
    return TM_DO;
}

"IF" {
    return TM_IF;
}

"THEN" {
    return TM_THEN;
}

"ELSE" {
    return TM_ELSE;
}

"FOR" {
    return TM_FOR;
}

"LOCAL" {
    return TM_LOCAL;
}

"IN" {
    return TM_IN;
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
