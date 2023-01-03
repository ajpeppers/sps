//slidepuzzle.cpp
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <sstream>
#include <queue>
#include <string>
#include <list>
#include "slidepuzzleNode.h"
using namespace std;
/*The value 1669 is chosen for the size of our hash table as it is the smallest prime number beyond the largest possible value of our hash value (uHash)*/
vector<list<int**> > uniques = vector<list<int**> >(1669);
int uHash(int** table);
vector<SlidePuzzleNode*> generateNeighbors(int** table);
bool uniqueCheck(int** table);
int inversionCount(int* arr);
bool possibleCheck(int** table);
int bfs(SlidePuzzleNode* start);

int main(int argc, char** argv){
  int** table = new int*[3];
  for(int i=0; i<3; i++){
    table[i] = new int[3];
    for(int j = 0; j < 3; j++){
      table[i][j] = 0;
    }
  }
  cout << "Enter puzzle" << endl;
  int col = 0;
  int row = 0;
  /*Input the starting state of the puzzle by giving one element in each line, moving left-to-right / top-to-bottom.*/
  for(int i = 0; i<9; i++){
    string line = "";
    cin >> line;
    int num = stoi(line);
    table[row][col]=num;
    if(col==2){
      col = 0;
      row++;
    }
    else{
      col++;
    }
  }
  int startHash = uHash(table);
  uniques[startHash].push_back(table);
  SlidePuzzleNode* start = new SlidePuzzleNode(table);
  cout<<"Solving Puzzle"<<endl;
  if(possibleCheck(table)){
    int minDist = bfs(start);
    cout << minDist << endl;
  }
  else{
    cout << "IMPOSSIBLE" << endl;
  }
  return 0;
}

/**
 * @author A.J. Peppers
 * @details This program serves as a hash method for the hash table of uniques.
 * @param table The state of the puzzle on which the hash value is being determined.
 * @date 4-29-22
 */
int uHash(int** table){
  int count = 0;
  /*The hashing method for this program is to cube the top row of the slide puzzle, square the second row, and maintain the third row.
  Then, these values are added together.  The sum of these values is the returned hash value.*/
  for(int i=0; i<3; i++){
    count = count + ((table[i][0])*(table[i][0])*(table[i][0]));
    count = count + ((table[i][1])*(table[i][1]));
    count = count + table[i][2];
  }
  return count;
}

/**
 * @author A.J. Peppers
 * @details This program takes in a node containing a two-dimensional table corresponding to the current state of the slide puzzle and generates "neighbors" or positions of the table that can be reached in one move.
 * @param start The starting condition of the table from which neighbors are generated.
 * @date 4-29-22
 */
vector<SlidePuzzleNode*> generateNeighbors(SlidePuzzleNode* start){
  vector<SlidePuzzleNode*> nodes;
  int** table = start->getTable();
  for(int i = 0; i<3; i++){
    for(int j=0; j<3; j++){
      /*If table[i][j] is equal to 0, we are at the open spot in the slide table.  Any potential move of the slide table will involve moving a value
      into this open spot, creating a new open spot at an adjacent location.*/
      if(table[i][j] == 0){
        /*This is the neighbor obtained from moving the tile above the blank spot into the blank spot.*/
        if(i>0){
          int** dup = new int*[3];
          for(int i=0; i<3; i++){
            dup[i] = new int[3];
            for(int j = 0; j < 3; j++){
              dup[i][j] = table[i][j];
            }
          }
          dup[i][j] = dup[i-1][j];
          dup[i-1][j] = 0;
          int dupHash = uHash(dup);
          if(uniqueCheck(dup)){
            uniques[dupHash].push_back(dup);
            SlidePuzzleNode* neighbor = new SlidePuzzleNode(dup);
            nodes.push_back(neighbor);
          }
        }
        /*This is the neighbor obtained from moving the tile below the blank spot into the blank spot.*/
        if(i<2){
          int** dup = new int*[3];
          for(int i=0; i<3; i++){
            dup[i] = new int[3];
            for(int j = 0; j < 3; j++){
              dup[i][j] = table[i][j];
            }
          }
          dup[i][j] = dup[i+1][j];
          dup[i+1][j] = 0;
          int dupHash = uHash(dup);
          if(uniqueCheck(dup)){
            uniques[dupHash].push_back(dup);
            SlidePuzzleNode* neighbor = new SlidePuzzleNode(dup);
            nodes.push_back(neighbor);
          }
        }
        /*This is the neighbor obtained from moving the tile to the left the blank spot into the blank spot.*/
        if(j>0){
          int** dup = new int*[3];
          for(int i=0; i<3; i++){
            dup[i] = new int[3];
            for(int j = 0; j < 3; j++){
              dup[i][j] = table[i][j];
            }
          }
          dup[i][j] = dup[i][j-1];
          dup[i][j-1] = 0;
          int dupHash = uHash(dup);
          if(uniqueCheck(dup)){
            uniques[dupHash].push_back(dup);
            SlidePuzzleNode* neighbor = new SlidePuzzleNode(dup);
            nodes.push_back(neighbor);
          }
        }
        /*This is the neighbor obtained from moving the tile to the right the blank spot into the blank spot.*/
        if(j<2){
          int** dup = new int*[3];
          for(int i=0; i<3; i++){
            dup[i] = new int[3];
            for(int j = 0; j < 3; j++){
              dup[i][j] = table[i][j];
            }
          }
          dup[i][j] = dup[i][j+1];
          dup[i][j+1] = 0;
          int dupHash = uHash(dup);
          if(uniqueCheck(dup)){
            uniques[dupHash].push_back(dup);
            SlidePuzzleNode* neighbor = new SlidePuzzleNode(dup);
            nodes.push_back(neighbor);
          }
        }
        i=3;
        j=3;
      }
    }
  }
  return nodes;
}

/**
 * @author A.J. Peppers
 * @details This program determines if the inputted state of the slide puzzle has already been reached in our breadth-first search (a state is reached if it has been added to the uniques array).
 * @param table The inputted state of the slide puzzle.
 * @date 4-29-22
 */
bool uniqueCheck(int** table){
  int hashValue = uHash(table);
  for(int** unique: uniques[hashValue]){
    int count=0;
    for(int i=0; i<3; i++){
      for(int j=0; j<3; j++){
        if(table[i][j]==unique[i][j]){
          count++;
        }
        /*If a value in the table is different from all of those that have already been reached, it can't have been reached before;
        thus, the given table is unique (it hasn't been reached yet)*/
        else{
          i=3;
          j=3;
        }
      }
    }
    /*If count = 9, this means that all of the values in the inputted table match those of a table that has already been reached.
    Given that we have already reached this table previously but with less steps, it is clear that the route where the table is reached
    again will not the the fastest.*/
    if(count==9){
      return false;
    }
  }
  return true;
}

/**
 * @author A.J. Peppers
 * @details This program calculates the amount of inversions of a given state of the slide puzzle.
 * @param arr The array corresponding to each number in the puzzle (The arr is constructed by modifying the 3x3 2-D array in possibleCheck).
 * @date 4-29-22
 */
int inversionCount(int* arr){
  /*An inversion is where an element in the slide puzzle is either to the right or downward of an element in the slide puzzle with a smaller value.*/
  int inversions = 0;
  for(int i=0; i<8; i++){
    for(int j=i+1; j<9; j++){
      if(arr[i] && arr[j] && (arr[i]>arr[j])){
	inversions++;
      }
    }
  }
  return inversions;
}

/**
 * @author A.J. Peppers
 * @details This program takes in a table corresponding to the starting state of the slide puzzle and determines whether or not it can be solved.
 * @param table The starting condition of the puzzle from which solvability is determined.
 * @date 4-29-22
 */
bool possibleCheck(int** table){
  int* invTable = new int[9];
  int index = 0;
  /*Transform the 2D-array corresponding to table into a 1D-array so that it can be processed by the inversionCount function.*/
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      invTable[index]= table[i][j];
      index++;
    }
  }
  int count = inversionCount(invTable);
  /*If a slide puzzle has an odd number of inversions, it is an unsolvable slide puzzle*/
  return(count%2==0);
}

/**
 * @author A.J. Peppers
 * @details This program takes in a node containing a two-dimensional table corresponding to the start of the slide puzzle and determines the minimum amount of moves necessary to solve the puzzle.
 * @param start The starting condition of the table from which the minimum amount of moves necessary to solve the puzzle will be found.
 * @date 4-29-22
 */
int bfs(SlidePuzzleNode* start){
  queue<SlidePuzzleNode*> q;
  q.push(start);
  while(!q.empty()){
    SlidePuzzleNode* n = q.front();
    /*This if statement is satisfied if we have arrived at the solved puzzle state; it is guaranteed to be arrived at with the least amount of moves
    due to the process of the breadth-first search.*/
    if(n->goal()){
      return n->getDistance();
    }
    q.pop();
    vector<SlidePuzzleNode*> neighbors = generateNeighbors(n);
    /*Each table state equidistant from the initial table state is pushed into the queue at the same 'level'
    (All of the states 1 move away from the start state are pushed, then all of the states that are 2 moves away from the start state,
    and so on).*/
    for(SlidePuzzleNode* neighbor: neighbors){
      int nDist = n->getDistance();
      neighbor->setDist(nDist+1);
      q.push(neighbor);
    }
  }
  /*This return statement will never be reached under the assumption of proper bfs implementation.*/
  return -1;
}
