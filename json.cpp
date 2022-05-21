#include "AST.h"

using namespace rmmc;

typedef std::pair<std::string, std::string> attribute_t;


std::string to_json(const std::string& name) {
  return "{ \"name\" : \"" + name + "\" }";
}
std::string to_json(const std::string& name, const std::vector<std::string>& children) {
  std::string result = "{ \"name\" : \"" + name + "\", \"children\" : [ ";
  int i = 0;
  for(auto &child : children) {
    if(i != children.size() - 1)
      result += (std::string)child + ", ";
    else
      result += (std::string)child + " ";
    i++;
 }
  return result+"] }";
}
std::string to_json(const std::string& name, const std::string& value) {
  return to_json(name, std::vector<std::string>{value});
}

std::string DoubleExpr::toJSON()
{
    return to_json("DoubleExpr", to_json(std::to_string(Value)));
}

std::string IntegerExpr::toJSON()
{
    return to_json("IntegerExpr", to_json(std::to_string(Value)));
}

// std::string UnsignedIntegerExpr::toXML()
// {
//     return to_xml("UnsignedIntegerExpr", std::to_string(Value));
// }

std::string BooleanExpr::toJSON()
{
    return to_json("BooleanExpr", to_json(std::to_string(Value)));
}

// std::string CharExpr::toXML()
// {
//     return to_xml("CharExpr", std::to_string(Value));
// }

std::string StringExpr::toJSON()
{
	return to_json("StringExpr", to_json(Value));
}

std::string IdentifierExpr::toJSON()
{
	//std::to_string()
	std::vector<std::string> children;
	children.push_back(to_json("Name",to_json(Name)));
	if(isType==true)
	children.push_back(to_json("isType",to_json("True")));
	else children.push_back(to_json("isType",to_json("False")));
	if(isArray==true)
	children.push_back(to_json("isArray",to_json("True")));
	else children.push_back(to_json("isArray",to_json("False")));
	std::vector<std::string> Arry_content ;
	int i=0;
    for (auto& Arry : *arraySize) {
       if(Arry) {
         Arry_content.push_back(Arry->toJSON());
		 i++;
	   }
    }
    if(i)
	children.push_back(to_json("ArraySize",Arry_content));
    return to_json("Identifier",children );
}

// std::string ArrayIndex::toJSON()
// {
// 	std::vector<std::string> children;
// 	children.push_back(to_json("ArrayName",arrayName->toJSON()));
// 	std::vector<std::string> ind_content ;
// 	int i=0;
//     for (auto& ind : *index) {
//        if(ind) {
//          ind_content.push_back(ind->toJSON());
// 		 i++;
// 	   }
//     }
//     if(i)
// 	children.push_back(to_json("Index",ind_content));
//     return to_json("ArrayIndexExpr",children );
// }

std::string SingleOperatorExpr::toJSON()
{
	std::vector<std::string> children;
	std::string opname;
	switch(Type){
		case SingleOperator::Negative:
			opname = "-";
		case SingleOperator::LOGICAL_NOT:
			opname = "!";
		case SingleOperator::BITWISE_NOT:
			opname = "~";
		case SingleOperator::INDIRECTION:
			opname = "*";
		case SingleOperator::ADDRESS_OF:
			opname = "&";
		case SingleOperator::MOVE:
			opname = "move";
	};
	children.push_back(to_json("op",to_json(opname)));
	children.push_back(Expr->toJSON());
    return to_json("BinaryOperator", children);
}

std::string ThreeOperatorExpr::toJSON()
{
	std::vector<std::string> children;
	std::string opname;
	switch(Type){
		case ThreeOperator::CONDITION:
			opname = "?:";
	}
	children.push_back(LHS->toJSON());
	children.push_back(MHS->toJSON());
	children.push_back(RHS->toJSON());
	children.push_back(to_json("op",to_json(opname)));
    return to_json("ThreeOperator",children);
}

std::string BinaryOperatorExpr::toJSON()
{
	std::vector<std::string> children;
	std::string opname;
	switch(Type){
		case BinaryOperator::SCOPE:
			opname = "::";break;
		case BinaryOperator::ARRAY_INDEX:
			opname = "[]";break;
		case BinaryOperator::STRUCT_REF:
			opname = ".";break;
		case BinaryOperator::STRUCT_DEREF:
			opname = "&gt";break;
		case BinaryOperator::AS:
			opname = "as";break;
		case BinaryOperator::ADD:
			opname = "+";break;
		case BinaryOperator::SUB:
			opname = "-";break;
		case BinaryOperator::MUL:
			opname = "*";break;
		case BinaryOperator::DIV:
			opname = "/";break;
		case BinaryOperator::MOD:
			opname = "%";break;
		case BinaryOperator::LEFT_SHIFT:
			opname = "&lt&lt";break;
		case BinaryOperator::RIGHT_SHIFT:
			opname = "&gt&gt";break;
		case BinaryOperator::LT:
			opname = "&lt";break;
		case BinaryOperator::ELT:
			opname = "&lt=";break;
		case BinaryOperator::GT:
			opname = "&gt";break;
		case BinaryOperator::EGT:
			opname = "&gt=";break;
		case BinaryOperator::E:
			opname = "==";break;
		case BinaryOperator::NE:
			opname = "!=";break;
		case BinaryOperator::AND:
			opname = "&amp";break;
		case BinaryOperator::XOR:
			opname = "^";break;
		case BinaryOperator::OR:
			opname = "|";break;
		case BinaryOperator::LOGICAL_AND:
			opname = "&amp&amp";break;
		case BinaryOperator::LOGICAL_OR:
			opname = "||";break;
	};
	children.push_back(LHS->toJSON());
	children.push_back(to_json("op",to_json(opname)));
	children.push_back(RHS->toJSON());
    return to_json("BinaryOperator", children);
}



std::string FunctionCallExpr::toJSON()
{
	std::vector<std::string> children;
	if(FunctionName) children.push_back(to_json("FunctionName",FunctionName->toJSON()));

	std::vector<std::string> Arg_content ;
	int i=0;
    for (auto& Arg : *Args) {
       if(Arg) {
         Arg_content.push_back(Arg->toJSON());
		 i++;
	   }
    }
    if(i)
	children.push_back(to_json("Args",Arg_content));
    return to_json("FunctionCall", children);
}



std::string AssignmentExpression::toJSON()
{
	std::vector<std::string> children;
	children.push_back(LHS->toJSON());
	children.push_back(RHS->toJSON());
    return to_json("assignment", children);
}

std::string ArrayIndex::toJSON()
{
	std::vector<std::string> children;
	if(arrayName) children.push_back(to_json("ArrayName",arrayName->toJSON()));

	std::vector<std::string> ind_content ;
	int i=0;
    for (auto& ind : *index) {
       if(ind) {
         ind_content.push_back(ind->toJSON());
		 i++;
	   }
    }
    if(i)
	children.push_back(to_json("Index",ind_content));
    return to_json("ArrayIndex", children);
}

std::string ExpressionStatement::toJSON()
{
	std::vector<std::string> children;
	children.push_back(expr->toJSON());
    return to_json("ExpressionStatement", children);
}

std::string VariableDeclarationStatement::toJSON()
{
	std::vector<std::string> children;
	if(VariableType) children.push_back(to_json("VariableType",VariableType->toJSON()));
	if(VariableName) children.push_back(to_json("VariableName",VariableName->toJSON()));
	std::vector<std::string> asg_content ;
	int i=0;
    for (auto& asg : *assignmentExpr) {
       if(asg) {
         asg_content.push_back(asg->toJSON());
		 i++;
	   }
    }
    if(i)
	children.push_back(to_json("assignmentExpression",asg_content));
    return to_json("VariableDeclarationStatement", children);
}

std::string StructDeclarationStatement::toJSON()
{
	std::vector<std::string> children;
	if (Name)
		children.push_back(to_json("StructureName",Name->toJSON()));
	std::vector<std::string> mem_content;
	int i1=0,i2=0;
	for (auto& member : *Members){
		if (member)
		{
			mem_content.push_back(member->toJSON());
			i1++;
		}
			
	}
	if(i1)
	children.push_back(to_json("Members",mem_content));
	return to_json("Struct Declaration", children);
}

std::string BlockStatement::toJSON()
{
	std::vector<std::string> children;
	std::vector<std::string> p_content;
	int i=0;
	for(auto& perContent : *Content){
		if (perContent)
		{
			p_content.push_back(perContent->toJSON());
			i++;
		}	
	}
	if(i)
	children.push_back(to_json("Content",p_content));
	return to_json("Block", children);
}

std::string ReturnStatement::toJSON()
{
	std::vector<std::string> children;
	if(ReturnValue) children.push_back(to_json("ReturnValue",ReturnValue->toJSON()));
	return to_json("Return", children);
}

std::string FunctionDeclarationStatement::toJSON()
{
	std::vector<std::string> children;
    if(FunctionName) children.push_back(to_json("FunctionName",FunctionName->toJSON()));
	if(ReturnType) children.push_back(to_json("ReturnType",ReturnType->toJSON()));
	if(Content) children.push_back(to_json("Content",Content->toJSON()));
	std::vector<std::string> Arg_content;
	int i1=0;
	for (auto& Arg : *Args){
		if(Arg) 
		{
			Arg_content.push_back(Arg->toJSON());
			i1++;
		}
		
	}
	if(i1) children.push_back(to_json("Args",Arg_content));
	return to_json("FunctionDeclaration", children);
}

std::string TypedefStatement::toJSON()
{
	std::vector<std::string> children;
	children.push_back(LHS->toJSON());
	children.push_back(RHS->toJSON());
    return to_json("type", children);
}

std::string IfStatement::toJSON()
{

	std::vector<std::string> children;
	if(Condition) children.push_back(to_json("Condition",Condition->toJSON()));
	if(TrueBlock) children.push_back(to_json("TrueBlock",TrueBlock->toJSON()));
	if(FalseBlock) children.push_back(to_json("FalseBlock",FalseBlock->toJSON()));
    return to_json("if", children);
}

std::string WhileStatement::toJSON()
{
	std::vector<std::string> children;
	if(Condition) children.push_back(to_json("Condition",Condition->toJSON()));
	if(Block) children.push_back(to_json("Block",Block->toJSON()));
    return to_json("while", children);
}

std::string ForStatement::toJSON()
{
	std::vector<std::string> children;
	if(initial) children.push_back(to_json("Initial",initial->toJSON()));
	if(condition) children.push_back(to_json("Condition",condition->toJSON()));
	if(increment) children.push_back(to_json("Increment",increment->toJSON()));
	if(content) children.push_back(to_json("Content",content->toJSON()));
    return to_json("while", children);
}

std::string BreakStatement::toJSON()
{
    return to_json("break");
}

std::string ContinueStatement::toJSON()
{
    return to_json("continue");
}

std::string  NameSpaceStatement::toJSON()
{
	std::vector<std::string> children;
	if(Name) children.push_back(to_json("Name",Name->toJSON()));
	/*** Chnage later ***/
    return to_json("mod", children);
}

std::string  UseStatement::toJSON()
{
	if(Name)
		return to_json("use", Name->toJSON());
	else
		return to_json("use");

}

std::string  ImportStatement::toJSON()
{
	if(Name)
		return to_json("import", Name->toJSON());
	else
		return to_json("import");
}

std::string FromStatement::toJSON()
{
	std::vector<std::string> children;
	if(FromName) children.push_back(FromName->toJSON());
	if(ImportName) children.push_back(ImportName->toJSON());


    return to_json("from", children);
}

std::string  ExportStatement::toJSON()
{
	if(Name)
		return to_json("export", Name->toJSON());
	else
		return to_json("export");
}

