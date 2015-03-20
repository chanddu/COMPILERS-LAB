/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "sil.y"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex.yy.c"
int yylex(void);
void yyerror(char *);

tnode	*thead = NULL;

lsymbol *lhead = NULL;
lsymbol *llast = NULL;

gsymbol *ghead = NULL;
gsymbol *glast = NULL;

int vartype;
int label=1,regcount=0,mem_loc;
int val,arr;

int evaltree(tnode *);
void typecheck(tnode *,tnode *,tnode *);

struct Tnode *treecreate(int ,int ,char *,int ,tnode *, tnode *, tnode *,lsymbol *);

lsymbol *Llookup(char *);
void Linstall(char *,int);
gsymbol *Glookup(char *);
void Ginstall(char *,int,int);
void typecheck(tnode *,tnode *,tnode *);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 35 "sil.y"
{
	struct Tnode *ptr;
}
/* Line 193 of yacc.c.  */
#line 198 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 211 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   329

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNRULES -- Number of states.  */
#define YYNSTATES  125

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    37,     2,     2,
      43,    44,    35,    33,    40,    34,     2,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    39,
       2,    38,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    41,     2,    42,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,    46,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,    10,    11,    14,    18,    20,    24,
      29,    31,    33,    35,    44,    48,    49,    53,    56,    58,
      62,    64,    69,    70,    74,    77,    81,    85,    89,    93,
      97,   101,   105,   109,   113,   117,   121,   125,   129,   133,
     135,   140,   142,   144,   146,   150,   152,   160,   165,   170,
     178,   186,   193,   197
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    49,    55,    -1,    27,    50,    28,    -1,
      -1,    50,    51,    -1,    54,    52,    39,    -1,    53,    -1,
      52,    40,    53,    -1,     4,    41,     3,    42,    -1,     4,
      -1,     7,    -1,    16,    -1,     7,    31,    43,    44,    45,
      56,    61,    46,    -1,    27,    57,    28,    -1,    -1,    57,
      58,    39,    -1,    54,    59,    -1,    60,    -1,    59,    40,
      60,    -1,     4,    -1,    29,    62,    66,    30,    -1,    -1,
      62,    65,    39,    -1,    32,    63,    -1,    63,    33,    63,
      -1,    63,    34,    63,    -1,    63,    35,    63,    -1,    63,
      36,    63,    -1,    63,    37,    63,    -1,    63,    10,    63,
      -1,    63,    11,    63,    -1,    63,     8,    63,    -1,    63,
       9,    63,    -1,    63,    12,    63,    -1,    63,    15,    63,
      -1,    63,    13,    63,    -1,    63,    14,    63,    -1,    43,
      63,    44,    -1,     3,    -1,     4,    41,    63,    42,    -1,
       4,    -1,    17,    -1,    18,    -1,    21,    62,    22,    -1,
      22,    -1,     5,    43,     4,    41,    63,    42,    44,    -1,
       5,    43,     4,    44,    -1,     6,    43,    63,    44,    -1,
      19,    43,    63,    44,    20,    62,    64,    -1,    23,    43,
      63,    44,    24,    62,    25,    -1,     4,    41,    63,    42,
      38,    63,    -1,     4,    38,    63,    -1,    26,    63,    39,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    52,    52,    55,    58,    59,    62,    65,    66,    69,
      70,    73,    74,    77,    80,    83,    84,    87,    90,    91,
      94,    97,   100,   101,   110,   115,   120,   125,   130,   135,
     140,   145,   150,   155,   160,   165,   169,   173,   177,   178,
     179,   209,   231,   232,   235,   236,   239,   269,   300,   320,
     327,   333,   361,   388
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONST", "ID", "READ", "WRITE",
  "INTEGER", "GT", "GE", "LT", "LE", "EQ", "AND", "OR", "NE", "BOOLEAN",
  "TRUE", "FALSE", "IF", "THEN", "ELSE", "ENDIF", "WHILE", "DO",
  "ENDWHILE", "RETURN", "DECL", "ENDDECL", "BEGINING", "END", "MAIN",
  "NOT", "'+'", "'-'", "'*'", "'/'", "'%'", "'='", "';'", "','", "'['",
  "']'", "'('", "')'", "'{'", "'}'", "$accept", "Prog", "GDefblock",
  "GDefList", "GDecl", "GIdList", "GId", "Type", "Mainblock", "LDefblock",
  "LDefList", "LDecl", "LIdList", "LId", "Body", "StmtList", "expr",
  "endif", "Stmt", "RetStmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,    43,    45,    42,    47,    37,    61,    59,
      44,    91,    93,    40,    41,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    50,    50,    51,    52,    52,    53,
      53,    54,    54,    55,    56,    57,    57,    58,    59,    59,
      60,    61,    62,    62,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    66
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     0,     2,     3,     1,     3,     4,
       1,     1,     1,     8,     3,     0,     3,     2,     1,     3,
       1,     4,     0,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       4,     1,     1,     1,     3,     1,     7,     4,     4,     7,
       7,     6,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     4,     0,     0,     0,     1,     0,     2,    11,    12,
       3,     5,     0,     0,    10,     0,     7,     0,     0,     6,
       0,     0,     0,     8,     0,     9,    15,     0,     0,    22,
       0,    14,     0,     0,     0,    13,    20,    17,    18,    16,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    39,    41,    42,    43,     0,
       0,     0,    23,    21,    19,    52,     0,     0,     0,     0,
       0,     0,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    53,     0,     0,
      47,    48,     0,     0,     0,    38,    32,    33,    30,    31,
      34,    36,    37,    35,    25,    26,    27,    28,    29,     0,
       0,    22,    22,    40,    51,     0,     0,     0,    46,    22,
      45,    49,    50,     0,    44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,    11,    15,    16,    12,     7,    27,
      28,    33,    37,    38,    30,    34,    61,   121,    46,    47
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -106
static const yytype_int16 yypact[] =
{
     -25,  -106,     8,    14,    47,  -106,    -7,  -106,  -106,  -106,
    -106,  -106,     9,    15,    18,    17,  -106,    21,    58,  -106,
       9,    23,    20,  -106,    39,  -106,  -106,    45,    48,  -106,
      31,  -106,    75,    50,   279,  -106,  -106,    51,  -106,  -106,
     -29,    49,    59,    60,    61,    35,    62,    81,    75,    35,
      35,    86,    35,    35,    35,  -106,    64,  -106,  -106,    35,
      35,   214,  -106,  -106,  -106,   222,   134,   -21,    36,    73,
      85,    35,  -106,   122,    35,    35,    35,    35,    35,    35,
      35,    35,    35,    35,    35,    35,    35,  -106,    74,    35,
    -106,  -106,    93,    90,   169,  -106,   -18,   -18,   -18,   -18,
     117,   260,   230,   117,     6,     6,  -106,  -106,  -106,    35,
     179,  -106,  -106,  -106,   222,    71,   295,   284,  -106,  -106,
    -106,  -106,  -106,   306,  -106
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -106,  -106,  -106,  -106,  -106,  -106,    96,    95,  -106,  -106,
    -106,  -106,  -106,    76,  -106,  -105,   -49,  -106,  -106,  -106
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      65,    66,     1,    68,    69,    70,   116,   117,     5,    49,
      72,    73,    50,    14,   123,    82,    83,    84,    85,    86,
      89,     6,    94,    90,    13,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,    55,    56,
     110,    84,    85,    86,    74,    75,    76,    77,    78,    79,
      80,    81,    57,    58,     8,     8,    19,    20,    17,    18,
     114,    22,    25,     9,     9,    21,    26,    59,    24,    82,
      83,    84,    85,    86,    29,    10,    31,    35,    60,    36,
      91,    74,    75,    76,    77,    78,    79,    80,    81,    39,
      67,    48,    51,    74,    75,    76,    77,    78,    79,    80,
      81,    62,    52,    53,    54,    71,    82,    83,    84,    85,
      86,    63,   109,   111,   112,   118,    23,    92,    82,    83,
      84,    85,    86,    32,    64,    74,    75,    76,    77,    93,
      74,    75,    76,    77,    78,    79,    80,    81,     0,     0,
       0,     0,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    82,    83,    84,    85,    86,
       0,     0,     0,     0,     0,     0,    95,    82,    83,    84,
      85,    86,     0,     0,     0,     0,    88,    74,    75,    76,
      77,    78,    79,    80,    81,     0,     0,    74,    75,    76,
      77,    78,    79,    80,    81,     0,     0,     0,     0,     0,
       0,     0,    82,    83,    84,    85,    86,     0,     0,     0,
       0,   113,    82,    83,    84,    85,    86,     0,     0,     0,
       0,   115,    74,    75,    76,    77,    78,    79,    80,    81,
      74,    75,    76,    77,    78,    79,    80,    81,    74,    75,
      76,    77,    78,    79,     0,    81,     0,    82,    83,    84,
      85,    86,     0,    87,     0,    82,    83,    84,    85,    86,
       0,     0,     0,    82,    83,    84,    85,    86,    74,    75,
      76,    77,    78,     0,     0,    81,     0,     0,     0,     0,
       0,     0,     0,    40,    41,    42,     0,     0,    40,    41,
      42,     0,     0,    82,    83,    84,    85,    86,    43,    40,
      41,    42,    44,    43,     0,    45,     0,    44,     0,   122,
      40,    41,    42,     0,    43,     0,   119,   120,    44,     0,
       0,     0,     0,     0,     0,    43,     0,     0,   124,    44
};

static const yytype_int8 yycheck[] =
{
      49,    50,    27,    52,    53,    54,   111,   112,     0,    38,
      59,    60,    41,     4,   119,    33,    34,    35,    36,    37,
      41,     7,    71,    44,    31,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,     3,     4,
      89,    35,    36,    37,     8,     9,    10,    11,    12,    13,
      14,    15,    17,    18,     7,     7,    39,    40,    43,    41,
     109,     3,    42,    16,    16,    44,    27,    32,    45,    33,
      34,    35,    36,    37,    29,    28,    28,    46,    43,     4,
      44,     8,     9,    10,    11,    12,    13,    14,    15,    39,
       4,    40,    43,     8,     9,    10,    11,    12,    13,    14,
      15,    39,    43,    43,    43,    41,    33,    34,    35,    36,
      37,    30,    38,    20,    24,    44,    20,    44,    33,    34,
      35,    36,    37,    28,    48,     8,     9,    10,    11,    44,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,     8,     9,    10,    11,    12,    13,    14,    15,
      33,    34,    35,    36,    37,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    -1,    42,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    42,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    42,     8,     9,    10,    11,    12,    13,    14,    15,
       8,     9,    10,    11,    12,    13,    14,    15,     8,     9,
      10,    11,    12,    13,    -1,    15,    -1,    33,    34,    35,
      36,    37,    -1,    39,    -1,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    33,    34,    35,    36,    37,     8,     9,
      10,    11,    12,    -1,    -1,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     4,     5,     6,    -1,    -1,     4,     5,
       6,    -1,    -1,    33,    34,    35,    36,    37,    19,     4,
       5,     6,    23,    19,    -1,    26,    -1,    23,    -1,    25,
       4,     5,     6,    -1,    19,    -1,    21,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,    22,    23
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    27,    48,    49,    50,     0,     7,    55,     7,    16,
      28,    51,    54,    31,     4,    52,    53,    43,    41,    39,
      40,    44,     3,    53,    45,    42,    27,    56,    57,    29,
      61,    28,    54,    58,    62,    46,     4,    59,    60,    39,
       4,     5,     6,    19,    23,    26,    65,    66,    40,    38,
      41,    43,    43,    43,    43,     3,     4,    17,    18,    32,
      43,    63,    39,    30,    60,    63,    63,     4,    63,    63,
      63,    41,    63,    63,     8,     9,    10,    11,    12,    13,
      14,    15,    33,    34,    35,    36,    37,    39,    42,    41,
      44,    44,    44,    44,    63,    44,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    38,
      63,    20,    24,    42,    63,    42,    62,    62,    44,    21,
      22,    64,    25,    62,    22
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 52 "sil.y"
    { return evaltree((yyvsp[(2) - (2)].ptr)); }
    break;

  case 9:
#line 69 "sil.y"
    { Ginstall((yyvsp[(1) - (4)].ptr)->NAME,vartype,(yyvsp[(3) - (4)].ptr)->VALUE); }
    break;

  case 10:
#line 70 "sil.y"
    { Ginstall((yyvsp[(1) - (1)].ptr)->NAME,vartype,1); }
    break;

  case 11:
#line 73 "sil.y"
    { vartype = INT_VARTYPE; }
    break;

  case 12:
#line 74 "sil.y"
    { 	vartype = BOOL_VARTYPE; }
    break;

  case 13:
#line 77 "sil.y"
    { (yyval.ptr) = (yyvsp[(7) - (8)].ptr); }
    break;

  case 20:
#line 94 "sil.y"
    { Linstall((yyvsp[(1) - (1)].ptr)->NAME,vartype); }
    break;

  case 21:
#line 97 "sil.y"
    { (yyval.ptr) = (yyvsp[(2) - (4)].ptr);}
    break;

  case 22:
#line 100 "sil.y"
    { (yyval.ptr) = NULL; }
    break;

  case 23:
#line 101 "sil.y"
    {
									tnode *temp;
									temp = treecreate(DUMMY_TYPE,DUMMY_NODETYPE,NULL,0,NULL,NULL,NULL,NULL);
										temp->Ptr1=(yyvsp[(1) - (3)].ptr);
										temp->Ptr2=(yyvsp[(2) - (3)].ptr);
										(yyval.ptr)=temp;
									}
    break;

  case 24:
#line 110 "sil.y"
    {
									typecheck((yyvsp[(2) - (2)].ptr),(yyvsp[(1) - (2)].ptr),NULL);
									(yyvsp[(1) - (2)].ptr)->Ptr1 = (yyvsp[(2) - (2)].ptr);
									(yyval.ptr) = (yyvsp[(1) - (2)].ptr);
								}
    break;

  case 25:
#line 115 "sil.y"
    {
									typecheck((yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));
									(yyvsp[(2) - (3)].ptr)->Ptr1=(yyvsp[(1) - (3)].ptr);(yyvsp[(2) - (3)].ptr)->Ptr2=(yyvsp[(3) - (3)].ptr);
									(yyval.ptr)=(yyvsp[(2) - (3)].ptr); 
								}
    break;

  case 26:
#line 120 "sil.y"
    {
									typecheck((yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));
										(yyvsp[(2) - (3)].ptr)->Ptr1=(yyvsp[(1) - (3)].ptr);(yyvsp[(2) - (3)].ptr)->Ptr2=(yyvsp[(3) - (3)].ptr);
										(yyval.ptr)=(yyvsp[(2) - (3)].ptr);
								}
    break;

  case 27:
#line 125 "sil.y"
    {
									typecheck((yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));
										(yyvsp[(2) - (3)].ptr)->Ptr1=(yyvsp[(1) - (3)].ptr);(yyvsp[(2) - (3)].ptr)->Ptr2=(yyvsp[(3) - (3)].ptr);
										(yyval.ptr)=(yyvsp[(2) - (3)].ptr);
								}
    break;

  case 28:
#line 130 "sil.y"
    {
									typecheck((yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));
										(yyvsp[(2) - (3)].ptr)->Ptr1=(yyvsp[(1) - (3)].ptr);(yyvsp[(2) - (3)].ptr)->Ptr2=(yyvsp[(3) - (3)].ptr);
										(yyval.ptr)=(yyvsp[(2) - (3)].ptr);
								}
    break;

  case 29:
#line 135 "sil.y"
    {
									typecheck((yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));
										(yyvsp[(2) - (3)].ptr)->Ptr1=(yyvsp[(1) - (3)].ptr);(yyvsp[(2) - (3)].ptr)->Ptr2=(yyvsp[(3) - (3)].ptr);
										(yyval.ptr)=(yyvsp[(2) - (3)].ptr);
								}
    break;

  case 30:
#line 140 "sil.y"
    {
									typecheck((yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));
										(yyvsp[(2) - (3)].ptr)->Ptr1=(yyvsp[(1) - (3)].ptr);(yyvsp[(2) - (3)].ptr)->Ptr2=(yyvsp[(3) - (3)].ptr);
										(yyval.ptr)=(yyvsp[(2) - (3)].ptr);
								}
    break;

  case 31:
#line 145 "sil.y"
    {
									typecheck((yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));
										(yyvsp[(2) - (3)].ptr)->Ptr1=(yyvsp[(1) - (3)].ptr);(yyvsp[(2) - (3)].ptr)->Ptr2=(yyvsp[(3) - (3)].ptr);
										(yyval.ptr)=(yyvsp[(2) - (3)].ptr);
								}
    break;

  case 32:
#line 150 "sil.y"
    {
									typecheck((yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));
										(yyvsp[(2) - (3)].ptr)->Ptr1=(yyvsp[(1) - (3)].ptr);(yyvsp[(2) - (3)].ptr)->Ptr2=(yyvsp[(3) - (3)].ptr);
										(yyval.ptr)=(yyvsp[(2) - (3)].ptr);
								}
    break;

  case 33:
#line 155 "sil.y"
    {
									typecheck((yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));
										(yyvsp[(2) - (3)].ptr)->Ptr1=(yyvsp[(1) - (3)].ptr);(yyvsp[(2) - (3)].ptr)->Ptr2=(yyvsp[(3) - (3)].ptr);
										(yyval.ptr)=(yyvsp[(2) - (3)].ptr);
								}
    break;

  case 34:
#line 160 "sil.y"
    {
									typecheck((yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));
										(yyvsp[(2) - (3)].ptr)->Ptr1=(yyvsp[(1) - (3)].ptr);(yyvsp[(2) - (3)].ptr)->Ptr2=(yyvsp[(3) - (3)].ptr);
										(yyval.ptr)=(yyvsp[(2) - (3)].ptr);
								}
    break;

  case 35:
#line 165 "sil.y"
    { typecheck((yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));
										(yyvsp[(2) - (3)].ptr)->Ptr1=(yyvsp[(1) - (3)].ptr);(yyvsp[(2) - (3)].ptr)->Ptr2=(yyvsp[(3) - (3)].ptr);
										(yyval.ptr)=(yyvsp[(2) - (3)].ptr);
								}
    break;

  case 36:
#line 169 "sil.y"
    { typecheck((yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));
									(yyvsp[(2) - (3)].ptr)->Ptr1=(yyvsp[(1) - (3)].ptr);(yyvsp[(2) - (3)].ptr)->Ptr2=(yyvsp[(3) - (3)].ptr);
										(yyval.ptr)=(yyvsp[(2) - (3)].ptr);
								}
    break;

  case 37:
#line 173 "sil.y"
    { typecheck((yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));
										(yyvsp[(2) - (3)].ptr)->Ptr1=(yyvsp[(1) - (3)].ptr);(yyvsp[(2) - (3)].ptr)->Ptr2=(yyvsp[(3) - (3)].ptr);
										(yyval.ptr)=(yyvsp[(2) - (3)].ptr);
								}
    break;

  case 38:
#line 177 "sil.y"
    { (yyval.ptr)=(yyvsp[(2) - (3)].ptr);}
    break;

  case 39:
#line 178 "sil.y"
    { (yyval.ptr)=(yyvsp[(1) - (1)].ptr);}
    break;

  case 40:
#line 179 "sil.y"
    {
									gsymbol *gtemp;
									gtemp = Glookup((yyvsp[(1) - (4)].ptr)->NAME);
									if(gtemp)	{
										(yyvsp[(1) - (4)].ptr)->Gentry = gtemp;
										if((yyvsp[(3) - (4)].ptr)->TYPE==BOOLEAN_TYPE)
											yyerror("invalid array index");
										else if ((yyvsp[(3) - (4)].ptr)->TYPE == VOID_TYPE){
											if ((yyvsp[(3) - (4)].ptr)->NODETYPE==ID_NODETYPE)	{
											if((yyvsp[(3) - (4)].ptr)->Gentry)	{
												if((yyvsp[(3) - (4)].ptr)->Gentry->TYPE==BOOL_VARTYPE)
													yyerror("invalid array index");
											}
											else	{
												if((yyvsp[(3) - (4)].ptr)->Lentry->TYPE==BOOL_VARTYPE)
													yyerror("invalid array index");
											}
											}
											else	{
												yyerror("not id type right child");
											}
										}
									}
									else	{
									printf("\nYou have not declared %s ",(yyvsp[(1) - (4)].ptr)->NAME);
										yyerror("");
									}
									(yyvsp[(1) - (4)].ptr)->Ptr1 = (yyvsp[(3) - (4)].ptr);
									(yyval.ptr) = (yyvsp[(1) - (4)].ptr);
								}
    break;

  case 41:
#line 209 "sil.y"
    {
								lsymbol *ltemp;
									gsymbol *gtemp;
									ltemp = Llookup((yyvsp[(1) - (1)].ptr)->NAME);
									if(!ltemp)	{
										gtemp = Glookup((yyvsp[(1) - (1)].ptr)->NAME) ;
										if(gtemp)	{
											(yyvsp[(1) - (1)].ptr)->Gentry = gtemp;
											if((gtemp->SIZE)>1)	{
												yyerror("\nInvalid array index");
											}
										}
										else	{
											printf("\nYou have not declared %s ",(yyvsp[(1) - (1)].ptr)->NAME);
											yyerror("");
										}
									}
									else	{
										(yyvsp[(1) - (1)].ptr)->Lentry = ltemp;
									}
									(yyval.ptr) = (yyvsp[(1) - (1)].ptr);
								}
    break;

  case 42:
#line 231 "sil.y"
    { (yyval.ptr)=(yyvsp[(1) - (1)].ptr);}
    break;

  case 43:
#line 232 "sil.y"
    { (yyval.ptr)=(yyvsp[(1) - (1)].ptr);}
    break;

  case 44:
#line 235 "sil.y"
    { (yyval.ptr)=(yyvsp[(2) - (3)].ptr);}
    break;

  case 45:
#line 236 "sil.y"
    { (yyval.ptr)=NULL; }
    break;

  case 46:
#line 239 "sil.y"
    {
									gsymbol *gtemp;
									gtemp = Glookup((yyvsp[(3) - (7)].ptr)->NAME);
									if(gtemp)	{
										(yyvsp[(3) - (7)].ptr)->Gentry = gtemp;
										if((yyvsp[(3) - (7)].ptr)->Gentry->TYPE==BOOL_VARTYPE)	{
											printf("ERR : Trying to read value for boolean variable %s \n",(yyvsp[(3) - (7)].ptr)->NAME);
												yyerror("");
										}
										if((yyvsp[(5) - (7)].ptr)->TYPE==BOOLEAN_TYPE)
											yyerror("invalid array index");
										else if(((yyvsp[(5) - (7)].ptr)->TYPE==VOID_TYPE) && ((yyvsp[(5) - (7)].ptr)->NODETYPE==ID_NODETYPE))	{
											if((yyvsp[(5) - (7)].ptr)->Gentry)	{
												if((yyvsp[(5) - (7)].ptr)->Gentry->TYPE==BOOL_VARTYPE)
													yyerror("invalid array index");
											}
											else	{
												if((yyvsp[(5) - (7)].ptr)->Lentry->TYPE==BOOL_VARTYPE) 
													yyerror("invalid array index");
											}
										}
									}
									else	{
									printf("\nYou have not declared %s ",(yyvsp[(3) - (7)].ptr)->NAME);
										yyerror("");
									}
									(yyvsp[(3) - (7)].ptr)->Ptr1 = (yyvsp[(5) - (7)].ptr);
									(yyvsp[(1) - (7)].ptr)->Ptr1 = (yyvsp[(3) - (7)].ptr);
									(yyval.ptr) = (yyvsp[(1) - (7)].ptr);
								}
    break;

  case 47:
#line 269 "sil.y"
    {
									lsymbol *ltemp;
									gsymbol *gtemp;
									ltemp = Llookup((yyvsp[(3) - (4)].ptr)->NAME);
									if(!ltemp)	{
										gtemp = Glookup((yyvsp[(3) - (4)].ptr)->NAME) ;
										if(gtemp)	{
											(yyvsp[(3) - (4)].ptr)->Gentry = gtemp;
											if((gtemp->SIZE)>1)	{
												yyerror("\nInvalid array index");
											}
											if(gtemp->TYPE!=INT_VARTYPE)	{
												printf("ERR : Trying to read value for boolean variable %s \n",(yyvsp[(3) - (4)].ptr)->NAME);
												yyerror("ERR : Trying to read value for boolean variable ");
										}
										}
										else	{
											printf("\nYou have not declared %s ",(yyvsp[(3) - (4)].ptr)->NAME);
											yyerror("");
										}
									}
									else	{
										(yyvsp[(3) - (4)].ptr)->Lentry = ltemp;
										if((yyvsp[(3) - (4)].ptr)->Lentry->TYPE!=INT_VARTYPE)	{
											printf("ERR : Trying to read value for boolean variable %s \n",(yyvsp[(3) - (4)].ptr)->NAME);
											yyerror("ERR : Trying to read value for boolean variable");
										}
									}
									(yyvsp[(1) - (4)].ptr)->Ptr1 = (yyvsp[(3) - (4)].ptr);
									(yyval.ptr) = (yyvsp[(1) - (4)].ptr);
								}
    break;

  case 48:
#line 300 "sil.y"
    {
									if((yyvsp[(3) - (4)].ptr)->TYPE==BOOLEAN_TYPE)
												yyerror("ERR : Writing boolean value");
										if((yyvsp[(3) - (4)].ptr)->TYPE==VOID_TYPE)	{
											if((yyvsp[(3) - (4)].ptr)->NODETYPE==ID_NODETYPE)	{
												if((yyvsp[(3) - (4)].ptr)->Lentry)	{
												if((yyvsp[(3) - (4)].ptr)->Lentry->TYPE==BOOL_VARTYPE)	{
													yyerror("ERR : Writing boolean value");
												}
											}
											else if((yyvsp[(3) - (4)].ptr)->Gentry)	{
												if((yyvsp[(3) - (4)].ptr)->Gentry->TYPE==BOOL_VARTYPE)	{
													yyerror("ERR : writing boolean value");
												}
											}
										}
									}
									(yyvsp[(1) - (4)].ptr)->Ptr1=(yyvsp[(3) - (4)].ptr);
										(yyval.ptr) = (yyvsp[(1) - (4)].ptr);
								}
    break;

  case 49:
#line 320 "sil.y"
    {
									typecheck((yyvsp[(3) - (7)].ptr),(yyvsp[(1) - (7)].ptr),NULL);
									(yyvsp[(1) - (7)].ptr)->Ptr1=(yyvsp[(3) - (7)].ptr);
									(yyvsp[(1) - (7)].ptr)->Ptr2=(yyvsp[(6) - (7)].ptr);
									(yyvsp[(1) - (7)].ptr)->Ptr3=(yyvsp[(7) - (7)].ptr);
									(yyval.ptr)=(yyvsp[(1) - (7)].ptr);
								}
    break;

  case 50:
#line 327 "sil.y"
    {
									typecheck((yyvsp[(3) - (7)].ptr),(yyvsp[(1) - (7)].ptr),NULL);
										(yyvsp[(1) - (7)].ptr)->Ptr1=(yyvsp[(3) - (7)].ptr);
										(yyvsp[(1) - (7)].ptr)->Ptr2=(yyvsp[(6) - (7)].ptr);
										(yyval.ptr)=(yyvsp[(1) - (7)].ptr);
								}
    break;

  case 51:
#line 333 "sil.y"
    {
									gsymbol *gtemp;
									gtemp = Glookup((yyvsp[(1) - (6)].ptr)->NAME);
									if(gtemp)	{
										(yyvsp[(1) - (6)].ptr)->Gentry = gtemp;
										if((yyvsp[(3) - (6)].ptr)->TYPE==BOOLEAN_TYPE)
											yyerror("ERR : invalid array index");
										else if (((yyvsp[(3) - (6)].ptr)->TYPE==VOID_TYPE) && ((yyvsp[(3) - (6)].ptr)->NODETYPE=ID_NODETYPE))	{
											if((yyvsp[(3) - (6)].ptr)->Gentry)	{
												if((yyvsp[(3) - (6)].ptr)->Gentry->TYPE==BOOL_VARTYPE)
													yyerror("invalid array index");
											}
											else	{
												if((yyvsp[(3) - (6)].ptr)->Lentry->TYPE==BOOL_VARTYPE)
													yyerror("invalid array index");
											}
										}
									}
									else	{
									printf("\nYou have not declared %s ",(yyvsp[(1) - (6)].ptr)->NAME);
										yyerror("");
									}
									typecheck((yyvsp[(1) - (6)].ptr),(yyvsp[(5) - (6)].ptr),(yyvsp[(6) - (6)].ptr));
									(yyvsp[(1) - (6)].ptr)->Ptr1 = (yyvsp[(3) - (6)].ptr);
									(yyvsp[(5) - (6)].ptr)->Ptr1 = (yyvsp[(1) - (6)].ptr);
									(yyvsp[(5) - (6)].ptr)->Ptr2 = (yyvsp[(6) - (6)].ptr);
									(yyval.ptr) = (yyvsp[(5) - (6)].ptr);
								}
    break;

  case 52:
#line 361 "sil.y"
    {
								lsymbol *ltemp;
									gsymbol *gtemp;
									ltemp = Llookup((yyvsp[(1) - (3)].ptr)->NAME);
									if(!ltemp)	{
										gtemp = Glookup((yyvsp[(1) - (3)].ptr)->NAME) ;
										if(gtemp)	{
											(yyvsp[(1) - (3)].ptr)->Gentry = gtemp;
											if((gtemp->SIZE)>1)	{
												yyerror("\nInvalid array index");
											}
										}
										else	{
											printf("\nYou have not declared %s ",(yyvsp[(1) - (3)].ptr)->NAME);
											yyerror("");
										}
									}
									else	{
										(yyvsp[(1) - (3)].ptr)->Lentry = ltemp;
									}
									typecheck((yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));
									(yyvsp[(2) - (3)].ptr)->Ptr1=(yyvsp[(1) - (3)].ptr);
									(yyvsp[(2) - (3)].ptr)->Ptr2=(yyvsp[(3) - (3)].ptr);
									(yyval.ptr) = (yyvsp[(2) - (3)].ptr);
								}
    break;

  case 53:
#line 388 "sil.y"
    { typecheck((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),NULL); }
    break;


/* Line 1267 of yacc.c.  */
#line 1995 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 392 "sil.y"


int main (int argc, char* argv[]) {
	if(argc > 1)
	{
		FILE *fp = fopen(argv[1], "r");
		if(fp)
			yyin = fp;
	}
	yyparse();
	return 0;
}

void yyerror (char *msg)	{
	fprintf (stderr, "%s\n", msg);
	exit(1);
}

struct Tnode *treecreate(int type,int nodetype,char *name,int value,tnode *ptr1, tnode *ptr2, tnode *ptr3,lsymbol *lentry) {
	tnode *temp=(tnode *)malloc(sizeof(tnode));
	temp->TYPE=type;
	temp->NODETYPE=nodetype;
	temp->NAME=name;
	temp->VALUE=value;
	temp->Ptr1=ptr1;
	temp->Ptr2=ptr2;
	temp->Ptr3=ptr3;
	temp->Lentry=lentry;
	return(temp);
}

lsymbol *Llookup(char *name)	{
	lsymbol *temp = lhead;
	while(temp)	{
		if(strcmp(name,temp->NAME)==0) 
			return temp;
		temp = temp->NEXT;
	}
	return NULL;
}

void typecheck(tnode *t1,tnode *t2,tnode *t3) {
	int flag = 1; int type;
	switch(t2->TYPE)	{
		case INT_TYPE :
					switch(t2->NODETYPE)	{
						case PLUS_NODETYPE :
						case MINUS_NODETYPE :
						case MULT_NODETYPE :
						case DIV_NODETYPE :
						case MODULO_NODETYPE :
									if((t1->TYPE==BOOLEAN_TYPE)||(t3->TYPE==BOOLEAN_TYPE))		// no boolean for -+* and div
										flag=0;
									if(t1->TYPE==VOID_TYPE)	{
										if(t1->Lentry!=NULL)	{							//check for entry in local symbol table
											if(t1->Lentry->TYPE!=INT_VARTYPE)
												flag=0;
										}
									else{
										if(t1->Gentry->TYPE!=INT_VARTYPE)
											flag=0;
									}
									}
									if(t3->TYPE==VOID_TYPE)	{
										if(t3->NODETYPE!=ID_NODETYPE)
											flag=0;
									if(t3->Lentry)	{
										if(t3->Lentry->TYPE!=INT_VARTYPE)
											flag=0;
									}
									else	{
										if(t3->Gentry->TYPE!=INT_VARTYPE)
											flag=0;
									}
									}
									break;
					case ASSIGN_NODETYPE :
									if(t1->Lentry!=NULL)	{
										type=t1->Lentry->TYPE;
									}
									else	{
										type=t1->Gentry->TYPE;
									}
									if(type==INT_VARTYPE) { 
										if(t3->TYPE==BOOLEAN_TYPE)	{
											flag=0;
										}
										else if(t3->TYPE==VOID_TYPE)	{
											if(t3->Lentry)	{
												if(t3->Lentry->TYPE==BOOL_VARTYPE)	{
													flag=0;
												}
											}
											else	{
												if(t3->Gentry->TYPE==BOOL_VARTYPE)	{
													flag=0;
												}
											}
										}
									}
									else	{
										if(t3->TYPE==INT_TYPE)	{
											flag=0;
										}
										else if(t3->TYPE==VOID_TYPE) {
										if(t3->Lentry) {
											if(t3->Lentry->TYPE==INT_VARTYPE)	{
												flag=0;
											}
										}
										else	{
											if(t3->Gentry->TYPE==INT_VARTYPE)	{
												flag=0;
											}
										}
										}
									}
									if(!flag)	{
										printf("ERR : Type mismatch for %s \n",t1->Lentry->NAME);
										yyerror("");
									}
									break;
					}
					break;
		case BOOLEAN_TYPE :
					switch(t2->NODETYPE)	{
						case LT_NODETYPE :
						case LE_NODETYPE :
						case GT_NODETYPE :
						case GE_NODETYPE :
						case EQ_NODETYPE :
						case NE_NODETYPE :
										if((t1->TYPE==BOOLEAN_TYPE)||(t3->TYPE==BOOLEAN_TYPE))
												flag=0;

											else if(t1->TYPE==VOID_TYPE)	{
								if(t1->NODETYPE!=ID_NODETYPE)
											flag=0;

										if(t1->Lentry)	{

											if(t1->Lentry->TYPE!=INT_VARTYPE)
												flag=0;

										}
										else	{
											if(t1->Gentry->TYPE!=INT_VARTYPE)
												flag=0;

										}
										}

										else if(t3->TYPE==VOID_TYPE)	{
									if(t3->NODETYPE!=ID_NODETYPE)
											flag=0;

										if(t3->Lentry)	{

											if(t3->Lentry->TYPE!=INT_VARTYPE)
												flag=0;
										}
										else	{
											if(t3->Gentry->TYPE!=INT_VARTYPE)
												flag=0;
										}
											}
											break;
						case AND_NODETYPE :
						case OR_NODETYPE :
										if((t1->TYPE==INT_TYPE)||(t3->TYPE==INT_TYPE))
											flag = 0;
										else if(t1->TYPE==VOID_TYPE)	{
								if(t1->NODETYPE!=ID_NODETYPE)
											flag=0;

										if(t1->Lentry)	{
											if(t1->Lentry->TYPE!=BOOL_VARTYPE)
												flag=0;
										}
										else	{
											if(t1->Gentry->TYPE!=BOOL_VARTYPE)
												flag=0;
										}
									}
										else if(t3->TYPE==VOID_TYPE)	{
									if(t3->NODETYPE!=ID_NODETYPE)
											flag=0;

										if(t3->Lentry)	{
											if(t3->Lentry->TYPE!=BOOL_VARTYPE)
												flag=0;
										}
										else	{
											if(t3->Gentry->TYPE!=BOOL_VARTYPE)
												flag=0;
										}
											}
											break;

							case NOT_NODETYPE :
										if(t1->TYPE==INT_TYPE)
											flag=0;
										else if(t1->TYPE==VOID_TYPE)	{

											if(t1->NODETYPE!=ID_NODETYPE)	{
												flag=0;
											}

											else {

												if(t1->Lentry)	{

													if(t1->Lentry->TYPE!=BOOL_VARTYPE)
														flag=0;
												}

												else if(t1->Gentry)	{
													if(t1->Gentry->TYPE!=BOOL_VARTYPE)
														flag=0;
												}

											}
										}
										break;
					}
					break;
		case VOID_TYPE :
					switch(t2->NODETYPE)	{
						case IF_NODETYPE :
										if(t1->TYPE==INT_TYPE)
											flag=0;
										else if(t1->TYPE==VOID_TYPE)	{
											if(t1->NODETYPE!=ID_NODETYPE)
											flag=0;
										if(t1->Lentry)	{
											if(t1->Lentry->TYPE!=BOOL_VARTYPE)
												flag=0;
										}
										else {

										if(t1->Gentry->TYPE!=BOOL_VARTYPE)
											flag=0;
										}
									}
										break;
						case WHILE_NODETYPE :
										if(t1->TYPE==INT_TYPE)
											flag=0;
										else if(t1->TYPE==VOID_TYPE)	{
											if(t1->NODETYPE!=ID_NODETYPE)
											flag=0;
										if(t1->Lentry)	{
											if(t1->Lentry->TYPE!=BOOL_VARTYPE)
												flag=0;
										}
										else {

										if(t1->Gentry->TYPE!=BOOL_VARTYPE)
											flag=0;
										}
									}
										break;
						case RETURN_NODETYPE :
									if(t1->TYPE==BOOLEAN_TYPE)	{
										flag = 0;
									}
									else if(t1->TYPE==VOID_TYPE)	{
										if(t1->NODETYPE!=ID_NODETYPE)	{
											flag = 0;
										}
										if(t1->Lentry)	{
											if(t1->Lentry->TYPE!=INT_VARTYPE)	{
											flag=0;
											}
										}
										else {
											if(t1->Gentry->TYPE!=INT_VARTYPE)
												flag=0;
										}
									}
					}
					break;
	}
	if(!flag)	{
		printf("ERR : Type mismatch at %d %d\n",t2->TYPE,t2->NODETYPE	);
		yyerror("");
	}
}

void Linstall(char *name,int type)	{
	lsymbol *temp;
	temp = Llookup(name);
	if(temp)	{
		printf("You have already declared %s ",name);
		yyerror("");
	}
	else	{
		temp = (lsymbol *)malloc(sizeof(lsymbol));
		temp->NAME = name;
		temp->TYPE = type;
		temp->BINDING = (int *)malloc(sizeof(int));
		*(temp->BINDING) = mem_loc;
		mem_loc = mem_loc + 1;
		temp->NEXT = NULL;
		if(lhead==NULL)
			lhead = llast = temp;
		else	{
			llast->NEXT = temp;
			llast = temp;
		}
	}
}

gsymbol *Glookup(char *name)	{
	gsymbol *temp = ghead;
	while(temp)	{
		if(strcmp(name,temp->NAME)==0) 
			return temp;
		temp = temp->NEXT;
	}
	return NULL;
}

void Ginstall(char *name,int type,int size)	{
	gsymbol *temp;
	temp = Glookup(name);
	if(temp)	{
		printf("You have already declared %s ",name);
		yyerror("");
	}
	else	{
		temp = (gsymbol *)malloc(sizeof(gsymbol));
		temp->NAME = name;
		temp->TYPE = type;
		temp->SIZE = size;
		temp->BINDING = (int *)malloc(sizeof(int));
		*(temp->BINDING) = mem_loc;
		mem_loc = mem_loc+size;
		temp->NEXT = NULL;
		if(ghead==NULL)
			ghead = glast = temp;
		else	{
			glast->NEXT = temp;
			glast = temp;
		}
	}
}

int evaltree(tnode *temp)	{
	int temp_label,*addr;
	if(temp)	{
		switch(temp->TYPE)	{
			case DUMMY_TYPE :	evaltree(temp->Ptr1);
						evaltree(temp->Ptr2);
						break;
			case VOID_TYPE : 
				switch(temp->NODETYPE)	{
					case READ_NODETYPE : 
								printf("READ %s:",temp->Ptr1->NAME);
								scanf("%d",&val);
								if(temp->Ptr1->Gentry)	{
									if((temp->Ptr1->Gentry->SIZE)>1)	{
										arr = evaltree(temp->Ptr1->Ptr1);         // array Index
										addr = temp->Ptr1->Gentry->BINDING;
										addr = addr + arr;
										*addr = val;
									}
									else	{
										*(temp->Ptr1->Gentry->BINDING) = val;
									}
								}
								else if(temp->Ptr1->Lentry)	{
									*(temp->Ptr1->Lentry->BINDING)=val;
								}
								else
									printf("\nNo memory allocated for var");
								//temp->Ptr1->VALUE = val;
								break;
					case WRITE_NODETYPE :
								printf("%d\n",evaltree(temp->Ptr1));
								break;
					case ID_NODETYPE :
								if(temp->Gentry)	{
									if((temp->Gentry->SIZE)>1)	{
										arr = evaltree(temp->Ptr1);
										if((arr<0)||(arr>=(temp->Gentry->SIZE)))	{
											printf("%d\n",arr);
											yyerror("Invalid array index");
										}
										addr = temp->Gentry->BINDING;
										addr = addr+arr;
									}
									else	{
										addr = temp->Gentry->BINDING;
									}
								}
								else if(temp->Lentry)	{
									addr = temp->Lentry->BINDING;
								}
								else 
									printf("No memory allocated for variable\n");
								return(*addr);
								break;
					case IF_NODETYPE :
								if(evaltree(temp->Ptr1)==1)	{
									evaltree(temp->Ptr2);
								}
								else	{
									evaltree(temp->Ptr3);
								}
								break;
					case WHILE_NODETYPE : 
								while(evaltree(temp->Ptr1)==1)	{
									evaltree(temp->Ptr2);
								}
					case RETURN_NODETYPE :
								return evaltree(temp->Ptr1);
								break;
					}
							break;
			case INT_TYPE : 
				switch(temp->NODETYPE)	{
				case NUMBER_NODETYPE :	
							return(temp->VALUE);
							break;
				case PLUS_NODETYPE :
							return(evaltree(temp->Ptr1)+evaltree(temp->Ptr2));
							break;
				case MINUS_NODETYPE :	
							return(evaltree(temp->Ptr1)-evaltree(temp->Ptr2));
							break;
				case MULT_NODETYPE :	
							return(evaltree(temp->Ptr1)*evaltree(temp->Ptr2));
							break;
				case DIV_NODETYPE :
							return(evaltree(temp->Ptr1)/evaltree(temp->Ptr2));
							break;
				case ASSIGN_NODETYPE :
							if(temp->Ptr1->Lentry)
								*(temp->Ptr1->Lentry->BINDING) = evaltree(temp->Ptr2);
							else if(temp->Ptr1->Gentry)	{
								if((temp->Ptr1->Gentry->SIZE)>1)	{
									addr = temp->Ptr1->Gentry->BINDING;
									addr = addr + evaltree(temp->Ptr1->Ptr1);
									*addr = evaltree(temp->Ptr2);
								}
								else{
									*(temp->Ptr1->Gentry->BINDING) = evaltree(temp->Ptr2);
								}
							}
							break;
				case MODULO_NODETYPE :	
							return(evaltree(temp->Ptr1)%evaltree(temp->Ptr2));
							break;
				}
				break;
			case BOOLEAN_TYPE : 
				switch(temp->NODETYPE)	{
				case NOT_NODETYPE :	
							val = evaltree(temp->Ptr1);
							return(!val);
							break;
				case LT_NODETYPE :
							val=((evaltree(temp->Ptr1))<(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case LE_NODETYPE :
							val=((evaltree(temp->Ptr1))<=(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case GT_NODETYPE :
							val=((evaltree(temp->Ptr1))>(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case GE_NODETYPE :
							val=((evaltree(temp->Ptr1))>=(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case EQ_NODETYPE :
							val=((evaltree(temp->Ptr1))==(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case NE_NODETYPE :
							val=((evaltree(temp->Ptr1))!=(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case AND_NODETYPE :
							val=((evaltree(temp->Ptr1))&&(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case OR_NODETYPE :
							val=((evaltree(temp->Ptr1))||(evaltree(temp->Ptr2)))?1 :0;
							return val;
							break;
				case TRUE_NODETYPE :
							return(1);
							break;
				case FALSE_NODETYPE :
							return(0);
							break;
					}
					break;
		}
	}
}


