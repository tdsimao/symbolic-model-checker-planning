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


BDD weak_pre_image(SymbolicAction action, BDD world_state) {
    BDD result = action.effect() & world_state;
    result = result.ExistAbstract(action.changes());
    result &= action.precondition();
    return result;
}

BDD strong_pre_image(SymbolicAction action, BDD world_state) {
    BDD result = ~action.effect() | world_state;
    result = result.ExistAbstract(action.changes());
    result &= action.precondition();
    return result;
}