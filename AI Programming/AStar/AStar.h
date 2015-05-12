#ifndef __AStar__AStar__
#define __AStar__AStar__

#include <iostream>
#include <list>
#include "Node.h"
#include "SFML\Graphics.hpp"

class AStar
{
public:
    void Setup();
	bool Step(sf::RectangleShape board[]);
	void UpdateBoardGraphic(sf::RectangleShape board[]);
    
private:
    const static int xMax = 10;
    const static int yMax = 10;
    const static int iStartNode = 98;
    const static int iEndNode = 4;
    
    void CreateGraph();
    void CreateGraphAdjs();
    void CreateNodeAdj(const int iRow, const int iCol);
    
    void ComputeGraphHeuristics();
    void ComputeNodeHeuristic(Node* pNode);
    
    void Clean();
    
    void Search();
    Node* VisitNode();
    void AddNodeToOpenList(Node* pParent, Node* pNode);
    
	void PrintPath(Node* pNode, sf::RectangleShape board[]) const;
    
    Node* tRoot[xMax * yMax];
    
    std::list<Node*> qOpenList;
};

#endif /* defined(__AStar__AStar__) */
