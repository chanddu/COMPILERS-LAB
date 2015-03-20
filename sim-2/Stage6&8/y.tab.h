/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CONST = 258,
     ID = 259,
     READ = 260,
     WRITE = 261,
     INTEGER = 262,
     GT = 263,
     GE = 264,
     LT = 265,
     LE = 266,
     EQ = 267,
     AND = 268,
     OR = 269,
     NE = 270,
     BOOLEAN = 271,
     TRUE = 272,
     FALSE = 273,
     IF = 274,
     THEN = 275,
     ELSE = 276,
     ENDIF = 277,
     WHILE = 278,
     DO = 279,
     ENDWHILE = 280,
     RETURN = 281,
     DECL = 282,
     ENDDECL = 283,
     BEGINING = 284,
     END = 285,
     MAIN = 286,
     NOT = 287
   };
#endif
/* Tokens.  */
#define CONST 258
#define ID 259
#define READ 260
#define WRITE 261
#define INTEGER 262
#define GT 263
#define GE 264
#define LT 265
#define LE 266
#define EQ 267
#define AND 268
#define OR 269
#define NE 270
#define BOOLEAN 271
#define TRUE 272
#define FALSE 273
#define IF 274
#define THEN 275
#define ELSE 276
#define ENDIF 277
#define WHILE 278
#define DO 279
#define ENDWHILE 280
#define RETURN 281
#define DECL 282
#define ENDDECL 283
#define BEGINING 284
#define END 285
#define MAIN 286
#define NOT 287




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 35 "sil.y"
{
	struct Tnode *ptr;
}
/* Line 1529 of yacc.c.  */
#line 117 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

