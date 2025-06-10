#ifndef NODE_H
#define NODE_H

/*
	What does a NODE do?
	- A Node is a Struct used to Communicate to the Engine in the Form of a GameObject

	void myFunction

	BE3DNODE exampleNode = CreateNode();
*/

#include "BE3DINST.H"

typedef int (*BE3DNODE_Update)(BE3DINST* inst);
typedef int (*BE3DNODE_Init)(BE3DINST* inst);

typedef struct BE3DNODE {
	BE3DNODE_Update updateF;
	BE3DNODE_Init initF;
} BE3DNODE;

BE3DNODE CreateNode(BE3DNODE_Init* initF, BE3DNODE_Update* updateF)
{
	BE3DNODE a;
	a.initF = *initF;
	a.updateF = *updateF;
	return a;
}

BE3DNODE InitNode(BE3DNODE* node) 
{
	
}

#endif