/*
    __   __   __     __
.--|  | |__| |  |_  |  |_  .-----.
|  _  | |  | |   _| |   _| |  _  |
|_____| |__| |____| |____| |_____|

			  Text Processing Unit for DGDK by frankie taylor 2009 ©
*/

#include "dittoTPU.h"

//GENERAL ///////////////////////////////////
//statics
dittoTPU *dittoTPU::processor;
int dittoTPU::toke;

void dittoTPU::start(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	processor = new dittoTPU;

	//debuglog
	processor->log = new debuglog;
	processor->log->open("dittoTPU.bug.log");
	processor->log->enable();
	processor->log->print("start bug.log");
	processor->log->print("{");
	processor->log->print("[");
	processor->log->print("apple,");
	processor->log->print("orange,");
	processor->log->print("banana");
	processor->log->print("]");
	processor->log->print("}");
	processor->log->print("stop bug.log");

	//interpreter
	processor->interpret = new interpreter;
	processor->interpret->read = new interpreter::reader;
	processor->interpret->write = new interpreter::writer;
	processor->interpret->parse = new interpreter::parser;

	processor->interpret->parse->token = new interpreter::parser::tokenizer;
	processor->interpret->parse->token->read = processor->interpret->parse->read = processor->interpret->read;
	processor->interpret->parse->token->write = processor->interpret->parse->write = processor->interpret->write;

	//parser token type must be defined prior to adding tokens
	processor->interpret->parse->token->define(interpreter::parser::tokenizer::WHITESPACE," \t\n"); //tab & LF
	processor->interpret->parse->token->define(interpreter::parser::tokenizer::CONSTANTS_NUMBER,".0123456789");
	processor->interpret->parse->token->define(interpreter::parser::tokenizer::CONSTANTS_ALPHABET,"ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz1234567890");
	processor->interpret->parse->token->define(interpreter::parser::tokenizer::DEFINE_DIRECTIVE,"#");
	processor->interpret->parse->token->define(interpreter::parser::tokenizer::OPERATORS,"+-*/^!<=>&|%?@");
	processor->interpret->parse->token->define(interpreter::parser::tokenizer::ENCLOSURES,"()[]{}");
	processor->interpret->parse->token->define(interpreter::parser::tokenizer::DELIMITERS,",");
	processor->interpret->parse->token->define(interpreter::parser::tokenizer::KEYWORDS_FIRSTCHR,"ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz");
	processor->interpret->parse->token->define(interpreter::parser::tokenizer::KEYWORDS,"ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz.1234567890");
	processor->interpret->parse->token->define(interpreter::parser::tokenizer::MLTAGS,"<@>");

	//add tokens
	//operators
	processor->interpret->parse->token->add("+",DITTOTPU_TOKEN_ADD);
	processor->interpret->parse->token->add("-",DITTOTPU_TOKEN_SUB);
	processor->interpret->parse->token->add("*",DITTOTPU_TOKEN_MUL);
	processor->interpret->parse->token->add("/",DITTOTPU_TOKEN_DIV);

	processor->interpret->parse->token->add("++",DITTOTPU_TOKEN_INC);
	processor->interpret->parse->token->add("--",DITTOTPU_TOKEN_DEC);
	processor->interpret->parse->token->add("<<",DITTOTPU_TOKEN_SHL);
	processor->interpret->parse->token->add(">>",DITTOTPU_TOKEN_SHR);
	processor->interpret->parse->token->add("^",DITTOTPU_TOKEN_EXP);

	processor->interpret->parse->token->add("=",DITTOTPU_TOKEN_EQ);
	processor->interpret->parse->token->add("<",DITTOTPU_TOKEN_LT);
	processor->interpret->parse->token->add(">",DITTOTPU_TOKEN_GT);
	processor->interpret->parse->token->add("=>",DITTOTPU_TOKEN_LE);
	processor->interpret->parse->token->add(">=",DITTOTPU_TOKEN_LE);
	processor->interpret->parse->token->add("<=",DITTOTPU_TOKEN_GE);
	processor->interpret->parse->token->add("=<",DITTOTPU_TOKEN_GE);
	processor->interpret->parse->token->add("<>",DITTOTPU_TOKEN_NE);

	//enclosures
	processor->interpret->parse->token->add("(",DITTOTPU_TOKEN_OPENPAR);
	processor->interpret->parse->token->add(")",DITTOTPU_TOKEN_CLOSEPAR);
	processor->interpret->parse->token->add("<@",DITTOTPU_TOKEN_OPENTAG);
	processor->interpret->parse->token->add("@>",DITTOTPU_TOKEN_CLOSETAG);
	processor->interpret->parse->token->add("<@>",DITTOTPU_TOKEN_ENDTAG);

	processor->interpret->parse->token->add(",",DITTOTPU_TOKEN_DELIMITER);

	//flow control keywords
	processor->interpret->parse->token->add("if",DITTOTPU_TOKEN_IF);
	processor->interpret->parse->token->add("then",DITTOTPU_TOKEN_THEN);
	processor->interpret->parse->token->add("else",DITTOTPU_TOKEN_ELSE);
	processor->interpret->parse->token->add("elseif",DITTOTPU_TOKEN_ELSEIF);
	processor->interpret->parse->token->add("label",DITTOTPU_TOKEN_LABEL);
	processor->interpret->parse->token->add("goto",DITTOTPU_TOKEN_GOTO);
	processor->interpret->parse->token->add("exit",DITTOTPU_TOKEN_EXIT);
	processor->interpret->parse->token->add("return",DITTOTPU_TOKEN_RETURN);
	processor->interpret->parse->token->add("function",DITTOTPU_TOKEN_SUBROUTINE);

	//directive keywords
	processor->interpret->parse->token->add("format",DITTOTPU_TOKEN_FORMAT);
	processor->interpret->parse->token->add("import",DITTOTPU_TOKEN_IMPORT);
	processor->interpret->parse->token->add("export",DITTOTPU_TOKEN_EXPORT);
	processor->interpret->parse->token->add("include",DITTOTPU_TOKEN_INCLUDE);
	processor->interpret->parse->token->add("exclude",DITTOTPU_TOKEN_EXCLUDE);
	processor->interpret->parse->token->add("use",DITTOTPU_TOKEN_USE);
	processor->interpret->parse->token->add("input",DITTOTPU_TOKEN_OUTPUT);
	processor->interpret->parse->token->add("output",DITTOTPU_TOKEN_OUTPUT);

	processor->interpret->parse->token->add("call",DITTOTPU_TOKEN_CALL);	

	//formatting keywords
	processor->interpret->parse->token->add("upper",DITTOTPU_TOKEN_UPPER);
	processor->interpret->parse->token->add("lower",DITTOTPU_TOKEN_LOWER);
	processor->interpret->parse->token->add("caps",DITTOTPU_TOKEN_CAPS);
	processor->interpret->parse->token->add("comment",DITTOTPU_TOKEN_COMMENT);
	processor->interpret->parse->token->add("cr",DITTOTPU_TOKEN_CR);
	processor->interpret->parse->token->add("trimfront",DITTOTPU_TOKEN_REMOVEFIRST);
	processor->interpret->parse->token->add("trimback",DITTOTPU_TOKEN_REMOVELAST);

	//list & form keywords
	processor->interpret->parse->token->add("list",DITTOTPU_TOKEN_LIST);
	processor->interpret->parse->token->add("start",DITTOTPU_TOKEN_LISTLOOP);
	processor->interpret->parse->token->add("stop",DITTOTPU_TOKEN_LISTNEXT);
	processor->interpret->parse->token->add("name",DITTOTPU_TOKEN_LISTNAME);
	processor->interpret->parse->token->add("count",DITTOTPU_TOKEN_LISTITEMCOUNT);
	processor->interpret->parse->token->add("item",DITTOTPU_TOKEN_LISTITEMNAME);
	processor->interpret->parse->token->add("index",DITTOTPU_TOKEN_LISTITEMINDEX);
	processor->interpret->parse->token->add("form",DITTOTPU_TOKEN_FORM);
	processor->interpret->parse->token->add("directory",DITTOTPU_TOKEN_DIRECTORY);

	processor->interpret->write->print("DittoTPU Compile");

	//virtualmachine
	processor->machine = new virtualmachine;

}

void dittoTPU::stop(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	delete processor->machine;

	delete processor->interpret->parse;
	delete processor->interpret->read;
	delete processor->interpret->write;
	delete processor->interpret;

	processor->log->close();
	delete processor->log;
	delete processor;
}

void dittoTPU::update(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	toke = processor->interpret->parse->statementget(toke);

}

void dittoTPU::build(string modulepath){
	/*!
	* Description:
	*
	* -#Input: 
	*	-# char *modulepath - the path that contains the module to be processed. 
	*		Searches and loads the ditto.module file (should located in module root directory) to gather directory/file structure and setup output..
	*
	* -#Output:
	*	-# none
	*/
	
	modulepath += "dittoTPU.module";
	processor->interpret->read->open((char*)modulepath.data());


}

//INTERPRETER::READER ///////////////////////////////////
dittoTPU::interpreter::reader::reader(void){

	/*!
	* Description: Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	lastlf = chrpos = chroffset = 0;
	lfindex = firstchr = 1;
}

int dittoTPU::interpreter::reader::open(char *filename){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	file.open(filename, fstream::in );//| fstream::out | fstream::app
	if(file.is_open()){
		return(1);
	} else {
		return(DITTOTPU_ERROR);
	}
	return(0);
}

void dittoTPU::interpreter::reader::close(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	file.close();
}

char dittoTPU::interpreter::reader::buffertop(int position=0){ //top

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	char bufferchr = '\0';

	if(!file.eof()){
		bufferchr =	file.peek();
		chrpos = file.tellg();

		if(bufferchr == '\n'){
			if(!lfmap[chrpos]){
				lfmap[chrpos] = ++lfindex;
			}
			lastlf = lfmap[chrpos];
			firstchr = chrpos + 1;
		}

		chroffset = chrpos - firstchr;

		return(bufferchr);//null chr
	}

	return(bufferchr);
}

int dittoTPU::interpreter::reader::bufferpop(int position=0){ //pop

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	if(file.is_open()){
		file.get();
		return(file.tellg());
	}

	return(DITTOTPU_ERROR);	
}

//INTERPRETER::WRITER ///////////////////////////////////
dittoTPU::interpreter::writer::writer(void){

	/*!
	* Description: Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	printrow = printcolumn = 0;
}


void dittoTPU::interpreter::writer::print(std::string text){

	/*!
	* Description: print function displays output on screen, outputs to log;
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	printrow+=16;
	dbText(printcolumn, printrow, (char *)text.data());
	//output to log
	if(processor->log != NULL){ processor->log->print((char *)text.data()); }
}

//INTERPRETER::PARSER ///////////////////////////////////
std::map<std::string,int> dittoTPU::interpreter::parser::tokenizer::identifiermap;
std::map<std::string,int>::iterator dittoTPU::interpreter::parser::tokenizer::identifiermapiterator;

dittoTPU::interpreter::parser::parser(void){

	/*!
	* Description: Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	label[0] = 0;
	format = DITTOTPU_FORMAT_ASCII;
}

void dittoTPU::interpreter::parser::tokenizer::add(std::string identifier, int constant){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	if(!identifiermap[identifier]){identifiermap[identifier] = constant;}
}

void dittoTPU::interpreter::parser::tokenizer::define(int tokentypeID, char *chrsallowed){

	/*!
	* Description: Defines Token Character Set and stored in in Character Array 
	*
	* -#Input:
	*	-# int tokentypeID - Charactet Set Element #
	*		char *chrsallowed - character set string
	* -#Output:
	*	-# none
	*/

	tokentypechrsallowed[tokentypeID] = chrsallowed;

}

int dittoTPU::interpreter::parser::tokenizer::get(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	std::string chr;
	std::string lexemefilter;

	//eof
	if(read->file.eof()){return(DITTOTPU_TOKEN_END);}

	//whitespace delimiter
	lexemefilter = tokentypechrsallowed[WHITESPACE];
    do{
        lexeme = read->buffertop();
	    read->bufferpop();
    }while(lexemefilter.find(lexeme) != std::string::npos);//while(lexeme == " "); //lexeme == tab chr(9) or Line Feed chr(10) 

	//constants (numerical)
	lexemefilter = tokentypechrsallowed[CONSTANTS_NUMBER];
	if(lexemefilter.find(lexeme) != std::string::npos){
        do{
           chr = read->buffertop();
		   if(lexemefilter.find(chr) == std::string::npos){return(DITTOTPU_TOKEN_CONSTANT);}
            lexeme += chr;
            read->bufferpop();
        } while(true);
    }

	//constants (defines)
	lexemefilter = tokentypechrsallowed[DEFINE_DIRECTIVE];
	if(lexemefilter.find(lexeme) != std::string::npos){
		lexemefilter = tokentypechrsallowed[CONSTANTS_ALPHABET];
        do{
			chr = read->buffertop();
			if(lexemefilter.find(chr) == string::npos){return(DITTOTPU_TOKEN_CONSTANT);}
            lexeme += chr;
            read->bufferpop();
        } while(true);
    }

	//keywords
	lexemefilter = tokentypechrsallowed[KEYWORDS_FIRSTCHR];//cannot start with a digit
	if(lexemefilter.find(lexeme) != string::npos){
		lexemefilter = tokentypechrsallowed[KEYWORDS];//extend range to allow digits after first char
        do{
            chr = read->buffertop();
            if(lexemefilter.find(chr) == string::npos){
				if(identifiermap[lexeme]) {
					return(identifiermap[lexeme]);
				} else {
					return(DITTOTPU_TOKEN_VARIABLE);
				}
            }
            lexeme += chr;
            read->bufferpop();
        } while(true);
    }

	//operators
	lexemefilter = tokentypechrsallowed[OPERATORS];
	if(lexemefilter.find(lexeme) != string::npos ){
        do{
            chr = read->buffertop();
            if(lexemefilter.find(chr) == string::npos){
				if(identifiermap[lexeme]) {
					return(identifiermap[lexeme]);
				} else {
					break;
				}
            }
            lexeme += chr;
            read->bufferpop();
        } while(true);
    }

	//enclosures
	lexemefilter = tokentypechrsallowed[ENCLOSURES];//single dual qoutes
	if(lexemefilter.find(lexeme) != string::npos ){
		if(identifiermap[lexeme]) {
			return(identifiermap[lexeme]);
		}
	}

	//delimiters
	lexemefilter = tokentypechrsallowed[DELIMITERS];
	if(lexemefilter.find(lexeme) != string::npos ){
		if(identifiermap[lexeme]) {
			return(identifiermap[lexeme]);
		}
	}

	return(DITTOTPU_ERROR);
}

int dittoTPU::interpreter::parser::tokenizer::set(void){

	/*!
	* Description: Sets file pointer to next open tag- locates open tag; includes whitespace; concenates output text as constant
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	std::string chr;
	std::string lexemefilter;

	lexeme.clear();

	//eof
	if(read->file.eof()){return(DITTOTPU_TOKEN_END);}

	//ASCII
	lexemefilter = tokentypechrsallowed[MLTAGS];
	if(lexemefilter.find(read->buffertop()) == string::npos){
		do{
			chr = read->buffertop();
			if(lexemefilter.find(chr) != std::string::npos || read->file.eof() == true ){return(DITTOTPU_TOKEN_CONSTANT);}
			lexeme += chr;
			read->bufferpop();
		} while(true);
	}

	//MLTAG
	//lexeme.clear();
    do{
		chr = read->buffertop();
		if(lexemefilter.find(chr) == string::npos){
			if(identifiermap[lexeme]) {
				return(identifiermap[lexeme]);
			} else {
				return(DITTOTPU_TOKEN_CONSTANT);
			}
		}
		lexeme += chr;
		read->bufferpop();
	} while(true);
		
	return(DITTOTPU_ERROR);
}

int dittoTPU::interpreter::parser::statementget(int tokenvalue){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	std::string text;
	std::string identifier;
	
	switch(format){

		case DITTOTPU_FORMAT_DITTOML:
		
			switch(tokenvalue){

				case DITTOTPU_TOKEN_FORMAT:
					token->get();
					processstack.push(format);
					processstack.push(DITTOTPU_TOKEN_FORMAT);
					if(token->lexeme == "ASCII") format = DITTOTPU_FORMAT_ASCII;
					if(token->lexeme == "DITTOML") format = DITTOTPU_FORMAT_DITTOML;
					text = "format = ";
					text.append(token->lexeme);
					write->print(text);
					break;
				
				case DITTOTPU_TOKEN_CLOSETAG:
					if(processstack.top() == DITTOTPU_TOKEN_FORMAT){
						processstack.pop();
						format = processstack.top();
						processstack.pop();
						token->lexeme.clear();
					} else {
						syntaxerror("Expected <@ Tag");
					}
					break;
 
				case DITTOTPU_TOKEN_OPENCOMMENT:
					do{	}while( token->get() != DITTOTPU_TOKEN_CLOSECOMMENT);
					break;

				case DITTOTPU_TOKEN_VARIABLE:
					identifier = token->lexeme;
					switch(token->get()){

						case DITTOTPU_TOKEN_EQ:
							variable::add(identifier);
							tokenvalue = expressionget();
							text = "    mov   [";
							text.append(identifier);
							text.append("],eax");
							write->print(text);
						
							processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_MOV_VAR_EAX);
							processor->machine->instructionvector.push_back(variable::identifiermap[identifier]);

							break;

						case DITTOTPU_TOKEN_OPENPAR: //check function table
							//if no call matched in the function table syntax error
							if(function::get(identifier) == DITTOTPU_ERROR){
								syntaxerror("Function not defined");
							} else {
								text = "    call  [";
								text.append(identifier);
								text.append("]");
								write->print(text);
								
								processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_PUSH_CALL);
								//processor->machine->instructionvector.push_back(); //call index
								
							}
							break;

						default:
							syntaxerror("Unrecognized Function Call");
							break;
					}
					break;

				case DITTOTPU_TOKEN_IF:
					if(expressionget() != DITTOTPU_TOKEN_THEN){syntaxerror("Expected `then`");}
					label[0]++;
					label[1] = label[0];

					identifier = "__";
					identifier.append(dbStr(label[1]));
					variable::add(identifier);
					
					text.clear();
					write->print("    and   eax,eax");
					
					text = "    jz    ";//__
					text.append(identifier);//dbStr(label[1])
					write->print(text);
					
					processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_AND_EAX);
					processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_JZ);
					processor->machine->instructionvector.push_back(variable::identifiermap[identifier]);//label[1]

					tokenvalue = statementget( token->get() );
					if(tokenvalue == DITTOTPU_TOKEN_ELSE){
						label[0]++;
						label[2] = label[0];

						identifier = "__";
						identifier.append(dbStr(label[2]));
						variable::add(identifier);

						text.clear();
						text = "    jmp   ";//__
						text.append(identifier);//dbStr(label[2])
						write->print( text );

						processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_JMP);
						processor->machine->instructionvector.push_back(variable::identifiermap[identifier]);//label[2]

						identifier = "__";
						identifier.append(dbStr(label[1]));
						variable::add(identifier);

						text.clear();
						//text = "__";
						//text.append(dbStr(label[1]));
						text = identifier;
						text.append(":");
						write->print(text);

						processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_LABEL);
						processor->machine->instructionvector.push_back(variable::identifiermap[identifier]);//label[1]
						variable::variablevector[variable::identifiermap[identifier]]->assign(dbStr((int)processor->machine->instructionvector.size()));//store instruction pointer in label variable
						variable::variablevector[variable::identifiermap[identifier]]->readonly();
						
						tokenvalue = statementget( token->get() );
						label[1] = label[2];
					}

					identifier = "__";
					identifier.append(dbStr(label[1]));
					variable::add(identifier);

					text.clear();
					//text = "__";
					//text.append(dbStr(label[1]));
					text = identifier;
					text.append(":");
					write->print(text);

					processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_LABEL);
					processor->machine->instructionvector.push_back(variable::identifiermap[identifier]);//label[1]
					variable::variablevector[variable::identifiermap[identifier]]->assign(dbStr((int)processor->machine->instructionvector.size()));//store instruction pointer in label variable
					variable::variablevector[variable::identifiermap[identifier]]->readonly();
					break;

				case DITTOTPU_TOKEN_END:
					endparseget();
					dbWaitKey();
					exit(1);
					break;

				//case DITTOTPU_TOKEN_LABEL:
				//case DITTOTPU_TOKEN_JUMP:
				//case DITTOTPU_TOKEN_GOTO:
				//case DITTOTPU_TOKEN_EXIT:
				//case DITTOTPU_TOKEN_LOOP:
				//case DITTOTPU_TOKEN_NEXT:
				//case DITTOTPU_TOKEN_RETURN:
				//case DITTOTPU_TOKEN_IMPORT:
				//case DITTOTPU_TOKEN_EXPORT:
				//case DITTOTPU_TOKEN_INCLUDE:
				//case DITTOTPU_TOKEN_EXCLUDE:
				
				case DITTOTPU_TOKEN_CALL:
					tokenvalue = expressionget();
					write->print("    call &");

					processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_PUSH_CALL);
					processor->machine->instructionvector.push_back(DITTOTPU_TOKEN_CALL-DITTOTPU_TOKEN_DEMARK);

					break;
				
				//case DITTOTPU_TOKEN_INPUT:
				//case DITTOTPU_TOKEN_OUTPUT:
				//case DITTOTPU_TOKEN_END:
				//case DITTOTPU_TOKEN_UPPER:
				//case DITTOTPU_TOKEN_LOWER:
				//case DITTOTPU_TOKEN_CAPS:
				//case DITTOTPU_TOKEN_NORM:
				//case DITTOTPU_TOKEN_CR:
				//case DITTOTPU_TOKEN_REMOVEFIRST:
				//case DITTOTPU_TOKEN_REMOVELAST:
				//case DITTOTPU_TOKEN_LIST:
				
				case DITTOTPU_TOKEN_LISTLOOP:
					//push file pointer to processstack
					//start list loop
					//listlabel
					break;
					
				case DITTOTPU_TOKEN_LISTNEXT:
					//push file pointer to processstack
					//increment list next list item and jump to listlabel
					break;
					
				//case DITTOTPU_TOKEN_LISTNAME:
				//case DITTOTPU_TOKEN_LISTITEMCOUNT:
				//case DITTOTPU_TOKEN_LISTITEMNAME:
				//case DITTOTPU_TOKEN_LISTITEMINDEX:
				//case DITTOTPU_TOKEN_FORM:
				//case DITTOTPU_TOKEN_DIRECTORY:

				default:
					syntaxerror("Unrecognized Statement");
					break;
			}
			break;

		default: //DITTOTPU_FORMAT_ASCII
			do{
				tokenvalue = token->set();
				switch(tokenvalue){

					case DITTOTPU_TOKEN_OPENTAG:
						processstack.push(format);
						processstack.push(DITTOTPU_TOKEN_FORMAT);
						format = DITTOTPU_FORMAT_DITTOML;
						break;

					case DITTOTPU_TOKEN_CLOSETAG:
						syntaxerror("Expected <@ Tag Prior To ");
						break;

					default: //DITTOTPU_TOKEN_CONSTANT
						asciiconstant::add(token->lexeme);
						text = "    out   \"";
						text.append(token->lexeme);
						text.append("\"");
						write->print(text);	
			
						processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_OUT_VALUE);
						processor->machine->instructionvector.push_back(asciiconstant::identifiermap[token->lexeme]);

						break;

					case DITTOTPU_TOKEN_END:
						endparseget();
						dbWaitKey();
						exit(1);
						break;

				}
			}while(tokenvalue != DITTOTPU_TOKEN_OPENTAG);
			tokenvalue = token->get();
			break;

	}

    return(tokenvalue);
}

int dittoTPU::interpreter::parser::expressionget(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	return(compareget());
}

int dittoTPU::interpreter::parser::compareget(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

    int tokenvalue = termget();
	char *op;
	int opcode;
	std::string text;

    do{
		switch(tokenvalue){
			case DITTOTPU_TOKEN_LT:
                op = "lt";    //these ops are wrong! x86 is weird!
				opcode = DITTOTPU_OPCODE_SLT_EAX;
				break;
			case DITTOTPU_TOKEN_GT:
                op = "gt";
				opcode = DITTOTPU_OPCODE_SGT_EAX;
				break;
			case DITTOTPU_TOKEN_LE:
                op = "le";
				opcode = DITTOTPU_OPCODE_SLE_EAX;
				break;
			case DITTOTPU_TOKEN_GE:
                op = "ge";
				opcode = DITTOTPU_OPCODE_SGE_EAX;
				break;
			case DITTOTPU_TOKEN_EQ:
                op = "eq";
				opcode = DITTOTPU_OPCODE_SEQ_EAX;
				break;
			case DITTOTPU_TOKEN_NE:
                op = "ne";
				opcode = DITTOTPU_OPCODE_SNE_EAX;
				break;
            default:
                return(tokenvalue);
				break;
        }
        write->print("    push  eax");
		processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_PUSH_EAX);
        tokenvalue = termget();
        write->print("    pop   ecx");
	    write->print("    cmp   ecx,eax");
		processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_POP_ECX);
		//processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_CMP_ECX_EAX);
		text = "    s";
		text.append(op);
		text.append("   eax");
        write->print(text);
		processor->machine->instructionvector.push_back(opcode); //select compare operator
        write->print("    and   eax,255");
		processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_AND_EAX);
    } while(true);
	return(0);
}

int dittoTPU::interpreter::parser::termget(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

    int tokenvalue = factget();
    do{
		switch(tokenvalue){
			case DITTOTPU_TOKEN_ADD:
				write->print("    push  eax");
				processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_PUSH_EAX);
                tokenvalue = factget();
                write->print("    pop   ecx");
                write->print("    add   eax,ecx");
				processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_POP_ECX);
				processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_ADD_EAX_ECX);
				break;

			case DITTOTPU_TOKEN_SUB:
                write->print("    push  eax");
				processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_PUSH_ECX);
                tokenvalue = factget();
                write->print("    mov   ecx,eax");
				processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_MOV_ECX_EAX);
                write->print("    pop   eax");
				processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_POP_EAX);
                write->print("    sub   eax,ecx");
				processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_SUB_EAX_ECX);
				break;

            default:
                return(tokenvalue);
				break;
        }
    } while(true);
	return(0);
}

int dittoTPU::interpreter::parser::factget(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

    int tokenvalue = leafget();
	do{
		switch(tokenvalue){
			case DITTOTPU_TOKEN_MUL:
                write->print("    push  eax");
				processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_PUSH_ECX);
                tokenvalue = leafget();
                write->print("    pop   ecx");
				processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_POP_ECX);
                write->print("    imul  eax,ecx");
				processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_MUL_EAX_ECX);
				break;

			case DITTOTPU_TOKEN_DIV:
                write->print("    push  eax");
				processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_PUSH_EAX);
                tokenvalue = leafget();
                write->print("    mov   ecx,eax");
				processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_MOV_ECX_EAX);
                write->print("    pop   ecx");
				processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_POP_ECX);
                write->print("    idiv  eax,ecx");
				processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_DIV_EAX_ECX);
				break;

            default:
                return(tokenvalue);
				break;
        }
	}while(true);
	return(0);
}

int dittoTPU::interpreter::parser::leafget(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	std::string text;
	int tokenvalue = token->get();
    switch(tokenvalue){
        case DITTOTPU_TOKEN_SUB:
            tokenvalue = leafget();
            write->print("    neg   eax");
			processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_NEG_EAX);
			break;

        case DITTOTPU_TOKEN_OPENPAR:
			if(expressionget() != DITTOTPU_TOKEN_CLOSEPAR){syntaxerror("Expected `)`");}
            tokenvalue = token->get();
			break;

        case DITTOTPU_TOKEN_VARIABLE:
			variable::add(token->lexeme);
			text = "    mov   eax,[";
			text.append(token->lexeme);
			text.append("]");
            write->print(text);
			processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_MOV_EAX_VAR);
			processor->machine->instructionvector.push_back(variable::identifiermap[token->lexeme]);
            tokenvalue = token->get();
			break;

        case DITTOTPU_TOKEN_CONSTANT:
			asciiconstant::add(token->lexeme);
			text = "    mov   eax,";
			text.append(token->lexeme);
			write->print(text);
			processor->machine->instructionvector.push_back(DITTOTPU_OPCODE_MOV_EAX_VALUE);
			processor->machine->instructionvector.push_back(asciiconstant::identifiermap[token->lexeme]);
            tokenvalue = token->get();
			break;

        default:
            syntaxerror("Syntax Error in leaf");
			break;
    }
	return(tokenvalue);
}


int dittoTPU::interpreter::parser::parameterget(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	return(0);
}

void dittoTPU::interpreter::parser::endparseget(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	std::string text;
	int variableindex, asciiconstantindex;

	write->print("    ret");
	write->print("");

	write->print("Variable Map");
	for(variable::identifiermapiterator = variable::identifiermap.begin(); variable::identifiermapiterator != variable::identifiermap.end(); variable::identifiermapiterator++){
		text.clear();
		text = " ";
		text.append((*variable::identifiermapiterator).first);
		text.append("[");
		text.append(dbStr((*variable::identifiermapiterator).second));
		text.append("]");
		write->print(text);
	}
	write->print("");

	write->print("Variable Vector");
	for(variableindex = 0;variableindex <= variable::identifierindex; variableindex++){
		text.clear();
		text = " [";
		text.append(dbStr(variableindex));
		text.append("]");
		text.append(variable::get(variableindex));
		write->print(text);
	}
	write->print("");

	write->print("Constant Map");
	for(asciiconstant::identifiermapiterator = asciiconstant::identifiermap.begin(); asciiconstant::identifiermapiterator != asciiconstant::identifiermap.end(); asciiconstant::identifiermapiterator++){
		text.clear();
		text = " [";
		text.append(dbStr((*asciiconstant::identifiermapiterator).second));
		text.append("]");
		text.append("\"");
		text.append((*asciiconstant::identifiermapiterator).first);
		text.append("\"");
		write->print(text);
	}
	write->print("");

	write->print("Constant Map by Index");
	for(asciiconstantindex = 0;asciiconstantindex <= asciiconstant::identifierindex; asciiconstantindex++){
		text.clear();
		text = " [";
		text.append(dbStr(asciiconstantindex));
		text.append("]");
		text.append("\"");
		text.append(asciiconstant::get(asciiconstantindex));
		text.append("\"");
		write->print(text);
	}
	write->print("");

	int vminstructionindex;

	write->print("VirtualMachine Byte Code Dump");
	for(vminstructionindex = 0;vminstructionindex < (int)processor->machine->instructionvector.size(); vminstructionindex++){
		text.clear();
		text = " [";
		text.append(dbStr(vminstructionindex));
		text.append("]");
		text.append(dbStr(processor->machine->instructionvector[vminstructionindex]));
		write->print(text);
	}
	write->print("");


	write->print("Done!");

}

int dittoTPU::interpreter::parser::syntaxerror(std::string errormessage){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	errormessage.insert(0, "SYNTAX ERROR: ");
	errormessage.append(" [Line:");
	errormessage.append(dbStr(read->lastlf));
	errormessage.append(" Chr:");
	errormessage.append(dbStr(read->chroffset));
	errormessage.append(" (Byte:");
	errormessage.append(dbStr(read->chrpos));
	errormessage.append(")]");
	write->print(errormessage);
	exit(1);
	return(0);
}

//VIRTUALMACHINE ///////////////////////////
std::list<dittoTPU::virtualmachine*> dittoTPU::virtualmachine::instance;

dittoTPU::virtualmachine::virtualmachine(void){
	/*!
	* Description: Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	instance.push_back(this);
	state = RUN;

}

dittoTPU::virtualmachine::~virtualmachine(void){
	/*!
	* Description: Destructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	instance.remove(this);
}


void dittoTPU::virtualmachine::process(void){
	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	switch(state){
		case RUN:
			state = RUNNING;
			break;

		case RUNNING:
			switch(instructionvector[instructionindex]){
				case DITTOTPU_OPCODE_MOV_EAX_ECX:
					eax = ecx;
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MOV_ECX_EAX:
					ecx = eax;
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MOV_EAX_VAR:
					eax = variable::variablevector[instructionvector[++instructionindex]]->access();
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MOV_ECX_VAR:
					ecx = variable::variablevector[instructionvector[++instructionindex]]->access();
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MOV_VAR_EAX:
					variable::variablevector[instructionvector[++instructionindex]]->assign(eax);
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MOV_VAR_ECX:
					variable::variablevector[instructionvector[++instructionindex]]->assign(ecx);
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MOV_EAX_VALUE:
					eax = asciiconstant::get(instructionvector[++instructionindex]);
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MOV_ECX_VALUE:
					ecx = asciiconstant::get(instructionvector[++instructionindex]);
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_PUSH_EAX:
					processstack.push(eax);
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_PUSH_ECX:
					processstack.push(ecx);
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_POP_EAX:
					eax = processstack.top();
					processstack.pop();
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_POP_ECX:
					ecx = processstack.top();
					processstack.pop();
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_POW_EAX_ECX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MUL_EAX_ECX:
					eax = dbStr(dbVal((char*)eax.data()) * dbVal((char*)ecx.data()));
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_SHL_EAX_ECX:
					eax = dbStr((int)dbVal((char*)eax.data()) << (int)dbVal((char*)ecx.data()));
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_DIV_EAX_ECX:
					eax = dbStr(dbVal((char*)eax.data()) / dbVal((char*)ecx.data()));
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_SHR_EAX_ECX:
					eax = dbStr((int)dbVal((char*)eax.data()) >> (int)dbVal((char*)ecx.data()));
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_ADD_EAX_ECX:
					eax = dbStr(dbVal((char*)eax.data()) + dbVal((char*)ecx.data()));
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_NEG_EAX:
					eax = dbStr(dbVal((char*)eax.data()) * -1); 
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_SUB_EAX_ECX:
					eax = dbStr(dbVal((char*)eax.data()) - dbVal((char*)ecx.data()));
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_INC_EAX:
					eax = dbStr(dbVal((char*)eax.data()) + 1);
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_DEC_EAX:
					eax = dbStr(dbVal((char*)eax.data()) - 1);
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_SEQ_EAX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_SNE_EAX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_SLE_EAX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_SGE_EAX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_SGT_EAX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_SLT_EAX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_SLE_STR:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_SGE_STR:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_SGT_STR:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_SLT_STR:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_AND_EAX_STR:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_OR_EAX_STR:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_XOR_EAX_STR:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_NOT_EAX_STR:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_AND_EAX_ECX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_OR_EAX_ECX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_NOT_EAX_ECX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_AND_EAX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_OR_EAX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_XOR_EAX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_NOT_EAX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_LABEL:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_JMP:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_JZ:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_JZ_START:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_JZ_NEXT:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_JMP_FIRST:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_JMP_LAST:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_LABEL_FIRST:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_LABEL_NEXT:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_LABEL_LAST:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_PUSH_CALL:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_POP_CALL:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_PUSH_ARG:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_POP_ARG:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_NEWBSR:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_PUSH_BSR:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_POP_BSR:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_RETURN:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_NEWVAR:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MUL_STR:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_NEWARRAY:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MOV_EAX_HEAD:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MOV_DIM_EAX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MOV_EAX_DIM:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MOV_IDX_EAX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MOV_EAX_IDX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_ARR_POP:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_IDX_POP:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_POP_ARR:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_ARR_SIZE:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_CONCENATE_EAX_ECX:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MOV_DAT_VALUE:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_MOV_VAR_DAT:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_RESTORE:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_OPENTHREAD:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_CLOSETHREAD:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_LOCK:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_UNLOCK:
					instructionindex++;
					break;
				case DITTOTPU_OPCODE_OUT_VALUE:
					instructionindex++;
					break;
				default:
					//process error
					break;
			}
			break;
		
		SUSPEND:
			state = SUSPENDING;
			break;

		SUSPENDING:
			state = SUSPENDED;
			break;

		SUSPENDED:
			if(--suspendtimer == 0){state = RUN;}
			break;

		HALT:
			break;
	}
}


void dittoTPU::virtualmachine::run(void){

	/*!
	* Description: 
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

}

void dittoTPU::virtualmachine::halt(void){

	/*!
	* Description: Immediately halts VM processing
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
	state = HALT;
	
}

void dittoTPU::virtualmachine::suspend(int duration){

	/*!
	* Description: Suspend VM for duration
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
	suspendtimer = duration;
	state = SUSPEND;

}

void dittoTPU::virtualmachine::resuspend(void){

	/*!
	* Description: Suspend VM for duration, will automatically resume after duration is up.
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	state = SUSPEND;

}

void dittoTPU::virtualmachine::pause(void){

	/*!
	* Description: Suspends VM indefinately.
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
	suspendtimer = -1;
	state = SUSPEND;

}



void dittoTPU::virtualmachine::save(char *filename){

	/*!
	* Description: Saves Compiled Form
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

}

//VARIABLE ///////////////////////////////////
std::map<string,int> dittoTPU::variable::identifiermap;
std::map<string,int>::iterator dittoTPU::variable::identifiermapiterator;
std::vector<dittoTPU::variable*> dittoTPU::variable::variablevector;
int dittoTPU::variable::identifierindex = -1;

dittoTPU::variable::variable(void){

	/*!
	* Description: Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	locked = false;
	visible = true;
	value = "";
}

int dittoTPU::variable::add(std::string identifier){
	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	if(identifiermap.find(identifier) == identifiermap.end()){
		identifiermap[identifier] = ++identifierindex;
		variablevector.push_back(new variable);
	}
	return(identifiermap[identifier]);

}

std::string dittoTPU::variable::get(int index){
	/*!
	* Description: Get by index; return string key
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	for(variable::identifiermapiterator = variable::identifiermap.begin(); variable::identifiermapiterator != variable::identifiermap.end(); variable::identifiermapiterator++){
		if((*variable::identifiermapiterator).second == index){
			return((*variable::identifiermapiterator).first);
		}
	}
	return("\0");
}

bool dittoTPU::variable::assign(std::string value){
	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# true if assign is successful, otherwise false
	*/

	if(!locked){
		this->value = value;
		return(true);
	}
	return(false);
}

bool dittoTPU::variable::islocked(void){
	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# returns true or false
	*/

	return(locked);
}

void dittoTPU::variable::readonly(void){
	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-#
	*/

	locked = true;
}

void dittoTPU::variable::readwrite(void){
	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# 
	*/

	locked = false;
}

std::string dittoTPU::variable::access(void){
	/*!
	* Description: returns value if visible = true, otherwise null character string
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-#
	*/

	if(visible){
		return(value);
	}
	return("\0");
}

bool dittoTPU::variable::isvisible(void){
	/*!
	* Description: returns true or false
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# 
	*/

	return(visible);
}

void dittoTPU::variable::show(void){
	/*!
	* Description: Turns visibility on
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-#
	*/

	visible = true;
}

void dittoTPU::variable::hide(void){
	/*!
	* Description: Turns visibility off
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# 
	*/

	visible = false;
}


//ASCIICONSTANT ///////////////////////////////////
std::map<string,int> dittoTPU::asciiconstant::identifiermap;
std::map<string,int>::iterator dittoTPU::asciiconstant::identifiermapiterator;
int dittoTPU::asciiconstant::identifierindex = -1;

int dittoTPU::asciiconstant::add(std::string content){
	/*!
	* Description: Add constant to map if not present, return index.
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	if(identifiermap.find(content) == identifiermap.end()){
		identifiermap[content] = ++identifierindex;
	}
	return(identifiermap[content]);
}

std::string dittoTPU::asciiconstant::get(int index){
	/*!
	* Description: Get by index; return string key
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	for(asciiconstant::identifiermapiterator = asciiconstant::identifiermap.begin(); asciiconstant::identifiermapiterator != asciiconstant::identifiermap.end(); asciiconstant::identifiermapiterator++){
		if((*asciiconstant::identifiermapiterator).second == index){
			return((*asciiconstant::identifiermapiterator).first);
		}
	}
	return("\0");
}


//DATALIST ///////////////////////////////////
std::map<string,int> dittoTPU::datalist::identifiermap;
std::map<string,int>::iterator dittoTPU::datalist::identifiermapiterator;
int dittoTPU::datalist::identifierindex = -1;

dittoTPU::datalist::datalist(void){

	/*!
	* Description: Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	description = "";

}

int dittoTPU::datalist::add(string name){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	if(identifiermap.find(name) == identifiermap.end()){
		identifiermap[name] = ++identifierindex;
	}
	return(identifiermap[name]);

}

//FUNCTION ///////////////////////////////////
std::map<string,int> dittoTPU::function::identifiermap;
std::map<string,int>::iterator dittoTPU::function::identifiermapiterator;
int dittoTPU::function::identifierindex = -1;

int dittoTPU::function::add(string identifier){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	if(identifiermap.find(identifier) == identifiermap.end()){
		identifiermap[identifier] = ++identifierindex;
	}
	return(identifiermap[identifier]);

}

int dittoTPU::function::get(string identifier){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	if(identifiermap.find(identifier) == identifiermap.end()){
		return(DITTOTPU_ERROR);
	}
	return(identifiermap[identifier]);

}

//DEBUGLOG ///////////////////////////////////
int dittoTPU::debuglog::open(char *filename){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	file.open(filename, fstream::out);
	if(file.is_open()){
		name = filename;
		appendtext = "";
		texttab = 0;
		printenabled = false;
		appendenabled = false;
		return(1);
	} else {
		return(-1);
	}

	return(0);
}

void dittoTPU::debuglog::close(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	file.close();

}

void dittoTPU::debuglog::enable(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	printenabled = true;

}

void dittoTPU::debuglog::disable(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	printenabled = false;
}

void dittoTPU::debuglog::print(std::string text){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	if(printenabled){

		if(text.substr(0,1) == "{"){
			//tab out
			text.append("\n");
			text.insert(text.begin(), texttab * DEBUGLOG_TEXTTAB_MULTIPLIER, ' ');
			texttab++;
			file.write(text.data(), text.length());

		}else if(text.substr(0,1) == "}"){
			//tab in
			texttab--;
			text.insert(text.begin(), texttab * DEBUGLOG_TEXTTAB_MULTIPLIER, ' ');
			file.write(text.data(), text.length());

		}else if(text.substr(0,1) == "["){
			//start appending
			if(!appendenabled){
				appendtext = text;
				appendtext.insert(appendtext.begin(), texttab * DEBUGLOG_TEXTTAB_MULTIPLIER, ' ');
			} else {
				appendtext.append(text);
			}
			appendenabled = true;

		}else if(text.substr(0,1) == "]"){
			//stop appending
			appendtext.append(text);
			appendtext.append("\n");
			file.write(appendtext.data(), appendtext.length());
			appendtext.clear();
			appendenabled = false;

		}else {
			if(appendenabled){
				appendtext.append(text);
			} else {
				text.insert(text.begin(), texttab * DEBUGLOG_TEXTTAB_MULTIPLIER,' ');
				text.append("\n");
				file.write(text.data(), text.length());

			}
		}
	}
}