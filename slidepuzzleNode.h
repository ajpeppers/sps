//slidepuzzleNode.h
#ifndef SLIDEPUZZLENODE_H
#define SLIDEPUZZLENODE_H
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;
class SlidePuzzleNode{
 public:
  SlidePuzzleNode(int** givenTable);
  int getDistance();
  int** getTable();
  void setDist(int d);
  bool goal();
  void printTable();
 private:
  int distance;
  int** table;
};
#endif
