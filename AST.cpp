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

llvm::Value *getActualValue(ValuePtr value, CodeGenContext &context)
{
    if (llvm::isa<llvm::Constant>(value))
    {
        return value;
    }
    else if (value->getType()->getTypeID() == 15)
    {
        return context.theBuilder.CreateLoad(value);
    }
    else
    {
        return value;
    }
}

llvm::Type *getLLVMType(std::shared_ptr<IdentifierExpr> type, rmmc::CodeGenContext &context)
{
    assert(type->isType == true);
    std::string name = type->getName();
    std::cout << "getLLVMType: " << name << std::endl;
    if (true)
    {
        if (!name.compare("bool"))
        {
            return context.typeSystem.boolTy;
        }
        else if (!name.compare("int"))
        {
            std::cout << "intTy" << std::endl;
            return context.typeSystem.intTy;
        }
        else if (!name.compare("float"))
        {
            return context.typeSystem.floatTy;
        }
        else if (!name.compare("double"))
        {
            std::cout << "doubleTy" << std::endl;
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
            StructTypePtr structType = context.theModule->getTypeByName(name);
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
        if (!name.compare("bool"))
        {
            return llvm::Type::getInt1PtrTy(context.theContext);
        }
        else if (!name.compare("int"))
        {
            return llvm::Type::getInt32PtrTy(context.theContext);
        }
        else if (!name.compare("float"))
        {
            return llvm::Type::getFloatPtrTy(context.theContext);
        }
        else if (!name.compare("double"))
        {
            return llvm::Type::getDoublePtrTy(context.theContext);
        }
        else if (!name.compare("void"))
        {
            return llvm::Type::getInt64PtrTy(context.theContext);
        }
        else if (!name.compare("string"))
        {
            return llvm::Type::getInt8PtrTy(context.theContext);
        }
        else if (!name.compare("char"))
        {
            return llvm::Type::getInt8PtrTy(context.theContext);
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
/*
[2][4][3]
[ [ [ [],[] ], [ [],[] ] ]  , [ [ [],[] ], [ [],[] ] ] ]
[1][1][1]
((0+1)*4+1)*3+1=16
[1][2][1]
((0+1)*4+2)*3+1=19
*/
llvm::Value *rmmc::ArrayIndex::codeGen(CodeGenContext &context)
{
    this->print();
    TypePtr type = context.getSymbolType(this->arrayName->getName());
    ValuePtr array = context.getSymbolTable(this->arrayName->getName());
    std::vector<int> *arraySize = context.getSymbolSize(this->arrayName->getName());
    if (array == nullptr)
    {
        return LogErrorV("The array doesn't exist");
    }
    assert(this->index->size() == arraySize->size());
    ValuePtr con_0 = (new IntegerExpr(0))->codeGen(context);
    std::vector<ValuePtr> Idxs;
    Idxs.push_back(con_0);

    int i = 1;
    int idx = 0;
    ValuePtr val_idx = (new IntegerExpr(0))->codeGen(context);
    for (auto &perIdx : *this->index)
    {
        ValuePtr val = getActualValue(perIdx->codeGen(context), context);
        if (val->getType()->getTypeID() != llvm::Type::IntegerTyID)
        {
            return LogErrorV("The index is illegal");
        }
        val_idx = context.theBuilder.CreateAdd(val_idx, val, "indexAdd");
        val_idx = getActualValue(val_idx, context);

        if (i < arraySize->size())
        {
            val_idx = context.theBuilder.CreateMul(
                val_idx,
                (new IntegerExpr(arraySize->at(i)))->codeGen(context),
                "indexAdd");
            val_idx = getActualValue(val_idx, context);
            i++;
        }
        // llvm::ConstantInt* tmp = llvm::dyn_cast<ConstantInt>(
        //     val);
        // std::cout<<val->getType()->getTypeID()<<std::endl;
        // if (tmp == nullptr)
        // {
        //     return LogErrorV("The index is illegal");
        // }
        // idx = idx+tmp->getSExtValue();
        // std::cout<<"get ArrayIndex"<<tmp->getSExtValue()<<std::endl;
        // if (i < arraySize->size())
        // {
        //     idx=idx*arraySize->at(i);
        //     i++;
        // }
    }
    // Idxs.push_back( (new IntegerExpr(idx))->codeGen(context) );
    Idxs.push_back(val_idx);
    ValuePtr array_i = context.theBuilder.CreateGEP(type, array, llvm::ArrayRef(Idxs));
    if (array_i == nullptr)
    {
        return LogErrorV("The array index is illegal");
    }
    return array_i;
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
    // return llvm::ConstantDataArray::getString(context.theContext, llvm::StringRef(this->Value), true);
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
    ValuePtr exp_val = getActualValue(exp, context);
    assert(exp != nullptr);
    ValuePtr con_neg_1 = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context.theContext), -1);
    switch (Type)
    {
    case ADDRESS_OF:
        return exp;
    case Negative:
        return context.theBuilder.CreateFMul(exp, con_neg_1, "fmul");
    case LOGICAL_NOT:
        return context.theBuilder.CreateNot(exp, "not");
    default:
        return LogErrorV("Not support the single-operator");
    }
    return nullptr;
}

llvm::Value *StructMember(std::shared_ptr<Expression> LHS, std::shared_ptr<Expression> RHS, CodeGenContext &context)
{
    ValuePtr lhs = LHS->codeGen(context);
    auto structPtr = context.theBuilder.CreateLoad(lhs, "structPtr");
    // structPtr->setAlignment(4);
    RHS->print();
    IdentifierExpr *RHS_tmp = dynamic_cast<IdentifierExpr *>(RHS.get());
    assert(RHS_tmp != nullptr);
    assert(structPtr->getType()->isStructTy());

    std::vector<ValuePtr> idxList;
    std::string structName = structPtr->getType()->getStructName().str();
    int memberIdx = context.getStructMemberId(structName, RHS_tmp->getName());
    idxList.push_back(ConstantInt::get(context.typeSystem.intTy, 0, false));
    idxList.push_back(ConstantInt::get(context.typeSystem.intTy, (uint64_t)memberIdx, false));

    return context.theBuilder.CreateInBoundsGEP(lhs, idxList, "StructMemberPtr");
}

llvm::Value *rmmc::BinaryOperatorExpr::codeGen(CodeGenContext &context)
{
    this->print();
    if (this->Type == BinaryOperator::STRUCT_REF)
    {
        return StructMember(this->LHS, this->RHS, context);
    }
    ValuePtr lhs = this->LHS->codeGen(context);
    ValuePtr rhs = this->RHS->codeGen(context);
    assert(lhs != nullptr);
    assert(rhs != nullptr);

    lhs = getActualValue(lhs, context);
    rhs = getActualValue(rhs, context);

    bool allInt = ((lhs->getType()->getTypeID() == llvm::Type::IntegerTyID) && (rhs->getType()->getTypeID() == llvm::Type::IntegerTyID));

    std::cout << "allInt== " << allInt << std::endl;

    if (allInt == true)
    {
        // std::cout << lhs->getType()->getTypeID() << " " << rhs->getType()->getTypeID() << std::endl;
        // std::cout << lhs->getType() << " " << rhs->getType() << std::endl;
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
        std::cout << lhs->getType()->getTypeID() << " " << rhs->getType()->getTypeID() << std::endl;
        lhs = context.typeSystem.cast(lhs, context.typeSystem.doubleTy, context.currentBlock(), context);
        rhs = context.typeSystem.cast(rhs, context.typeSystem.doubleTy, context.currentBlock(), context);
        std::cout << lhs->getType()->getTypeID() << " " << rhs->getType()->getTypeID() << std::endl;
        if (lhs == nullptr || rhs == nullptr)
        {
            return LogErrorV("The LHS or RHS has illegal type in BinaryOperatorStatement");
        }
        std::cout << lhs->getType()->getTypeID() << " " << rhs->getType()->getTypeID() << std::endl;
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
            if (this->FunctionName->getName().compare("scanf"))
            {
                tmp = getActualValue(tmp, context);
            }
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
    ValuePtr l = nullptr;
    ValuePtr l_val = nullptr;
    TypePtr lType = nullptr;
    l = this->LHS->codeGen(context);
    if (l == nullptr)
    {
        return LogErrorV("Assignment LHS is nullptr");
    }
    l_val = context.theBuilder.CreateLoad(l);
    lType = l_val->getType();

    ValuePtr r = this->RHS->codeGen(context);

    std::cout << l->getType()->getTypeID() << " " << r->getType()->getTypeID() << std::endl;
    r = context.typeSystem.cast(r, lType, context.currentBlock(), context);

    if (r == nullptr)
    {
        std::cout << l->getType() << " " << r->getType() << std::endl;
        return LogErrorV("l  and r type different");
    }
    // ValuePtr r_val = context.theBuilder.CreateLoad(r);
    // std::cout<< l->getValueName() <<std::endl;
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
        std::cout << "process args....." << std::endl;
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
    std::cout << retType->getTypeID() << std::endl;
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
        context.setSymbolType((*it)->getName().getName(), perArg.getType());
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
    assert(this->VariableName != nullptr && this->VariableType != nullptr);
    assert(this->VariableType->isType == true);
    if (this->VariableType->isArray)
    {
        std::vector<int> *symbolSize = new std::vector<int>();
        uint64_t arraySize = 1;
        int64_t perSize;
        for (auto it = this->VariableType->arraySize->begin(); it != this->VariableType->arraySize->end(); it++)
        {
            llvm::ConstantInt *tmp = llvm::dyn_cast<ConstantInt>((*it)->codeGen(context));
            if (tmp == nullptr)
            {
                return LogErrorV("The arraySize is illegal");
            }
            perSize = tmp->getSExtValue();
            arraySize *= perSize;
            std::cout << perSize << std::endl;
            symbolSize->push_back(perSize);
        }
        std::cout << "ArraySize=" << arraySize << std::endl;
        //    TypePtr type = getLLVMType(this->VariableType, context);
        ArrayTypePtr type = llvm::ArrayType::get(getLLVMType(this->VariableType, context), arraySize);
        std::cout << "ArrayType Finished" << std::endl;
        ValuePtr alloca = context.theBuilder.CreateAlloca(type);
        std::cout << "Array Alloca Finished" << std::endl;
        context.setSymbolTable(this->VariableName->getName(), alloca);
        context.setSymbolType(this->VariableName->getName(), type);
        context.setSymbolSize(this->VariableName->getName(), symbolSize);
        if (this->hasAssignmentExpr() == true)
        {
            if (arraySize != this->assignmentExpr->size())
            {
                return LogErrorV("The array assignemnt size is different");
            }
            std::vector<ValuePtr> idxList;
            int idx = 0;
            idxList.push_back((new IntegerExpr(0))->codeGen(context));
            for (auto &it : *this->assignmentExpr)
            {
                ValuePtr r = it->codeGen(context);
                ValuePtr r_val = getActualValue(r, context);
                idxList.push_back((new IntegerExpr(idx))->codeGen(context));
                context.theBuilder.CreateStore(
                    r_val,
                    context.theBuilder.CreateGEP(type, alloca, llvm::ArrayRef(idxList)));
                idxList.pop_back();
                idx++;
            }
            std::cout << "Array Declaration Finished" << std::endl;
        }

        return alloca;
    }
    else
    {
        TypePtr type = getLLVMType(this->VariableType, context);
        std::cout << "Variable Declaration Finished" << std::endl;
        std::cout << type->getTypeID() << std::endl;
        ValuePtr alloca = context.theBuilder.CreateAlloca(type);
        std::cout << "Variable Declaration Finished" << std::endl;
        context.setSymbolTable(this->VariableName->getName(), alloca);
        context.setSymbolType(this->VariableName->getName(), type);
        if (this->hasAssignmentExpr() == true)
        {
            std::make_shared<AssignmentExpression>(this->VariableName, this->assignmentExpr->at(0))->codeGen(context);
        }
        std::cout << "Variable Declaration Finished" << std::endl;
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
    this->print();
    StructTypePtr structType = context.theModule->getTypeByName(this->Name->getName());
    if (structType)
    {
        return LogErrorV("The struct already exists");
    }
    structType = llvm::StructType::create(context.theContext, this->Name->getName());

    context.addStruct(this->Name->getName());
    std::vector<TypePtr> memberType;
    int memeberIdx = 0;
    for (auto &perMember : *this->Members)
    {
        // perMember->codeGen(context);
        // std::cout<<"x finished"<<std::endl;
        memberType.push_back(getLLVMType(perMember->VariableType, context));
        context.addStructMember(this->Name->getName(), perMember->VariableName->getName(), memeberIdx);
        memeberIdx++;
        // std::cout << "x finished" << std::endl;
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
    context.theBuilder.CreateRet(getActualValue(returnVal, context));
    //    context.setCurrentReturnValue(returnVal);
    return returnVal;
}

llvm::Value *rmmc::TypedefStatement::codeGen(CodeGenContext &context)
{
    return nullptr;
}

llvm::Value *CastToBool(ValuePtr val, CodeGenContext &context)
{
    TypePtr from = val->getType();
    TypePtr type = context.typeSystem.doubleTy;
    if (from != type)
    {
        std::cout << "[TYPE CAST] : " << from->getTypeID() << " " << type->getTypeID() << std::endl;
        if (context.typeSystem._castTable.find(from) == context.typeSystem._castTable.end())
        {
            return LogErrorV("No Cast");
        }
        else if (context.typeSystem._castTable[from].find(type) == context.typeSystem._castTable[from].end())
        {
            return LogErrorV("No Cast");
        }
        else
        {
            val = context.theBuilder.CreateCast(context.typeSystem._castTable[from][type], val, type, "cast");
        }
    }
    val = context.theBuilder.CreateFCmpONE(
        val, ConstantFP::get(context.theContext, APFloat(0.0)), "cond");
    return val;
}

llvm::Value *rmmc::IfStatement::codeGen(CodeGenContext &context)
{
    ValuePtr condValue = this->Condition->codeGen(context);
    if (condValue == nullptr)
    {
        return LogErrorV("The condition of IfStatement is illegal!");
    }

    FunctionPtr theFunction = context.theBuilder.GetInsertBlock()->getParent();

    condValue = getActualValue(condValue, context);
    condValue = CastToBool(condValue, context);

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
    this->print();
    FunctionPtr theFunction = context.theBuilder.GetInsertBlock()->getParent();
    BasicBlockPtr LoopBB = llvm::BasicBlock::Create(context.theContext, "loop", theFunction);
    BasicBlockPtr LoopAfterBB = llvm::BasicBlock::Create(context.theContext, "loop_after");

    if (this->initial)
        this->initial->codeGen(context);
    // std::cout<<"Initial Finished"<<std::endl;
    if (this->condition == nullptr)
    {
        return LogErrorV("The forStatement doesn't have jump condition");
    }
    ValuePtr condValue = this->condition->codeGen(context);
    condValue = getActualValue(condValue, context);
    condValue = CastToBool(condValue, context);
    std::cout << "Condition Finished" << std::endl;
    if (condValue == nullptr)
    {
        return LogErrorV("The jump condition is illegal");
    }

    context.theBuilder.CreateCondBr(condValue, LoopBB, LoopAfterBB);

    context.theBuilder.SetInsertPoint(LoopBB);
    context.pushBlock(LoopBB);
    this->content->codeGen(context);
    context.popBlock();

    if (this->increment != nullptr)
    {
        this->increment->codeGen(context);
    }
    // context.theBuilder.SetInsertPoint(LoopBB);
    condValue = this->condition->codeGen(context);
    condValue = getActualValue(condValue, context);

    condValue = CastToBool(condValue, context);

    context.theBuilder.CreateCondBr(condValue, LoopBB, LoopAfterBB);

    theFunction->getBasicBlockList().push_back(LoopAfterBB);
    context.theBuilder.SetInsertPoint(LoopAfterBB);

    return nullptr;
}
// llvm::Value *rmmc::ForStatement::codeGen(CodeGenContext &context)
// {
//     this->print();
//     FunctionPtr theFunction = context.theBuilder.GetInsertBlock()->getParent();
//     BasicBlockPtr LoopEntryBB = llvm::BasicBlock::Create(context.theContext, "loop_entry", theFunction);
//     BasicBlockPtr LoopBB = llvm::BasicBlock::Create(context.theContext, "loop");
//     BasicBlockPtr LoopAfterBB = llvm::BasicBlock::Create(context.theContext, "loop_after");

//     context.theBuilder.CreateBr(LoopEntryBB);

//     context.pushBlock(LoopEntryBB);
//     context.theBuilder.SetInsertPoint(LoopEntryBB);
//     // LoopEntryBlock content
//     if (this->initial)
//         this->initial->codeGen(context);
//     // std::cout<<"Initial Finished"<<std::endl;
//     if (this->condition == nullptr)
//     {
//         return LogErrorV("The forStatement doesn't have jump condition");
//     }
//     ValuePtr condValue = this->condition->codeGen(context);
//     condValue = getActualValue(condValue, context);
//     // std::cout << "Finished"<<std::endl;
//     // condValue = getActualValue(condValue, context);
//     // std::cout << "Condition Start" << std::endl;
//     // std::cout << (llvm::ConstantFP::get(context.theContext, APFloat(0.0)) )->getType()<<std::endl;
//     std::cout << condValue->getType()->getTypeID() << std::endl;
//     condValue = context.typeSystem.cast(condValue, context.typeSystem.doubleTy, context.currentBlock());
//     condValue = context.theBuilder.CreateFCmpONE(
//         llvm::ConstantFP::get(context.theContext, APFloat(0.0)), condValue,"loop_cond");
//     std::cout << "Condition Finished" << std::endl;
//     if (condValue == nullptr)
//     {
//         return LogErrorV("The jump condition is illegal");
//     }
//     context.theBuilder.CreateCondBr(condValue, LoopBB, LoopAfterBB);

//     theFunction->getBasicBlockList().push_back(LoopBB);
//     context.theBuilder.SetInsertPoint(LoopBB);
//     context.pushBlock(LoopBB);
//     this->content->codeGen(context);
//     if (this->increment != nullptr)
//     {
//         this->increment->codeGen(context);
//     }
//     condValue = this->condition->codeGen(context);
//     condValue = getActualValue(condValue, context);
//     condValue = context.typeSystem.cast(condValue, context.typeSystem.doubleTy, context.currentBlock());
//     condValue = context.theBuilder.CreateFCmpONE(
//         condValue, ConstantFP::get(context.theContext, APFloat(0.0)), "loop_cond");
//     context.theBuilder.CreateCondBr(condValue, LoopBB, LoopAfterBB);
//     context.popBlock();

//     theFunction->getBasicBlockList().push_back(LoopAfterBB);
//     context.theBuilder.SetInsertPoint(LoopAfterBB);
//     // pop loop entry block
//     context.popBlock();

//     return nullptr;
// }

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
    context.popBlock();
    condValue = this->Condition->codeGen(context);
    condValue = context.theBuilder.CreateFCmpONE(
        condValue, ConstantFP::get(context.theContext, APFloat(0.0)), "loop_cond");
    context.theBuilder.CreateCondBr(condValue, LoopBB, LoopAfterBB);

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
