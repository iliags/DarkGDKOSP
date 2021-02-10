/*
    __   __   __     __
.--|  | |__| |  |_  |  |_  .-----.
|  _  | |  | |   _| |   _| |  _  |
|_____| |__| |____| |____| |_____|

			  Text Processing Unit for DGDK by frankie taylor 2009 ©
*/

#pragma once
#ifndef DITTOTPU_H
#define DITTOTPU_H

#include "..\..\..\Include\DarkGDK\DarkGDK.h"
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>
using namespace std;


//#define DITTOTPU_TOKENTYPE_WHITESPACE	0
#define DITTOTPU_TOKENTYPE_CONSTANTS_NUMBER	1
#define DITTOTPU_TOKENTYPE_CONSTANTS_ALPHABET	2
#define DITTOTPU_TOKENTYPE_DEFINE_DIRECTIVE	3
#define DITTOTPU_TOKENTYPE_SYMBOLS	4
#define DITTOTPU_TOKENTYPE_OPERATORS	5
#define DITTOTPU_TOKENTYPE_ENCLOSURES	6
#define DITTOTPU_TOKENTYPE_DELIMITERS	7
#define DITTOTPU_TOKENTYPE_KEYWORDS_FIRSTCHR	8
#define DITTOTPU_TOKENTYPE_KEYWORDS	9

//TOKENS.ods /////////////////////////////////
#define	DITTOTPU_TOKEN_VARIABLE	1	//Constructs
#define	DITTOTPU_TOKEN_ARRAY	2	
#define	DITTOTPU_TOKEN_CONSTANT	3	
#define	DITTOTPU_TOKEN_STRINGCONSTANT	4	
#define	DITTOTPU_TOKEN_DEFINE	5	
#define	DITTOTPU_TOKEN_SUBROUTINE	6	
#define	DITTOTPU_TOKEN_ADD	7	//Operators
#define	DITTOTPU_TOKEN_SUB	8	
#define	DITTOTPU_TOKEN_MUL	9	
#define	DITTOTPU_TOKEN_DIV	10	
#define	DITTOTPU_TOKEN_INC	11	
#define	DITTOTPU_TOKEN_DEC	12	
#define	DITTOTPU_TOKEN_SHL	13	
#define	DITTOTPU_TOKEN_SHR	14	
#define	DITTOTPU_TOKEN_EXP	15	
#define	DITTOTPU_TOKEN_EQ	16	
#define	DITTOTPU_TOKEN_LT	17	
#define	DITTOTPU_TOKEN_GT	18	
#define	DITTOTPU_TOKEN_LE	19	
#define	DITTOTPU_TOKEN_GE	20	
#define	DITTOTPU_TOKEN_NE	21	
#define	DITTOTPU_TOKEN_OPENPAR	22	//Enclosures
#define	DITTOTPU_TOKEN_CLOSEPAR	23	
#define	DITTOTPU_TOKEN_OPENBRACKET	24	
#define	DITTOTPU_TOKEN_CLOSEBRACKET	25	
#define	DITTOTPU_TOKEN_OPENBRACE	26	
#define	DITTOTPU_TOKEN_CLOSEBRACE	27	
#define	DITTOTPU_TOKEN_COMMENT	28	
#define	DITTOTPU_TOKEN_OPENCOMMENT	29	
#define	DITTOTPU_TOKEN_CLOSECOMMENT	30	
#define	DITTOTPU_TOKEN_OPENQUOTE	31	
#define	DITTOTPU_TOKEN_CLOSEQUOTE	32	
#define	DITTOTPU_TOKEN_OPENDOUBLEQUOTE	33	
#define	DITTOTPU_TOKEN_CLOSEDOUBLEQUOTE	34	
#define	DITTOTPU_TOKEN_OPENTAG	35	
#define	DITTOTPU_TOKEN_CLOSETAG	36	
#define	DITTOTPU_TOKEN_ENDTAG	37	
#define	DITTOTPU_TOKEN_DELIMITER	38	//Delimiters
#define	DITTOTPU_TOKEN_SCOPE	39	//Scope
#define	DITTOTPU_TOKEN_IF	40	//FlowControls
#define	DITTOTPU_TOKEN_THEN	41	
#define	DITTOTPU_TOKEN_ELSEIF	42	
#define	DITTOTPU_TOKEN_ELSE	43	
#define	DITTOTPU_TOKEN_LABEL	44	
#define	DITTOTPU_TOKEN_JUMP	45	
#define	DITTOTPU_TOKEN_GOTO	46	
#define	DITTOTPU_TOKEN_EXIT	47	
#define	DITTOTPU_TOKEN_LOOP	48	
#define	DITTOTPU_TOKEN_NEXT	49	
#define	DITTOTPU_TOKEN_CALL	50	
#define	DITTOTPU_TOKEN_RETURN	51	
#define	DITTOTPU_TOKEN_FORMAT	52	//Directive Keywords
#define	DITTOTPU_TOKEN_IMPORT	53	
#define	DITTOTPU_TOKEN_EXPORT	54	
#define	DITTOTPU_TOKEN_INCLUDE	55	
#define	DITTOTPU_TOKEN_EXCLUDE	56	
#define	DITTOTPU_TOKEN_USE	57	
#define	DITTOTPU_TOKEN_INPUT	58	
#define	DITTOTPU_TOKEN_OUTPUT	59	
#define	DITTOTPU_TOKEN_END	60	
#define	DITTOTPU_TOKEN_UPPER	61	//Formatting Keywords
#define	DITTOTPU_TOKEN_LOWER	62	
#define	DITTOTPU_TOKEN_CAPS	63	
#define	DITTOTPU_TOKEN_NORM	64	
#define	DITTOTPU_TOKEN_CR	65	
#define	DITTOTPU_TOKEN_REMOVEFIRST	66	
#define	DITTOTPU_TOKEN_REMOVELAST	67	
#define	DITTOTPU_TOKEN_LIST	68	//List & Form Keywords
#define	DITTOTPU_TOKEN_LISTLOOP	69	
#define	DITTOTPU_TOKEN_LISTNEXT	70	
#define	DITTOTPU_TOKEN_LISTNAME	71	
#define	DITTOTPU_TOKEN_LISTITEMCOUNT	72	
#define	DITTOTPU_TOKEN_LISTITEMNAME	73	
#define	DITTOTPU_TOKEN_LISTITEMINDEX	74	
#define	DITTOTPU_TOKEN_FORM	75	
#define	DITTOTPU_TOKEN_DIRECTORY	76	
#define	DITTOTPU_TOKEN_DEMARK	77	//LastToken

//OPCODES.ods /////////////////////////////////
#define	DITTOTPU_OPCODE_MOV_EAX_ECX	1
#define	DITTOTPU_OPCODE_MOV_ECX_EAX	2
#define	DITTOTPU_OPCODE_MOV_EAX_VAR	3
#define	DITTOTPU_OPCODE_MOV_ECX_VAR	4
#define	DITTOTPU_OPCODE_MOV_VAR_EAX	5
#define	DITTOTPU_OPCODE_MOV_VAR_ECX	6
#define	DITTOTPU_OPCODE_MOV_EAX_VALUE	7
#define	DITTOTPU_OPCODE_MOV_ECX_VALUE	8
#define	DITTOTPU_OPCODE_PUSH_EAX	9
#define	DITTOTPU_OPCODE_PUSH_ECX	10
#define	DITTOTPU_OPCODE_POP_EAX	11
#define	DITTOTPU_OPCODE_POP_ECX	12
#define	DITTOTPU_OPCODE_POW_EAX_ECX	13
#define	DITTOTPU_OPCODE_MUL_EAX_ECX	14
#define	DITTOTPU_OPCODE_SHL_EAX_ECX	15
#define	DITTOTPU_OPCODE_DIV_EAX_ECX	16
#define	DITTOTPU_OPCODE_SHR_EAX_ECX	17
#define	DITTOTPU_OPCODE_ADD_EAX_ECX	18
#define	DITTOTPU_OPCODE_NEG_EAX	19
#define	DITTOTPU_OPCODE_SUB_EAX_ECX	20
#define	DITTOTPU_OPCODE_INC_EAX	21
#define	DITTOTPU_OPCODE_DEC_EAX	22
#define	DITTOTPU_OPCODE_SEQ_EAX	23
#define	DITTOTPU_OPCODE_SNE_EAX	24
#define	DITTOTPU_OPCODE_SLE_EAX	25
#define	DITTOTPU_OPCODE_SGE_EAX	26
#define	DITTOTPU_OPCODE_SGT_EAX	27
#define	DITTOTPU_OPCODE_SLT_EAX	28
#define	DITTOTPU_OPCODE_SLE_STR	29
#define	DITTOTPU_OPCODE_SGE_STR	30
#define	DITTOTPU_OPCODE_SGT_STR	31
#define	DITTOTPU_OPCODE_SLT_STR	32
#define	DITTOTPU_OPCODE_AND_EAX_STR	33
#define	DITTOTPU_OPCODE_OR_EAX_STR	34
#define	DITTOTPU_OPCODE_XOR_EAX_STR	35
#define	DITTOTPU_OPCODE_NOT_EAX_STR	36
#define	DITTOTPU_OPCODE_AND_EAX_ECX	37
#define	DITTOTPU_OPCODE_OR_EAX_ECX	38
#define	DITTOTPU_OPCODE_NOT_EAX_ECX	39
#define	DITTOTPU_OPCODE_AND_EAX	40
#define	DITTOTPU_OPCODE_OR_EAX	41
#define	DITTOTPU_OPCODE_XOR_EAX	42
#define	DITTOTPU_OPCODE_NOT_EAX	43
#define	DITTOTPU_OPCODE_LABEL	44
#define	DITTOTPU_OPCODE_JMP	45
#define	DITTOTPU_OPCODE_JZ	46
#define	DITTOTPU_OPCODE_JZ_START	47
#define	DITTOTPU_OPCODE_JZ_NEXT	48
#define	DITTOTPU_OPCODE_JMP_FIRST	49
#define	DITTOTPU_OPCODE_JMP_LAST	50
#define	DITTOTPU_OPCODE_LABEL_FIRST	51
#define	DITTOTPU_OPCODE_LABEL_NEXT	52
#define	DITTOTPU_OPCODE_LABEL_LAST	53
#define	DITTOTPU_OPCODE_PUSH_CALL	54
#define	DITTOTPU_OPCODE_POP_CALL	55
#define	DITTOTPU_OPCODE_PUSH_ARG	56
#define	DITTOTPU_OPCODE_POP_ARG	57
#define	DITTOTPU_OPCODE_NEWBSR	58
#define	DITTOTPU_OPCODE_PUSH_BSR	59
#define	DITTOTPU_OPCODE_POP_BSR	60
#define	DITTOTPU_OPCODE_RETURN	61
#define	DITTOTPU_OPCODE_NEWVAR	62
#define	DITTOTPU_OPCODE_MUL_STR	63
#define	DITTOTPU_OPCODE_NEWARRAY	64
#define	DITTOTPU_OPCODE_MOV_EAX_HEAD	65
#define	DITTOTPU_OPCODE_MOV_DIM_EAX	66
#define	DITTOTPU_OPCODE_MOV_EAX_DIM	67
#define	DITTOTPU_OPCODE_MOV_IDX_EAX	68
#define	DITTOTPU_OPCODE_MOV_EAX_IDX	69
#define	DITTOTPU_OPCODE_ARR_POP	70
#define	DITTOTPU_OPCODE_IDX_POP	71
#define	DITTOTPU_OPCODE_POP_ARR	72
#define	DITTOTPU_OPCODE_ARR_SIZE	73
#define	DITTOTPU_OPCODE_CONCENATE_EAX_ECX	74
#define	DITTOTPU_OPCODE_MOV_DAT_VALUE	75
#define	DITTOTPU_OPCODE_MOV_VAR_DAT	76
#define	DITTOTPU_OPCODE_RESTORE	77
#define	DITTOTPU_OPCODE_OPENTHREAD	78
#define	DITTOTPU_OPCODE_CLOSETHREAD	79
#define	DITTOTPU_OPCODE_LOCK	80
#define	DITTOTPU_OPCODE_UNLOCK	81
#define	DITTOTPU_OPCODE_OUT_VALUE 	82

#define DITTOTPU_FORMAT_ASCII 0
#define DITTOTPU_FORMAT_DITTOML 1
#define DITTOTPU_FORMAT_CPPP 2
#define DITTOTPU_FORMAT_CSV 3
#define DITTOTPU_FORMAT_SQL 4
#define DITTOTPU_FORMAT_XML 5

#define DEBUGLOG_TEXTTAB_MULTIPLIER 8
#define	DITTOTPU_ERROR	-1

//CLASSES ///////////////////////////////////
class dittoTPU{

	private:

	public:
		static dittoTPU *processor;

		static void start(void);
		static void stop(void);
		static void update(void);

		static void build(string modulepath);

		static int toke;
		
		//format flags

		class interpreter{

			private:

			public:
				int load(char* filename);

				class reader{
					public:
						std::fstream file;

						std::map<int,int> lfmap;
						int lastlf;
						int lfindex;
						int chrpos;
						int chroffset;
						int firstchr;

						reader(void); //constructor
						int open(char *filename);
						void close(void);
						char buffertop(int position);
						int bufferpop(int position);

				} *read;

				class writer{
					private:
					public:
						int printrow;
						int printcolumn;

						writer(void); //constructor
						void print(std::string text);
						std::fstream file;
						int save(char *filename);
				} *write;

				class parser{
					private:
					public:
						std::stack<int> processstack;

						reader *read;
						writer *write;

						int format;
						int label[3];
						enum states{IDLE} state;

						parser(void); //constructor
						int statementget(int t);
						int expressionget(void);
						int compareget(void);
						int termget(void);
						int factget(void);
						int leafget(void);
						int parameterget(void);
						void endparseget(void);
						int syntaxerror(std::string errormessage);

						class tokenizer{
							private:
							public:
								enum tokentypes{WHITESPACE,CONSTANTS_NUMBER,CONSTANTS_ALPHABET,DEFINE_DIRECTIVE,OPERATORS,ENCLOSURES,MLTAGS,DELIMITERS,KEYWORDS_FIRSTCHR,KEYWORDS,TOKENTYPES_MAX} tokentype;
								static std::map<std::string,int> identifiermap;
								static std::map<std::string,int>::iterator identifiermapiterator;
								std::string lexeme;
								reader *read;
								writer *write;
								char *tokentypechrsallowed[TOKENTYPES_MAX];
								void define(int tokentypeID, char *chrsallowed); //define token token types  allowed chrs
								void add(std::string identifier, int constant);
								int get(void);
								int set(void);
						} *token;

				} *parse;

		} *interpret;

		class importer{
			interpreter *interpret;
		} *import;

		class virtualmachine{
			public:
				static std::list<virtualmachine*> instance;

				std::vector<int> instructionvector;
				std::stack<std::string> processstack;

				std::string eax;
				std::string ecx;
				bool zflag;
				int instructionindex;
				int suspendtimer;
				
				enum states{HALT,SUSPEND,SUSPENDING,SUSPENDED,RESUSPEND,RUN,RUNNING} state;

				virtualmachine(void); //constructor
				~virtualmachine(void); //destructor
				void process(void);
				void run(void);
				void halt(void);
				void suspend(int duration);
				void resuspend(void);
				void pause(void);

				void load(char *filename);
				void save(char *filename);

		} *machine;

		class variable{
			/*!
			* Description: Variable Table
			*
			*/
			private:
				bool locked;
				bool visible;
				string value;

			public:

				static std::map<std::string,int> identifiermap;
				static std::map<std::string,int>::iterator identifiermapiterator;
				
				static std::vector<variable*> variablevector;
				
				static int identifierindex;
				static int add(std::string identifier);

				variable(void); //constructor
				
				bool assign(string value);
				bool islocked(void);
				void readonly(void);
				void readwrite(void);

				std::string access(void);
				bool isvisible(void);
				void show(void);
				void hide(void);
				
				static std::string get(int index);

		};

		class asciiconstant{
			/*!
			* Description: Stores ASCII Constants by Integer Index
			*
			*/

			public:
				static std::map<std::string,int> identifiermap;
				static std::map<std::string,int>::iterator identifiermapiterator;
				static int identifierindex;
				static int add(std::string content);
				static std::string get(int index);
		};

		class datalist{
			public:
				static std::map<std::string,int> identifiermap;
				static std::map<std::string,int>::iterator identifiermapiterator;
				static std::vector<datalist*> datalistvector;
				static int identifierindex;
				static int add(string name);

				struct item{
					char *name;
					std::string value;
				}; 
				
				std::vector<item> itemvector;
				int itemsindex;
				string name;
				string description;
				string *parent, *next, *previous, *first, *last;
				
				datalist(void); //constructor
				int load(char *filename);

		};

		class function{
			/*!
			* Description: Function Table
			*
			*/
			public:
				static std::map<std::string,int> identifiermap;
				static std::map<std::string,int>::iterator identifiermapiterator;
				static int get(std::string identifier);
				static int add(std::string identifier);
				static int identifierindex;
		};

		class form{//templates
			public:
				static std::vector<form*> instance;

				static std::map<std::string,int> namemap;
				static std::map<std::string,int>::iterator namemapiterator;
				static int nameindex;

				std::fstream file;

				int load(char *filename);
		};

		class debuglog{
			private:
				bool printenabled;
				bool appendenabled;

			public:
				std::string name;
				std::string appendtext;
				int texttab;
				int type;
				std::fstream file;

				int open(char *filename);
				void close(void);
				void print(std::string text);
				void enable(void);
				void disable(void);

		} *log;

};
#endif