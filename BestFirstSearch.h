//
// Created by renana on 1/7/19.
//

#ifndef MILESTONE2_BESTFIRSTSEARCH_H
#define MILESTONE2_BESTFIRSTSEARCH_H


#include "Searcher.h"
#include "Point.h"
#include <iostream>
#include <queue>

template<class T>
class BestFirstSearch : public Searcher<T> {
    class Comp {
    public:
        bool operator()(State<T>* left, State<T>* right) {
            return (left->getCost()) > (right->getCost());
        }
    };

public:
    T search(Searchable<T> searchable) {
        State<T> *current;
        vector<State<T> *> neighbors;
        priority_queue<State<T>*, vector<State<T>*>, Comp> open;
        open.push(searchable.getInitialState());
        vector<State<T> *> backup = {searchable.getInitialState()};
        vector<State<T> *> closed;

        while (!open.empty()) {
            current = open.top();
            open.pop();
            closed.push_back(current);
            if (current->Equals(searchable.getGoalState())) {
                // todo  return get path
            }
            neighbors = searchable.getNeighbors(current);
            for (State<T> *neighbor : neighbors) {
                //first time encountering state
                if (!inOpen(open, neighbor) && !inClosed(closed, neighbor)) {
                    neighbor->setComeFrom(current);
                    neighbor->addCost(current->getTrailCost());
                    open.push(neighbor);
                    backup.push_back(neighbor);
                    //can improve path
                } else if (current->getTrailCost() + neighbor->getCost() < neighbor->getTrailCost()) {
                    //todo ??????????????????????
                    //in closed
                    if (!inOpen(neighbor)) {
                        deleteFromClose(closed);
                        open.push(neighbor);
                    }
                    neighbor->setTrailCost(current->getTrailCost() + neighbor->getCost());
                    neighbor->setComeFrom(current);
                    open = updatePriorityQ(open);
                }
            }
        }
    }

    bool inOpen(priority_queue<State<T> *, vector<State<T> *>, Comp> p, State<T> *current) {
        while (!p.empty()) {
            if (current->Equals(p.top())) { return true; }
            p.pop();
        }
        return false;
    }

    bool inClosed(vector<State<T>> closed, State<T> current) {
        for (auto state:closed) {
            if (current.Equals(state)) {
                return true;
            }
        }
        return false;
    }

    priority_queue<State<T> *, vector<State<T> *>, Comp> updatePriorityQ(priority_queue<State<T> *,
            vector<State<T> *>, Comp> p ){
        priority_queue<State<T> *, vector<State<T> *>, Comp> newQ;
        for (State<T> *neighbor : p) {
            newQ.push(p);
        }
        return newQ;
    }

    string getPath(vector<State<T> *> closed, State<T>* goal) {
        State<T>* current = goal;
        string path;
        while(current->getComeFrom() != nullptr) {
            path +=
        }

    }

    void deleteFromClose(vector<State<T> *> &closed, State<T>* del) {
        for (State<T>* state : closed) {
            if (state->Equals(del)) {
                closed.erase(state);
            }
        }
    }




};

#endif //MILESTONE2_BESTFIRSTSEARCH_H