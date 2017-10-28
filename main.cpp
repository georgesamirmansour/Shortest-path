#include <fstream>
#include <iostream>
#include "includes.h"
using namespace std;
int main()
{
	char key = 'k';
	fstream file;
	char startCity, goalCity;
	node* pCurrentNode = new node();
	list* pFrontier = new list(NULL, NULL);
	vector<link> inputs;
	acquirelinks(inputs);
	cout << inputs.size() << endl;
	for (int i = 0; i < inputs.size(); i++)
	{
		cout << inputs[i].getC1() << "\t" << inputs[i].getC2() << "\t" << inputs[i].getLinkCost() << endl;
	}
	cout << "please enter the start city and goal city" << endl;
	cin >> startCity >> goalCity;
	pCurrentNode = new node(startCity, NULL, NULL, 0.0, false);
	pFrontier->setpFirstNode(pCurrentNode);
	pFrontier->setpLastNode(pCurrentNode);
	int choose;
	cout << "please enter the number of your choose to use the algorithm" << endl;
	cout << "choose 1 is Breadth first search" << endl;
	cout << "choose 2 is Deapth first search" << endl;
	cout << "choose 3 is uniCost search" << endl;
	cout << "choose 4 is heuristic search" << endl;
	cout << "choose 5 is A star search" << endl;
	cin >> choose;
	switch (choose)
	{
	case 1:
		while (!pCurrentNode->isGoal(goalCity))
		{
			pCurrentNode->setExplored(true);
			pCurrentNode->expand(inputs, pFrontier);
			pCurrentNode = pCurrentNode->getpNext();
		}
		break;
	case 2:
	{
		while (!pCurrentNode->isGoal(goalCity))
		{
			pCurrentNode->setExplored(true);
			pCurrentNode->expand(inputs, pFrontier);
			if (pFrontier->getpLastNode()->getName() == goalCity)
			{	
				pCurrentNode = pFrontier->getpLastNode();
			}
			else if (pFrontier->getpFirstNode()->getName() == pCurrentNode->getName())
			{
				pCurrentNode = pCurrentNode->getpNext();	
			}
			else if (pCurrentNode->getpNext()->getName() == goalCity)
			{
				pCurrentNode = pCurrentNode->getpNext();
			}
			else
			{
				pCurrentNode = pFrontier->getpLastNode();
			}
		}
	}
	case 3:
	{
		float cost1, cost2;
		while (!pCurrentNode->isGoal(goalCity))
		{
			pCurrentNode->setExplored(true);
			pCurrentNode->expand(inputs, pFrontier);
			cost1 = pCurrentNode->getpNext()->getCost();
			cost2 = pFrontier->getpLastNode()->getCost();
			if (pFrontier->getpLastNode()->getName() == goalCity)
			{
				pCurrentNode = pFrontier->getpLastNode();
			}
			else if (pCurrentNode->getpNext()->getName() == goalCity)
			{
				pCurrentNode = pCurrentNode->getpNext();
			}
			else
			{
				if (cost1 < cost2)
				{
					pCurrentNode = pCurrentNode->getpNext();
				}
				else if (cost2 < cost1)
				{
					pCurrentNode = pFrontier->getpLastNode();				
				}
				else
				{
					pCurrentNode = pFrontier->getpLastNode();
				}

			}
		}
	}
		break;
	case 4:
	{
		file.clear();
		file.open("heuristic.txt");
		int heuristic;
		char name;
		cout << "please enter the huristic name and it value" << endl;
		cout << "if u want to enter new data of heuristic press k" << " else press any key" << endl;
		cin >> key;
		if (key == 'k')
		{
			for (int i = 0; i < inputs.size(); i++)
			{
				cin >> name >> heuristic;
				file << name << "\t" << heuristic << endl;
			}
		}
		file.close();
		int heuristic1, heuristic2;
		float cost1, cost2;
		while (!pCurrentNode->isGoal(goalCity))
		{
			pCurrentNode->setExplored(true);
			pCurrentNode->expand(inputs, pFrontier);
			bool found = false;

			file.open("heuristic.txt");
			while (!file.eof())
			{
				file >> name >> heuristic;
				if (name == pFrontier->getpLastNode()->getName())
				{
					heuristic1 = heuristic;
					found = true;
					if (found == true)
					{
						file.clear();
						file.seekg(0, ios::beg);
						file.close();
						break;
					}
				}
			}
			file.open("heuristic.txt");
			while (!file.eof())
			{
				file >> name >> heuristic;
				if (name == pCurrentNode->getpNext()->getName())
				{
					heuristic2 = heuristic;
					found = true;
					if (found == true)
					{
						file.clear();
						file.seekg(0, ios::beg);
						file.close();
						break;
					}
				}
			}
			 if (heuristic1 < heuristic2)
			{
				pCurrentNode = pCurrentNode->getpNext();
			}
			else
			{
				pCurrentNode = pFrontier->getpLastNode();
			}
		}
	}
		break;
	case 5:
	{
		char name;
		float heuristic;
		file.clear();
		file.open("heuristic.txt");
		cout << "please enter the huristic name and it value" << endl;
		cout << "if u want to enter new data of heuristic press k" << " else press any key" << endl;
		cin >> key;
		if (key == 'k')
		{
			for (int i = 0; i < inputs.size(); i++)
			{
				cin >> name >> heuristic;
				file << name << "\t" << heuristic << endl;
			}
		}
		file.close();
		float cost1, cost2;
		bool found = false;
		int heuristic1, heuristic2;
		while (!pCurrentNode->isGoal(goalCity))
		{
			pCurrentNode->setExplored(true);
			pCurrentNode->expand(inputs, pFrontier);
			cost1 = pCurrentNode->getpNext()->getCost();
			cost2 = pFrontier->getpLastNode()->getCost();
			file.open("heuristic.txt");
			while (!file.eof())
			{
				file >> name >> heuristic;
				if (name == pFrontier->getpLastNode()->getName())
				{
					heuristic1 = heuristic + cost2;
					found = true;
					if (found == true)
					{
						file.clear();
						file.seekg(0, ios::beg);
						file.close();
						break;
					}
				}
			}
			file.open("heuristic.txt");
			while (!file.eof())
			{
				file >> name >> heuristic;
				if (name == pCurrentNode->getpNext()->getName())
				{
					heuristic2 = heuristic + cost1;
					found = true;
					if (found == true)
					{
						file.clear();
						file.seekg(0, ios::beg);
						file.close();
						break;
					}
				}
			}
			if (pFrontier->getpLastNode()->getName() == goalCity)
			{
				pCurrentNode = pFrontier->getpLastNode();
			}
			else if (pCurrentNode->getpNext()->getName() == goalCity)
			{
				pCurrentNode = pCurrentNode->getpNext();
			}
			else if (heuristic1 < heuristic2)
			{
				pCurrentNode = pCurrentNode->getpNext();
			}
			else
			{
				pCurrentNode = pFrontier->getpLastNode();
			}
		}
	}
		break;
		}
	cout << "the node that poshed to list is :" << endl;
	pFrontier->printList();
	cout << "goal is reached" << endl;
	cout << "The final Bath is :" << endl;
	if (pCurrentNode->isGoal(goalCity))
	{
		pCurrentNode->setExplored(true);
		pFrontier->printResult();
		cout << startCity << "\t" << goalCity << "\t" << pCurrentNode->getCost() << endl;
	}
	cin >> key;
}


