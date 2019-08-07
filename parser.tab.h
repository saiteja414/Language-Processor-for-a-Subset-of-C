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
     INTEGER_NUMBER = 258,
     DOUBLE_NUMBER = 259,
     NAME = 260,
     INTEGER = 261,
     FLOAT = 262,
     VOID = 263,
     RETURN = 264,
     PRINT = 265,
     ASSIGN = 266,
     DO = 267,
     WHILE = 268,
     IF = 269,
     ELSE = 270,
     LESS_THAN_EQUAL = 271,
     GREATER_THAN_EQUAL = 272,
     EQUAL = 273,
     NOT_EQUAL = 274,
     LESS_THAN = 275,
     GREATER_THAN = 276,
     AND = 277,
     OR = 278,
     NOT = 279
   };
#endif
/* Tokens.  */
#define INTEGER_NUMBER 258
#define DOUBLE_NUMBER 259
#define NAME 260
#define INTEGER 261
#define FLOAT 262
#define VOID 263
#define RETURN 264
#define PRINT 265
#define ASSIGN 266
#define DO 267
#define WHILE 268
#define IF 269
#define ELSE 270
#define LESS_THAN_EQUAL 271
#define GREATER_THAN_EQUAL 272
#define EQUAL 273
#define NOT_EQUAL 274
#define LESS_THAN 275
#define GREATER_THAN 276
#define AND 277
#define OR 278
#define NOT 279




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 17 "src/parser.y"
{
    int integer_value;
	double double_value;
	std::string * string_value;
	list<Ast *> * ast_list;
	Ast * ast;
	Sequence_Ast * seq_ast;
	Symbol_Table * symbol_table;
	Symbol_Table_Entry * symbol_entry;
	Basic_Block * basic_block;
	Procedure * procedure;
}
/* Line 1529 of yacc.c.  */
#line 110 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

