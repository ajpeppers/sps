//slidepuzzleNode.cpp
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <sstream>
#include "slidepuzzleNode.h"
using namespace std;

SlidePuzzleNode::SlidePuzzleNode(int** givenTable){
  table = givenTable;
  distance = 0;
}
int SlidePuzzleNode::getDistance(){
  return distance;
}
int** SlidePuzzleNode::getTable(){
  return table;
}
void SlidePuzzleNode::setDist(int d){
  distance = d;
}
bool SlidePuzzleNode::goal(){
  int count = 1;
  for(int i =0; i<3; i++){
    for(int j=0; j<3; j++){
      if(!(table[i][j]==count)){
	return false;
      }
      if(count==8){
	count=0;
      }
      else{
	count++;
      }
    }
  }
  return true;
}
void SlidePuzzleNode::printTable(){
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      cout << table[i][j] << " ";
      if(j==2){
	cout << endl;
      }
    }
  }
}
