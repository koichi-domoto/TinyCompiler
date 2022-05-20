#include <signal.h>
#include <unistd.h>
#include <getopt.h>
#include <string>
#include <string.h>
#include <filesystem>
#include <fstream>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/raw_ostream.h>
#include "CodeGen.h"
using namespace rmmc;
using namespace llvm;
using legacy::PassManager;
using namespace std;

void ObjGen(CodeGenContext &context, const std::string &filename)
{
	// Initialize the target registry etc.
	llvm::InitializeAllTargetInfos();
	llvm::InitializeAllTargets();
	llvm::InitializeAllTargetMCs();
	llvm::InitializeAllAsmParsers();
	llvm::InitializeAllAsmPrinters();

	auto targetTriple = llvm::sys::getDefaultTargetTriple();
	context.theModule->setTargetTriple(targetTriple);

	std::string error;
	auto Target = llvm::TargetRegistry::lookupTarget(targetTriple, error);

	if (!Target)
	{
		llvm::errs() << error;
		return;
	}

	auto CPU = "generic";
	auto features = "";

	llvm::TargetOptions opt;
	auto RM = llvm::Optional<llvm::Reloc::Model>();
	auto theTargetMachine = Target->createTargetMachine(targetTriple, CPU, features, opt, RM);

	context.theModule->setDataLayout(theTargetMachine->createDataLayout());
	context.theModule->setTargetTriple(targetTriple);

	std::error_code EC;
	llvm::raw_fd_ostream dest(filename.c_str(), EC, llvm::sys::fs::F_None);
	
	llvm::legacy::PassManager pass;
	auto fileType = llvm::CodeGenFileType::CGFT_ObjectFile;

	if (theTargetMachine->addPassesToEmitFile(pass, dest, nullptr, fileType))
	{
		llvm::errs() << "theTargetMachine can't emit a file of this type";
		return;
	}

	pass.run(*context.theModule.get());
	dest.flush();

	llvm::outs() << "Object code wrote to " << filename.c_str() << "\n";

	return;
}

extern int yyparse();
extern rmmc::BlockStatement* programBlock;

int main(int argc, char *const *argv)
{
	//(1)scanner and parser
	yyparse();
	cout<<"Parser Finished"<<endl;
	//(2)generate json 
	std::string json_string=programBlock->toJSON();
	ofstream out("AST.json");
	if(out.is_open()){
		out<<json_string;
		out.close();
	}else{
		cout<<"Can't open file"<<endl;
	}
	//(3)generate AST and module
	CodeGenContext code;
	code.CodeGen(shared_ptr<BlockStatement>(programBlock));
	//(4)print IR code
	PassManager passManager;
	passManager.add(createPrintModulePass(outs()));
	passManager.run(*(code.theModule.get()));
	//(5)write object code
	ObjGen(code,"output.o");
	return 0;

	// cout << "Hello World" << endl;
	// //<---------------Case1------------->
	// shared_ptr<IdentifierExpr> ReturnType = make_shared<IdentifierExpr>(string("int"), true, false);
	// shared_ptr<IdentifierExpr> FunctionName = make_shared<IdentifierExpr>(string("main"));
	// // unique_ptr<VariableDeclarationStatement> arg1 = make_shared<VariableDeclarationStatement>();
	// shared_ptr<VariableList> Args = make_shared<VariableList>();
	// shared_ptr<Statement> st1 = make_shared<VariableDeclarationStatement>(
	// 	make_shared<IdentifierExpr>("int", true, false),
	// 	make_shared<IdentifierExpr>("a")
	// 	);
	
	// shared_ptr<Expression> st2_expr = make_shared<AssignmentExpression>(
	// 	make_shared<IdentifierExpr>("a"),
	// 	make_shared<IntegerExpr>(1)
	// );
	// shared_ptr<Statement> st2 = make_shared<ExpressionStatement>(
	// 	st2_expr
	// );
	// shared_ptr<ExpressionList> st3_args = make_shared<ExpressionList>();
	// st3_args->push_back( make_shared<StringExpr>("Hello") );
    // //st3_args->push_back( make_shared<IdentifierExpr>("a", loc) );
	// shared_ptr<Expression> st3_expr = make_shared<FunctionCallExpr>(
	// 	make_shared<IdentifierExpr>("printf"),
	// 	st3_args
	// );
	// shared_ptr<Statement> st3 = make_shared<ExpressionStatement>(
	// 	st3_expr
	// );
	// shared_ptr<ReturnStatement> Return = make_shared<ReturnStatement>(
	// 	move(make_shared<IntegerExpr>(0)));
	// // unique_ptr<Statement> st2 = make_shared<AssignmentExpression>()
	// shared_ptr<StatementList> contentList = make_shared<StatementList>();
	// contentList->push_back(st1);
	// contentList->push_back(st2);
	// contentList->push_back(st3);
	// contentList->push_back(Return);
	// shared_ptr<BlockStatement> Content = make_shared<BlockStatement>(contentList);
	
	// shared_ptr<Statement> main = make_shared<FunctionDeclarationStatement>(
	// 	move(ReturnType),
	// 	move(FunctionName),
	// 	move(Args),
	// 	move(Content),
	// 	false);
	// shared_ptr<StatementList> rootList = make_shared<StatementList>();
	// //rootList->push_back(print);
	// rootList->push_back(main);
	// shared_ptr<BlockStatement> root = make_shared<BlockStatement>(rootList);
	// CodeGenContext code;
	// code.CodeGen(move(root));
	// std::cout<<"Code Gen Finished"<<std::endl;
	// // string xml=main->toXML();
	// // //cout<<xml<<endl;
	// // ofstream out("AST.xml");
	// // if(out.is_open()){
	// // 	out<<xml;
	// // 	out.close();
	// // }
	// PassManager passManager;
	// passManager.add(createPrintModulePass(outs()));
	// passManager.run(*(code.theModule.get()));

	// ObjGen(code,"output.o");
	// return 0;
}