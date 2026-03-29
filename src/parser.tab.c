
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "util.h"

extern FILE *yyin;
extern int lineNo;
extern int yylex(void); // Chamada do scanner
extern char *yytext;

void yyerror(const char *s);

TreeNode *AST = NULL;


/* Line 189 of yacc.c  */
#line 91 "parser.tab.c"

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     ID = 259,
     IF = 260,
     ELSE = 261,
     INT = 262,
     RETURN = 263,
     VOID = 264,
     WHILE = 265,
     SOMA = 266,
     SUB = 267,
     MUL = 268,
     DIV = 269,
     MENOR = 270,
     MENOR_IGUAL = 271,
     MAIOR = 272,
     MAIOR_IGUAL = 273,
     IGUAL_IGUAL = 274,
     DIFERENTE = 275,
     ATRIBUICAO = 276,
     PONTO_VIRGULA = 277,
     VIRGULA = 278,
     ABRE_PARENTESE = 279,
     FECHA_PARENTESE = 280,
     ABRE_COLCHETE = 281,
     FECHA_COLCHETE = 282,
     ABRE_CHAVE = 283,
     FECHA_CHAVE = 284,
     ERROR = 285
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 18 "parser.y"

    TreeNode *tree;
    int val;
    char *name;
    ExpType type;



/* Line 214 of yacc.c  */
#line 166 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 178 "parser.tab.c"

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
# if YYENABLE_NLS
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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   97

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNRULES -- Number of states.  */
#define YYNSTATES  103

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    18,    25,
      27,    29,    30,    38,    40,    42,    46,    48,    51,    56,
      61,    64,    65,    68,    69,    71,    73,    75,    77,    79,
      82,    84,    90,    98,   104,   107,   111,   115,   117,   119,
     124,   128,   130,   132,   134,   136,   138,   140,   142,   146,
     148,   150,   152,   156,   158,   160,   162,   166,   168,   170,
     172,   177,   179,   180,   184
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      32,     0,    -1,    33,    -1,    33,    34,    -1,    34,    -1,
      35,    -1,    37,    -1,    36,     4,    22,    -1,    36,     4,
      26,     3,    27,    22,    -1,     7,    -1,     9,    -1,    -1,
      36,     4,    38,    24,    39,    25,    42,    -1,    40,    -1,
       9,    -1,    40,    23,    41,    -1,    41,    -1,    36,     4,
      -1,    36,     4,    26,    27,    -1,    28,    43,    44,    29,
      -1,    43,    35,    -1,    -1,    44,    45,    -1,    -1,    46,
      -1,    42,    -1,    47,    -1,    48,    -1,    49,    -1,    50,
      22,    -1,    22,    -1,     5,    24,    50,    25,    45,    -1,
       5,    24,    50,    25,    45,     6,    45,    -1,    10,    24,
      50,    25,    45,    -1,     8,    22,    -1,     8,    50,    22,
      -1,    51,    21,    50,    -1,    52,    -1,     4,    -1,     4,
      26,    50,    27,    -1,    54,    53,    54,    -1,    54,    -1,
      16,    -1,    15,    -1,    17,    -1,    18,    -1,    19,    -1,
      20,    -1,    54,    55,    56,    -1,    56,    -1,    11,    -1,
      12,    -1,    56,    57,    58,    -1,    58,    -1,    13,    -1,
      14,    -1,    24,    50,    25,    -1,    51,    -1,    59,    -1,
       3,    -1,     4,    24,    60,    25,    -1,    61,    -1,    -1,
      61,    23,    50,    -1,    50,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    90,    90,    97,   111,   119,   120,   124,   130,   142,
     143,   147,   147,   164,   165,   169,   180,   184,   189,   199,
     209,   220,   225,   236,   241,   242,   243,   244,   245,   250,
     251,   256,   261,   271,   280,   284,   292,   297,   302,   307,
     317,   324,   329,   330,   331,   332,   333,   334,   339,   347,
     352,   353,   358,   364,   369,   370,   375,   378,   379,   380,
     388,   397,   398,   403,   415
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "ID", "IF", "ELSE", "INT",
  "RETURN", "VOID", "WHILE", "SOMA", "SUB", "MUL", "DIV", "MENOR",
  "MENOR_IGUAL", "MAIOR", "MAIOR_IGUAL", "IGUAL_IGUAL", "DIFERENTE",
  "ATRIBUICAO", "PONTO_VIRGULA", "VIRGULA", "ABRE_PARENTESE",
  "FECHA_PARENTESE", "ABRE_COLCHETE", "FECHA_COLCHETE", "ABRE_CHAVE",
  "FECHA_CHAVE", "ERROR", "$accept", "programa", "declaracao_lista",
  "declaracao", "var_declaracao", "tipo_especificador", "fun_declaracao",
  "$@1", "params", "param_lista", "param", "composto_decl",
  "local_declaracoes", "statement_lista", "statement", "expressao_decl",
  "selecao_decl", "iteracao_decl", "retorno_decl", "expressao", "var",
  "simples_expressao", "relacional", "soma_expressao", "soma", "termo",
  "mult", "fator", "ativacao", "args", "arg_lista", 0
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
     285
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    35,    35,    36,
      36,    38,    37,    39,    39,    40,    40,    41,    41,    42,
      43,    43,    44,    44,    45,    45,    45,    45,    45,    46,
      46,    47,    47,    48,    49,    49,    50,    50,    51,    51,
      52,    52,    53,    53,    53,    53,    53,    53,    54,    54,
      55,    55,    56,    56,    57,    57,    58,    58,    58,    58,
      59,    60,    60,    61,    61
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     0,     7,     1,     1,     3,     1,     2,     4,     4,
       2,     0,     2,     0,     1,     1,     1,     1,     1,     2,
       1,     5,     7,     5,     2,     3,     3,     1,     1,     4,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       4,     1,     0,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     9,    10,     0,     2,     4,     5,     0,     6,     1,
       3,    11,     7,     0,     0,     0,     0,     0,    10,     0,
       0,    13,    16,     8,    17,     0,     0,     0,    21,    12,
      15,    18,    23,    20,     0,     0,     0,    59,    38,     0,
       0,     0,    30,     0,    19,    25,    22,    24,    26,    27,
      28,     0,    57,    37,    41,    49,    53,    58,    62,     0,
       0,    34,     0,     0,     0,    29,     0,    50,    51,    43,
      42,    44,    45,    46,    47,     0,     0,    54,    55,     0,
      64,     0,    61,     0,     0,    35,     0,    56,    36,    57,
      40,    48,    52,    60,     0,    39,     0,     0,    63,    31,
      33,     0,    32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,     8,    14,    20,    21,
      22,    45,    32,    35,    46,    47,    48,    49,    50,    51,
      52,    53,    75,    54,    76,    55,    79,    56,    57,    81,
      82
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -93
static const yytype_int8 yypact[] =
{
      50,   -93,   -93,    17,    50,   -93,   -93,     8,   -93,   -93,
     -93,   -12,   -93,    18,     0,    21,    51,    40,    14,    60,
      44,    47,   -93,   -93,    45,    46,    50,    48,   -93,   -93,
     -93,   -93,    50,   -93,    68,     3,   -12,   -93,    37,    49,
      12,    53,   -93,    -2,   -93,   -93,   -93,   -93,   -93,   -93,
     -93,    54,    57,   -93,    26,    52,   -93,   -93,    -2,    -2,
      -2,   -93,    58,    -2,    59,   -93,    -2,   -93,   -93,   -93,
     -93,   -93,   -93,   -93,   -93,    -2,    -2,   -93,   -93,    -2,
     -93,    61,    62,    55,    63,   -93,    64,   -93,   -93,   -93,
      56,    52,   -93,   -93,    -2,   -93,    25,    25,   -93,    73,
     -93,    25,   -93
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -93,   -93,   -93,    77,    65,    24,   -93,   -93,   -93,   -93,
      66,    69,   -93,   -93,   -92,   -93,   -93,   -93,   -93,   -40,
     -24,   -93,   -93,    15,   -93,     7,   -93,    16,   -93,   -93,
     -93
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -15
static const yytype_int8 yytable[] =
{
      62,    37,    38,    64,    99,   100,    37,    38,    39,   102,
      12,    40,    11,    41,    13,    37,    38,     9,    80,    83,
      84,    15,    43,    86,    16,    42,    88,    43,    37,    38,
      39,    28,    44,    40,    61,    41,    43,    67,    68,   -14,
      19,    69,    70,    71,    72,    73,    74,    42,    17,    43,
      19,    89,    89,    28,    98,    89,    34,     1,     1,     2,
      18,    58,    23,    59,    24,    77,    78,    67,    68,    25,
      26,    27,    36,    60,    28,    31,    65,    63,    66,   101,
      85,    10,    95,    91,    87,    94,    93,     0,    96,    97,
      90,     0,    30,     0,    29,    92,     0,    33
};

static const yytype_int8 yycheck[] =
{
      40,     3,     4,    43,    96,    97,     3,     4,     5,   101,
      22,     8,     4,    10,    26,     3,     4,     0,    58,    59,
      60,     3,    24,    63,    24,    22,    66,    24,     3,     4,
       5,    28,    29,     8,    22,    10,    24,    11,    12,    25,
      16,    15,    16,    17,    18,    19,    20,    22,    27,    24,
      26,    75,    76,    28,    94,    79,    32,     7,     7,     9,
       9,    24,    22,    26,     4,    13,    14,    11,    12,    25,
      23,    26,     4,    24,    28,    27,    22,    24,    21,     6,
      22,     4,    27,    76,    25,    23,    25,    -1,    25,    25,
      75,    -1,    26,    -1,    25,    79,    -1,    32
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     9,    32,    33,    34,    35,    36,    37,     0,
      34,     4,    22,    26,    38,     3,    24,    27,     9,    36,
      39,    40,    41,    22,     4,    25,    23,    26,    28,    42,
      41,    27,    43,    35,    36,    44,     4,     3,     4,     5,
       8,    10,    22,    24,    29,    42,    45,    46,    47,    48,
      49,    50,    51,    52,    54,    56,    58,    59,    24,    26,
      24,    22,    50,    24,    50,    22,    21,    11,    12,    15,
      16,    17,    18,    19,    20,    53,    55,    13,    14,    57,
      50,    60,    61,    50,    50,    22,    50,    25,    50,    51,
      54,    56,    58,    25,    23,    27,    25,    25,    50,    45,
      45,     6,    45
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
# if YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1455 of yacc.c  */
#line 90 "parser.y"
    { 
            AST = (yyvsp[(1) - (1)].tree); //raíz da AST
      ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 97 "parser.y"
    {
            TreeNode *t = (yyvsp[(1) - (2)].tree);
            // Lista encadeada de declarações no escopo
            if (t != NULL){
                  while (t->sibling != NULL)
                        t = t->sibling;
                  t->sibling = (yyvsp[(2) - (2)].tree);
                  (yyval.tree) = (yyvsp[(1) - (2)].tree);
            }
            else {
                  // Caso for uma primeira declaração, será um novo nó com o item de 'declaracao'
                  (yyval.tree) = (yyvsp[(2) - (2)].tree);
            }
      ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 111 "parser.y"
    {
            // Caso for uma primeira declaração, será um novo nó com o item de 'declaracao'
            (yyval.tree) = (yyvsp[(1) - (1)].tree);
     ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 119 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 120 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 124 "parser.y"
    {
            //Criação do nó da variável
            (yyval.tree) = newExpNode(VarDeclK);
            (yyval.tree)->type = (yyvsp[(1) - (3)].type);
            (yyval.tree)->attr.name = copyString((yyvsp[(2) - (3)].name));
      ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 130 "parser.y"
    {
            //Criação do nó do vetor
            (yyval.tree) = newExpNode(ArrDeclK);
            (yyval.tree)->type = (yyvsp[(1) - (6)].type);
            (yyval.tree)->attr.name = copyString((yyvsp[(2) - (6)].name));
            //Tamanho do vetor salvo como filho da variável
            (yyval.tree)->child[0] = newExpNode(ConstK);
            (yyval.tree)->child[0]->attr.val = (yyvsp[(4) - (6)].val);
    ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 142 "parser.y"
    {(yyval.type) = Integer;;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 143 "parser.y"
    {(yyval.type) = Void;;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 147 "parser.y"
    {
            strncpy(currentScope, (yyvsp[(2) - (2)].name), 255); //Parâmetros terão escopo de nome 'ID'
      ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 149 "parser.y"
    {
            //Nó raíz da função
            (yyval.tree) = newStmtNode(FunctDeclK);
            (yyval.tree)->type = (yyvsp[(1) - (7)].type);
            (yyval.tree)->attr.name = copyString((yyvsp[(2) - (7)].name));
            //Nós filhos: Lista de parâmetros (Esq) e o Corpo da função (Dir)
            (yyval.tree)->child[0] = (yyvsp[(5) - (7)].tree); //params
            (yyval.tree)->child[1] = (yyvsp[(7) - (7)].tree); //composto_decl

            //Reset do escopo ao término da função (composto_decl)
            strcpy(currentScope, "global");
      ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 164 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 165 "parser.y"
    {(yyval.tree) = NULL;;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 169 "parser.y"
    {
            TreeNode *t = (yyvsp[(1) - (3)].tree);
            if (t != NULL){
                  while (t->sibling != NULL)
                        t = t->sibling;
                  t->sibling = (yyvsp[(3) - (3)].tree);
                  (yyval.tree) = (yyvsp[(1) - (3)].tree);
            } else {
                  (yyval.tree) = (yyvsp[(3) - (3)].tree);
            }
      ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 180 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 184 "parser.y"
    {
            (yyval.tree) = newExpNode(ParamK);
            (yyval.tree)->type = (yyvsp[(1) - (2)].type);
            (yyval.tree)->attr.name = copyString((yyvsp[(2) - (2)].name));
       ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 189 "parser.y"
    {
            (yyval.tree) = newExpNode(ParamArrK);
            (yyval.tree)->type = (yyvsp[(1) - (4)].type);
            (yyval.tree)->attr.name = copyString((yyvsp[(2) - (4)].name));
    ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 199 "parser.y"
    {
            // Nó que define o escopo
            (yyval.tree) = newStmtNode(CompoundK);
            (yyval.tree)->child[0] = (yyvsp[(2) - (4)].tree); //Esq: lista de declarações
            (yyval.tree)->child[1] = (yyvsp[(3) - (4)].tree); //Dir: lista de instruções (statements)
      ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 209 "parser.y"
    {
            TreeNode *t = (yyvsp[(1) - (2)].tree);
            if (t!=NULL){
                  while (t->sibling != NULL)
                        t = t->sibling;
                  t->sibling = (yyvsp[(2) - (2)].tree);
                  (yyval.tree) = (yyvsp[(1) - (2)].tree);
            } else {
                  (yyval.tree) = (yyvsp[(2) - (2)].tree);
            }
      ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 220 "parser.y"
    {(yyval.tree) = NULL;;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 225 "parser.y"
    {
            TreeNode *t = (yyvsp[(1) - (2)].tree);
            if (t != NULL){
                  while(t->sibling != NULL)
                        t = t->sibling;
                  t->sibling = (yyvsp[(2) - (2)].tree);
                  (yyval.tree) = (yyvsp[(1) - (2)].tree);
            } else {
                  (yyval.tree) = (yyvsp[(2) - (2)].tree);
            }
      ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 236 "parser.y"
    {(yyval.tree) = NULL;;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 241 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 242 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 243 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 244 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 245 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 250 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (2)].tree);;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 251 "parser.y"
    {(yyval.tree) = NULL;;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 256 "parser.y"
    {
            (yyval.tree) = newStmtNode(IfK); //Pai: IF
            (yyval.tree)->child[0] = (yyvsp[(3) - (5)].tree); //Filho 1: expressão
            (yyval.tree)->child[1] = (yyvsp[(5) - (5)].tree); //Filho 2: instruções
      ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 261 "parser.y"
    {
            (yyval.tree) = newStmtNode(IfK); //Pai: IF
            (yyval.tree)->child[0] = (yyvsp[(3) - (7)].tree); //Filho 1: expressão condicional
            (yyval.tree)->child[1] = (yyvsp[(5) - (7)].tree); //Filho 2: instruções then
            (yyval.tree)->child[2] = (yyvsp[(7) - (7)].tree); //Filho 3: instruções else
    ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 271 "parser.y"
    {
            (yyval.tree) = newStmtNode(WhileK);
            (yyval.tree)->child[0] = (yyvsp[(3) - (5)].tree); //Filho 1: expressão condicional
            (yyval.tree)->child[1] = (yyvsp[(5) - (5)].tree); //Filho 2: instruções
      ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 280 "parser.y"
    {
            (yyval.tree) = newStmtNode(ReturnK);
            // Return; => Filhos nulos
      ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 284 "parser.y"
    {
            (yyval.tree) = newStmtNode(ReturnK);
            (yyval.tree)->child[0] = (yyvsp[(2) - (3)].tree);
    ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 292 "parser.y"
    {
            (yyval.tree) = newExpNode(AssignK);
            (yyval.tree)->child[0] = (yyvsp[(1) - (3)].tree);
            (yyval.tree)->child[1] = (yyvsp[(3) - (3)].tree);
      ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 297 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 302 "parser.y"
    {
            //Uso de variável já declarada
            (yyval.tree) = newExpNode(VarK);
            (yyval.tree)->attr.name = copyString((yyvsp[(1) - (1)].name));
      ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 307 "parser.y"
    {
            (yyval.tree) = newExpNode(ArrK);
            (yyval.tree)->attr.name = copyString((yyvsp[(1) - (4)].name));
            (yyval.tree)->child[0] = (yyvsp[(3) - (4)].tree); //índice dado pela expressão

    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 317 "parser.y"
    {
            //Operação lógica/relacional (i.e: a < b, x==5)
            (yyval.tree) = newExpNode(OpK);
            (yyval.tree)->attr.op = (yyvsp[(2) - (3)].val);
            (yyval.tree)->child[0] = (yyvsp[(1) - (3)].tree);
            (yyval.tree)->child[1] = (yyvsp[(3) - (3)].tree);
      ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 324 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 329 "parser.y"
    {(yyval.val) = MENOR_IGUAL;;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 330 "parser.y"
    {(yyval.val) = MENOR;;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 331 "parser.y"
    {(yyval.val) = MAIOR;;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 332 "parser.y"
    {(yyval.val) = MAIOR_IGUAL;;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 333 "parser.y"
    {(yyval.val) = IGUAL_IGUAL;;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 334 "parser.y"
    {(yyval.val) = DIFERENTE;;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 339 "parser.y"
    {
            //Operação de adição/subtração
            (yyval.tree) = newExpNode(OpK); //soma -> + | -
            (yyval.tree)->attr.op = (yyvsp[(2) - (3)].val);
            // TODO: verificar precedência
            (yyval.tree)->child[0] = (yyvsp[(1) - (3)].tree);
            (yyval.tree)->child[1] = (yyvsp[(3) - (3)].tree);
      ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 347 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 352 "parser.y"
    {(yyval.val) = SOMA;;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 353 "parser.y"
    {(yyval.val) = SUB;;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 358 "parser.y"
    {
            (yyval.tree) = newExpNode(OpK);
            (yyval.tree)->attr.op = (yyvsp[(2) - (3)].val);
            (yyval.tree)->child[0] = (yyvsp[(1) - (3)].tree);
            (yyval.tree)->child[1] = (yyvsp[(3) - (3)].tree);
      ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 364 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 369 "parser.y"
    {(yyval.val) = MUL;;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 370 "parser.y"
    {(yyval.val) = DIV;;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 375 "parser.y"
    {
            (yyval.tree) = (yyvsp[(2) - (3)].tree); //Parênteses força o Bison à priorizar a conta
      ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 378 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 379 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 380 "parser.y"
    {
            (yyval.tree) = newExpNode(ConstK);
            (yyval.tree)->attr.val = (yyvsp[(1) - (1)].val);
    ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 388 "parser.y"
    {
            (yyval.tree) = newExpNode(CallK);
            (yyval.tree)->attr.name = copyString((yyvsp[(1) - (4)].name));
            (yyval.tree)->child[0] = (yyvsp[(3) - (4)].tree);
      ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 397 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 398 "parser.y"
    {(yyval.tree) = NULL;;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 403 "parser.y"
    {
            //Lista de argumentos para ativação
            TreeNode *t = (yyvsp[(1) - (3)].tree);
            if (t!=NULL){
                  while(t->sibling != NULL)
                        t = t->sibling;
                  t->sibling = (yyvsp[(3) - (3)].tree);
                  (yyval.tree) = (yyvsp[(1) - (3)].tree);
            } else {
                  (yyval.tree) = (yyvsp[(3) - (3)].tree);
            }
      ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 415 "parser.y"
    {(yyval.tree) = (yyvsp[(1) - (1)].tree);;}
    break;



/* Line 1455 of yacc.c  */
#line 2065 "parser.tab.c"
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
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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



/* Line 1675 of yacc.c  */
#line 418 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "ERRO SINTATICO: token inesperado '%s' - lineNo: %d\n", yytext, lineNo);
}
