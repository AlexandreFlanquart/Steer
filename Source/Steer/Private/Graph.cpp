// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph.h"

Graph::Graph()
{
	//find all nodes
	// TArray<AActor*> FoundActors;
	// UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyNode, FoundActors);

	// calcul heuristique
	//CalculHeuristique();
}

Graph::~Graph()
{
}
float Graph::Distance(AMyNode* n1, AMyNode* n2) {
	return (n1->GetActorLocation() - n2->GetActorLocation()).Length();
}

void Graph::CalculHeuristique(AMyNode* end) {
	for (AMyNode* n : allNodes) {
		n->heuristique = Distance(n, end);
	}
}



bool InList(AMyNode* n1, vector<AMyNode*> l) {
	for (auto& n : l) {
		if (n1->id == n->id) {
			return true;
		}
	}
	return false;
}

void  Graph::CalculNode(AMyNode* n, AMyNode* current) {
	if (Distance(n, current) + current->dist <= n->dist) {// dist not init
		n->dist = Distance(n, current);
		n->cost = n->dist + n->heuristique;
		n->parent = current;
	}
}

int  Graph::ClosestNeighbor(vector<AMyNode*> l, AMyNode* current) {
	int min = 0, pos = 0, i = 0;
	min = l[0]->cost;

	for (AMyNode* c : l)
	{
		if (c->cost < min) {
			min = c->cost;
			pos = i;
		}
		// if ==
		i++;
	}
	return pos;
}



vector<AMyNode*>  Graph::AStar(AMyNode* start, AMyNode* end) {
	vector<AMyNode*> openListe;
	vector<AMyNode*> closeListe;
	vector<AMyNode*> path;
	AMyNode* current = start;
	int pos = 0;
	bool find = false;

	openListe.push_back(start);

	while (!openListe.empty()) {
		pos = ClosestNeighbor(openListe, current);
		current = openListe[pos];

		for (AMyNode* c : current->listNeighbor) // add child
		{
			if (!InList(c, openListe) & !InList(c, closeListe)) {// not already check
				openListe.push_back(c);
			}
			CalculNode(c, current);
			if (c == end) {
				find = true;
				break;
			}
		}

		// remove current
		openListe.erase(openListe.begin() + pos); 
		closeListe.push_back(current);
	}

	if (find == true) {

	}
	else {
		path.push_back(start);
	}

	return path;
}
