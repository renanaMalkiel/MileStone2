//
// Created by renana on 1/7/19.
//

#ifndef MILESTONE2_BESTFIRSTSEARCH_H
#define MILESTONE2_BESTFIRSTSEARCH_H


#include "Searcher.h"
#include "Point.h"
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

template<class T>
class BestFirstSearch : public Searcher<T> {
    class Comp {
    public:
        bool operator()(State<T>* left, State<T>* right) {
            return (left->getTrailCost()) > (right->getTrailCost());
        }
    };

public:
    string search(Searchable<T>* searchable) override {
        this->searchable = searchable;
        State<T> *current;
        vector<State<T> *> neighbors;
        priority_queue<State<T>*, vector<State<T>*>, Comp> open;
        open.push(searchable->getInitialState());
        vector<State<T> *> closed;

        while (!open.empty()) {
            current = open.top();
            open.pop();
            closed.push_back(current);
            this->numOfNodesEvaluated++;
            if (current->Equals(searchable->getGoalState())) {
                cout<<"num of nodes: " << this->numOfNodesEvaluated<<endl;
                this->numOfNodesEvaluated++;
                return searchable->getPath();
            }
            neighbors = searchable->getNeighbors(current);
            for (State<T> *neighbor : neighbors) {
                //first time encountering state
                if (!inOpen(open, neighbor) && !inClosed(closed, neighbor)) {
                    neighbor->setComeFrom(current);
                    neighbor->addCost(current->getTrailCost());
                    open.push(neighbor);
                    continue;
                    //neighbor is either in open or closed and - can improve path
                }else if (inClosed(closed, neighbor)){
                    continue;
                }
                else if (current->getTrailCost() + neighbor->getCost() < neighbor->getTrailCost()) {
                    neighbor->setTrailCost(current->getTrailCost() + neighbor->getCost());
                    neighbor->setComeFrom(current);
                    open = updatePriorityQ(open);
                }
            }
        }
        searchable->getGoalState()->setTrailCost(-1);
        return to_string(-1);
    }

    bool inOpen(priority_queue<State<T> *, vector<State<T> *>, Comp> p, State<T> *current) {
        while (!p.empty()) {
            //found state in priority/-queue
            if (current->Equals(p.top())) { return true; }
            p.pop();
        }
        return false;
    }

    bool inClosed(vector<State<T>*> closed, State<T>* current) {
        for (auto state:closed) {
            if (current->Equals(state)) {
                return true;
            }
        }
        return false;
    }

    priority_queue<State<T>*, vector<State<T> *>, Comp> updatePriorityQ(priority_queue<State<T> *,
            vector<State<T> *>, Comp> p ){
        priority_queue<State<T> *, vector<State<T> *>, Comp> newQ;
        while (!p.empty()) {
            newQ.push(p.top());
            p.pop();
        }
        return newQ;
    }

    /*  void deleteFromClose(vector<State<T>*> &closed, State<T>* del) {
         for (State<T>* state=closed.begin(); state != closed.end(); state++) {
              if (state->Equals(del)) {
                  closed.erase(state);
              }
          }
      }*/
/*    string getPath(vector<State<T> *> closed, State<T> * goal, State<T> * initial){
        State<T> * current = goal;
        string path;
        //end when at the father
        while (current->getComaFrom() != nullptr) {
            for (State<T> *state:closed) {
                if (state->getComaFrom() != nullptr) {
                    //find father node of current
                    if (current->getComaFrom()->Equals(state)) {
                        path += current->getState().move(state->getState());
                        break;
                    }
                }
            }
            current = current->getComaFrom();
            //when the current is the initial state
            if (current->getComaFrom()->Equals(initial) ){
                break;
            }
        }
        //find the last move to the initial state
        path += current->getState().move(initial->getState());
        reverse(path.begin(), path.end());
        return path;
    }*/



};

#endif //MILESTONE2_BESTFIRSTSEARCH_H




