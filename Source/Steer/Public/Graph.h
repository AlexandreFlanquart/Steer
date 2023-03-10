// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <list>

#include "Node.h"

using namespace std;


/**
 * 
 */
class STEER_API Graph{
public:
	list<Node> listNodes = list<Node>();
	list<Node> listPath = list<Node>();

	Graph();
	~Graph();

	float Distance(Node n1, Node n2);
	bool IsList(Node n1, list<Node> l);
};
