#ifndef __TOKEN_H
#define __TOKEN_H
#endif

typedef enum LexType {
	/* 单词符号 */
	ENDFILE, ERROR,
	/* 保留字 */
	PROGRAM, PROCEDURE, TYPE, VAR, IF, THEN,
	ELSE, FI, WHILE, DO, ENDWH, BEGIN1, END1,
	READ, WRITE, ARRAY, OF, RECORD, RETURN1,
	/* Type */
	INTEGER, CHAR1,
	/* 多单词符号 */
	ID, INTC, CHARC,
	/* 特殊符号 */
	ASSIGN, EQ, LT, PLUS, MINUS, TIMES, OVER,
	LPAREN, RPAREN, DOT, COLON, SEMI, COMMA,
	LMIDPAREN, RMIDPAREN, UNDERANGE
} LexType;

struct Token
{
	int lineRow;
	LexType lex;
	char* sem;
};

