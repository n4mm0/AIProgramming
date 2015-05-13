#include <cmath>
#include <list>
#include <iostream>
#include "AStar.h"

void AStar::Setup()
{
    CreateGraph();
    
    CreateGraphAdjs();
    
    ComputeGraphHeuristics();
    
	AddNodeToOpenList(NULL, tRoot[iStartNode]);
    /*Search();
    
    Clean();*/
}

bool AStar::Step(sf::RectangleShape board[])
{
	Node* pCurrentNode;
	if (!qOpenList.empty())
	{
		pCurrentNode = VisitNode();
	}
	else
	{ 
		std::cout << "Can't find a path" << std::endl;
		return true;
	}

	UpdateBoardGraphic(board);

	if (pCurrentNode == tRoot[iEndNode])
	{
		PrintPath(pCurrentNode, board);
		return true;
	}

	board[pCurrentNode->X()*yMax + pCurrentNode->Y()].setFillColor(sf::Color::Red);

	return false;
}

void AStar::UpdateBoardGraphic(sf::RectangleShape board[])
{
	for (int i = 0; i < xMax*yMax; ++i)
	{
		switch (tRoot[i]->eState)
		{
			case NodeState::Block:
			{
				board[i].setFillColor(sf::Color::Black);
				break;
			}
			case NodeState::Closed:
			{
				board[i].setFillColor(sf::Color::Yellow);
				break;
			}
			case NodeState::Open:
			{
				board[i].setFillColor(sf::Color::Blue);
				break;
			}
			default: break;
		}

		if (tRoot[i] == tRoot[iEndNode])
		{
			board[i].setFillColor(sf::Color::White);
		}
	}
}

void AStar::CreateGraph()
{
    std::cout << "Creating Nodes...\n";
    for (int iRow = 0; iRow < xMax; ++iRow)
    {
        std::cout << "  ";
        for (int iCol = 0; iCol < yMax; ++iCol)
        {
            tRoot[(iRow*yMax) + iCol] = new Node(iRow, iCol);
            std::cout << "(" << iRow << "," << iCol << ") - ";
        }
        std::cout << "\n";
    }
    std::cout << "Creating Nodes...DONE\n\n";

	srand(time(NULL));
	int nBlocks = rand()%30+15;
	for (int i = 0; i < nBlocks; ++i)
	{
		//Non consideriamo il primo e l'ultimo nodo, cioé l'inizio e la fine
		tRoot[rand() % 98 + 1]->eState = NodeState::Block;
	}
}

void AStar::CreateGraphAdjs()
{
    std::cout << "Creating Graph Adj...\n\n";
    for (int iRow = 0; iRow < xMax; ++iRow)
    {
        for (int iCol = 0; iCol < yMax; ++iCol)
        {
            CreateNodeAdj(iRow, iCol);
        }
    }
    std::cout << "Creating Graph Adj...DONE\n\n";
}

void AStar::CreateNodeAdj(const int iRow, const int iCol)
{
    const int iNode((iRow * yMax) + iCol);
    
    std::cout << "  Creating Node Adj (" << iRow <<", " << iCol << ") ...\n";
    std::cout << "      Adjs: ";
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            if (std::abs(x) == std::abs(y) || (x == 0 && y == 0))
                continue;
            
            const int iNodeRow(iRow + x);
            const int iNodeCol(iCol + y);
            
            if (iNodeRow < 0 || iNodeRow >= xMax)
                continue;
            
            if (iNodeCol < 0 || iNodeCol >= yMax)
                continue;
            
            tRoot[iNode]->lAdj.push_back(tRoot[(iNodeRow * yMax) + iNodeCol]);
            std::cout << "(" << iNodeRow <<", " << iNodeCol << ") - ";
        }
    }
    std::cout << "\n  Creating Node Adj (" << iRow <<", " << iCol << ") ...DONE\n\n";
}

void AStar::ComputeGraphHeuristics()
{
    for (int iRow = 0; iRow < xMax; ++iRow)
    {
        for (int iCol = 0; iCol < yMax; ++iCol)
        {
            ComputeNodeHeuristic(tRoot[(iRow * yMax) + iCol]);
        }
    }
}

void AStar::ComputeNodeHeuristic(Node* pNode)
{
    pNode->iH = std::abs(pNode->X() - tRoot[iEndNode]->X()) + std::abs(pNode->Y() - tRoot[iEndNode]->Y());
}

void AStar::Clean()
{
    std::cout << "Deleting Nodes...\n";
    for (int iRow = 0; iRow < xMax; ++iRow)
    {
        std::cout << "  ";
        for (int iCol = 0; iCol < yMax; ++iCol)
        {
            delete tRoot[(iRow * yMax) + iCol];
            std::cout << "(" << iRow << "," << iCol << ") - ";
        }
        std::cout << "\n";
    }
    std::cout << "Deleting Nodes...\n\n";
}
/*
void AStar::Search()
{
    AddNodeToOpenList(NULL, tRoot[iStartNode]);
    Node* pCurrentNode = NULL;
     
    while(!qOpenList.empty())
    {
        pCurrentNode = VisitNode();
        
        if (pCurrentNode == tRoot[iEndNode])
        {
            //PrintPath(pCurrentNode, board);
            break;
        }
    }
}*/

Node* AStar::VisitNode()
{
    Node* pCurrentNode = qOpenList.front();
    qOpenList.pop_front();
    pCurrentNode->eState = NodeState::Closed;

    std::cout << "Visiting Node(" << pCurrentNode->X() << "," << pCurrentNode->Y() << ")...\n";
    
    std::cout << "  Adding Adj Node...\n";
    
    std::list<Node*>::iterator iAdjEnd(pCurrentNode->lAdj.end());
    for(std::list<Node*>::iterator iter = pCurrentNode->lAdj.begin(); iter != iAdjEnd; ++iter)
    {
        AddNodeToOpenList(pCurrentNode, *iter);
    }
    std::cout << "  Adding Adj Node...DONE\n";
    
    
    std::cout << "  OPENLIST - START Elements: " << qOpenList.size() << "\n";
    std::list<Node*>::iterator iEnd(qOpenList.end());
    for(std::list<Node*>::iterator iter = qOpenList.begin(); iter != iEnd;++iter)
    {
        std::cout << "      (" << (*iter)->X() << "," << (*iter)->Y() << ") F = " <<  (*iter)->iF << " = G(" << (*iter)->iG << ") + H(" << (*iter)->iH << ")\n";
    }   
    std::cout << "  OPENLIST - END \n";
    
    std::cout << "Visiting Node(" << pCurrentNode->X() << "," << pCurrentNode->Y() << ")... DONE\n";
    
    return pCurrentNode;
}

void AStar::AddNodeToOpenList(Node* pParent, Node* pNode)
{
    std::cout << "    (" << pNode->X() << "," << pNode->Y() << ")";
    
    switch (pNode->eState)
    {
		case NodeState::Block:
			return;

        case NodeState::Closed:
            if (pNode->iG <= pParent->iG + 1)
            {
                std::cout << " already visited.\n";
                return;
            }
            break;
            
        case NodeState::Open:
            if (pNode->iG <= pParent->iG + 1)
            {
                std::cout << " already in open list.\n";
                return;
            }
            else
            {
                qOpenList.remove(pNode);
            }
            break;
            
        default:
            break;
    }
    
    pNode->pParent = pParent;
    pNode->iG = (pParent == NULL) ? 0 : pParent->iG + 1;
    pNode->iF = pNode->iG + pNode->iH;
    pNode->eState = NodeState::Open;
    
    bool bInserted(false);
    
    std::list<Node*>::iterator iEnd(qOpenList.end());
    for(std::list<Node*>::iterator iter = qOpenList.begin(); iter != iEnd;++iter)
    {
        Node* pIterNode(*iter);
        if (pIterNode->iF > pNode->iF)
        {
            qOpenList.insert(iter, pNode);
            bInserted = true;
            std::cout << " correctly added.\n";
            break;
        }
    }
    
    if (!bInserted)
    {
        qOpenList.push_back(pNode);
        std::cout << " correctly added.\n";
    }
}

void AStar::PrintPath(Node* pNode, sf::RectangleShape board[]) const
{
    std::list<Node*> lPath;
    while (pNode != NULL)
    {
        lPath.push_front(pNode);
        pNode = pNode->pParent;
    }
    
    std::cout << "\n\nPATH FOUND - ";
    
	std::list<Node*>::iterator iEnd(lPath.end());
	for (std::list<Node*>::iterator iter = lPath.begin(); iter != iEnd; ++iter)
	{
		board[(*iter)->X()*yMax + (*iter)->Y()].setFillColor(sf::Color::Green);
		std::cout << "(" << (*iter)->X() << "," << (*iter)->Y() << ")";
	}

    /*std::list<Node*>::iterator iEnd(lPath.end());
    for (std::list<Node*>::iterator iter = lPath.begin(); iter != iEnd; ++iter)
    {
        std::cout << "(" << (*iter)->X() << "," << (*iter)->Y() << ")";
    }
    
    std::cout << "\n\n\n";*/
}









