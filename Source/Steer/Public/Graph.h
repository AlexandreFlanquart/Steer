// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <list>
#include <MyNode.h>


using namespace std;


/**
 * 
 */
class STEER_API Graph{
public:
	vector<AMyNode*> allNodes;

	Graph();
	~Graph();

	void CalculHeuristique(AMyNode* end);
	float Distance(AMyNode* n1, AMyNode* n2);
	void CalculNode(AMyNode* n, AMyNode* current);
	int ClosestNeighbor(vector<AMyNode*> l, AMyNode* current);
	vector<AMyNode*> AStar(AMyNode* start, AMyNode* end);
};
