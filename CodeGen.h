#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Target/TargetMachine.h>

#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/ADT/Optional.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/IR/LegacyPassManager.h>

#include <vector>
#include <memory>
#include <cstring>
#include <map>

#include "AST.h"

namespace rmmc
{
    typedef llvm::Type *TypePtr;
    typedef llvm::ArrayType *ArrayTypePtr;
    typedef llvm::FunctionType *FunctionTypePtr;
    typedef llvm::Function *FunctionPtr;
    typedef llvm::Value *ValuePtr;
    typedef llvm::BasicBlock *BasicBlockPtr;
    class CodeGenContext;
    class TypeSystem
    {
    public:
        std::map<TypePtr, std::map<TypePtr, llvm::CastInst::CastOps>> _castTable;
        TypePtr floatTy = nullptr;
        TypePtr intTy = nullptr;
        TypePtr charTy = nullptr;
        TypePtr doubleTy = nullptr;
        TypePtr stringTy = nullptr;
        TypePtr voidTy = nullptr;
        TypePtr boolTy = nullptr;

        TypeSystem(llvm::LLVMContext& llvmContext)
        {
            floatTy = llvm::Type::getFloatTy(llvmContext);
            intTy = llvm::Type::getInt32Ty(llvmContext);
            charTy = llvm::Type::getInt8Ty(llvmContext);
            doubleTy = llvm::Type::getDoubleTy(llvmContext);
            stringTy = llvm::Type::getInt8PtrTy(llvmContext);
            voidTy = llvm::Type::getVoidTy(llvmContext);
            boolTy = llvm::Type::getInt1Ty(llvmContext);
            addCast(intTy, floatTy, llvm::CastInst::SIToFP);
            addCast(intTy, doubleTy, llvm::CastInst::SIToFP);
            addCast(boolTy, doubleTy, llvm::CastInst::SIToFP);
            addCast(floatTy, doubleTy, llvm::CastInst::FPExt);
            addCast(floatTy, intTy, llvm::CastInst::FPToSI);
            addCast(doubleTy, intTy, llvm::CastInst::FPToSI);
            addCast(intTy, boolTy, llvm::CastInst::SExt);
        }
        void addCast(TypePtr from, TypePtr to, llvm::CastInst::CastOps op)
        {
            if (_castTable.find(from) == _castTable.end())
            {
                _castTable[from] = std::map<TypePtr, llvm::CastInst::CastOps>();
            }
            _castTable[from][to] = op;
        }
        ValuePtr cast(ValuePtr value, TypePtr type, BasicBlockPtr block)
        {
            TypePtr from = value->getType();
            if (from == type)
                return value;
            if (_castTable.find(from) == _castTable.end())
            {
                std::cout << "No cast" << std::endl;
                return nullptr;
            }
            if (_castTable[from].find(type) == _castTable[from].end())
            {
                std::cout << "No cast" << std::endl;
                return nullptr;
            }
            return llvm::CastInst::Create(_castTable[from][type], value, type, "cast", block);
        }
        // ValuePtr CastToBool(CodeGenContext& context, ValuePtr value)
        // {
        //     context.theBuilder.CreateIntCast();
        //     if(value->getType()->getTypeID() == llvm::Type::IntegerTyID)
        //     {
        //         context.theBuilder.CreateICmpEQ()
        //     }
        // }
    };
    // llvm::Type* getLLVMType(std::shared_ptr<IdentifierExpr> type, rmmc::CodeGenContext &context)
    // {
    //     std::string name=type->getName();
    //     if( name.compare("int") )
    //         return llvm::Type::getInt64Ty(context.theContext);
    //     return nullptr;
    // }

}

namespace rmmc
{

    typedef llvm::BasicBlock *BasicBlockPtr;
    typedef llvm::Value *ValuePtr;
    typedef llvm::Type *TypePtr;
    typedef CodeGenBlock *CodeGenBlockPtr;

    class CodeGenBlock
    {
    public:
        BasicBlockPtr block;
        std::map<std::string, ValuePtr> SymbolTable;
        std::map<std::string, TypePtr > SymbolType;
        ValuePtr returnValue;
    };

    class CodeGenContext
    {
    public:
        std::vector<CodeGenBlockPtr> blockStack;

        llvm::LLVMContext theContext;
        llvm::IRBuilder<> theBuilder;
        std::unique_ptr<llvm::Module> theModule;
        rmmc::TypeSystem typeSystem;

        FunctionPtr getPrintf = nullptr;


        CodeGenContext() : typeSystem(theContext),theBuilder(theContext)
        {
            theModule = std::make_unique<llvm::Module>("main", this->theContext);
            const std::string name="printf";
            getPrintf = theModule->getFunction(llvm::StringRef(name));
            if(getPrintf==nullptr){
                FunctionTypePtr func_type = llvm::FunctionType::get(
                    llvm::Type::getInt32Ty(theContext),
                    {llvm::Type::getInt8PtrTy(theContext)},
                    true
                );
                getPrintf = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, name.c_str(), theModule.get());
            }
        }

        void CodeGen(std::shared_ptr<ASTNode> root);

        BasicBlockPtr currentBlock(){
            return blockStack.back()->block;
        }

        void setCurrentReturnValue(ValuePtr value)
        {
            blockStack.back()->returnValue = value;
        }

        ValuePtr getCurrentReturnValue()
        {
            return blockStack.back()->returnValue;
        }

        void pushBlock(BasicBlockPtr block)
        {
            CodeGenBlockPtr newBlock = new CodeGenBlock();
            newBlock->block = block;
            blockStack.push_back(newBlock);
        }

        void popBlock()
        {
            if(blockStack.back()==nullptr) std::cout<<"Stack is empty"<<std::endl;
            CodeGenBlockPtr delBlock = blockStack.back();
            blockStack.pop_back();
            if(delBlock==nullptr)
                std::cout << "Stack is empty" << std::endl;
            //delete delBlock;
        }

        void setSymbolTable(std::string name, ValuePtr alloca)
        {
            blockStack.back()->SymbolTable[name] = alloca;
        }
        void setSymbolType(std::string name, TypePtr type)
        {
            blockStack.back()->SymbolType[name] = type;
        }
        ValuePtr getSymbolTable(std::string name)
        {
            std::vector<CodeGenBlockPtr>::reverse_iterator it;
            for (it = this->blockStack.rbegin(); it != this->blockStack.rend(); it++)
            {
                if ((*it)->SymbolTable.find(name) != (*it)->SymbolTable.end())
                {
                    return (*it)->SymbolTable[name];
                }
            }
            return nullptr;
        }
        TypePtr getSymbolType(std::string name){
            std::vector<CodeGenBlockPtr>::reverse_iterator it;
            for (it = this->blockStack.rbegin(); it != this->blockStack.rend(); it++)
            {
                if ((*it)->SymbolType.find(name) != (*it)->SymbolType.end())
                {
                    return (*it)->SymbolType[name];
                }
            }
            return nullptr;
        }
    };
}



#endif
