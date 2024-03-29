#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/raw_ostream.h>

#include <vector>

#include "CodeGen.h"

typedef llvm::Type *TypePtr;
typedef llvm::FunctionType *FunctionTypePtr;

void rmmc::CodeGenContext::CodeGen(std::shared_ptr<rmmc::ASTNode> root)
{
    root->codeGen(*this);
}
