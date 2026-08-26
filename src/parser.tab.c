/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
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

#line 88 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUM = 258,                     /* NUM  */
    ID = 259,                      /* ID  */
    IF = 260,                      /* IF  */
    ELSE = 261,                    /* ELSE  */
    INT = 262,                     /* INT  */
    RETURN = 263,                  /* RETURN  */
    VOID = 264,                    /* VOID  */
    WHILE = 265,                   /* WHILE  */
    SOMA = 266,                    /* SOMA  */
    SUB = 267,                     /* SUB  */
    MUL = 268,                     /* MUL  */
    DIV = 269,                     /* DIV  */
    MENOR = 270,                   /* MENOR  */
    MENOR_IGUAL = 271,             /* MENOR_IGUAL  */
    MAIOR = 272,                   /* MAIOR  */
    MAIOR_IGUAL = 273,             /* MAIOR_IGUAL  */
    IGUAL_IGUAL = 274,             /* IGUAL_IGUAL  */
    DIFERENTE = 275,               /* DIFERENTE  */
    ATRIBUICAO = 276,              /* ATRIBUICAO  */
    PONTO_VIRGULA = 277,           /* PONTO_VIRGULA  */
    VIRGULA = 278,                 /* VIRGULA  */
    ABRE_PARENTESE = 279,          /* ABRE_PARENTESE  */
    FECHA_PARENTESE = 280,         /* FECHA_PARENTESE  */
    ABRE_COLCHETE = 281,           /* ABRE_COLCHETE  */
    FECHA_COLCHETE = 282,          /* FECHA_COLCHETE  */
    ABRE_CHAVE = 283,              /* ABRE_CHAVE  */
    FECHA_CHAVE = 284,             /* FECHA_CHAVE  */
    ERROR = 285                    /* ERROR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "parser.y"

    TreeNode *tree;
    int val;
    char *name;
    ExpType type;

#line 172 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_WHILE = 10,                     /* WHILE  */
  YYSYMBOL_SOMA = 11,                      /* SOMA  */
  YYSYMBOL_SUB = 12,                       /* SUB  */
  YYSYMBOL_MUL = 13,                       /* MUL  */
  YYSYMBOL_DIV = 14,                       /* DIV  */
  YYSYMBOL_MENOR = 15,                     /* MENOR  */
  YYSYMBOL_MENOR_IGUAL = 16,               /* MENOR_IGUAL  */
  YYSYMBOL_MAIOR = 17,                     /* MAIOR  */
  YYSYMBOL_MAIOR_IGUAL = 18,               /* MAIOR_IGUAL  */
  YYSYMBOL_IGUAL_IGUAL = 19,               /* IGUAL_IGUAL  */
  YYSYMBOL_DIFERENTE = 20,                 /* DIFERENTE  */
  YYSYMBOL_ATRIBUICAO = 21,                /* ATRIBUICAO  */
  YYSYMBOL_PONTO_VIRGULA = 22,             /* PONTO_VIRGULA  */
  YYSYMBOL_VIRGULA = 23,                   /* VIRGULA  */
  YYSYMBOL_ABRE_PARENTESE = 24,            /* ABRE_PARENTESE  */
  YYSYMBOL_FECHA_PARENTESE = 25,           /* FECHA_PARENTESE  */
  YYSYMBOL_ABRE_COLCHETE = 26,             /* ABRE_COLCHETE  */
  YYSYMBOL_FECHA_COLCHETE = 27,            /* FECHA_COLCHETE  */
  YYSYMBOL_ABRE_CHAVE = 28,                /* ABRE_CHAVE  */
  YYSYMBOL_FECHA_CHAVE = 29,               /* FECHA_CHAVE  */
  YYSYMBOL_ERROR = 30,                     /* ERROR  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_programa = 32,                  /* programa  */
  YYSYMBOL_declaracao_lista = 33,          /* declaracao_lista  */
  YYSYMBOL_declaracao = 34,                /* declaracao  */
  YYSYMBOL_var_declaracao = 35,            /* var_declaracao  */
  YYSYMBOL_tipo_especificador = 36,        /* tipo_especificador  */
  YYSYMBOL_fun_declaracao = 37,            /* fun_declaracao  */
  YYSYMBOL_38_1 = 38,                      /* @1  */
  YYSYMBOL_params = 39,                    /* params  */
  YYSYMBOL_param_lista = 40,               /* param_lista  */
  YYSYMBOL_param = 41,                     /* param  */
  YYSYMBOL_composto_decl = 42,             /* composto_decl  */
  YYSYMBOL_local_declaracoes = 43,         /* local_declaracoes  */
  YYSYMBOL_statement_lista = 44,           /* statement_lista  */
  YYSYMBOL_statement = 45,                 /* statement  */
  YYSYMBOL_expressao_decl = 46,            /* expressao_decl  */
  YYSYMBOL_selecao_decl = 47,              /* selecao_decl  */
  YYSYMBOL_iteracao_decl = 48,             /* iteracao_decl  */
  YYSYMBOL_retorno_decl = 49,              /* retorno_decl  */
  YYSYMBOL_expressao = 50,                 /* expressao  */
  YYSYMBOL_var = 51,                       /* var  */
  YYSYMBOL_simples_expressao = 52,         /* simples_expressao  */
  YYSYMBOL_relacional = 53,                /* relacional  */
  YYSYMBOL_soma_expressao = 54,            /* soma_expressao  */
  YYSYMBOL_soma = 55,                      /* soma  */
  YYSYMBOL_termo = 56,                     /* termo  */
  YYSYMBOL_mult = 57,                      /* mult  */
  YYSYMBOL_fator = 58,                     /* fator  */
  YYSYMBOL_ativacao = 59,                  /* ativacao  */
  YYSYMBOL_args = 60,                      /* args  */
  YYSYMBOL_arg_lista = 61                  /* arg_lista  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   103

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  105

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    90,    90,    97,   111,   119,   120,   124,   130,   142,
     143,   147,   147,   166,   167,   171,   182,   186,   191,   201,
     211,   222,   227,   238,   243,   244,   245,   246,   247,   252,
     253,   258,   263,   273,   282,   286,   294,   299,   304,   309,
     319,   326,   331,   332,   333,   334,   335,   336,   341,   349,
     354,   355,   360,   366,   371,   372,   377,   380,   381,   382,
     386,   395,   404,   405,   410,   422
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "ID", "IF",
  "ELSE", "INT", "RETURN", "VOID", "WHILE", "SOMA", "SUB", "MUL", "DIV",
  "MENOR", "MENOR_IGUAL", "MAIOR", "MAIOR_IGUAL", "IGUAL_IGUAL",
  "DIFERENTE", "ATRIBUICAO", "PONTO_VIRGULA", "VIRGULA", "ABRE_PARENTESE",
  "FECHA_PARENTESE", "ABRE_COLCHETE", "FECHA_COLCHETE", "ABRE_CHAVE",
  "FECHA_CHAVE", "ERROR", "$accept", "programa", "declaracao_lista",
  "declaracao", "var_declaracao", "tipo_especificador", "fun_declaracao",
  "@1", "params", "param_lista", "param", "composto_decl",
  "local_declaracoes", "statement_lista", "statement", "expressao_decl",
  "selecao_decl", "iteracao_decl", "retorno_decl", "expressao", "var",
  "simples_expressao", "relacional", "soma_expressao", "soma", "termo",
  "mult", "fator", "ativacao", "args", "arg_lista", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-64)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-15)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      43,   -64,   -64,     2,    43,   -64,   -64,     1,   -64,   -64,
     -64,   -10,   -64,    11,    -7,    -1,    48,    17,    22,    56,
      37,    45,   -64,   -64,    52,    51,    43,    53,   -64,   -64,
     -64,   -64,    43,   -64,    77,     3,   -10,   -64,    35,    58,
       6,    59,    30,   -64,    30,   -64,   -64,   -64,   -64,   -64,
     -64,   -64,    62,    64,   -64,    55,     9,   -64,   -64,    30,
      30,    30,   -64,    66,    30,   -64,   -64,    61,   -64,    30,
     -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,    30,    30,
     -64,   -64,    30,   -64,    67,    68,    60,    69,   -64,    70,
     -64,   -64,    65,     9,   -64,   -64,    30,   -64,    41,    41,
     -64,    83,   -64,    41,   -64
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     9,    10,     0,     2,     4,     5,     0,     6,     1,
       3,    11,     7,     0,     0,     0,     0,     0,    10,     0,
       0,    13,    16,     8,    17,     0,     0,     0,    21,    12,
      15,    18,    23,    20,     0,     0,     0,    59,    38,     0,
       0,     0,     0,    30,     0,    19,    25,    22,    24,    26,
      27,    28,     0,    57,    37,    41,    49,    53,    58,    63,
       0,     0,    34,     0,     0,    57,    60,     0,    29,     0,
      50,    51,    43,    42,    44,    45,    46,    47,     0,     0,
      54,    55,     0,    65,     0,    62,     0,     0,    35,     0,
      56,    36,    40,    48,    52,    61,     0,    39,     0,     0,
      64,    31,    33,     0,    32
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -64,   -64,   -64,    86,    71,    32,   -64,   -64,   -64,   -64,
      72,    74,   -64,   -64,   -63,   -64,   -64,   -64,   -64,   -40,
     -41,   -64,   -64,    15,   -64,    18,   -64,   -39,   -64,   -64,
     -64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,     7,     8,    14,    20,    21,
      22,    46,    32,    35,    47,    48,    49,    50,    51,    52,
      53,    54,    78,    55,    79,    56,    82,    57,    58,    84,
      85
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      63,    65,     9,    66,    67,    11,    37,    38,    39,    37,
      38,    40,    12,    41,    15,    42,    13,    16,    42,    83,
      86,    87,    80,    81,    89,    43,    17,    44,    62,    91,
      44,    28,    45,    37,    38,   101,   102,    65,    65,    23,
     104,    65,    42,    94,    37,    38,    39,   -14,    19,    40,
       1,    41,     2,    42,    44,     1,   100,    18,    19,    59,
      24,    60,    25,    43,    34,    44,    70,    71,    26,    28,
      72,    73,    74,    75,    76,    77,    70,    71,    27,    28,
      31,    36,    61,    64,    68,    69,    90,    97,    88,   103,
      10,    96,    95,    92,    98,    99,     0,    93,    30,    29,
       0,     0,     0,    33
};

static const yytype_int8 yycheck[] =
{
      40,    42,     0,    42,    44,     4,     3,     4,     5,     3,
       4,     8,    22,    10,     3,    12,    26,    24,    12,    59,
      60,    61,    13,    14,    64,    22,    27,    24,    22,    69,
      24,    28,    29,     3,     4,    98,    99,    78,    79,    22,
     103,    82,    12,    82,     3,     4,     5,    25,    16,     8,
       7,    10,     9,    12,    24,     7,    96,     9,    26,    24,
       4,    26,    25,    22,    32,    24,    11,    12,    23,    28,
      15,    16,    17,    18,    19,    20,    11,    12,    26,    28,
      27,     4,    24,    24,    22,    21,    25,    27,    22,     6,
       4,    23,    25,    78,    25,    25,    -1,    79,    26,    25,
      -1,    -1,    -1,    32
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     9,    32,    33,    34,    35,    36,    37,     0,
      34,     4,    22,    26,    38,     3,    24,    27,     9,    36,
      39,    40,    41,    22,     4,    25,    23,    26,    28,    42,
      41,    27,    43,    35,    36,    44,     4,     3,     4,     5,
       8,    10,    12,    22,    24,    29,    42,    45,    46,    47,
      48,    49,    50,    51,    52,    54,    56,    58,    59,    24,
      26,    24,    22,    50,    24,    51,    58,    50,    22,    21,
      11,    12,    15,    16,    17,    18,    19,    20,    53,    55,
      13,    14,    57,    50,    60,    61,    50,    50,    22,    50,
      25,    50,    54,    56,    58,    25,    23,    27,    25,    25,
      50,    45,    45,     6,    45
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    35,    35,    36,
      36,    38,    37,    39,    39,    40,    40,    41,    41,    42,
      43,    43,    44,    44,    45,    45,    45,    45,    45,    46,
      46,    47,    47,    48,    49,    49,    50,    50,    51,    51,
      52,    52,    53,    53,    53,    53,    53,    53,    54,    54,
      55,    55,    56,    56,    57,    57,    58,    58,    58,    58,
      58,    59,    60,    60,    61,    61
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     0,     7,     1,     1,     3,     1,     2,     4,     4,
       2,     0,     2,     0,     1,     1,     1,     1,     1,     2,
       1,     5,     7,     5,     2,     3,     3,     1,     1,     4,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       2,     4,     1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: declaracao_lista  */
#line 90 "parser.y"
                       { 
            AST = (yyvsp[0].tree); //raíz da AST
      }
#line 1287 "parser.tab.c"
    break;

  case 3: /* declaracao_lista: declaracao_lista declaracao  */
#line 97 "parser.y"
                                  {
            TreeNode *t = (yyvsp[-1].tree);
            // Lista encadeada de declarações no escopo
            if (t != NULL){
                  while (t->sibling != NULL)
                        t = t->sibling;
                  t->sibling = (yyvsp[0].tree);
                  (yyval.tree) = (yyvsp[-1].tree);
            }
            else {
                  // Caso for uma primeira declaração, será um novo nó com o item de 'declaracao'
                  (yyval.tree) = (yyvsp[0].tree);
            }
      }
#line 1306 "parser.tab.c"
    break;

  case 4: /* declaracao_lista: declaracao  */
#line 111 "parser.y"
                 {
            // Caso for uma primeira declaração, será um novo nó com o item de 'declaracao'
            (yyval.tree) = (yyvsp[0].tree);
     }
#line 1315 "parser.tab.c"
    break;

  case 5: /* declaracao: var_declaracao  */
#line 119 "parser.y"
                     {(yyval.tree) = (yyvsp[0].tree);}
#line 1321 "parser.tab.c"
    break;

  case 6: /* declaracao: fun_declaracao  */
#line 120 "parser.y"
                     {(yyval.tree) = (yyvsp[0].tree);}
#line 1327 "parser.tab.c"
    break;

  case 7: /* var_declaracao: tipo_especificador ID PONTO_VIRGULA  */
#line 124 "parser.y"
                                          {
            //Criação do nó da variável
            (yyval.tree) = newExpNode(VarDeclK);
            (yyval.tree)->type = (yyvsp[-2].type);
            (yyval.tree)->attr.name = copyString((yyvsp[-1].name));
      }
#line 1338 "parser.tab.c"
    break;

  case 8: /* var_declaracao: tipo_especificador ID ABRE_COLCHETE NUM FECHA_COLCHETE PONTO_VIRGULA  */
#line 130 "parser.y"
                                                                           {
            //Criação do nó do vetor
            (yyval.tree) = newExpNode(ArrDeclK);
            (yyval.tree)->type = (yyvsp[-5].type);
            (yyval.tree)->attr.name = copyString((yyvsp[-4].name));
            //Tamanho do vetor salvo como filho da variável
            (yyval.tree)->child[0] = newExpNode(ConstK);
            (yyval.tree)->child[0]->attr.val = (yyvsp[-2].val);
    }
#line 1352 "parser.tab.c"
    break;

  case 9: /* tipo_especificador: INT  */
#line 142 "parser.y"
           {(yyval.type) = Integer;}
#line 1358 "parser.tab.c"
    break;

  case 10: /* tipo_especificador: VOID  */
#line 143 "parser.y"
           {(yyval.type) = Void;}
#line 1364 "parser.tab.c"
    break;

  case 11: /* @1: %empty  */
#line 147 "parser.y"
                            { 
            (yyval.val) = lineNo; 
      }
#line 1372 "parser.tab.c"
    break;

  case 12: /* fun_declaracao: tipo_especificador ID @1 ABRE_PARENTESE params FECHA_PARENTESE composto_decl  */
#line 150 "parser.y"
                                                          {
            (yyval.tree) = newStmtNode(FunctDeclK);
            (yyval.tree)->lineNo = (yyvsp[-4].val); //resgata o número da linha salvo na ação intermediária (posição 3 da regra)
            (yyval.tree)->type = (yyvsp[-6].type);
            (yyval.tree)->attr.name = copyString((yyvsp[-5].name));
            (yyval.tree)->child[0] = (yyvsp[-2].tree); // params
            (yyval.tree)->child[1] = (yyvsp[0].tree); // composto_decl

            //o compound da função é determinado como corpo da função (uso na análise semântica)
            if ((yyval.tree)->child[1] != NULL) {
                (yyval.tree)->child[1]->kind.stmt = FunctBodyK; 
            }
      }
#line 1390 "parser.tab.c"
    break;

  case 13: /* params: param_lista  */
#line 166 "parser.y"
                  {(yyval.tree) = (yyvsp[0].tree);}
#line 1396 "parser.tab.c"
    break;

  case 14: /* params: VOID  */
#line 167 "parser.y"
           {(yyval.tree) = NULL;}
#line 1402 "parser.tab.c"
    break;

  case 15: /* param_lista: param_lista VIRGULA param  */
#line 171 "parser.y"
                                {
            TreeNode *t = (yyvsp[-2].tree);
            if (t != NULL){
                  while (t->sibling != NULL)
                        t = t->sibling;
                  t->sibling = (yyvsp[0].tree);
                  (yyval.tree) = (yyvsp[-2].tree);
            } else {
                  (yyval.tree) = (yyvsp[0].tree);
            }
      }
#line 1418 "parser.tab.c"
    break;

  case 16: /* param_lista: param  */
#line 182 "parser.y"
            {(yyval.tree) = (yyvsp[0].tree);}
#line 1424 "parser.tab.c"
    break;

  case 17: /* param: tipo_especificador ID  */
#line 186 "parser.y"
                            {
            (yyval.tree) = newExpNode(ParamK);
            (yyval.tree)->type = (yyvsp[-1].type);
            (yyval.tree)->attr.name = copyString((yyvsp[0].name));
       }
#line 1434 "parser.tab.c"
    break;

  case 18: /* param: tipo_especificador ID ABRE_COLCHETE FECHA_COLCHETE  */
#line 191 "parser.y"
                                                         {
            (yyval.tree) = newExpNode(ParamArrK);
            (yyval.tree)->type = (yyvsp[-3].type);
            (yyval.tree)->attr.name = copyString((yyvsp[-2].name));
    }
#line 1444 "parser.tab.c"
    break;

  case 19: /* composto_decl: ABRE_CHAVE local_declaracoes statement_lista FECHA_CHAVE  */
#line 201 "parser.y"
                                                               {
            // Nó que define o escopo
            (yyval.tree) = newStmtNode(CompoundK);
            (yyval.tree)->child[0] = (yyvsp[-2].tree); //Esq: lista de declarações
            (yyval.tree)->child[1] = (yyvsp[-1].tree); //Dir: lista de instruções (statements)
      }
#line 1455 "parser.tab.c"
    break;

  case 20: /* local_declaracoes: local_declaracoes var_declaracao  */
#line 211 "parser.y"
                                       {
            TreeNode *t = (yyvsp[-1].tree);
            if (t!=NULL){
                  while (t->sibling != NULL)
                        t = t->sibling;
                  t->sibling = (yyvsp[0].tree);
                  (yyval.tree) = (yyvsp[-1].tree);
            } else {
                  (yyval.tree) = (yyvsp[0].tree);
            }
      }
#line 1471 "parser.tab.c"
    break;

  case 21: /* local_declaracoes: %empty  */
#line 222 "parser.y"
                  {(yyval.tree) = NULL;}
#line 1477 "parser.tab.c"
    break;

  case 22: /* statement_lista: statement_lista statement  */
#line 227 "parser.y"
                                {
            TreeNode *t = (yyvsp[-1].tree);
            if (t != NULL){
                  while(t->sibling != NULL)
                        t = t->sibling;
                  t->sibling = (yyvsp[0].tree);
                  (yyval.tree) = (yyvsp[-1].tree);
            } else {
                  (yyval.tree) = (yyvsp[0].tree);
            }
      }
#line 1493 "parser.tab.c"
    break;

  case 23: /* statement_lista: %empty  */
#line 238 "parser.y"
                  {(yyval.tree) = NULL;}
#line 1499 "parser.tab.c"
    break;

  case 24: /* statement: expressao_decl  */
#line 243 "parser.y"
                     {(yyval.tree) = (yyvsp[0].tree);}
#line 1505 "parser.tab.c"
    break;

  case 25: /* statement: composto_decl  */
#line 244 "parser.y"
                    {(yyval.tree) = (yyvsp[0].tree);}
#line 1511 "parser.tab.c"
    break;

  case 26: /* statement: selecao_decl  */
#line 245 "parser.y"
                   {(yyval.tree) = (yyvsp[0].tree);}
#line 1517 "parser.tab.c"
    break;

  case 27: /* statement: iteracao_decl  */
#line 246 "parser.y"
                    {(yyval.tree) = (yyvsp[0].tree);}
#line 1523 "parser.tab.c"
    break;

  case 28: /* statement: retorno_decl  */
#line 247 "parser.y"
                   {(yyval.tree) = (yyvsp[0].tree);}
#line 1529 "parser.tab.c"
    break;

  case 29: /* expressao_decl: expressao PONTO_VIRGULA  */
#line 252 "parser.y"
                              {(yyval.tree) = (yyvsp[-1].tree);}
#line 1535 "parser.tab.c"
    break;

  case 30: /* expressao_decl: PONTO_VIRGULA  */
#line 253 "parser.y"
                    {(yyval.tree) = NULL;}
#line 1541 "parser.tab.c"
    break;

  case 31: /* selecao_decl: IF ABRE_PARENTESE expressao FECHA_PARENTESE statement  */
#line 258 "parser.y"
                                                            {
            (yyval.tree) = newStmtNode(IfK); //Pai: IF
            (yyval.tree)->child[0] = (yyvsp[-2].tree); //Filho 1: expressão
            (yyval.tree)->child[1] = (yyvsp[0].tree); //Filho 2: instruções
      }
#line 1551 "parser.tab.c"
    break;

  case 32: /* selecao_decl: IF ABRE_PARENTESE expressao FECHA_PARENTESE statement ELSE statement  */
#line 263 "parser.y"
                                                                           {
            (yyval.tree) = newStmtNode(IfK); //Pai: IF
            (yyval.tree)->child[0] = (yyvsp[-4].tree); //Filho 1: expressão condicional
            (yyval.tree)->child[1] = (yyvsp[-2].tree); //Filho 2: instruções then
            (yyval.tree)->child[2] = (yyvsp[0].tree); //Filho 3: instruções else
    }
#line 1562 "parser.tab.c"
    break;

  case 33: /* iteracao_decl: WHILE ABRE_PARENTESE expressao FECHA_PARENTESE statement  */
#line 273 "parser.y"
                                                               {
            (yyval.tree) = newStmtNode(WhileK);
            (yyval.tree)->child[0] = (yyvsp[-2].tree); //Filho 1: expressão condicional
            (yyval.tree)->child[1] = (yyvsp[0].tree); //Filho 2: instruções
      }
#line 1572 "parser.tab.c"
    break;

  case 34: /* retorno_decl: RETURN PONTO_VIRGULA  */
#line 282 "parser.y"
                           {
            (yyval.tree) = newStmtNode(ReturnK);
            // Return; => Filhos nulos
      }
#line 1581 "parser.tab.c"
    break;

  case 35: /* retorno_decl: RETURN expressao PONTO_VIRGULA  */
#line 286 "parser.y"
                                     {
            (yyval.tree) = newStmtNode(ReturnK);
            (yyval.tree)->child[0] = (yyvsp[-1].tree);
    }
#line 1590 "parser.tab.c"
    break;

  case 36: /* expressao: var ATRIBUICAO expressao  */
#line 294 "parser.y"
                               {
            (yyval.tree) = newExpNode(AssignK);
            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
      }
#line 1600 "parser.tab.c"
    break;

  case 37: /* expressao: simples_expressao  */
#line 299 "parser.y"
                        {(yyval.tree) = (yyvsp[0].tree);}
#line 1606 "parser.tab.c"
    break;

  case 38: /* var: ID  */
#line 304 "parser.y"
         {
            //Uso de variável já declarada
            (yyval.tree) = newExpNode(VarK);
            (yyval.tree)->attr.name = copyString((yyvsp[0].name));
      }
#line 1616 "parser.tab.c"
    break;

  case 39: /* var: ID ABRE_COLCHETE expressao FECHA_COLCHETE  */
#line 309 "parser.y"
                                                {
            (yyval.tree) = newExpNode(ArrK);
            (yyval.tree)->attr.name = copyString((yyvsp[-3].name));
            (yyval.tree)->child[0] = (yyvsp[-1].tree); //índice dado pela expressão

    }
#line 1627 "parser.tab.c"
    break;

  case 40: /* simples_expressao: soma_expressao relacional soma_expressao  */
#line 319 "parser.y"
                                               {
            //Operação lógica/relacional (i.e: a < b, x==5)
            (yyval.tree) = newExpNode(OpK);
            (yyval.tree)->attr.op = (yyvsp[-1].val);
            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
      }
#line 1639 "parser.tab.c"
    break;

  case 41: /* simples_expressao: soma_expressao  */
#line 326 "parser.y"
                     {(yyval.tree) = (yyvsp[0].tree);}
#line 1645 "parser.tab.c"
    break;

  case 42: /* relacional: MENOR_IGUAL  */
#line 331 "parser.y"
                  {(yyval.val) = MENOR_IGUAL;}
#line 1651 "parser.tab.c"
    break;

  case 43: /* relacional: MENOR  */
#line 332 "parser.y"
            {(yyval.val) = MENOR;}
#line 1657 "parser.tab.c"
    break;

  case 44: /* relacional: MAIOR  */
#line 333 "parser.y"
            {(yyval.val) = MAIOR;}
#line 1663 "parser.tab.c"
    break;

  case 45: /* relacional: MAIOR_IGUAL  */
#line 334 "parser.y"
                  {(yyval.val) = MAIOR_IGUAL;}
#line 1669 "parser.tab.c"
    break;

  case 46: /* relacional: IGUAL_IGUAL  */
#line 335 "parser.y"
                  {(yyval.val) = IGUAL_IGUAL;}
#line 1675 "parser.tab.c"
    break;

  case 47: /* relacional: DIFERENTE  */
#line 336 "parser.y"
                {(yyval.val) = DIFERENTE;}
#line 1681 "parser.tab.c"
    break;

  case 48: /* soma_expressao: soma_expressao soma termo  */
#line 341 "parser.y"
                                {
            //Operação de adição/subtração
            (yyval.tree) = newExpNode(OpK); //soma -> + | -
            (yyval.tree)->attr.op = (yyvsp[-1].val);
            // TODO: verificar precedência
            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
      }
#line 1694 "parser.tab.c"
    break;

  case 49: /* soma_expressao: termo  */
#line 349 "parser.y"
            {(yyval.tree) = (yyvsp[0].tree);}
#line 1700 "parser.tab.c"
    break;

  case 50: /* soma: SOMA  */
#line 354 "parser.y"
           {(yyval.val) = SOMA;}
#line 1706 "parser.tab.c"
    break;

  case 51: /* soma: SUB  */
#line 355 "parser.y"
          {(yyval.val) = SUB;}
#line 1712 "parser.tab.c"
    break;

  case 52: /* termo: termo mult fator  */
#line 360 "parser.y"
                       {
            (yyval.tree) = newExpNode(OpK);
            (yyval.tree)->attr.op = (yyvsp[-1].val);
            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
      }
#line 1723 "parser.tab.c"
    break;

  case 53: /* termo: fator  */
#line 366 "parser.y"
            {(yyval.tree) = (yyvsp[0].tree);}
#line 1729 "parser.tab.c"
    break;

  case 54: /* mult: MUL  */
#line 371 "parser.y"
          {(yyval.val) = MUL;}
#line 1735 "parser.tab.c"
    break;

  case 55: /* mult: DIV  */
#line 372 "parser.y"
          {(yyval.val) = DIV;}
#line 1741 "parser.tab.c"
    break;

  case 56: /* fator: ABRE_PARENTESE expressao FECHA_PARENTESE  */
#line 377 "parser.y"
                                               {
            (yyval.tree) = (yyvsp[-1].tree); //Parênteses força o Bison à priorizar a conta
      }
#line 1749 "parser.tab.c"
    break;

  case 57: /* fator: var  */
#line 380 "parser.y"
          {(yyval.tree) = (yyvsp[0].tree);}
#line 1755 "parser.tab.c"
    break;

  case 58: /* fator: ativacao  */
#line 381 "parser.y"
               {(yyval.tree) = (yyvsp[0].tree);}
#line 1761 "parser.tab.c"
    break;

  case 59: /* fator: NUM  */
#line 382 "parser.y"
          {
            (yyval.tree) = newExpNode(ConstK);
            (yyval.tree)->attr.val = (yyvsp[0].val);
    }
#line 1770 "parser.tab.c"
    break;

  case 60: /* fator: SUB fator  */
#line 386 "parser.y"
                {
            (yyval.tree) = newExpNode(OpK);
            (yyval.tree)->attr.op = SUB;
            (yyval.tree)->child[0] = (yyvsp[0].tree);
    }
#line 1780 "parser.tab.c"
    break;

  case 61: /* ativacao: ID ABRE_PARENTESE args FECHA_PARENTESE  */
#line 395 "parser.y"
                                             {
            (yyval.tree) = newExpNode(CallK);
            (yyval.tree)->attr.name = copyString((yyvsp[-3].name));
            (yyval.tree)->child[0] = (yyvsp[-1].tree);
      }
#line 1790 "parser.tab.c"
    break;

  case 62: /* args: arg_lista  */
#line 404 "parser.y"
                {(yyval.tree) = (yyvsp[0].tree);}
#line 1796 "parser.tab.c"
    break;

  case 63: /* args: %empty  */
#line 405 "parser.y"
                  {(yyval.tree) = NULL;}
#line 1802 "parser.tab.c"
    break;

  case 64: /* arg_lista: arg_lista VIRGULA expressao  */
#line 410 "parser.y"
                                  {
            //Lista de argumentos para ativação
            TreeNode *t = (yyvsp[-2].tree);
            if (t!=NULL){
                  while(t->sibling != NULL)
                        t = t->sibling;
                  t->sibling = (yyvsp[0].tree);
                  (yyval.tree) = (yyvsp[-2].tree);
            } else {
                  (yyval.tree) = (yyvsp[0].tree);
            }
      }
#line 1819 "parser.tab.c"
    break;

  case 65: /* arg_lista: expressao  */
#line 422 "parser.y"
                {(yyval.tree) = (yyvsp[0].tree);}
#line 1825 "parser.tab.c"
    break;


#line 1829 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 425 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "ERRO SINTATICO: token inesperado '%s' - LINHA: %d\n", yytext, lineNo);
}
