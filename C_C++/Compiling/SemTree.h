#ifndef __SEMTREE_H
#define __SEMTREE_H
#endif

typedef char symbol;

typedef struct treeNode {
	symbol t;
	int n;
	treeNode* son;
} treeNode;

treeNode* buildNode(symbol);
treeNode* addNode(treeNode* father, treeNode* son);
