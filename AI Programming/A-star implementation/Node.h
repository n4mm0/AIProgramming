#pragma once

#include "NodeState.h"

class Node
{
public:

	static const int numberOfAdjElements = 4;

	Node(int x, int y) : G(0), H(0), state(Unknown), numberOfAdj(0)
	{
		this->x = x;
		this->y = y;

		for (int i = 0; i < 4; ++i)
			adj[i] = nullptr;
	}

	int getx()
	{
		return x;
	}

	int gety()
	{
		return y;
	}

	float getF() 
	{
		return G + H;
	}

	int getNumberOfAdj()
	{
		return numberOfAdj;
	}

	void setG(float G)
	{
		this->G = G;
	}

	float getG()
	{
		return G;
	}

	void setH(float H)
	{
		this->H = H;
	}

	float getH()
	{
		return H;
	}

	void setState(NodeState state)
	{
		this->state = state;
	}

	NodeState getState()
	{
		return state;
	}

	void setPrevMe(Node* PrevMe)
	{
		pathPrevMe = PrevMe;
	}

	Node* getPrevMe()
	{
		return pathPrevMe;
	}

	void insertAdj(Node* adj)
	{
		if (numberOfAdj < numberOfAdjElements)
		{
			this->adj[numberOfAdj] = adj;
			++numberOfAdj;
		}
	}

	Node* getAdj(int adjPos)
	{
		if (adjPos < numberOfAdjElements)
		{
			return adj[adjPos];
		}
		else
		{
			return nullptr;
		}
	}

private:

	int x;
	int y;

	float G;
	float H;

	NodeState state;

	int numberOfAdj;
	Node* adj[numberOfAdjElements];

	Node* pathPrevMe;
};