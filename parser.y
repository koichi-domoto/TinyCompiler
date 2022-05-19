%{
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
%}
%union
{
	rmmc::BlockStatement* block;
	rmmc::Expression* expr;
	rmmc::Statement* stmt;
	rmmc::IdentifierExpr* ident;
	rmmc::VariableDeclarationStatement* var_decl;
	rmmc::ArrayIndex* index;
	std::vector< std::shared_ptr<rmmc::VariableDeclarationStatement> >*  varvec;
	std::vector< std::shared_ptr<rmmc::Expression> >* exprvec;
	std::string* string;
	int token;
}

%token <string> TIDENTIFIER TINTEGER TDOUBLE TYINT TYDOUBLE TYFLOAT TYCHAR TYBOOL TYVOID TYSTRING TEXTERN TLITERAL
%token <token> TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TDOT TSEMICOLON TLBRACKET TRBRACKET TQUOTATION
%token <token> TPLUS TMINUS TMUL TDIV TAND TOR TXOR TMOD TNEG TNOT TSHIFTL TSHIFTR
%token <token> TIF TELSE TFOR TWHILE TRETURN TSTRUCT

%type <index> array_index
%type <ident> ident primary_typename array_typename struct_typename typename
%type <expr> numeric expr assign
%type <varvec> func_decl_args struct_members
%type <exprvec> call_args
%type <block> program stmts block
%type <stmt> stmt var_decl func_decl struct_decl if_stmt for_stmt while_stmt
%type <token> comparison

%left TPLUS TMINUS
%left TMUL TDIV TMOD

%start program

%%
program : stmts { programBlock = $1; }
				;
stmts : stmt { $$ = new rmmc::BlockStatement(); $$->Content->push_back(std::shared_ptr<rmmc::Statement>($1)); }
			| stmts stmt { $1->Content->push_back(std::shared_ptr<rmmc::Statement>($2)); }
			;
stmt : var_decl | func_decl | struct_decl
		 | expr { $$ = new rmmc::ExpressionStatement(std::shared_ptr<rmmc::Expression>($1)); }
		 | TRETURN expr { $$ = new rmmc::ReturnStatement(std::shared_ptr<rmmc::Expression>($2)); }
		 | if_stmt
		 | for_stmt
		 | while_stmt
		 ;

block : TLBRACE stmts TRBRACE { $$ = $2; }
			| TLBRACE TRBRACE { $$ = new rmmc::BlockStatement(); }
			;

primary_typename : TYINT { $$ = new rmmc::IdentifierExpr(*$1); $$->isType = true; }
					| TYDOUBLE { $$ = new rmmc::IdentifierExpr(*$1); $$->isType = true;  }
					| TYFLOAT { $$ = new rmmc::IdentifierExpr(*$1); $$->isType = true;  }
					| TYCHAR { $$ = new rmmc::IdentifierExpr(*$1); $$->isType = true; }
					| TYBOOL { $$ = new rmmc::IdentifierExpr(*$1); $$->isType = true; }
					| TYVOID { $$ = new rmmc::IdentifierExpr(*$1); $$->isType = true; }
					| TYSTRING { $$ = new rmmc::IdentifierExpr(*$1); $$->isType = true;  }

array_typename : primary_typename TLBRACKET TINTEGER TRBRACKET { 
					$1->isArray = true; 
					$1->arraySize->push_back(std::make_shared<rmmc::IntegerExpr>(atoi($3->c_str()))); 
					$$ = $1; 
				}
				| array_typename TLBRACKET TINTEGER TRBRACKET {
					$1->arraySize->push_back(std::make_shared<rmmc::IntegerExpr>(atoi($3->c_str())));
					$$ = $1;
				}

struct_typename : TSTRUCT ident {
				$2->isType = true;
				$$ = $2;
			}

typename : primary_typename { $$ = $1; }
			| array_typename { $$ = $1; }
			| struct_typename { $$ = $1; }

var_decl : typename ident { $$ = new rmmc::VariableDeclarationStatement(std::shared_ptr<rmmc::IdentifierExpr>($1), std::shared_ptr<rmmc::IdentifierExpr>($2)); }
				 | typename ident TEQUAL expr { $$ = new rmmc::VariableDeclarationStatement(std::shared_ptr<rmmc::IdentifierExpr>($1), std::shared_ptr<rmmc::IdentifierExpr>($2), std::shared_ptr<rmmc::Expression>($4)); }
				 | typename ident TEQUAL TLBRACKET call_args TRBRACKET {
					 $$ = new rmmc::VariableDeclarationStatement(std::shared_ptr<rmmc::IdentifierExpr>($1), std::shared_ptr<rmmc::IdentifierExpr>($2), std::shared_ptr<rmmc::ExpressionList>($5));
				 }
				 ;

func_decl : typename ident TLPAREN func_decl_args TRPAREN block
				{ $$ = new rmmc::FunctionDeclarationStatement(std::shared_ptr<rmmc::IdentifierExpr>($1), std::shared_ptr<rmmc::IdentifierExpr>($2), std::shared_ptr<rmmc::VariableList>($4), std::shared_ptr<rmmc::BlockStatement>($6));  }
			

func_decl_args : /* blank */ { $$ = new rmmc::VariableList(); }
							 | var_decl { $$ = new rmmc::VariableList(); $$->push_back(std::shared_ptr<rmmc::VariableDeclarationStatement>($<var_decl>1)); }
							 | func_decl_args TCOMMA var_decl { $1->push_back(std::shared_ptr<rmmc::VariableDeclarationStatement>($<var_decl>3)); }
							 ;

ident : TIDENTIFIER { $$ = new rmmc::IdentifierExpr(*$1); }
			;

numeric : TINTEGER { $$ = new rmmc::IntegerExpr(atoi($1->c_str())); }
				| TDOUBLE { $$ = new rmmc::DoubleExpr(atof($1->c_str())); }
				;
expr : 	assign { $$ = $1; }
		 | ident TLPAREN call_args TRPAREN { $$ = new rmmc::FunctionCallExpr(std::shared_ptr<rmmc::IdentifierExpr>($1), std::shared_ptr<rmmc::ExpressionList>($3)); }
		 | ident { $<ident>$ = $1; }
		 | numeric
		 | expr comparison expr { $$ = new rmmc::BinaryOperatorExpr(std::shared_ptr<rmmc::Expression>($1), rmmc::BinaryOperator($2) , std::shared_ptr<rmmc::Expression>($3)); }
		 | expr TMOD expr { $$ = new rmmc::BinaryOperatorExpr(std::shared_ptr<rmmc::Expression>($1), rmmc::BinaryOperator::MOD, std::shared_ptr<rmmc::Expression>($3)); }
		 | expr TMUL expr { $$ = new rmmc::BinaryOperatorExpr(std::shared_ptr<rmmc::Expression>($1), rmmc::BinaryOperator::MUL, std::shared_ptr<rmmc::Expression>($3)); }
		 | expr TDIV expr { $$ = new rmmc::BinaryOperatorExpr(std::shared_ptr<rmmc::Expression>($1), rmmc::BinaryOperator::DIV, std::shared_ptr<rmmc::Expression>($3));  }
		 | expr TPLUS expr { $$ = new rmmc::BinaryOperatorExpr(std::shared_ptr<rmmc::Expression>($1), rmmc::BinaryOperator::ADD, std::shared_ptr<rmmc::Expression>($3));  }
		 | expr TMINUS expr { $$ = new rmmc::BinaryOperatorExpr(std::shared_ptr<rmmc::Expression>($1), rmmc::BinaryOperator::SUB, std::shared_ptr<rmmc::Expression>($3));  }
		 | expr TDOT expr { $$ = new rmmc::BinaryOperatorExpr(std::shared_ptr<rmmc::Expression>($1), rmmc::BinaryOperator::STRUCT_REF, std::shared_ptr<rmmc::Expression>($3));  }
		 | TLPAREN expr TRPAREN { $$ = $2; }
		 | TMINUS expr { $$ = nullptr; /* TODO */ }
		 | array_index { $$ = $1; }
		 ;

array_index : ident TLBRACKET expr TRBRACKET 
				{ $$ = new rmmc::ArrayIndex(std::shared_ptr<rmmc::IdentifierExpr>($1), std::shared_ptr<rmmc::Expression>($3)); }
				| array_index TLBRACKET expr TRBRACKET 
					{ 	
						$1->index->push_back(std::shared_ptr<rmmc::Expression>($3));
						$$ = $1;
					}
assign : ident TEQUAL expr { $$ = new rmmc::AssignmentExpression(std::shared_ptr<rmmc::Expression>($<expr>1), std::shared_ptr<rmmc::Expression>($3)); }
			| array_index TEQUAL expr {
				$$ = new rmmc::AssignmentExpression(std::shared_ptr<rmmc::Expression>($1), std::shared_ptr<rmmc::Expression>($3));
			}
			| expr TEQUAL expr {
				$$ = new rmmc::AssignmentExpression(std::shared_ptr<rmmc::Expression>($1), std::shared_ptr<rmmc::Expression>($3)); 
			}
			;

call_args : /* blank */ { $$ = new rmmc::ExpressionList(); }
					| expr { $$ = new rmmc::ExpressionList(); $$->push_back(std::shared_ptr<rmmc::Expression>($1)); }
					| call_args TCOMMA expr { $1->push_back(std::shared_ptr<Expression>($3)); }
comparison :  TCEQ { $$ = rmmc::BinaryOperator::E; }
			| TCNE { $$ = rmmc::BinaryOperator::NE; }
			| TCLT { $$ = rmmc::BinaryOperator::LT; }
			| TCLE { $$ = rmmc::BinaryOperator::ELT; }
			| TCGT { $$ = rmmc::BinaryOperator::GT; }
			| TCGE { $$ = rmmc::BinaryOperator::EGT; }
			| TAND { $$ = rmmc::BinaryOperator::AND; }
			| TOR  { $$ = rmmc::BinaryOperator::OR; }
			| TXOR { $$ = rmmc::BinaryOperator::XOR; }
			;
if_stmt : TIF expr block { $$ = new rmmc::IfStatement(std::shared_ptr<rmmc::Expression>($2), std::shared_ptr<rmmc::BlockStatement>($3)); }
		| TIF expr block TELSE block { $$ = new rmmc::IfStatement(std::shared_ptr<rmmc::Expression>($2), std::shared_ptr<rmmc::BlockStatement>($3), std::shared_ptr<rmmc::BlockStatement>($5)); }
		| TIF expr block TELSE if_stmt { 
			auto blk = new rmmc::BlockStatement(); 
			blk->Content->push_back(std::shared_ptr<rmmc::Statement>($5)); 
			$$ = new rmmc::IfStatement(std::shared_ptr<rmmc::Expression>($2), std::shared_ptr<rmmc::BlockStatement>($3), std::shared_ptr<rmmc::BlockStatement>(blk)); 
		}

for_stmt : TFOR TLPAREN stmt TSEMICOLON expr TSEMICOLON expr TRPAREN block { $$ = new rmmc::ForStatement(std::shared_ptr<rmmc::Statement>($3), std::shared_ptr<rmmc::Expression>($5), std::shared_ptr<rmmc::Expression>($7), std::shared_ptr<rmmc::BlockStatement>($9)); }
		
while_stmt : TWHILE TLPAREN expr TRPAREN block { $$ = new rmmc::WhileStatement(std::shared_ptr<rmmc::Expression>($3), std::shared_ptr<rmmc::BlockStatement>($5)); }

struct_decl : TSTRUCT ident TLBRACE struct_members TRBRACE {$$ = new rmmc::StructDeclarationStatement(std::shared_ptr<rmmc::IdentifierExpr>($2), std::shared_ptr<rmmc::VariableList>($4)); }

struct_members : /* blank */ { $$ = new rmmc::VariableList(); }
				| var_decl { $$ = new rmmc::VariableList(); $$->push_back(std::shared_ptr<rmmc::VariableDeclarationStatement>($<var_decl>1)); }
				| struct_members var_decl { $1->push_back(std::shared_ptr<rmmc::VariableDeclarationStatement>($<var_decl>2)); }

%%