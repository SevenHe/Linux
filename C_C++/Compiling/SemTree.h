#ifndef __SEMTREE_H
#define __SEMTREE_H
#endif

#define RootK 0x00
#define ProK 0x01
#define PheadK 0x02
#define TypeK 0x03
#define VarK 0x04
#define ProcDecK 0x05
#define StmLK 0x06
#define DecK 0x07
#define StmtK 0x08
#define ExpK 0x09
#define ArrayK 0x10
#define CharK 0x11
#define IntegerK 0x12
#define RecordK 0x13
#define IdK 0x14
#define IfK 0x20
#define WhileK 0x21
#define AssignK 0x22
#define ReadK 0x23
#define WriteK 0x24
#define CallK 0x25
#define ReturnK 0x26
#define OpK 0x30
#define ConstK 0x31
#define IdEK 0x32

 

typedef char symbol;

typedef struct treeNode {
	symbol t;
	char* content;
	int n;
	struct treeNode* son;
} treeNode;

treeNode* buildNode(symbol, char*);
treeNode* addNode(treeNode* father, treeNode* son);
