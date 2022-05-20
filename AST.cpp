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
    std::cout << Str << std::endl;
    return;
}

llvm::Value *LogErrorV(std::string Str)
{
    LogError(Str);
    return nullptr;
}

llvm::Type *LogErrorT(std::string Str)
{
    LogError(Str);
    return nullptr;
}

llvm::Type *getLLVMType(std::shared_ptr<IdentifierExpr> type, rmmc::CodeGenContext &context)
{
    assert(type->isType == true);
    std::string name = type->getName();
    std::cout << "getLLVMType: " << name << std::endl;
    if (type->isArray == false)
    {
        if (!name.compare("bool"))
        {
            return context.typeSystem.boolTy;
        }
        else if (!name.compare("int"))
        {
            std::cout<<"intTy"<<std::endl;
            return context.typeSystem.intTy;
        }
        else if (!name.compare("float"))
        {
            return context.typeSystem.floatTy;
        }
        else if (!name.compare("double"))
        {
            return context.typeSystem.doubleTy;
        }
        else if (!name.compare("void"))
        {
            return context.typeSystem.voidTy;
        }
        else if (!name.compare("string"))
        {
            return context.typeSystem.stringTy;
        }
        else if (!name.compare("char"))
        {
            return context.typeSystem.charTy;
        }
        else
        {
            StructTypePtr structType = context.theModule->getTypeByName("name");
            if (structType == nullptr)
            {
                return LogErrorT("The type is illegal");
            }
            else
            {
                return structType;
            }
        }
    }
    else
    {
        return nullptr;
    }
    return nullptr;
}

llvm::Value *rmmc::ExpressionStatement::codeGen(CodeGenContext &context)
{
    if (this->expr == nullptr)
    {
        return LogErrorV("The ExpressionStatement doesn't have expr");
    }
    return this->expr->codeGen(context);
}

llvm::Value *rmmc::ArrayIndex::codeGen(CodeGenContext &context)
{
    this->print();
    ValuePtr array = context.getSymbolTable(this->arrayName->getName());
    if (array == nullptr)
    {
        return LogErrorV("The array doesn't exist");
    }
    ValuePtr con_0 = std::make_shared<rmmc::IntegerExpr>(0)->codeGen(context);
    std::vector<ValuePtr> Idxs;
    Idxs.push_back(con_0);
    for (auto &perIdx : *this->index)
    {
        Idxs.push_back(perIdx->codeGen(context));
    }
    ValuePtr array_i = context.theBuilder.CreateInBoundsGEP(array, llvm::ArrayRef(Idxs));
    if (array_i == nullptr)
    {
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
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context.theContext), this->Value);
}

llvm::Value *rmmc::BooleanExpr::codeGen(CodeGenContext &context)
{
    this->print();
    return llvm::ConstantInt::get(llvm::Type::getInt1Ty(context.theContext), this->Value);
}

llvm::Value *rmmc::StringExpr::codeGen(CodeGenContext &context)
{
     return context.theBuilder.CreateGlobalString(this->Value, "string");
    //return llvm::ConstantDataArray::getString(context.theContext, llvm::StringRef(this->Value), true);
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
        return val;
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
    assert(exp != nullptr);
    ValuePtr con_neg_1 = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context.theContext), -1);
    switch (Type)
    {
    case Negative:
        return context.theBuilder.CreateFMul(exp, con_neg_1, "fmul");
    case LOGICAL_NOT:
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
    assert(lhs != nullptr);
    assert(rhs != nullptr);
    TypePtr lType = lhs->getType();
    TypePtr rType = rhs->getType();

    bool allInt = ((lhs->getType()->getTypeID() == llvm::Type::IntegerTyID) && (rhs->getType()->getTypeID() == llvm::Type::IntegerTyID));

    if (allInt == true)
    {
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
    }
    else
    {
        ValuePtr lhs_double = context.typeSystem.cast(lhs, context.typeSystem.doubleTy, context.currentBlock());
        ValuePtr rhs_double = context.typeSystem.cast(lhs, context.typeSystem.doubleTy, context.currentBlock());
        if (lhs_double == nullptr || rhs_double == nullptr)
        {
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
// to-do-1
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
    // else if (callF->arg_size() != this->Args->size())
    // {
    //     std::string error = "Function Args size different : ";
    //     error += std::to_string(callF->arg_size());
    //     error += "  ";
    //     error += std::to_string(this->Args->size());
    //     return LogErrorV(error);
    // }
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
    ValuePtr l_val = context.theBuilder.CreateLoad(l);
    TypePtr lType = l_val->getType();

    ValuePtr r = this->RHS->codeGen(context);
    
    std::cout << l->getType()->getTypeID() << " " << r->getType()->getTypeID() << std::endl;
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
        std::cout<<"process args....."<<std::endl;
        funcArgs.push_back(getLLVMType(perArg->getType(), context));
    }
    std::cout << "Args finished" << std::endl;
    // Construct function return type
    TypePtr retType = getLLVMType(ReturnType, context);
    if (retType == nullptr)
    {
        return LogErrorV("Return type is nullptr");
    }
    std::cout << "Return Type Finished" << std::endl;
    std::cout << retType->getTypeID() <<std::endl;
    // get function type and construct function
    FunctionTypePtr funcType = llvm::FunctionType::get(retType, llvm::ArrayRef(funcArgs), false);
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
    // ValuePtr returnVal = context.getCurrentReturnValue();
    // if (returnVal == nullptr){
    //     return LogErrorV("Return value is nullptr");
    // }
    // context.theBuilder.CreateRet(returnVal);
    // std::cout << "Return Value Finished" << std::endl;
    // Pop Block
    context.popBlock();
    llvm::verifyFunction(*func);
    std::cout << "Function Finished" << std::endl;
    return func;
}

llvm::Value *rmmc::VariableDeclarationStatement::codeGen(CodeGenContext &context)
{
    this->print();
    assert(this->VariableType->isType == true);
    if (this->VariableType->isArray)
    {
        uint64_t arraySize = 1;
        for (auto it = this->VariableType->arraySize->begin(); it != this->VariableType->arraySize->end(); it++)
        {
            IntegerExpr *perSize = dynamic_cast<IntegerExpr *>(it->get());
            arraySize *= perSize->getValue();
        }
        ArrayTypePtr type = llvm::ArrayType::get(getLLVMType(this->VariableType, context), arraySize);
        ValuePtr alloca = context.theBuilder.CreateAlloca(type);
        context.setSymbolTable(this->VariableName->getName(), alloca);
        context.setSymbolType(this->VariableName->getName(), this->VariableType);
        return alloca;
    }
    else
    {
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
    if (structType)
    {
        return LogErrorV("The struct already exists");
    }
    structType = llvm::StructType::create(context.theContext, this->Name->getName());
    std::vector<TypePtr> memberType;
    for (auto &perMember : *this->Members)
    {
        memberType.push_back(perMember->codeGen(context)->getType());
    }
    structType->setBody(llvm::ArrayRef(memberType));
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
    if (returnVal == nullptr)
    {
        return LogErrorV("return value nullptr");
    }
    context.theBuilder.CreateRet(returnVal);
    //    context.setCurrentReturnValue(returnVal);
    return returnVal;
}

llvm::Value *rmmc::TypedefStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *rmmc::IfStatement::codeGen(CodeGenContext &context)
{
    ValuePtr condValue = this->Condition->codeGen(context);
    if (condValue == nullptr)
    {
        return LogErrorV("The condition of IfStatement is illegal!");
    }

    FunctionPtr theFunction = context.theBuilder.GetInsertBlock()->getParent();

    condValue = context.theBuilder.CreateFCmpONE(
        condValue, ConstantFP::get(context.theContext, APFloat(0.0)), "ifcond");

    BasicBlockPtr ThenBB = llvm::BasicBlock::Create(context.theContext, "then", theFunction);
    BasicBlockPtr ElseBB = llvm::BasicBlock::Create(context.theContext, "else");
    BasicBlockPtr MergeBB = llvm::BasicBlock::Create(context.theContext, "ifcont");

    context.theBuilder.CreateCondBr(condValue, ThenBB, ElseBB);

    context.theBuilder.SetInsertPoint(ThenBB);
    context.pushBlock(ThenBB);
    if (this->TrueBlock != nullptr)
        this->TrueBlock->codeGen(context);
    context.popBlock();
    context.theBuilder.CreateBr(MergeBB);
    ThenBB = context.theBuilder.GetInsertBlock();

    theFunction->getBasicBlockList().push_back(ElseBB);

    context.theBuilder.SetInsertPoint(ElseBB);
    context.pushBlock(ElseBB);
    if (this->FalseBlock != nullptr)
        this->FalseBlock->codeGen(context);
    context.popBlock();
    context.theBuilder.CreateBr(MergeBB);
    ElseBB = context.theBuilder.GetInsertBlock();

    theFunction->getBasicBlockList().push_back(MergeBB);
    context.theBuilder.SetInsertPoint(MergeBB);

    return nullptr;
}
llvm::Value *rmmc::ForStatement::codeGen(CodeGenContext &context)
{
    FunctionPtr theFunction = context.theBuilder.GetInsertBlock()->getParent();
    BasicBlockPtr LoopEntryBB = llvm::BasicBlock::Create(context.theContext, "loop_entry", theFunction);
    BasicBlockPtr LoopBB = llvm::BasicBlock::Create(context.theContext, "loop");
    BasicBlockPtr LoopAfterBB = llvm::BasicBlock::Create(context.theContext, "loop_after");

    context.theBuilder.CreateBr(LoopEntryBB);

    context.pushBlock(LoopEntryBB);
    context.theBuilder.SetInsertPoint(LoopEntryBB);
    // LoopEntryBlock content
    if (this->initial)
        this->initial->codeGen(context);
    if (this->condition == nullptr)
    {
        return LogErrorV("The forStatement doesn't have jump condition");
    }
    ValuePtr condValue = this->condition->codeGen(context);
    condValue = context.theBuilder.CreateFCmpONE(
        condValue, ConstantFP::get(context.theContext, APFloat(0.0)), "loop_cond");
    if (condValue == nullptr)
    {
        return LogErrorV("The jump condition is illegal");
    }
    context.theBuilder.CreateCondBr(condValue, LoopBB, LoopAfterBB);

    theFunction->getBasicBlockList().push_back(LoopBB);
    context.theBuilder.SetInsertPoint(LoopBB);
    context.pushBlock(LoopBB);
    this->content->codeGen(context);
    if (this->increment != nullptr)
    {
        this->increment->codeGen(context);
    }
    condValue = this->condition->codeGen(context);
    condValue = context.theBuilder.CreateFCmpONE(
        condValue, ConstantFP::get(context.theContext, APFloat(0.0)), "loop_cond");
    context.theBuilder.CreateCondBr(condValue, LoopBB, LoopAfterBB);
    context.popBlock();

    theFunction->getBasicBlockList().push_back(LoopAfterBB);
    context.theBuilder.SetInsertPoint(LoopAfterBB);
    // pop loop entry block
    context.popBlock();

    return nullptr;
}

llvm::Value *rmmc::WhileStatement::codeGen(CodeGenContext &context)
{
    FunctionPtr theFunction = context.theBuilder.GetInsertBlock()->getParent();
    BasicBlockPtr LoopBB = llvm::BasicBlock::Create(context.theContext, "loop", theFunction);
    BasicBlockPtr LoopAfterBB = llvm::BasicBlock::Create(context.theContext, "loop_after");

    ValuePtr condValue = this->Condition->codeGen(context);
    condValue = context.theBuilder.CreateFCmpONE(
        condValue, ConstantFP::get(context.theContext, APFloat(0.0)), "loop_cond");
    if (condValue == nullptr)
    {
        return LogErrorV("The jump condition is illegal");
    }
    context.theBuilder.CreateCondBr(condValue, LoopBB, LoopAfterBB);

    context.theBuilder.SetInsertPoint(LoopBB);
    context.pushBlock(LoopBB);
    if (this->Block != nullptr)
    {
        this->Block->codeGen(context);
    }
    condValue = this->Condition->codeGen(context);
    condValue = context.theBuilder.CreateFCmpONE(
        condValue, ConstantFP::get(context.theContext, APFloat(0.0)), "loop_cond");
    context.theBuilder.CreateCondBr(condValue, LoopBB, LoopAfterBB);
    context.popBlock();

    theFunction->getBasicBlockList().push_back(LoopAfterBB);
    context.theBuilder.SetInsertPoint(LoopAfterBB);

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
