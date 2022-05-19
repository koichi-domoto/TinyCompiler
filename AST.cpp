#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/raw_ostream.h>
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include <vector>
#include <cstdlib>

#include "CodeGen.h"

typedef llvm::Type *TypePtr;
typedef llvm::ArrayType *ArrayTypePtr;
typedef llvm::FunctionType *FunctionTypePtr;
typedef llvm::Function *FunctionPtr;
typedef llvm::Value *ValuePtr;
typedef llvm::StructType *StructTypePtr;

    using namespace llvm;
using namespace rmmc;

// class Error
// {
//     std::string Str="Error:";
// public:
//     Error()=default;
//     Error(std::string _Str):Str(_Str)
//     {
//     }
//     ~Error(){}

//     void ErrorPrint() const{
//         std::cout<<Str<<std::endl;
//     }
// };

void LogError(std::string Str)
{
    std::cout<<Str<<std::endl;
    return;
}

llvm::Value *LogErrorV(std::string Str)
{
    LogError(Str);
    return nullptr;
}

llvm::Type *getLLVMType(std::shared_ptr<IdentifierExpr> type, rmmc::CodeGenContext &context)
{
    // std::string name = type->getName();
    // std::cout << "getLLVMType: " << name << std::endl;
    // // std::cout<<name.compare("int")<<std::endl;
    // if (!name.compare("int"))
    //     return llvm::Type::getInt32Ty(context.theContext);
    // if (!name.compare("string"))
    //     return llvm::Type::getInt8PtrTy(context.theContext);
    // std::cout << "Return nullptr" << std::endl;
    return nullptr;
}

llvm::Value *rmmc::ExpressionStatement::codeGen(CodeGenContext &context)
{
    if(this->expr==nullptr){
        return LogErrorV("The ExpressionStatement doesn't have expr");
    }
    return this->expr->codeGen(context);
}

llvm::Value *rmmc::ArrayIndex::codeGen(CodeGenContext &context)
{
    this->print();
    ValuePtr array = context.getSymbolTable(this->arrayName->getName());
    if(array==nullptr){
        return LogErrorV("The array doesn't exist");
    }
    ValuePtr con_0 = std::make_shared<rmmc::IntegerExpr>(0)->codeGen(context);
    std::vector<ValuePtr> Idxs;
    Idxs.push_back(con_0);
    for(auto& perIdx : *this->index){
        Idxs.push_back( perIdx->codeGen(context) );
    }
    ValuePtr array_i = context.theBuilder.CreateInBoundsGEP(array, llvm::ArrayRef(Idxs));
    if(array_i==nullptr){
        return LogErrorV("The array index is illegal");
    }
    return context.theBuilder.CreateLoad(array_i);
}

llvm::Value *rmmc::DoubleExpr::codeGen(CodeGenContext &context)
{
    this->print();
    return llvm::ConstantFP::get(llvm::Type::getDoubleTy(context.theContext), this->Value);
}

llvm::Value *rmmc::IntegerExpr::codeGen(CodeGenContext &context)
{
    this->print();
    return llvm::ConstantInt::get(llvm::Type::getInt64Ty(context.theContext), this->Value);
}

llvm::Value *rmmc::BooleanExpr::codeGen(CodeGenContext &context)
{
    this->print();
    return llvm::ConstantInt::get(llvm::Type::getInt1Ty(context.theContext), this->Value);
}

llvm::Value *rmmc::StringExpr::codeGen(CodeGenContext &context)
{
    // return context.theBuilder.CreateGlobalString(this->Value, "string");
    return llvm::ConstantDataArray::getString(context.theContext, llvm::StringRef(this->Value), true);
}

llvm::Value *rmmc::IdentifierExpr::codeGen(CodeGenContext &context)
{
    this->print();
    if (this->isType == false)
    {
        ValuePtr val = context.getSymbolTable(this->getName());
        if (val == nullptr)
        {
            return LogErrorV("The identifier " + this->getName() + " not find");
        }
        return context.theBuilder.CreateLoad(val);
    }
    else
    {
        return LogErrorV("A type-IdentifierExpr can't return ValuePtr");
    }
}


llvm::Value *rmmc::SingleOperatorExpr::codeGen(CodeGenContext &context)
{
    this->print();
    ValuePtr exp = this->Expr->codeGen(context);
    assert(exp!=nullptr);
    switch (Type)
    {
    case rmmc::SingleOperator::Negative:
        ValuePtr con_neg_1 = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context.theContext), -1);
        return context.theBuilder.CreateFMul(exp, con_neg_1, "fmul");
    case rmmc::SingleOperator::LOGICAL_NOT:
        return context.theBuilder.CreateNot(exp, "not");
    default:
        return LogErrorV("Not support the single-operator");
    }
    return nullptr;
}

llvm::Value *rmmc::BinaryOperatorExpr::codeGen(CodeGenContext &context)
{
    this->print();
    ValuePtr lhs = this->LHS->codeGen(context);
    ValuePtr rhs = this->RHS->codeGen(context);
    assert(lhs!=nullptr);
    assert(rhs!=nullptr);
    TypePtr lType = lhs->getType();
    TypePtr rType = rhs->getType();

    bool allInt =( (lhs->getType()->getTypeID() == llvm::Type::IntegerTyID) && (rhs->getType()->getTypeID() == llvm::Type::IntegerTyID) );

    if(allInt==true){
        switch (this->Type)
        {
        case ADD:
            return context.theBuilder.CreateAdd(lhs, rhs, "addf");
        case SUB:
            return context.theBuilder.CreateSub(lhs, rhs, "subf");
        case MUL:
            return context.theBuilder.CreateMul(lhs, rhs, "mulf");
        case DIV:
            return context.theBuilder.CreateFDiv(lhs, rhs, "divf");
        case LT:
            return context.theBuilder.CreateICmpSLT(lhs, rhs, "LTf");
        case ELT:
            return context.theBuilder.CreateICmpSLE(lhs, rhs, "LEf");
        case GT:
            return context.theBuilder.CreateICmpSGT(lhs, rhs, "GTf");
        case EGT:
            return context.theBuilder.CreateICmpSGE(lhs, rhs, "GEf");
        case E:
            return context.theBuilder.CreateICmpEQ(lhs, rhs, "EQf");
        case NE:
            return context.theBuilder.CreateICmpNE(lhs, rhs, "NEf");
        case AND:
            return context.theBuilder.CreateAnd(lhs, rhs, "and");
        case XOR:
            return context.theBuilder.CreateXor(lhs, rhs, "xor");
        case OR:
            return context.theBuilder.CreateOr(lhs, rhs, "or");
        default:
            return LogErrorV("Not support the binary operator");
        }
    }else{
        ValuePtr lhs_double = context.typeSystem.cast(lhs, context.typeSystem.doubleTy, context.currentBlock());
        ValuePtr rhs_double = context.typeSystem.cast(lhs, context.typeSystem.doubleTy, context.currentBlock());
        if( lhs_double==nullptr || rhs_double==nullptr ){
            return LogErrorV("The LHS or RHS has illegal type in BinaryOperatorStatement");
        }
        switch (this->Type)
        {
        case ADD:
            return context.theBuilder.CreateFAdd(lhs, rhs, "addf");
        case SUB:
            return context.theBuilder.CreateFSub(lhs, rhs, "subf");
        case MUL:
            return context.theBuilder.CreateFMul(lhs, rhs, "mulf");
        case DIV:
            return context.theBuilder.CreateFDiv(lhs, rhs, "divf");
        case LT:
            return context.theBuilder.CreateFCmpOLT(lhs, rhs, "LTf");
        case ELT:
            return context.theBuilder.CreateFCmpOLE(lhs, rhs, "LEf");
        case GT:
            return context.theBuilder.CreateFCmpOGT(lhs, rhs, "GTf");
        case EGT:
            return context.theBuilder.CreateFCmpOGE(lhs, rhs, "GEf");
        case E:
            return context.theBuilder.CreateFCmpOEQ(lhs, rhs, "EQf");
        case NE:
            return context.theBuilder.CreateFCmpONE(lhs, rhs, "NEf");
        default:
            return LogErrorV("Not support the binary operator");
        }
    }
    return nullptr;
}
//to-do-1
llvm::Value *rmmc::ThreeOperatorExpr::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::FunctionCallExpr::codeGen(CodeGenContext &context)
{
    this->print();
    FunctionPtr callF = context.theModule->getFunction(this->FunctionName->getName());
    if (callF == nullptr)
    {
        return LogErrorV("Not find the function : " + this->FunctionName->getName());
    }
    else if (callF->arg_size() != this->Args->size())
    {
        std::string error = "Function Args size different : ";
        error += std::to_string( callF->arg_size() );
        error += "  ";
        error += std::to_string( this->Args->size() );
        return LogErrorV(error);
    }
    else
    {
        ExpressionList::iterator it;
        std::vector<ValuePtr> callArgs;
        for (it = this->Args->begin(); it != this->Args->end(); it++)
        {
            ValuePtr tmp = (*it)->codeGen(context);
            if (tmp == nullptr)
            {
                return LogErrorV("The function params is nullptr");
            }
            callArgs.push_back(tmp);
        }
        return context.theBuilder.CreateCall(callF, callArgs, "callF");
    }
}

llvm::Value *rmmc::AssignmentExpression::codeGen(CodeGenContext &context)
{
    this->print();
    ValuePtr l = this->LHS->codeGen(context);
    if (l == nullptr)
    {
        return LogErrorV("Assignment LHS is nullptr");
    }
    TypePtr lType = l->getType();
    
    ValuePtr r = this->RHS->codeGen(context);
    r = context.typeSystem.cast(r, lType, context.currentBlock());
    if (r == nullptr)
    {
        std::cout << l->getType() << " " << r->getType() << std::endl;
        return LogErrorV("l  and r type different");
    }
    context.theBuilder.CreateStore(r, l);
    return l;
}

llvm::Value *rmmc::FunctionDeclarationStatement::codeGen(CodeGenContext &context)
{
    this->print();
    // Construct function params type
    std::vector<TypePtr> funcArgs;
    VariableList::iterator it;
    for (auto &perArg : *Args)
    {
        funcArgs.push_back(getLLVMType(perArg->getType(), context));
    }
    std::cout << "Args finished" << std::endl;
    // Construct function return type
    TypePtr retType = getLLVMType(ReturnType, context);
    if (retType == nullptr){
        return LogErrorV("Return type is nullptr");
    }
    std::cout << "Return Type Finished" << std::endl;
    // get function type and construct function
    FunctionTypePtr funcType = llvm::FunctionType::get(retType, funcArgs, false);
    std::cout << "Func Type Finished" << std::endl;
    FunctionPtr func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, this->FunctionName->getName().c_str(), context.theModule.get());
    std::cout << "Func Finished" << std::endl;
    if (this->isExternal)
        return func;
    // entry block
    BasicBlockPtr entryBlock = llvm::BasicBlock::Create(context.theContext, "entry", func, nullptr);
    context.theBuilder.SetInsertPoint(entryBlock);
    context.pushBlock(entryBlock);
    // store the params
    it = this->Args->begin();
    for (auto &perArg : func->args())
    {
        perArg.setName((*it)->getName().getName());
        context.setSymbolTable((*it)->getName().getName(), &perArg);
        context.setSymbolType((*it)->getName().getName(), (*it)->getType());
        it++;
    }
    // Generate the code of function content
    this->Content->codeGen(context);
    // Return Value
    ValuePtr returnVal = context.getCurrentReturnValue();
    if (returnVal == nullptr){
        return LogErrorV("Return value is nullptr");
    }
    context.theBuilder.CreateRet(returnVal);
    std::cout << "Return Value Finished" << std::endl;
    // Pop Block
    context.popBlock();
    llvm::verifyFunction(*func);
    std::cout << "Function Finished" << std::endl;
    return func;
}

llvm::Value *rmmc::VariableDeclarationStatement::codeGen(CodeGenContext &context)
{
    this->print();
    assert(this->VariableType->isType==true);
    if(this->VariableType->isArray){
        uint64_t arraySize=1;
        for(auto it=this->VariableType->arraySize->begin();it!=this->VariableType->arraySize->end();it++)
        {
            IntegerExpr *perSize = dynamic_cast<IntegerExpr*>(it->get());
            arraySize *= perSize->getValue();
        }
        ArrayTypePtr type = llvm::ArrayType::get(getLLVMType(this->VariableType, context), arraySize);
        ValuePtr alloca = context.theBuilder.CreateAlloca(type);
        context.setSymbolTable(this->VariableName->getName(), alloca);
        context.setSymbolType(this->VariableName->getName(), this->VariableType);
        return alloca;
    }else{
        TypePtr type = getLLVMType(this->VariableType, context);
        ValuePtr alloca = context.theBuilder.CreateAlloca(type);
        context.setSymbolTable(this->VariableName->getName(), alloca);
        context.setSymbolType(this->VariableName->getName(), this->VariableType);
        return alloca;
    }
    return nullptr;
}
/***
 *
 *
 */
// llvm::Value *rmmc::SingleVariableDeclarationStatement::codeGen(CodeGenContext &context)
// {
//     this->print();
//     TypePtr type = getLLVMType(this->VariableType, context);
//     ValuePtr alloca = context.theBuilder.CreateAlloca(type);

//     context.setSymbolTable(this->VariableName->getName(), alloca);
//     context.setSymbolType(this->VariableName->getName(), this->VariableType);

//     return alloca;
// }

// llvm::Value *rmmc::ArrayDeclarationStatement::codeGen(CodeGenContext &context)
// {
//     this->print();
//     ArrayTypePtr type = llvm::ArrayType::get(getLLVMType(this->ArrayType, context), ArraySize->getValue());
//     ValuePtr alloca = context.theBuilder.CreateAlloca(type);

//     context.setSymbolTable(this->ArrayName->getName(), alloca);
//     context.setSymbolType(this->ArrayName->getName(), this->ArrayType);

//     return alloca;
// }

llvm::Value *rmmc::StructDeclarationStatement::codeGen(CodeGenContext &context)
{
    StructTypePtr structType = context.theModule->getTypeByName(this->Name->getName());
    if(structType){
        return LogErrorV("The struct already exists");
    }
    structType = llvm::StructType::create(context.theContext, this->Name->getName());
    std::vector<TypePtr> memberType;
    for(auto& perMember : *this->Members)
    {
        memberType.push_back( perMember->codeGen(context)->getType() );
    }
    structType->setBody( llvm::ArrayRef(memberType) );
    return nullptr;
}

llvm::Value *rmmc::BlockStatement::codeGen(CodeGenContext &context)
{
    StatementList::iterator it;
    for (it = this->Content->begin(); it != this->Content->end(); it++)
    {
        (*it)->codeGen(context);
    }
    return nullptr;
}

// llvm::Value *rmmc::TypeExpr::codeGen(CodeGenContext &context)
// {
//     return nullptr;
// }

llvm::Value *rmmc::ReturnStatement::codeGen(CodeGenContext &context)
{
    ValuePtr returnVal = this->ReturnValue->codeGen(context);
    if (returnVal == nullptr){
        return LogErrorV("return value nullptr");
    }
    context.setCurrentReturnValue(returnVal);
    return returnVal;
}

llvm::Value *rmmc::TypedefStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::IfStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}
llvm::Value *rmmc::ForStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::WhileStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::BreakStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::ContinueStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::NameSpaceStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::UseStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::ImportStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::FromStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::ExportStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}
