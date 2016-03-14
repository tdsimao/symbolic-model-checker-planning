#include <iostream>

using namespace std;

#include "smcp.h"
#include "cuddObj.hh"
#include "gtest/gtest.h"
#include <map>


int main() {
    Cudd test_mgr_(0, 0);
    BDD one = test_mgr_.bddOne();
    smcp::set_mgr(test_mgr_);
#define N 8
    std::map<string, BDD> v;
    string fluente[N] = {"spare_in_n1", "spare_in_n2", "spare_in_n3", "vehicle_at_n1", "vehicle_at_n2", "vehicle_at_n3",
                        "not_flattire_", "_"};
    int i = 0;
    for(int i = 0; i<N; i++)
        v[fluente[i]] = test_mgr_.bddVar(i);


    SymbolicAction action = SymbolicAction("teste");


    action.set_effect(v["spare_in_n1"]);
    action.set_precondition(one);
    BDD e = action.effect();

    BDD p = action.precondition();
    BDD c = action.changes();

    cout << "Hello, World!" << endl;

    return 0;
}