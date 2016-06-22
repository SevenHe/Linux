#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Token.h"
#include "SemTree.h"

#define bool unsigned short
#define true 1
#define false 0

treeNode* root;
struct Token tokens[] = {
	{1,PROGRAM,"program"}, {1, ID, "p"}, {2,TYPE,"type"}, {2, ID, "t1"},
	{2, EQ, "="}, {2, INTEGER, "integer"}, {2, SEMI, ";"},
	{3, VAR, "var"}, {3, INTEGER, "integer"}, {3, ID, "v1"},
	{3, COMMA, ","}, {3, ID, "v2"}, {3, SEMI, ";"}, {4, PROCEDURE, "procedure"},
	{4, ID, "q"}, {4, LPAREN, "("}, {4, INTEGER, "integer"}, {4, ID, "i"},
	{4, RPAREN, ")"}, {4, SEMI, ";"}, {5, END1, "end"}
};
static int in= 0;
struct Token* getToken()
{
	
	return &tokens[in++];
}


void print_error(char* error)
{
	printf("Error in %s!\n", error);
	exit(1);
}

void syntax_parsing()
{
	struct Token* token;
	treeNode* tmp;
	treeNode* tmpRoot;
	treeNode* lastVarNode = NULL;
	char lastId[20];
	bool is_end = false;
	bool ids = false;
	bool is_equal = false;
	while(!is_end)
	{
		symbol s;
		token = getToken();
#ifdef DEBUG
	printf("Get token: %d %d %s\n", token->lineRow, token->lex == END1, token->sem);
#endif
		if(token->lex == END1)
		{
#ifdef DEBUG
		printf("Get the end!\n");
#endif
			s = ReturnK;
			tmp = buildNode(s, token->sem);
			addNode(tmpRoot, tmp);
			is_end = true;
			continue;
		}
		/* PROGRAM PARSING */
		if(token->lex == PROGRAM)
		{
			s = ProK;
			if(root == NULL)
				print_error("PROGRAM: root == NULL");
			tmp = buildNode(s, token->sem);
			tmpRoot = tmp;
			addNode(root, tmp);	
			token = getToken();
			if(token->lex == ID)
			{
				s = PheadK;
				tmp = buildNode(s, token->sem);
				addNode(tmpRoot, tmp);
			}
		}
		else if(token->lex == PROCEDURE)
		{
			s = ProcDecK;
			tmp = buildNode(s, token->sem);
			if(token->sem == "" || token->sem == NULL)
				lastVarNode = tmp;
			addNode(tmpRoot, tmp);
		}
		else if(token->lex == TYPE)
		{
			s = TypeK;
			if(tmpRoot == NULL)
				print_error("TYPE: tmpRoot == NULL");
			tmp = buildNode(s, token->sem);
			addNode(tmpRoot, tmp);
		}
		else if(token->lex == ID)
		{
			s = IdK;
			tmp = buildNode(s, token->sem);
			addNode(tmpRoot, tmp);
		}
		else if(token->lex == EQ)
			is_equal = true;
		else if(token->lex == INTEGER)
		{
			s = DecK;
			tmp = buildNode(s, NULL);
			addNode(tmpRoot, tmp);
			s = IntegerK;
			tmp = buildNode(s, lastId);
			if(lastId == "" || lastId == NULL)
				lastVarNode = tmp;
			addNode(tmpRoot, tmp);
		}
		else if(token->lex == SEMI)
		{
			is_equal = false;
			ids = false;
			memset(lastId, 0, sizeof(lastId));
			lastVarNode = NULL;
		}
		else if(token->lex == VAR)
		{
			s = VarK;
			if(tmpRoot == NULL)
				print_error("VAR: tmpRoot == NULL");
			tmp = buildNode(s, token->sem);
			addNode(tmpRoot, tmp);
		}
		else if(token->lex == LPAREN || token->lex == RPAREN)
		{
			memset(lastId, 0, sizeof(lastId));
			lastVarNode = NULL;
		}
	}
}

treeNode* buildNode(symbol t, char* content)
{
	treeNode* tmp = (treeNode*)malloc(sizeof(treeNode));
#ifdef  DEBUG
	printf("Build a new node: %p, %d\n", tmp, t);
#endif
	tmp->t = t;
	tmp->n = 1;
	tmp->son = NULL;
	tmp->content = content;
	return tmp;
}

treeNode* addNode(treeNode* parent, treeNode* child)
{
	int childNo = parent->n;
	treeNode* tmp = parent;
	for(;tmp->son != NULL;)
		tmp = tmp->son;
	if(tmp == NULL)
	{
#ifdef DEBUG
		printf("Add node: %d, %s\n", child->t, child->content);
#endif
		tmp = child;
		parent->n ++;
	}
	else if(tmp != NULL && tmp->son == NULL)
	{
#ifdef DEBUG
		printf("Add node: %d, %s\n", child->t, child->content);
#endif
		tmp->son = child;
		parent->n ++;
	}
	while(parent != NULL)
	{
		printf("%p -> ", parent);
		parent = parent->son;
	}
	printf("\n");

	return parent;
}

void print_tree(treeNode* root)
{
	static char lastVar[32];
	static bool in_typeof = false;
#ifdef DEBUG
	printf("Node: %p\n", root);
#endif
	if(root == NULL)
		return;
	if(root->t == RootK)
		print_tree(root->son);
	else if(root->t == ReturnK)
		return;
	else 
	{
		char var[32];
		memset(var, 0, sizeof(var));
		if(root->t == ProK)
			root->content = "ProK";
		else if(root->t == PheadK)
			root->content = "PheadK";
		else if(root->t == ProcDecK)
		{
			root->content = "ProcDecK";
		}
		else if(root->t == IntegerK)
		{
			if(in_typeof)
			{	
				strcpy(var, lastVar);
				memset(lastVar, 0, sizeof(lastVar));
				in_typeof = false;
			}
			root->content = "IntegerK";
		}
		else if(root->t == DecK)
			root->content = "Deck";
		else if(root->t == 0x04)
			root->content = "VarK";
		else if(root->t == TypeK)
		{
			root->content = "TypeK";
			in_typeof = true;
		}
		else if(root->t == IdK)
		{
			if(in_typeof)
				strcat(lastVar, root->content);
			else
				strcpy(var, root->content);
			root->content = "";
		}
		if(in_typeof && root->t == IdK)
			/* nothing */;
		else
			printf("- %d %s %s-\n", root->t, root->content, var);
		print_tree(root->son);
	}
}
		
int main()
{
	root = buildNode(RootK, "root");
	syntax_parsing();
	print_tree(root);
	treeNode* tmp = root;
	while(root != NULL)
	{
		root = root->son;
		free(tmp);
		tmp = root;
	}
	return 0;
}

