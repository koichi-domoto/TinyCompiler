/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

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

	#include "AST.h"
	#include <cstdio>
	#include <vector>
	#include <memory>
	using namespace rmmc;
	rmmc::BlockStatement* programBlock;
	extern int yylex();
	void yyerror(const char* s)
	{
		printf("Error: %s\n", s);
	}

#line 84 "parser.cpp"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TIDENTIFIER = 258,
    TINTEGER = 259,
    TDOUBLE = 260,
    TYINT = 261,
    TYDOUBLE = 262,
    TYFLOAT = 263,
    TYCHAR = 264,
    TYBOOL = 265,
    TYVOID = 266,
    TYSTRING = 267,
    TEXTERN = 268,
    TLITERAL = 269,
    TCEQ = 270,
    TCNE = 271,
    TCLT = 272,
    TCLE = 273,
    TCGT = 274,
    TCGE = 275,
    TEQUAL = 276,
    TLPAREN = 277,
    TRPAREN = 278,
    TLBRACE = 279,
    TRBRACE = 280,
    TCOMMA = 281,
    TDOT = 282,
    TSEMICOLON = 283,
    TLBRACKET = 284,
    TRBRACKET = 285,
    TQUOTATION = 286,
    TPLUS = 287,
    TMINUS = 288,
    TMUL = 289,
    TDIV = 290,
    TAND = 291,
    TOR = 292,
    TXOR = 293,
    TMOD = 294,
    TNEG = 295,
    TNOT = 296,
    TSHIFTL = 297,
    TSHIFTR = 298,
    TIF = 299,
    TELSE = 300,
    TFOR = 301,
    TWHILE = 302,
    TRETURN = 303,
    TSTRUCT = 304,
    TSCANF = 305,
    TPRINTF = 306
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 15 "parser.y"

	rmmc::BlockStatement* block;
	rmmc::Expression* expr;
	rmmc::Statement* stmt;
	rmmc::IdentifierExpr* ident;
	rmmc::VariableDeclarationStatement* var_decl;
	rmmc::VariableDeclarationStatement* input;
	rmmc::VariableDeclarationStatement* output;
	rmmc::ArrayIndex* index;
	std::vector< std::shared_ptr<rmmc::VariableDeclarationStatement> >*  varvec;
	std::vector< std::shared_ptr<rmmc::Expression> >* exprvec;
	std::string* string;
	int token;

#line 203 "parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */



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
typedef yytype_uint8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  46
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   563

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  141

#define YYUNDEFTOK  2
#define YYMAXUTOK   306


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    51,    51,    53,    54,    57,    57,    57,    58,    59,
      60,    61,    62,    65,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    77,    82,    87,    92,    93,    94,    96,
      97,    98,   103,   107,   108,   109,   112,   115,   116,   117,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   136,   138,   143,   144,   147,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   165,   166,   167,   173,   175,   177,   179,   180,
     181
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TIDENTIFIER", "TINTEGER", "TDOUBLE",
  "TYINT", "TYDOUBLE", "TYFLOAT", "TYCHAR", "TYBOOL", "TYVOID", "TYSTRING",
  "TEXTERN", "TLITERAL", "TCEQ", "TCNE", "TCLT", "TCLE", "TCGT", "TCGE",
  "TEQUAL", "TLPAREN", "TRPAREN", "TLBRACE", "TRBRACE", "TCOMMA", "TDOT",
  "TSEMICOLON", "TLBRACKET", "TRBRACKET", "TQUOTATION", "TPLUS", "TMINUS",
  "TMUL", "TDIV", "TAND", "TOR", "TXOR", "TMOD", "TNEG", "TNOT", "TSHIFTL",
  "TSHIFTR", "TIF", "TELSE", "TFOR", "TWHILE", "TRETURN", "TSTRUCT",
  "TSCANF", "TPRINTF", "$accept", "program", "stmts", "stmt", "block",
  "trblk", "primary_typename", "array_typename", "struct_typename",
  "typename", "var_decl", "func_decl", "func_decl_args", "ident",
  "numeric", "expr", "array_index", "assign", "call_args", "comparison",
  "if_stmt", "for_stmt", "while_stmt", "struct_decl", "struct_members", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306
};
# endif

#define YYPACT_NINF (-82)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     203,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,   -82,   240,   240,   240,   240,   -13,    -7,   240,    16,
      23,   203,   -82,     0,     1,   -82,    16,    11,   -82,    35,
     -82,   250,   -11,   -82,   -82,   -82,   -82,   -82,   275,   500,
     475,   300,   203,   240,   325,    24,   -82,   -82,    59,    61,
      -8,   -82,   240,   240,   240,   -82,   -82,   -82,   -82,   -82,
     -82,   240,    16,   -82,   240,   240,   240,   240,   -82,   -82,
     -82,   240,   240,   240,   240,   -82,   109,    25,   240,   350,
     -82,    87,    39,    41,   224,    87,   475,   475,     2,   375,
     475,   -82,   500,   500,   525,   525,   525,   475,   475,   400,
     -82,   156,   -82,   -17,   425,    49,    16,    16,    46,    26,
     -82,   -82,   240,   475,   -82,    20,   -82,   240,   -82,   -82,
     -82,   -82,   -82,   240,   -82,   -82,    55,   -82,   -82,    50,
     -18,    49,    87,   475,   450,   -82,   -82,   -82,   -82,    49,
     -82
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    36,    37,    38,    16,    17,    18,    19,    20,    21,
      22,    39,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     3,    26,    27,    28,     0,     0,     6,    42,
      43,     0,    54,    40,    10,    11,    12,     7,     0,    53,
      44,     0,     0,     0,     0,    25,     1,     4,     0,     0,
      29,     5,     0,    60,     0,    63,    64,    65,    66,    67,
      68,     0,     0,     8,     0,     0,     0,     0,    69,    70,
      71,     0,     0,     0,     0,    52,     0,    72,     0,     0,
       9,    78,     0,     0,     0,    33,    57,    61,     0,     0,
      59,    51,    49,    50,    47,    48,    46,    45,    58,     0,
      15,     0,    13,     0,     0,     0,     0,     0,     0,     0,
      23,    24,    60,    30,    34,     0,    41,     0,    55,    56,
      14,    73,    74,     0,    76,    25,    29,    79,    77,     0,
       0,     0,     0,    62,     0,    80,    31,    32,    35,     0,
      75
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -82,   -82,     3,   -16,   -81,   -82,   -82,   -82,   -82,   -65,
     -64,   -82,   -82,   -15,   -82,   -12,   -82,   -82,   -35,   -82,
     -23,   -82,   -82,   -82,   -82
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    20,    21,    22,    77,   102,    23,    24,    25,    26,
      27,    28,   115,    29,    30,    31,    32,    33,    88,    72,
      34,    35,    36,    37,   109
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      38,    39,    40,    41,    45,    47,    44,    76,   117,    42,
      73,    50,   136,    84,    85,    43,   107,   108,    74,     1,
     107,   114,   121,    46,   124,   116,    78,    15,   117,    48,
      49,    79,     4,     5,     6,     7,     8,     9,    10,    51,
      86,    87,    89,   131,   107,   129,   132,    91,    81,    90,
     137,   128,    92,    93,    94,    95,    52,    53,   140,    96,
      97,    98,    99,    82,    54,    83,   104,   107,   138,   110,
     103,   111,   113,    76,   127,   106,    84,   130,   135,   101,
     122,     0,     0,     0,     0,    47,     0,     0,     0,     0,
       0,   125,   126,     4,     5,     6,     7,     8,     9,    10,
      87,     0,     0,     0,     0,   133,     0,     0,     0,     0,
       0,   134,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,     0,    11,     0,     0,     0,     0,     0,     0,
       0,    12,     0,     0,   100,     0,   106,     0,     0,     0,
       0,     0,    13,     0,     0,    14,     0,     0,     0,     0,
       0,     0,     0,    15,     0,    16,    17,    18,    19,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,     0,
      11,     0,     0,     0,     0,     0,     0,     0,    12,     0,
       0,   120,     0,     0,     0,     0,     0,     0,     0,    13,
       0,     0,    14,     0,     0,     0,     0,     0,     0,     0,
      15,     0,    16,    17,    18,    19,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,     0,    11,     0,     0,
       0,     0,     0,     0,     0,    12,     0,     1,     2,     3,
       0,     0,     0,     0,     0,     0,    13,     0,    11,    14,
       0,     0,     0,     1,     2,     3,    12,    15,     0,    16,
      17,    18,    19,   112,    11,     0,     0,    13,     0,     0,
      14,     0,    12,     0,     0,    55,    56,    57,    58,    59,
      60,    61,     0,    13,     0,     0,    14,    62,    63,     0,
       0,     0,    64,    65,    66,    67,    68,    69,    70,    71,
      55,    56,    57,    58,    59,    60,    61,     0,    75,     0,
       0,     0,    62,     0,     0,     0,     0,    64,    65,    66,
      67,    68,    69,    70,    71,    55,    56,    57,    58,    59,
      60,    61,     0,     0,    76,     0,     0,    62,     0,     0,
       0,     0,    64,    65,    66,    67,    68,    69,    70,    71,
      55,    56,    57,    58,    59,    60,    61,     0,     0,     0,
       0,     0,    62,    80,     0,     0,     0,    64,    65,    66,
      67,    68,    69,    70,    71,    55,    56,    57,    58,    59,
      60,    61,     0,   105,     0,     0,     0,    62,     0,     0,
       0,     0,    64,    65,    66,    67,    68,    69,    70,    71,
      55,    56,    57,    58,    59,    60,    61,     0,     0,     0,
       0,     0,    62,     0,     0,   118,     0,    64,    65,    66,
      67,    68,    69,    70,    71,    55,    56,    57,    58,    59,
      60,    61,     0,     0,     0,     0,     0,    62,     0,     0,
     119,     0,    64,    65,    66,    67,    68,    69,    70,    71,
      55,    56,    57,    58,    59,    60,    61,     0,     0,     0,
       0,     0,    62,   123,     0,     0,     0,    64,    65,    66,
      67,    68,    69,    70,    71,    55,    56,    57,    58,    59,
      60,    61,     0,   139,     0,     0,     0,    62,     0,     0,
       0,     0,    64,    65,    66,    67,    68,    69,    70,    71,
      55,    56,    57,    58,    59,    60,    61,     0,     0,     0,
       0,     0,    62,     0,     0,     0,     0,    64,    65,    66,
      67,    68,    69,    70,    71,    55,    56,    57,    58,    59,
      60,    61,     0,     0,     0,     0,     0,    62,     0,     0,
       0,     0,     0,     0,    66,    67,    68,    69,    70,    71,
      55,    56,    57,    58,    59,    60,    61,     0,     0,     0,
       0,     0,    62,     0,     0,     0,     0,     0,     0,     0,
       0,    68,    69,    70
};

static const yytype_int16 yycheck[] =
{
      12,    13,    14,    15,    19,    21,    18,    24,    26,    22,
      21,    26,    30,    21,    22,    22,    81,    81,    29,     3,
      85,    85,   103,     0,   105,    23,    42,    44,    26,    29,
      29,    43,     6,     7,     8,     9,    10,    11,    12,    28,
      52,    53,    54,    23,   109,   109,    26,    62,    24,    61,
     131,    25,    64,    65,    66,    67,    21,    22,   139,    71,
      72,    73,    74,     4,    29,     4,    78,   132,   132,    30,
      45,    30,    84,    24,    28,    49,    21,   112,    28,    76,
     103,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,
      -1,   106,   107,     6,     7,     8,     9,    10,    11,    12,
     112,    -1,    -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,
      -1,   123,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    22,    -1,    -1,    25,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    46,    47,    48,    49,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    46,    47,    48,    49,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    -1,    14,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    22,    -1,     3,     4,     5,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    14,    36,
      -1,    -1,    -1,     3,     4,     5,    22,    44,    -1,    46,
      47,    48,    49,    29,    14,    -1,    -1,    33,    -1,    -1,
      36,    -1,    22,    -1,    -1,    15,    16,    17,    18,    19,
      20,    21,    -1,    33,    -1,    -1,    36,    27,    28,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      15,    16,    17,    18,    19,    20,    21,    -1,    23,    -1,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    27,    28,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    15,    16,    17,    18,    19,
      20,    21,    -1,    23,    -1,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    27,    -1,    -1,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,
      30,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    27,    28,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    15,    16,    17,    18,    19,
      20,    21,    -1,    23,    -1,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,    39,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    14,    22,    33,    36,    44,    46,    47,    48,    49,
      53,    54,    55,    58,    59,    60,    61,    62,    63,    65,
      66,    67,    68,    69,    72,    73,    74,    75,    67,    67,
      67,    67,    22,    22,    67,    65,     0,    55,    29,    29,
      65,    28,    21,    22,    29,    15,    16,    17,    18,    19,
      20,    21,    27,    28,    32,    33,    34,    35,    36,    37,
      38,    39,    71,    21,    29,    23,    24,    56,    55,    67,
      28,    24,     4,     4,    21,    22,    67,    67,    70,    67,
      67,    65,    67,    67,    67,    67,    67,    67,    67,    67,
      25,    54,    57,    45,    67,    23,    49,    61,    62,    76,
      30,    30,    29,    67,    62,    64,    23,    26,    30,    30,
      25,    56,    72,    28,    56,    65,    65,    28,    25,    62,
      70,    23,    26,    67,    67,    28,    30,    56,    62,    23,
      56
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    54,    54,    55,    55,    55,    55,    55,
      55,    55,    55,    56,    57,    57,    58,    58,    58,    58,
      58,    58,    58,    59,    59,    60,    61,    61,    61,    62,
      62,    62,    63,    64,    64,    64,    65,    66,    66,    66,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    68,    68,    69,    69,    69,
      70,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    72,    72,    72,    73,    74,    75,    76,    76,
      76
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     1,     1,     2,     3,
       1,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     4,     2,     1,     1,     1,     2,
       4,     6,     6,     0,     1,     3,     1,     1,     1,     1,
       1,     4,     1,     1,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     1,     4,     4,     3,     3,     3,
       0,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     5,     5,     8,     5,     5,     0,     2,
       3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
  case 2:
#line 51 "parser.y"
                { programBlock = (yyvsp[0].block); }
#line 1567 "parser.cpp"
    break;

  case 3:
#line 53 "parser.y"
             { (yyval.block) = new rmmc::BlockStatement(); (yyval.block)->Content->push_back(std::shared_ptr<rmmc::Statement>((yyvsp[0].stmt)));}
#line 1573 "parser.cpp"
    break;

  case 4:
#line 54 "parser.y"
                                      { (yyvsp[-1].block)->Content->push_back(std::shared_ptr<rmmc::Statement>((yyvsp[0].stmt))); }
#line 1579 "parser.cpp"
    break;

  case 8:
#line 58 "parser.y"
                                  { (yyval.stmt) = new rmmc::ExpressionStatement(std::shared_ptr<rmmc::Expression>((yyvsp[-1].expr))); }
#line 1585 "parser.cpp"
    break;

  case 9:
#line 59 "parser.y"
                                           { (yyval.stmt) = new rmmc::ReturnStatement(std::shared_ptr<rmmc::Expression>((yyvsp[-1].expr))); }
#line 1591 "parser.cpp"
    break;

  case 13:
#line 65 "parser.y"
                      { (yyval.block) = (yyvsp[0].block);}
#line 1597 "parser.cpp"
    break;

  case 14:
#line 67 "parser.y"
                      { (yyval.block) = (yyvsp[-1].block); }
#line 1603 "parser.cpp"
    break;

  case 15:
#line 68 "parser.y"
                            { (yyval.block) = new rmmc::BlockStatement(); }
#line 1609 "parser.cpp"
    break;

  case 16:
#line 69 "parser.y"
                         { (yyval.ident) = new rmmc::IdentifierExpr(*(yyvsp[0].string)); (yyval.ident)->isType = true; }
#line 1615 "parser.cpp"
    break;

  case 17:
#line 70 "parser.y"
                                                   { (yyval.ident) = new rmmc::IdentifierExpr(*(yyvsp[0].string)); (yyval.ident)->isType = true;  }
#line 1621 "parser.cpp"
    break;

  case 18:
#line 71 "parser.y"
                                                  { (yyval.ident) = new rmmc::IdentifierExpr(*(yyvsp[0].string)); (yyval.ident)->isType = true;  }
#line 1627 "parser.cpp"
    break;

  case 19:
#line 72 "parser.y"
                                                 { (yyval.ident) = new rmmc::IdentifierExpr(*(yyvsp[0].string)); (yyval.ident)->isType = true; }
#line 1633 "parser.cpp"
    break;

  case 20:
#line 73 "parser.y"
                                                 { (yyval.ident) = new rmmc::IdentifierExpr(*(yyvsp[0].string)); (yyval.ident)->isType = true; }
#line 1639 "parser.cpp"
    break;

  case 21:
#line 74 "parser.y"
                                                 { (yyval.ident) = new rmmc::IdentifierExpr(*(yyvsp[0].string)); (yyval.ident)->isType = true; }
#line 1645 "parser.cpp"
    break;

  case 22:
#line 75 "parser.y"
                                                   { (yyval.ident) = new rmmc::IdentifierExpr(*(yyvsp[0].string)); (yyval.ident)->isType = true;  }
#line 1651 "parser.cpp"
    break;

  case 23:
#line 77 "parser.y"
                                                               { 
					(yyvsp[-3].ident)->isArray = true; 
					(yyvsp[-3].ident)->arraySize->push_back(std::make_shared<rmmc::IntegerExpr>(atoi((yyvsp[-1].string)->c_str()))); 
					(yyval.ident) = (yyvsp[-3].ident); 
				}
#line 1661 "parser.cpp"
    break;

  case 24:
#line 82 "parser.y"
                                                                              {
					(yyvsp[-3].ident)->arraySize->push_back(std::make_shared<rmmc::IntegerExpr>(atoi((yyvsp[-1].string)->c_str())));
					(yyval.ident) = (yyvsp[-3].ident);
				}
#line 1670 "parser.cpp"
    break;

  case 25:
#line 87 "parser.y"
                                {
				(yyvsp[0].ident)->isType = true;
				(yyval.ident) = (yyvsp[0].ident);
			}
#line 1679 "parser.cpp"
    break;

  case 26:
#line 92 "parser.y"
                            { (yyval.ident) = (yyvsp[0].ident); }
#line 1685 "parser.cpp"
    break;

  case 27:
#line 93 "parser.y"
                                         { (yyval.ident) = (yyvsp[0].ident); }
#line 1691 "parser.cpp"
    break;

  case 28:
#line 94 "parser.y"
                                          { (yyval.ident) = (yyvsp[0].ident); }
#line 1697 "parser.cpp"
    break;

  case 29:
#line 96 "parser.y"
                           { (yyval.stmt) = new rmmc::VariableDeclarationStatement(std::shared_ptr<rmmc::IdentifierExpr>((yyvsp[-1].ident)), std::shared_ptr<rmmc::IdentifierExpr>((yyvsp[0].ident))); }
#line 1703 "parser.cpp"
    break;

  case 30:
#line 97 "parser.y"
                                                               { (yyval.stmt) = new rmmc::VariableDeclarationStatement(std::shared_ptr<rmmc::IdentifierExpr>((yyvsp[-3].ident)), std::shared_ptr<rmmc::IdentifierExpr>((yyvsp[-2].ident)), std::shared_ptr<rmmc::Expression>((yyvsp[0].expr))); }
#line 1709 "parser.cpp"
    break;

  case 31:
#line 98 "parser.y"
                                                                                         {
					 (yyval.stmt) = new rmmc::VariableDeclarationStatement(std::shared_ptr<rmmc::IdentifierExpr>((yyvsp[-5].ident)), std::shared_ptr<rmmc::IdentifierExpr>((yyvsp[-4].ident)), std::shared_ptr<rmmc::ExpressionList>((yyvsp[-1].exprvec)));
				 }
#line 1717 "parser.cpp"
    break;

  case 32:
#line 104 "parser.y"
                                { (yyval.stmt) = new rmmc::FunctionDeclarationStatement(std::shared_ptr<rmmc::IdentifierExpr>((yyvsp[-5].ident)), std::shared_ptr<rmmc::IdentifierExpr>((yyvsp[-4].ident)), std::shared_ptr<rmmc::VariableList>((yyvsp[-2].varvec)), std::shared_ptr<rmmc::BlockStatement>((yyvsp[0].block)));  }
#line 1723 "parser.cpp"
    break;

  case 33:
#line 107 "parser.y"
                             { (yyval.varvec) = new rmmc::VariableList(); }
#line 1729 "parser.cpp"
    break;

  case 34:
#line 108 "parser.y"
                                                                    { (yyval.varvec) = new rmmc::VariableList(); (yyval.varvec)->push_back(std::shared_ptr<rmmc::VariableDeclarationStatement>((yyvsp[0].var_decl))); }
#line 1735 "parser.cpp"
    break;

  case 35:
#line 109 "parser.y"
                                                                                          { (yyvsp[-2].varvec)->push_back(std::shared_ptr<rmmc::VariableDeclarationStatement>((yyvsp[0].var_decl))); }
#line 1741 "parser.cpp"
    break;

  case 36:
#line 112 "parser.y"
                    { (yyval.ident) = new rmmc::IdentifierExpr(*(yyvsp[0].string)); }
#line 1747 "parser.cpp"
    break;

  case 37:
#line 115 "parser.y"
                   { (yyval.expr) = new rmmc::IntegerExpr(atoi((yyvsp[0].string)->c_str())); }
#line 1753 "parser.cpp"
    break;

  case 38:
#line 116 "parser.y"
                                          { (yyval.expr) = new rmmc::DoubleExpr(atof((yyvsp[0].string)->c_str())); }
#line 1759 "parser.cpp"
    break;

  case 39:
#line 117 "parser.y"
                                             { (yyval.expr) = new rmmc::StringExpr((yyvsp[0].string)->c_str()); }
#line 1765 "parser.cpp"
    break;

  case 40:
#line 119 "parser.y"
               { (yyval.expr) = (yyvsp[0].expr); }
#line 1771 "parser.cpp"
    break;

  case 41:
#line 120 "parser.y"
                                                   { (yyval.expr) = new rmmc::FunctionCallExpr(std::shared_ptr<rmmc::IdentifierExpr>((yyvsp[-3].ident)), std::shared_ptr<rmmc::ExpressionList>((yyvsp[-1].exprvec))); }
#line 1777 "parser.cpp"
    break;

  case 42:
#line 121 "parser.y"
                         { (yyval.ident) = (yyvsp[0].ident); }
#line 1783 "parser.cpp"
    break;

  case 44:
#line 123 "parser.y"
                             { (yyval.expr) = new SingleOperatorExpr(std::shared_ptr<rmmc::Expression>((yyvsp[0].expr)), rmmc::SingleOperator::ADDRESS_OF); }
#line 1789 "parser.cpp"
    break;

  case 45:
#line 124 "parser.y"
                                        { (yyval.expr) = new rmmc::BinaryOperatorExpr(std::shared_ptr<rmmc::Expression>((yyvsp[-2].expr)), rmmc::BinaryOperator((yyvsp[-1].token)) , std::shared_ptr<rmmc::Expression>((yyvsp[0].expr))); }
#line 1795 "parser.cpp"
    break;

  case 46:
#line 125 "parser.y"
                                  { (yyval.expr) = new rmmc::BinaryOperatorExpr(std::shared_ptr<rmmc::Expression>((yyvsp[-2].expr)), rmmc::BinaryOperator::MOD, std::shared_ptr<rmmc::Expression>((yyvsp[0].expr))); }
#line 1801 "parser.cpp"
    break;

  case 47:
#line 126 "parser.y"
                                  { (yyval.expr) = new rmmc::BinaryOperatorExpr(std::shared_ptr<rmmc::Expression>((yyvsp[-2].expr)), rmmc::BinaryOperator::MUL, std::shared_ptr<rmmc::Expression>((yyvsp[0].expr))); }
#line 1807 "parser.cpp"
    break;

  case 48:
#line 127 "parser.y"
                                  { (yyval.expr) = new rmmc::BinaryOperatorExpr(std::shared_ptr<rmmc::Expression>((yyvsp[-2].expr)), rmmc::BinaryOperator::DIV, std::shared_ptr<rmmc::Expression>((yyvsp[0].expr)));  }
#line 1813 "parser.cpp"
    break;

  case 49:
#line 128 "parser.y"
                                   { (yyval.expr) = new rmmc::BinaryOperatorExpr(std::shared_ptr<rmmc::Expression>((yyvsp[-2].expr)), rmmc::BinaryOperator::ADD, std::shared_ptr<rmmc::Expression>((yyvsp[0].expr)));  }
#line 1819 "parser.cpp"
    break;

  case 50:
#line 129 "parser.y"
                                    { (yyval.expr) = new rmmc::BinaryOperatorExpr(std::shared_ptr<rmmc::Expression>((yyvsp[-2].expr)), rmmc::BinaryOperator::SUB, std::shared_ptr<rmmc::Expression>((yyvsp[0].expr)));  }
#line 1825 "parser.cpp"
    break;

  case 51:
#line 130 "parser.y"
                                   { (yyval.expr) = new rmmc::BinaryOperatorExpr(std::shared_ptr<rmmc::Expression>((yyvsp[-2].expr)), rmmc::BinaryOperator::STRUCT_REF, std::shared_ptr<rmmc::Expression>((yyvsp[0].ident)));  }
#line 1831 "parser.cpp"
    break;

  case 52:
#line 131 "parser.y"
                                        { (yyval.expr) = (yyvsp[-1].expr); }
#line 1837 "parser.cpp"
    break;

  case 53:
#line 132 "parser.y"
                               { (yyval.expr) = nullptr; /* TODO */ }
#line 1843 "parser.cpp"
    break;

  case 54:
#line 133 "parser.y"
                               { (yyval.expr) = (yyvsp[0].index); }
#line 1849 "parser.cpp"
    break;

  case 55:
#line 137 "parser.y"
                                { (yyval.index) = new rmmc::ArrayIndex(std::shared_ptr<rmmc::IdentifierExpr>((yyvsp[-3].ident)), std::shared_ptr<rmmc::Expression>((yyvsp[-1].expr))); }
#line 1855 "parser.cpp"
    break;

  case 56:
#line 139 "parser.y"
                                        { 	
						(yyvsp[-3].index)->index->push_back(std::shared_ptr<rmmc::Expression>((yyvsp[-1].expr)));
						(yyval.index) = (yyvsp[-3].index);
					}
#line 1864 "parser.cpp"
    break;

  case 57:
#line 143 "parser.y"
                            { (yyval.expr) = new rmmc::AssignmentExpression(std::shared_ptr<rmmc::Expression>((yyvsp[-2].expr)), std::shared_ptr<rmmc::Expression>((yyvsp[0].expr))); }
#line 1870 "parser.cpp"
    break;

  case 58:
#line 144 "parser.y"
                                                   {
				(yyval.expr) = new rmmc::AssignmentExpression(std::shared_ptr<rmmc::Expression>((yyvsp[-2].index)), std::shared_ptr<rmmc::Expression>((yyvsp[0].expr)));
			}
#line 1878 "parser.cpp"
    break;

  case 59:
#line 147 "parser.y"
                                            {
				(yyval.expr) = new rmmc::AssignmentExpression(std::shared_ptr<rmmc::Expression>((yyvsp[-2].expr)), std::shared_ptr<rmmc::Expression>((yyvsp[0].expr))); 
			}
#line 1886 "parser.cpp"
    break;

  case 60:
#line 152 "parser.y"
                        { (yyval.exprvec) = new rmmc::ExpressionList(); }
#line 1892 "parser.cpp"
    break;

  case 61:
#line 153 "parser.y"
                                               { (yyval.exprvec) = new rmmc::ExpressionList(); (yyval.exprvec)->push_back(std::shared_ptr<rmmc::Expression>((yyvsp[0].expr))); }
#line 1898 "parser.cpp"
    break;

  case 62:
#line 154 "parser.y"
                                                                { (yyvsp[-2].exprvec)->push_back(std::shared_ptr<Expression>((yyvsp[0].expr))); }
#line 1904 "parser.cpp"
    break;

  case 63:
#line 155 "parser.y"
                   { (yyval.token) = rmmc::BinaryOperator::E; }
#line 1910 "parser.cpp"
    break;

  case 64:
#line 156 "parser.y"
                               { (yyval.token) = rmmc::BinaryOperator::NE; }
#line 1916 "parser.cpp"
    break;

  case 65:
#line 157 "parser.y"
                               { (yyval.token) = rmmc::BinaryOperator::LT; }
#line 1922 "parser.cpp"
    break;

  case 66:
#line 158 "parser.y"
                               { (yyval.token) = rmmc::BinaryOperator::ELT; }
#line 1928 "parser.cpp"
    break;

  case 67:
#line 159 "parser.y"
                               { (yyval.token) = rmmc::BinaryOperator::GT; }
#line 1934 "parser.cpp"
    break;

  case 68:
#line 160 "parser.y"
                               { (yyval.token) = rmmc::BinaryOperator::EGT; }
#line 1940 "parser.cpp"
    break;

  case 69:
#line 161 "parser.y"
                               { (yyval.token) = rmmc::BinaryOperator::AND; }
#line 1946 "parser.cpp"
    break;

  case 70:
#line 162 "parser.y"
                               { (yyval.token) = rmmc::BinaryOperator::OR; }
#line 1952 "parser.cpp"
    break;

  case 71:
#line 163 "parser.y"
                               { (yyval.token) = rmmc::BinaryOperator::XOR; }
#line 1958 "parser.cpp"
    break;

  case 72:
#line 165 "parser.y"
                         { (yyval.stmt) = new rmmc::IfStatement(std::shared_ptr<rmmc::Expression>((yyvsp[-1].expr)), std::shared_ptr<rmmc::BlockStatement>((yyvsp[0].block))); }
#line 1964 "parser.cpp"
    break;

  case 73:
#line 166 "parser.y"
                                             { (yyval.stmt) = new rmmc::IfStatement(std::shared_ptr<rmmc::Expression>((yyvsp[-3].expr)), std::shared_ptr<rmmc::BlockStatement>((yyvsp[-2].block)), std::shared_ptr<rmmc::BlockStatement>((yyvsp[0].block))); }
#line 1970 "parser.cpp"
    break;

  case 74:
#line 167 "parser.y"
                                               { 
			auto blk = new rmmc::BlockStatement(); 
			blk->Content->push_back(std::shared_ptr<rmmc::Statement>((yyvsp[0].stmt))); 
			(yyval.stmt) = new rmmc::IfStatement(std::shared_ptr<rmmc::Expression>((yyvsp[-3].expr)), std::shared_ptr<rmmc::BlockStatement>((yyvsp[-2].block)), std::shared_ptr<rmmc::BlockStatement>(blk)); 
		}
#line 1980 "parser.cpp"
    break;

  case 75:
#line 173 "parser.y"
                                                                 { (yyval.stmt) = new rmmc::ForStatement(std::shared_ptr<rmmc::Statement>((yyvsp[-5].stmt)), std::shared_ptr<rmmc::Expression>((yyvsp[-4].expr)), std::shared_ptr<rmmc::Expression>((yyvsp[-2].expr)), std::shared_ptr<rmmc::BlockStatement>((yyvsp[0].block))); }
#line 1986 "parser.cpp"
    break;

  case 76:
#line 175 "parser.y"
                                               { (yyval.stmt) = new rmmc::WhileStatement(std::shared_ptr<rmmc::Expression>((yyvsp[-2].expr)), std::shared_ptr<rmmc::BlockStatement>((yyvsp[0].block))); }
#line 1992 "parser.cpp"
    break;

  case 77:
#line 177 "parser.y"
                                                           {(yyval.stmt) = new rmmc::StructDeclarationStatement(std::shared_ptr<rmmc::IdentifierExpr>((yyvsp[-3].ident)), std::shared_ptr<rmmc::VariableList>((yyvsp[-1].varvec))); }
#line 1998 "parser.cpp"
    break;

  case 78:
#line 179 "parser.y"
                             { (yyval.varvec) = new rmmc::VariableList(); }
#line 2004 "parser.cpp"
    break;

  case 79:
#line 180 "parser.y"
                                                     { (yyval.varvec) = new rmmc::VariableList(); (yyval.varvec)->push_back(std::shared_ptr<rmmc::VariableDeclarationStatement>((yyvsp[-1].var_decl))); }
#line 2010 "parser.cpp"
    break;

  case 80:
#line 181 "parser.y"
                                                                    { (yyvsp[-2].varvec)->push_back(std::shared_ptr<rmmc::VariableDeclarationStatement>((yyvsp[-1].var_decl))); }
#line 2016 "parser.cpp"
    break;


#line 2020 "parser.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 184 "parser.y"
