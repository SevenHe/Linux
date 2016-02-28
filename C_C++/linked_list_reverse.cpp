#include <iostream>
using namespace std;
struct node {
	int data;
	node* next;
};

node* iteration(node*, node*);
node* recursion(node*, node*);

int main()
{
	/*node* test = NULL;
	if(test == NULL){
		cout << "ok" << endl;
	}*/
	node* header = new node;
	node* temp = header;
	for(int i=0; i<5; i++)
	{
		cout << "Please input the data:";
		cin >> temp->data;
		// must initialize!
		if(i != 4)
		{
			temp->next = new node;
			temp = temp->next;
		}
		else
		{
			temp->next = NULL;
		}
	}
	temp = header;
	for(int i=0; i<5; i++)
	{
		cout << "input " << i << " : " << temp->data << endl;
		if(temp->next != NULL) temp = temp->next;
	}
	// reversion from here, if it is not a real memory location, it will raise a Segmentation Fault!
	// NULL is a value, it should be specified explicitly.
	node* cur = header;
	node* pre = cur;
	// reversion print!
	cout << "--Reversion list--" << endl;
	temp = recursion(header, pre);
	pre = temp;
	for(int i=0; i<5; i++)
	{
		cout << "input " << i << " : " << temp->data << endl;		
		if(temp->next != NULL)temp = temp->next;
	}
	// for iteration deletion!
	if(temp->next == temp)
	{
		temp->next = NULL;
		cout << "Have handled the end problem!" << endl;
	}
	// for recursion deletion!
	if(temp->next->next == temp)
	{
		temp->next->next = NULL;
		cout << "Have handled the end problem!" << endl;
	}
	// after reversion, pre is the header.
	while(pre != NULL)
	{
		node* next = pre;
		pre = pre->next;
		delete next;
	}

	return 0;
}

// the special point is the first->next = first!
node* iteration(node* cur, node* pre)
{
	// if there is a accurate number about the linked list, it doesn't matter whether the end->next=NULL or not
	while(cur != NULL) 
	{
		node* nt = cur->next;
		cur->next = pre;
		pre = cur;
		cur = nt;
	}

	return pre;
}

// In fact, it passes a value.
// adverse thinking!
// the special point is the last->next = before_last!
node* recursion(node* header, node* rvs)
{
	// header is the variable.
	if(header->next->next == NULL)
	{
		rvs = header->next;
		header->next->next = header;
		return rvs;
	}
	rvs = recursion(header->next, rvs);
	header->next->next = header;
	
	return rvs;
}
