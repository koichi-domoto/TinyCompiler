//
// Created by Yuying on 2022/5/3.
//

#ifndef __AST_H__
#define __AST_H__

#include "llvm/IR/Value.h"
#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <cstring>

namespace rmmc
{

    class Statement;
    class Expression;
    class VariableDeclarationStatement;
    class FunctionDeclarationStatement;
    class CodeGenBlock;
    class CodeGenContext;

    typedef std::vector<std::shared_ptr<Statement>> StatementList;
    typedef std::vector<std::shared_ptr<Expression>> ExpressionList;
    typedef std::vector<std::shared_ptr<VariableDeclarationStatement>> VariableList;
    typedef std::vector<std::shared_ptr<FunctionDeclarationStatement>> FunctionList;

    class ASTNode
    {
        //    protected:
        //        location loc;

    public:
        virtual ~ASTNode() {}

        virtual void print() = 0;
        virtual std::string toJSON() = 0;
        virtual llvm::Value *codeGen(CodeGenContext &context) = 0;
    };

    class Statement : public ASTNode
    {
    public:
        virtual ~Statement() {}

        virtual void print() = 0;
        virtual std::string toJSON() = 0;
        virtual llvm::Value *codeGen(CodeGenContext &context) = 0;
    };

    class Expression : public ASTNode
    {
    public:
        virtual ~Expression() {}

        virtual void print() = 0;
        virtual std::string toJSON() = 0;
        virtual llvm::Value *codeGen(CodeGenContext &context) = 0;
    };

    /***
     * Constant Value : Double Integer UnsignedInteger Boolean
     *
     */
    class DoubleExpr : public Expression
    {
        double Value;

    public:
        DoubleExpr(double _value) : Value(_value)
        {
        }
        virtual ~DoubleExpr() {}

        virtual void print() override
        {
            std::cout << "Generate constant double = " << Value << std::endl;
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;

        double getValue() const
        {
            return this->Value;
        }
    };

    class IntegerExpr : public Expression
    {
        long long Value;

    public:
        IntegerExpr(long long _value) : Value(_value)
        {
        }
        virtual ~IntegerExpr() {}

        virtual void print() override
        {
            std::cout << "Generate constant integer = " << Value << std::endl;
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;

        long long getValue() const
        {
            return this->Value;
        }
    };

    // class UnsignedIntegerExpr : public Expression
    // {
    // public:
    //     unsigned long long Value;

    //     UnsignedIntegerExpr(unsigned long long _value, location _loc): Value(_value) {
    //         loc=_loc;
    //     }
    //     ~UnsignedIntegerExpr() {}

    //     virtual void print();
    //     virtual void toXML();
    //     virtual llvm::Value *codeGen();
    // };
    //<--------------To-Do------------------>
    class BooleanExpr : public Expression
    {
        bool Value;

    public:
        BooleanExpr(bool _value) : Value(_value)
        {
        }
        virtual ~BooleanExpr() {}

        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;

        bool getValue() const
        {
            return this->Value;
        }
    };

    class StringExpr : public Expression
    {
        std::string Value;

    public:
        StringExpr(std::string _value) : Value(_value)
        {
        }
        virtual ~StringExpr() {}

        virtual void print() override
        {
            std::cout << "Generate constant string = " << Value << std::endl;
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;

        std::string getValue() const
        {
            return this->Value;
        }
    };

    // class CharExpr : public Expression
    // {
    // public:
    //     char Value;

    //     CharExpr(char _value, location _loc) : Value(_value) {
    //         loc=_loc;
    //     }
    //     ~CharExpr() {}

    //     virtual void print();
    //     virtual void toXML();
    //     virtual llvm::Value *codeGen();
    // };

    class IdentifierExpr : public Expression
    {
    public:
        std::string Name;
        bool isType;
        bool isArray;
        //reverse a[3][2] {2,3}
        std::shared_ptr<ExpressionList> arraySize = std::make_shared<ExpressionList>();
        
        IdentifierExpr(std::string _name) : Name(_name)
        {
        }
        virtual ~IdentifierExpr() {}

        virtual void print() override
        {
            std::cout << "Generate identifier "
                      << Name << " "
                      << std::endl;
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;

        std::string getName() const
        {
            return this->Name;
        }
    };

    // class ArrayIndexExpr : public Expression
    // {
    // public:
    //     std::shared_ptr<IdentifierExpr> arrayName;
    //     std::shared_ptr<ExpressionList> index = std::make_shared<ExpressionList>();
    // };

    // class TypeExpr : public Expression
    // {
    // public:
    //     enum BASICTYPE
    //     {
    //         INT,
    //         FLOAT,
    //         DOUBLE,
    //         CHAR,
    //         BOOL,
    //         STRING,
    //         VOID,
    //         STRUCT
    //     };

    //     BASICTYPE type;
    //     std::shared_ptr<IdentifierExpr> structName;
    //     bool isArray = false;
    //     std::shared_ptr<ExpressionList> arraySize = std::make_shared<ExpressionList>();

    //     TypeExpr() = default;

    //     // primary type
    //     TypeExpr(BASICTYPE _type) : type(_type)
    //     {
    //     }
    //     // struct type
    //     TypeExpr(BASICTYPE _type, std::shared_ptr<IdentifierExpr> _structName) : type(_type), structName(_structName)
    //     {
    //     }
    //     // array type
    //     TypeExpr(BASICTYPE _type, bool _isArray, std::shared_ptr<ExpressionList> _arraySize)
    //         : type(_type), isArray(_isArray), arraySize(_arraySize)
    //     {
    //     }

    //     virtual ~TypeExpr() {}
    //     virtual void print() override
    //     {
    //         std::cout << "Generate Type Expression "
    //                   << std::endl;
    //     }
    //     virtual std::string toJSON() override;
    //     virtual llvm::Value *codeGen(CodeGenContext &context) override;
    // };

    enum BinaryOperator
    {
        SCOPE,        //::
        ARRAY_INDEX,  //[]
        STRUCT_REF,   //.
        STRUCT_DEREF, //->
        AS,           // as
        ADD,
        SUB,
        MUL,
        DIV,
        MOD, //%
        LEFT_SHIFT,
        RIGHT_SHIFT,
        LT,          //<
        ELT,         //<=
        GT,          //>
        EGT,         //>=
        E,           //==
        NE,          //!=
        AND,         //&
        XOR,         //^
        OR,          //|
        LOGICAL_AND, //&&
        LOGICAL_OR,  //||
    };

    enum SingleOperator
    {
        Negative,//-
        LOGICAL_NOT, //
        BITWISE_NOT, //~
        INDIRECTION, //*
        ADDRESS_OF,  //&
        MOVE,        // move
    };

    enum ThreeOperator
    {
        CONDITION //? : ;
    };

    class SingleOperatorExpr : public Expression
    {
        SingleOperator Type;
        std::shared_ptr<Expression> Expr = nullptr;

    public:
        SingleOperatorExpr(std::shared_ptr<Expression> _Expr, SingleOperator _Type)
            : Type(_Type),
              Expr(std::move(_Expr))
        {
        }
        virtual ~SingleOperatorExpr() {}

        virtual void print() override
        {
            std::cout << "Generate single operator "
                      << Type
                      << std::endl;
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class BinaryOperatorExpr : public Expression
    {
        BinaryOperator Type;
        std::shared_ptr<Expression> LHS = nullptr;
        std::shared_ptr<Expression> RHS = nullptr;

    public:
        BinaryOperatorExpr(std::shared_ptr<Expression> _LHS, BinaryOperator _Type, std::shared_ptr<Expression> _RHS)
            : Type(_Type),
              LHS{std::move(_LHS)},
              RHS{std::move(_RHS)}
        {
        }
        virtual ~BinaryOperatorExpr() {}

        virtual void print() override
        {
            std::cout << "Generate binary operator "
                      << Type
                      << std::endl;
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class ThreeOperatorExpr : public Expression
    {
        ThreeOperator Type;
        std::shared_ptr<Expression> LHS = nullptr;
        std::shared_ptr<Expression> MHS = nullptr;
        std::shared_ptr<Expression> RHS = nullptr;

    public:
        ThreeOperatorExpr(std::shared_ptr<Expression> _LHS, std::shared_ptr<Expression> _MHS, std::shared_ptr<Expression> _RHS, ThreeOperator _Type)
            : Type(_Type),
              LHS{std::move(_LHS)},
              MHS{std::move(_MHS)},
              RHS{std::move(_RHS)}
        {
        }
        virtual ~ThreeOperatorExpr() {}

        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class FunctionCallExpr : public Expression
    {
    public:
        std::shared_ptr<IdentifierExpr> FunctionName = nullptr;
        std::shared_ptr<ExpressionList> Args = std::make_shared<ExpressionList>();

        FunctionCallExpr(std::shared_ptr<IdentifierExpr> _FunctionName)
            : FunctionName{std::move(_FunctionName)}
        {
        }
        FunctionCallExpr(std::shared_ptr<IdentifierExpr> _FunctionName, std::shared_ptr<ExpressionList> _Args)
            : FunctionName{std::move(_FunctionName)},
              Args{std::move(_Args)}
        {
        }
        virtual ~FunctionCallExpr() {}

        virtual void print() override
        {
            std::cout << "Generate functin call :"
                      << FunctionName->getName() << " "
                      << std::endl;
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class AssignmentExpression : public Expression
    {
    public:
        std::shared_ptr<Expression> LHS = nullptr;
        std::shared_ptr<Expression> RHS = nullptr;

        AssignmentExpression(std::shared_ptr<Expression> _LHS,
                             std::shared_ptr<Expression> _RHS)
            : LHS(_LHS),
              RHS(_RHS)
        {
        }
        virtual ~AssignmentExpression() {}

        virtual void print() override
        {
            std::cout << "Generate Assignment Statement" << std::endl;
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class ArrayIndex : public Expression
    {
    public:
        std::shared_ptr<IdentifierExpr> arrayName;
        std::shared_ptr<ExpressionList> index = std::make_shared<ExpressionList>();

        ArrayIndex() = default;
        ArrayIndex(std::shared_ptr<IdentifierExpr> _arrayName,
                   std::shared_ptr<Expression> _index)
        : arrayName(_arrayName)
        {
            index->push_back(_index);
        }
        virtual ~ArrayIndex() {}

        virtual void print() override
        {
            std::cout << "Generate Array Index" << std::endl;
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    /***
     * Statement
     *
     */

    class ExpressionStatement : public Statement
    {
    public:
        std::shared_ptr<Expression> expr;
        ExpressionStatement() = default;
        ExpressionStatement(std::shared_ptr<Expression> _expr)
            : expr(_expr)
        {
        }
        virtual ~ExpressionStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class VariableDeclarationStatement : public Statement
    {
    public:
        std::shared_ptr<IdentifierExpr> VariableType = nullptr;
        std::shared_ptr<IdentifierExpr> VariableName = nullptr;
        std::shared_ptr<ExpressionList> assignmentExpr = std::make_shared<ExpressionList>();

        VariableDeclarationStatement()=default;
        VariableDeclarationStatement(std::shared_ptr<IdentifierExpr> _VariableType,
                                     std::shared_ptr<IdentifierExpr> _VariableName
                                    )
            : VariableType(_VariableType),
              VariableName(_VariableName)
        {
        }
        VariableDeclarationStatement(std::shared_ptr<IdentifierExpr> _VariableType,
                                     std::shared_ptr<IdentifierExpr> _VariableName,
                                     std::shared_ptr<Expression> _expr)
            : VariableType(_VariableType),
              VariableName(_VariableName)
        {
            assignmentExpr->push_back(_expr);
        }
        VariableDeclarationStatement(std::shared_ptr<IdentifierExpr> _VariableType,
                                     std::shared_ptr<IdentifierExpr> _VariableName,
                                     std::shared_ptr<ExpressionList> _assignmentExpr)
        : VariableType(_VariableType),
          VariableName(_VariableName),
          assignmentExpr(_assignmentExpr)
        {
        }

        virtual ~VariableDeclarationStatement() {}

        bool isArrayDeclaration()
        {
            return VariableType->isType;
        }
        bool hasAssignmentExpr(){
            return assignmentExpr->size()==0 ? false : true ;
        }

        std::shared_ptr<IdentifierExpr> getType(){
            return VariableType;
        }
        IdentifierExpr getName(){
            return (*VariableName);
        }

        virtual void print() override{

        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    // class SingleVariableDeclarationStatement : public VariableDeclarationStatement
    // {
    //     std::shared_ptr<IdentifierExpr> VariableType = nullptr;
    //     std::shared_ptr<IdentifierExpr> VariableName = nullptr;

    // public:
    //     SingleVariableDeclarationStatement(std::shared_ptr<IdentifierExpr> _VariableType,
    //                                        std::shared_ptr<IdentifierExpr> _VariableName)
    //         : VariableType{std::move(_VariableType)},
    //           VariableName{std::move(_VariableName)}
    //     {
    //     }
    //     virtual ~SingleVariableDeclarationStatement() {}

    //     virtual std::shared_ptr<IdentifierExpr> getType() override
    //     {
    //         return VariableType;
    //     }
    //     virtual IdentifierExpr getName() override
    //     {
    //         return (*VariableName);
    //     }

    //     virtual void print() override
    //     {
    //         std::cout << "Generating single varible declaration: "
    //                   << this->VariableType->getName() << " "
    //                   << this->VariableName->getName() << std::endl;
    //     }
    //     virtual std::string toJSON() override;
    //     virtual llvm::Value *codeGen(CodeGenContext &context) override;
    // };

    // class ArrayDeclarationStatement : public VariableDeclarationStatement
    // {
    //     std::shared_ptr<IdentifierExpr> ArrayType = nullptr;
    //     std::shared_ptr<IdentifierExpr> ArrayName = nullptr;
    //     std::shared_ptr<IntegerExpr> ArraySize = nullptr;

    //     ArrayDeclarationStatement(std::shared_ptr<IdentifierExpr> _ArrayType,
    //                               std::shared_ptr<IdentifierExpr> _ArrayName,
    //                               std::shared_ptr<IntegerExpr> _ArraySize)
    //         : ArrayType{std::move(_ArrayType)},
    //           ArrayName{std::move(_ArrayName)},
    //           ArraySize{std::move(_ArraySize)}
    //     {
    //     }
    //     virtual ~ArrayDeclarationStatement() {}

    //     virtual std::shared_ptr<IdentifierExpr> getType() override
    //     {
    //         return ArrayType;
    //     }
    //     virtual IdentifierExpr getName() override
    //     {
    //         return (*ArrayName);
    //     }

    //     virtual void print() override
    //     {
    //         std::cout << "Generating array varible declaration: "
    //                   << this->ArrayType->getName() << " "
    //                   << this->ArrayName->getName() << " "
    //                   << this->ArraySize->getValue()
    //                   << std::endl;
    //     }
    //     virtual std::string toJSON() override;
    //     virtual llvm::Value *codeGen(CodeGenContext &context) override;
    // };

    class StructDeclarationStatement : public Statement
    {
    public:
        std::shared_ptr<IdentifierExpr> Name = nullptr;
        std::shared_ptr<VariableList> Members = std::make_shared<VariableList>();
        //std::shared_ptr<FunctionList> FuncMembers = std::make_shared<FunctionList>();

        StructDeclarationStatement(std::shared_ptr<IdentifierExpr> _Name,
                                   std::shared_ptr<VariableList> _Members
                                   )
            : Name{std::move(_Name)},
              Members{std::move(_Members)}
        {
        }
        virtual ~StructDeclarationStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class BlockStatement : public Statement
    {
    public:
        std::shared_ptr<StatementList> Content = std::make_shared<StatementList>();
        BlockStatement() = default;
        BlockStatement(std::shared_ptr<StatementList> _Content)
            : Content(std::move(_Content)) {}
        virtual ~BlockStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class ReturnStatement : public Statement
    {
    public:
        std::shared_ptr<Expression> ReturnValue = nullptr;
        ReturnStatement()=default;
        ReturnStatement(std::shared_ptr<Expression> _ReturnValue)
            : ReturnValue(std::move(_ReturnValue))
        {
        }
        virtual ~ReturnStatement() {}

        virtual void print() override
        {
            std::cout << "Generate Return"
                      << std::endl;
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class FunctionDeclarationStatement : public Statement
    {
        std::shared_ptr<IdentifierExpr> ReturnType = nullptr;
        std::shared_ptr<IdentifierExpr> FunctionName = nullptr;
        std::shared_ptr<VariableList> Args = std::make_shared<VariableList>();
        std::shared_ptr<BlockStatement> Content = nullptr;
        //std::shared_ptr<ReturnStatement> Return = nullptr;
        bool isExternal = false;

    public:
        FunctionDeclarationStatement(std::shared_ptr<IdentifierExpr> _ReturnType,
                                     std::shared_ptr<IdentifierExpr> _FunctionName,
                                     std::shared_ptr<VariableList> _Args,
                                     std::shared_ptr<BlockStatement> _Content,
                                     //std::shared_ptr<ReturnStatement> _Return,
                                     bool _isExternal = false)
            : ReturnType{std::move(_ReturnType)},
              FunctionName{std::move(_FunctionName)},
              Args{std::move(_Args)},
              Content{std::move(_Content)}
        {
            isExternal = _isExternal;
        }

        virtual void print() override
        {
            std::cout << "Function Decalration :"
                      << ReturnType->getName() << "  "
                      << FunctionName->getName() << "  ";
            for (auto &perArg : *Args)
            {
                perArg->print();
            }
            std::cout << std::endl;
            std::cout << "Function Decalration Finished" << std::endl;
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class TypedefStatement : public Statement
    {
        std::shared_ptr<IdentifierExpr> LHS = nullptr;
        std::shared_ptr<IdentifierExpr> RHS = nullptr;

    public:
        TypedefStatement(std::shared_ptr<IdentifierExpr> LHS, std::shared_ptr<IdentifierExpr> RHS)
            : LHS{std::move(LHS)},
              RHS{std::move(RHS)}
        {
        }
        virtual ~TypedefStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class IfStatement : public Statement
    {
        std::shared_ptr<Expression> Condition = nullptr;
        std::shared_ptr<BlockStatement> TrueBlock = nullptr;
        std::shared_ptr<BlockStatement> FalseBlock = nullptr;

    public:
        IfStatement(std::shared_ptr<Expression> _Condition,
                    std::shared_ptr<BlockStatement> _TrueBlock
                    )
            : Condition{std::move(_Condition)},
              TrueBlock{std::move(_TrueBlock)}
        {
        }
        IfStatement(std::shared_ptr<Expression> _Condition,
                    std::shared_ptr<BlockStatement> _TrueBlock,
                    std::shared_ptr<BlockStatement> _FalseBlock)
            : Condition(_Condition),
              TrueBlock(_TrueBlock),
              FalseBlock(_FalseBlock)
        {
        }
        virtual ~IfStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class WhileStatement : public Statement
    {
        std::shared_ptr<Expression> Condition = nullptr;
        std::shared_ptr<BlockStatement> Block = nullptr;

    public:
        WhileStatement(std::shared_ptr<Expression> _Condition,
                       std::shared_ptr<BlockStatement> _Block)
            : Condition(_Condition),
              Block(_Block)
        {
        }
        virtual ~WhileStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class ForStatement : public Statement
    {
    public:
        std::shared_ptr<Statement> initial = nullptr;
        std::shared_ptr<Expression> condition = nullptr;
        std::shared_ptr<Expression> increment = nullptr;
        std::shared_ptr<BlockStatement> content = nullptr;

        ForStatement()=default;
        ForStatement(
            std::shared_ptr<Statement> _initial,
            std::shared_ptr<Expression> _condition,
            std::shared_ptr<Expression> _increment,
            std::shared_ptr<BlockStatement> _content)
            : initial(_initial),
              condition(_condition),
              increment(_increment),
              content(_content)
        {

        }
        virtual ~ForStatement(){}
        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    }; 

    class BreakStatement : public Statement
    {
    public:
        BreakStatement()
        {
        }
        virtual ~BreakStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class ContinueStatement : public Statement
    {
    public:
        ContinueStatement()
        {
        }
        virtual ~ContinueStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class NameSpaceStatement : public Statement
    {
        std::shared_ptr<IdentifierExpr> Name = nullptr;
        std::shared_ptr<StatementList> Block = std::make_shared<StatementList>();

    public:
        NameSpaceStatement(std::shared_ptr<IdentifierExpr> Name,
                           std::shared_ptr<StatementList> Block)
            : Name{std::move(Name)},
              Block{std::move(Block)}
        {
        }
        ~NameSpaceStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class UseStatement : public Statement
    {
        std::shared_ptr<IdentifierExpr> Name = nullptr;

    public:
        UseStatement(std::shared_ptr<IdentifierExpr> Name)
            : Name{std::move(Name)}
        {
        }
        ~UseStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class ImportStatement : public Statement
    {
        std::shared_ptr<Expression> Name = nullptr;

    public:
        ImportStatement(std::shared_ptr<Expression> Name)
            : Name{std::move(Name)}
        {
        }
        ~ImportStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class FromStatement : public Statement
    {
        std::shared_ptr<Expression> FromName = nullptr;
        std::shared_ptr<Expression> ImportName = nullptr;

    public:
        FromStatement(std::shared_ptr<Expression> FromName,
                      std::shared_ptr<Expression> ImportName)
            : FromName{std::move(FromName)},
              ImportName{std::move(ImportName)}
        {
        }
        ~FromStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };

    class ExportStatement : public Statement
    {
        std::shared_ptr<Expression> Name = nullptr;

    public:
        ExportStatement(std::shared_ptr<Expression> Name)
            : Name{std::move(Name)}
        {
        }
        ~ExportStatement() {}

        virtual void print() override
        {
        }
        virtual std::string toJSON() override;
        virtual llvm::Value *codeGen(CodeGenContext &context) override;
    };
}

#endif
