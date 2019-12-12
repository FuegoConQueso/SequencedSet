#include "BTreeNode.h"

BTreeNode::BTreeNode()
{
	numKeys = 0;
	leaf = true;
}

BTreeNode::BTreeNode(int md)
{
	minDegree = md;
}
