

# 序言

## 0.1 概述

本实验实现了一个类C的编译系统，该编译器包含了词法分析、语法分析、语义分析、中间代码、代码生成阶段。

## 0.2 开发环境

- 操作系统：目前编译器只支持RISC-V，推荐使用docker

- 编译环境：Bison >3.8;flex >2.6;llvm >10.0.0

- 测试环境：Google test

## 0.3 文件说明

### 0.3.1 文件结构

本实验提交的文件结构及说明如下：

TinyCompiler
├── AST.h 抽象语法树节点的定义
├── AST.cpp 
├── AST.json 抽象树可视化
├── AST.json 
├── CodeGen.cpp 抽象语法树生成中间代码
├── CodeGen.h
├── Makefile
├── ObjGen.cpp 中间代码生成目标代码
├── ObjGen.h
├── report.pdf实验报告
├── out 可执行文件
├── tree.html 抽象树可视化渲染
├── parser.y 语法分析yacc文件
├── main.cpp TinyCompiler程序入口
├── test.mmc 用于测试词法、语法、语义分析的源代码
├── testmain.cpp 用于测试链接目标文件的源代码
├── parser.l 词法分析lex文件
├── Cases 测试用例及结果图
    ├── testArray.input
    ├── testArray.png
    ├── testArrayAST.png
    ├── testBasic.input
    ├── testBasic.png
    ├── testBasicAST.png
    ├── testStruct.input
    ├── testStruct.png
    └── testStructAST.png

### 0.3.2 编译运行

- 编译

  ```bash
  make
  ```

- 运行

  ```bash
  cat ./Cases/test1.mmc| ./compiler
  ```

- 生成可执行文件

  ```bash
  clang++ output.o -o out
  ```

- 执行可执行文件

  ```bash
  ./out
  ```

## 0.4 组员分工

| 姓名   | 分工                                               |
| ------ | -------------------------------------------------- |
| 刘玉英 | 语义分析，中间代码生成，运行环境设计，目标代码生成 |
| 李若洋 | 词法分析，语法分析，AST可视化，测试设计，报告撰写  |

## 0.5 类C语言介绍

本实验项目的类C语言是C语言的一个子集，介绍如下。

支持的数据类型有：

- int
- double 
- float
- char
- string
- bool
- struct
- array（多维）

支持的语法有：

- 变量声明

  ```c++
  int a1;
  int a2 = 1;
  int[3] a3;
  int[3] a4 = [1,2,3];
  int[3][4] a5;
  int[2][2]a6 = [1,2,3,4]
  struct Type
  {
      int x;
      int y;
  }
  struct Type t;
  ```

- 变量赋值

  ```c++
  a1 = 1;
  a2[0] = 2;
  a3[1][1] = 1;
  t.x = 1;
  ```

- 函数的声明和调用

  ```c++
  int sum(int x, int y)
  {
      int z;
      z=x+y;
      return z;
  }
  int a = sum(1,3);
  ```

- 控制语句

  ```c++
  if (x==1)
  {
      x=x+1;
  }
  else 
  {
      x=x-1;
  }
  
  for(int i=0;i<3;i=i+1)
  {
      x=x+1;
  }
  
  while(x<3)
  {
      x=x+1;
  }
  ```

- 运算符、赋值、函数参数的隐式类型转换

- ……

# 第一章 词法分析

词法分析是计算机科学中将字符序列转换为标记（token）序列的过程。在词法分析阶段，编译器读入源程序字符串流，将字符流转换为标记序列，同时将所需要的信息存储，然后将结果交给语法分析器。

## 1.1 Lex介绍

Lex是一个产生词法分析器的程序，是大多数UNIX系统的词法分析器产生程序。Lex读入Lex文件中定义的词法分析规则，输出C语言词法分析器源码。

## 1.2 具体实现

### 1.2.1 定义区

Lex源程序在定义区导入需要的头文件：

```c
%{
#include <stdio.h>
#include <string>
#include "AST.h"
#include "parser.h"
#define SAVE_TOKEN yylval.string = new string(yytext)
#define TOKEN(t) ( yylval.token = t)
static FILE* yyparse_file_ptr;
%}
```

设置特定指令

```c
%option noyywrap
```

### 1.2.2 规则区

识别关键词，解析关键字。部分关键词如下：

```c
"if"                    puts("TIF"); return TOKEN(TIF);
"else"                  puts("TELSE"); return TOKEN(TELSE);
"return"                puts("TRETURN"); return TOKEN(TRETURN);
"for"                   puts("TFOR"); return TOKEN(TFOR);
"while"                 puts("TWHILE"); return TOKEN(TWHILE);
"struct"                puts("TSTRUCT"); return TOKEN(TSTRUCT);
"int"                   SAVE_TOKEN; puts("TYINT");  return TYINT;
"double"                SAVE_TOKEN; puts("TYDOUBLE"); return TYDOUBLE;
"float"                 SAVE_TOKEN; puts("TYFLOAT"); return TYFLOAT;
"char"                  SAVE_TOKEN; puts("TYCHAR"); return TYCHAR;
"bool"                  SAVE_TOKEN; puts("TYBOOL"); return TYBOOL;
"string"                SAVE_TOKEN; puts("TYSTRING"); return TYSTRING;
```

识别标识符、数字、字符串等

```c++
[a-zA-Z_][a-zA-Z0-9_]*	SAVE_TOKEN; puts("TIDENTIFIER"); return TIDENTIFIER;
[0-9]+\.[0-9]*			SAVE_TOKEN; puts("TDOUBLE"); return TDOUBLE;
[0-9]+  				SAVE_TOKEN; puts("TINTEGER"); return TINTEGER;
\"(\\.|[^"])*\"         SAVE_TOKEN; puts("TLITERAL"); return TLITERAL;
```

识别各种符号与运算符号，部分如下：

```c
"="						puts("TEQUAL"); return TOKEN(TEQUAL);
"=="					puts("TCEQ"); return TOKEN(TCEQ);
"!="                    puts("TCNE"); return TOKEN(TCNE);
"<"                     puts("TCLT"); return TOKEN(TCLT);
"<="                    puts("TCLE"); return TOKEN(TCLE);
">"                     puts("TCGT"); return TOKEN(TCGT);
">="                    puts("TCGE"); return TOKEN(TCGE);
"("                     puts("TLPAREN"); return TOKEN(TLPAREN);
")"                     puts("TRPAREN"); return TOKEN(TRPAREN);
```

排除空格的干扰

```c
[ \t\r\n]				; /* ignore whitespace */
```

# 第二章 语法分析

## 2.1 Yacc

SPL编译器的语法分析使用Yacc（Bison）完成。Yacc是Unix/Linux上一个用来生成编译器的编译器（编译器代码生成器）。Yacc生成的编译器主要是用C语言写成的语法解析器（Parser），需要与词法解析器Lex一起使用，再把两部分产生出来的C程序一并编译。与Lex相似，Yacc的输入文件由以%%分割的三部分组成，分别是声明区、规则区和程序区。三部分的功能与Lex相似，不同的是规则区的正则表达式替换为CFG，在声明区要提前声明好使用到的终结符以及非终结符的类型。

## 2.2 具体实现

首先声明终结符与非终结符，部分代码如下

```c++
%token <string> TIDENTIFIER TINTEGER TDOUBLE TYINT TYDOUBLE TYFLOAT TYCHAR TYBOOL TYVOID TYSTRING TEXTERN TLITERAL
%token <token> TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
```

接着按顺序构造语法树，以基础类型为例,其下面对应不同类型的数据

```c++
primary_typename : TYINT { $$ = std::make_shared<rmmc::IdentifierExpr(*$1); $$->isType = true; }
					| TYDOUBLE { $$ = std::make_shared<rmmc::IdentifierExpr(*$1); $$->isType = true;  }
					| TYFLOAT { $$ = std::make_shared<rmmc::IdentifierExpr(*$1); $$->isType = true;  }
					| TYCHAR { $$ = std::make_shared<rmmc::IdentifierExpr(*$1); $$->isType = true; }
					| TYBOOL { $$ = std::make_shared<rmmc::IdentifierExpr(*$1); $$->isType = true; }
					| TYVOID { $$ = std::make_shared<rmmc::IdentifierExpr(*$1); $$->isType = true; }
					| TYSTRING { $$ = std::make_shared<rmmc::IdentifierExpr(*$1); $$->isType = true;  }
```

## 2.3 抽象语法树

### 抽象树节点类型

<img src="C:/Users/LL/AppData/Roaming/Typora/typora-user-images/image-20220519001833350.png" alt="image-20220519001833350" style="zoom:150%;" />

## 2.4 可视化

- 可视化实现流程：
  - 生成抽象树并调用getJSON
  - 根据to_json生成抽象树对应的.json文件
  - 在同一个文件夹下打开tree.html文件，通过html渲染.json文件实现抽象树的可视化

- 具体效果

  ![image-20220522000749938](C:/Users/LL/AppData/Roaming/Typora/typora-user-images/image-20220522000749938.png)		

# 第三章 语义分析

照着report再修改一下

## 3.1实现方式

LLVM(Low Level Virtual Machine)是以C++编写的编译器基础设施，包含一系列模块化的编译器组件和工具教练用俩开发编译器前端和后端。LLVM IR是LLVM的核心所在，通过将不同高级语言的前端变换成LLVM IR进行优化、链接后再传给不同目标的后端转换成为二进制代码，前端、优化、后端三个阶段互相解耦，这种模块化的设计使得LLVM优化不依赖于任何源码和目标机器。

## 3.2 具体实现

- TypeSystem表示类型类，LLVM支持7种数据类型，可以通过Type ID判断类型

  ```c++
  floatTy = llvm::Type::getFloatTy(llvmContext);
  intTy = llvm::Type::getInt32Ty(llvmContext);
  charTy = llvm::Type::getInt8Ty(llvmContext);
  doubleTy = llvm::Type::getDoubleTy(llvmContext);
  stringTy = llvm::Type::getInt8PtrTy(llvmContext);
  voidTy = llvm::Type::getVoidTy(llvmContext);
  boolTy = llvm::Type::getInt1Ty(llvmContext);
  ```

- 隐式类型转换

- 静态全局的上下文变量和构造器变量

  ```c++
  llvm::LLVMContext theContext;
  llvm::IRBuilder<> theBuilder;
  ```

- 符号表

  ```c++
  std::map<std::string, ValuePtr> SymbolTable;
  std::map<std::string, TypePtr > SymbolType;
  std::map<std::string, std::vector<int>* > SymbolSize;
  ```

- 用block来存储{}中的内容

  ```c++
  BasicBlockPtr block;
  std::vector<CodeGenBlockPtr> blockStack;
  ```

- 当遍历各个AST节点类的时候通过在Node中定义的codeGen来实现中间代码，而codeGen方法中需生成AST节点对应的IR代码和其他的信息。

  下面以部分类为例展现具体的实现方法。

  可以通过get直接获取，例如Integer类

```c++
llvm::Value *rmmc::IntegerExpr::codeGen(CodeGenContext &context)
{
    this->print();
    return llvm::ConstantInt::get(llvm::Type::getInt64Ty(context.theContext), this->Value);
}
```

​        BockStatement中间代码的生成过程就是调用其内部的语句列表（Statements）中每个语句的codeGen生成对应的中间代码，并将最后一个语句（Return语句）的SSA值作为该结点的值返回。

```c++
llvm::Value *rmmc::BlockStatement::codeGen(CodeGenContext &context)
{
    StatementList::iterator it;
    for (it = this->Content->begin(); it != this->Content->end(); it++)
    {
        (*it)->codeGen(context);
    }
    return nullptr;
}
```

​      Identifier类通过getSymbolTable取出存储的地址，再通过CreateLoad创建一条Load指令将变量值取出来并返回寄存器的地址给调用者

```c++
llvm::Value *rmmc::IdentifierExpr::codeGen(CodeGenContext &context)
{
    this->print();
    ValuePtr val = context.getSymbolTable(this->Name);
    if(val==nullptr){
        return nullptr;
    }
    return context.theBuilder.CreateLoad(val, false, "");
}
```

# 第四章 代码生成

## 4.1 实现方式

LLVM中的平台无关代码生成器（Code Generator），同时也是一个编译器开发框架（Framework）。它提供了一些可复用的组件，帮助用户将LLVM IR编译到特定的平台上。LLVM平台描述相关的类（Target Description Classes） 为不同的平台提供了相同的抽象接口。这些类在设计上仅用来表达目标平台的属性，例如平台所支持的指令和寄存器，但不会保存任何和具体算法相关的描述。

## 4.2 具体实现

- 根据本地运行环境初始化生成目标代码的TargetMachine
- 获取并设置当前环境的target triple
- 获取并设置TargetMachine信息
- 将目标代码输出到文件

具体实现objGen如下所示

```c++
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
```

# 第五章 测试

## 5.1 数据类型测试

### 变量定义

```c
int main()
{
	int x=2;
	double y=2;
	int[2] a = [1,2];
	int[2][2] b =[2,3,4,5];
	printf("x=%d y=%lf a[1]=%d b[0][1]=%d",x,y,a[1],b[0][1]);
	return 0;
}
```

#### IR

```
; ModuleID = 'main'
source_filename = "main"

@string = private unnamed_addr constant [30 x i8] c"x=%d y=%lf a[1]=%d b[0][1]=%d\00", align 1

declare i32 @printf(i8*, ...)

define i32 @main() {
entry:
  %0 = alloca i32
  %1 = load i32, i32* %0
  store i32 2, i32* %0
  %2 = alloca double
  %3 = load double, double* %2
  %cast = sitofp i32 2 to double
  store double %cast, double* %2
  %4 = alloca [2 x i32]
  %5 = getelementptr [2 x i32], [2 x i32]* %4, i32 0, i32 0
  store i32 1, i32* %5
  %6 = getelementptr [2 x i32], [2 x i32]* %4, i32 0, i32 1
  store i32 2, i32* %6
  %7 = alloca [4 x i32]
  %8 = getelementptr [4 x i32], [4 x i32]* %7, i32 0, i32 0
  store i32 2, i32* %8
  %9 = getelementptr [4 x i32], [4 x i32]* %7, i32 0, i32 1
  store i32 3, i32* %9
  %10 = getelementptr [4 x i32], [4 x i32]* %7, i32 0, i32 2
  store i32 4, i32* %10
  %11 = getelementptr [4 x i32], [4 x i32]* %7, i32 0, i32 3
  store i32 5, i32* %11
  %12 = load i32, i32* %0
  %13 = load double, double* %2
  %14 = getelementptr [2 x i32], [2 x i32]* %4, i32 0, i32 1
  %15 = load i32, i32* %14
  %16 = getelementptr [4 x i32], [4 x i32]* %7, i32 0, i32 1
  %17 = load i32, i32* %16
  %callF = call i32 (i8*, ...) @printf([30 x i8]* @string, i32 %12, double %13, i32 %15, i32 %17)
  ret i32 0
}
```

#### 抽象树

见test1.pdf

#### 输出结果

![image-20220522012332453](C:/Users/LL/AppData/Roaming/Typora/typora-user-images/image-20220522012332453.png)	

### 隐式类型转换

```c
int main()
{
	int x=2;
	double y=2;
	y=x+y;
	x=x*y;
	printf("%lf  ",y);
	printf("%d   ",x);
	return 0;
}
```

#### 抽象树

见test2.pdf

#### 输出结果

![image-20220522004503323](C:/Users/LL/AppData/Roaming/Typora/typora-user-images/image-20220522004503323.png)	

## 5.2 运算测试

```c
int main()
{
	int x=4;
	int y=2;
	int a1;
	int a2;
	int a3;
	int a4;
	a1=x+y;
	a2=x-y;
   	a3=x/y;
	a4=x*y;
	printf("a1=%d,a2=%d,a3=%d,a4=%d",a1,a2,a3,a4);
	return 0;
}
```

### 抽象树

见test3.pdf

### 输出结果



## 5.3 控制语句测试

### 5.3.1 if语句

```c
int main()
{
	int x=4;
	if(x>0)
	{
		x=x-1;
	}
	printf("x=%d   ",x);
	return 0;
}
```

#### 抽象树

见test4

#### 输出结果

![image-20220522010914650](C:/Users/LL/AppData/Roaming/Typora/typora-user-images/image-20220522010914650.png)	

### 5.3.2 for语句

```c
int main()
{
	int x=4;
	for(int i=0;i<3;i=i+1)
	{
		x=x-1;
	}
	printf("x=%d   ",x);
	return 0;
}
```

#### 抽象树

见test5.pdf

#### 输出结果

![image-20220522010003662](C:/Users/LL/AppData/Roaming/Typora/typora-user-images/image-20220522010003662.png)	

### 5.3.3 while语句

```c
int main()
{
	int x=4;
	int i=0;
	while(i<3)
	{
		i=i+1;
		x=x-1;
	}
	printf("x=%d   ",x);
	return 0;
}
```

#### 抽象树

见test6.pdf

#### 输出结果

![image-20220522011030937](C:/Users/LL/AppData/Roaming/Typora/typora-user-images/image-20220522011030937.png)	

## 5.4 函数测试

### 5.4.1 简单函数

```c
int sum(int a, int b)
{
	int z=a+b;
	return z;
}

int main()
{
	int x=4;
	int y=3;
	int k=sum(x,y);
	printf("k=%d    ",k);
	return 0;
}
```

#### 抽象树

见test7.pdf

#### 输出结果

![image-20220522010803232](C:/Users/LL/AppData/Roaming/Typora/typora-user-images/image-20220522010803232.png)	

### 5.4.2 递归函数

```c
int sum(int a,int b)
{
	int z;
	if(a>0)
	{
		z=sum(a-1,b-1);
	}
	else 
	{
		z=b;
	}
	return z;
}
int main()
{
	int x=4;
	int y=10;
	int k=sum(x,y);
	printf("k=%d    ",k);
	return 0;
}
```

#### 抽象树

见test8.pdf

#### 输出结果

![image-20220522011730861](C:/Users/LL/AppData/Roaming/Typora/typora-user-images/image-20220522011730861.png)	



