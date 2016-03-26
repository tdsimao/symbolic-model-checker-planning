//
// Created by thiago on 10/03/16.
//

#include <iostream>
#include "smcp.h"

Cudd smcp::mgr_;

void smcp::set_mgr(Cudd mgr) {
    smcp::mgr_ = mgr;
}


SymbolicAction::SymbolicAction(const std::string &name, BDD prec, BDD eff) :
        name_(name),
        precondition_(prec),
        effect_(eff) {
    update_changes();
}

SymbolicAction::SymbolicAction(const std::string &name) :
        SymbolicAction(name, BDD_ONE, BDD_ONE) { }

SymbolicAction::SymbolicAction() :
        SymbolicAction("") { }


BDD SymbolicAction::precondition() {
    return precondition_;
}

void SymbolicAction::set_precondition(BDD prec) {
    precondition_ = prec;
}

void SymbolicAction::set_effect(BDD eff) {
    effect_ = eff;
    update_changes();

}

BDD SymbolicAction::effect() {
    return effect_;
}

BDD SymbolicAction::changes() {
    return changes_;
}

void SymbolicAction::update_changes() {
    changes_ = effect_.Support();
}


std::string  SymbolicAction::name() {
    return name_;
}

void SymbolicAction::set_name(std::string name) {
    name_ = name;
}


BDD weak_pre_image(SymbolicAction * action, BDD world_state) {
    BDD result = action->effect() & world_state;
    result = result.ExistAbstract(action->changes());
    result &= action->precondition();
    return result;
}

BDD strong_pre_image(SymbolicAction * action, BDD world_state) {
    BDD result = ~action->effect() | world_state;
    result = result.UnivAbstract(action->changes());
    result &= action->precondition();
    return result;
}


BDD pre_image(SymbolicActionList actions, BDD world_state, BDD(* f)(SymbolicAction *, BDD)) {
    BDD result = BDD_ZERO;
    for (SymbolicActionList::const_iterator ei = actions.begin(); ei != actions.end(); ++ei)
        result |= f(*ei, world_state);
    return result;
}


BDD weak_pre_image_actions(SymbolicActionList actions, BDD world_state ) {
    return pre_image(actions, world_state, weak_pre_image);
}

BDD strong_pre_image_actions(SymbolicActionList actions, BDD world_state) {
    return pre_image(actions, world_state, strong_pre_image);
}

BDD least_fixed_point(SymbolicActionList actions, BDD G, BDD constraints,  BDD (*f)(SymbolicActionList, BDD)) {
    BDD X = BDD_ZERO;
    BDD Y = BDD_ONE;
    G = G & constraints;
    while (X != Y){
        Y = X;
        X = G | (f(actions, X) & constraints) ;
    }
    return X;
}

BDD weak_regression(SymbolicActionList actions, BDD goal, BDD constraints) {
    return least_fixed_point(actions, goal, constraints, weak_pre_image_actions);
}

BDD strong_regression(SymbolicActionList actions, BDD goal, BDD constraints) {
    return least_fixed_point(actions, goal, constraints, strong_pre_image_actions);
}
