#pragma once 

#include "NodeState.h"
#include <list>
#include "Configuration.h"

/*struct Node
{
	Node()
	{
		x = 0;
		y = 0;
		G = 0;
		H = 0;
		state = Unknown;

		.reserve(4);
		adjs[0] = nullptr;
		adjs[1] = nullptr;
		adjs[2] = nullptr;
		adjs[3] = nullptr;
		//nAdjs = 0;

		previous = nullptr;
	}

	void addAdj(Node* adj)
	{
		adjs[nAdjs] = adj;
		nAdjs++;
		adjs.push_back(adj);
	}

	int x, y;
	int G;
	int H;
	NodeState state;
	std::list<Node*> adjs;
	Node* adjs[4];
	int nAdjs;
	Node* previous;

	int F()
	{
		return G + H;
	}
};*/

struct Node
{
	Node(Configuration _config)
	{
		cConfig = _config;
		state=NodeState::Unknown;
		F = -1;
		G = -1;
		//Compute Heuristic
		H = 0;
		for (int i = 0; i < 16; ++i)
		{
			int tile = cConfig.getElementAt(i);
			int tileX = i / 4;
			int tileY = i % 4;
			int goalX = (tile - 1) / 4;
			int goalY = (tile - 1) % 4;
			H += abs(tileX - goalX) + abs(tileY - goalY);
		}
	}
	NodeState state;
	Configuration cConfig;
	Node* previous;
	std::list<Node*> lAdjs;
	int F;
	int G;
	int H;
	void createAdjs()
	{
		if (lAdjs.empty())
		{
			int blankTile = cConfig.getBlankPosition();
			//boardSize=4
			//Limite superiore NO
			if (blankTile >= 4)
			{
				Configuration cTemp(cConfig);
				cTemp.swapElements(blankTile, blankTile - 4);
				lAdjs.push_front(new Node(cTemp));
			}
			//Limite sinistro NO
			if (blankTile % 4 != 0)
			{
				Configuration cTemp(cConfig);
				cTemp.swapElements(blankTile, blankTile - 1);
				lAdjs.push_front(new Node(cTemp));
			}
			//Limite inferiore NO
			if (blankTile <= 11)
			{
				Configuration cTemp(cConfig);
				cTemp.swapElements(blankTile, blankTile + 4);
				lAdjs.push_front(new Node(cTemp));
			}
			//Limite destro NO
			if ((blankTile+1) % 4 != 0)
			{
				Configuration cTemp(cConfig);
				cTemp.swapElements(blankTile, blankTile + 1);
				lAdjs.push_front(new Node(cTemp));
			}
		}
	}
};
/*
class Node
{
	public:
		Node();
		int getF();
		int getG();
		int getH();
		void setG(int _G);
		void setH(int _H);

	private:
		Configuration nConfig;
		NodeState state;
		int G;
		int H;
		Node* previous;
}
*/

/*class Node
{
	public:
		Node()
		{
			G = 0;
			H = 0;
			state = Unknown;

			//LOOP UNROLLING!
			adjs[0] = nullptr;
			adjs[1] = nullptr;
			adjs[2] = nullptr;
			adjs[3] = nullptr;
		}

		int getF()
		{
			return G + H;
		}

		int getG()
		{
			return G;
		}

		void setG(int g)
		{
			G = g;
		}

		int getH()
		{
			return H;
		}

		void setH(int h)
		{
			H = h;
		}

		NodeState getState()
		{
			return state;
		}

		void setState(NodeState _state)
		{
			state = _state;
		}

		Node* getPrev()
		{
			return previous;
		}

		void setPrev(Node* _previous)
		{
			previous = _previous;
		}

	private:
		int G;
		int H;
		NodeState state;
		Node* adjs[4];
		Node* previous;
};*/