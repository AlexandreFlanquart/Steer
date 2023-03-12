// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph.h"
#include <Kismet/GameplayStatics.h>

Graph::Graph() {

}

Graph::Graph(UWorld* const World)
{
	//find all nodes
	 TArray<AActor*> FoundActors;
	 UGameplayStatics::GetAllActorsOfClass(World, AMyNode::StaticClass(), FoundActors);

	 for (int i = 0; i < FoundActors.Num(); i++) {
		 allNodes.push_back((AMyNode*)(FoundActors[i]));
		 GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green,  FoundActors[i]->GetName());
		 //UE_LOG(LogTemp, Warning, TEXT("test"));
		// printFString("Name : %s", FoundActors[i]->GetName());
	 }

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
		n->parent = nullptr;
		n->cost = 1000;
		n->dist = 0;
	}
}



bool InList(AMyNode* n1, vector<AMyNode*> l) {
	for (auto& n : l) {
		if (n1 == n) {
			return true;
		}
	}
	return false;
}

void  Graph::CalculNode(AMyNode* n, AMyNode* current) {
	float temp = Distance(n, current) + current->dist + n->heuristique;
	if (temp <= n->cost) {
		n->dist = Distance(n, current) + current->dist;
		n->cost = n->dist + n->heuristique;
		n->parent = current;
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Blue, TEXT("parent"));
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
	CalculHeuristique(end);

	while (!openListe.empty()) {
		pos = ClosestNeighbor(openListe, current);
		current = openListe[pos];
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Blue, TEXT("A*"));
		for (AMyNode* c : current->listNeighbor) // add child
		{
			if (!InList(c, openListe) && !InList(c, closeListe)) {// not already check
				openListe.push_back(c);
			}
			GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Blue, TEXT("CALCUL"));
			CalculNode(c, current);
			if (c == end) {
				GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Blue, TEXT("FIN"));
				find = true;
				break;
			}
		}
		if (find)
			break;
		// remove current
		openListe.erase(openListe.begin() + pos); 
		closeListe.push_back(current);
	}

	if (find == true) {
		path.insert(path.begin(), end);
		AMyNode* cur = path[0];
		GEngine->AddOnScreenDebugMessage(-1, 400, FColor::Green, path[0]->GetName());
		while (cur->parent != nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 400, FColor::Green, path[0]->GetName());
			path.insert(path.begin(), path[0]->parent);
			cur = path[0];
		}
	}
	else {
		path.push_back(start);
	}

	return path;
}
