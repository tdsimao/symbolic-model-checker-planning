//
// Created by thiago on 10/03/16.
//

#include <iostream>
#include "smcp.h"

Cudd  smcp::mgr_;

void smcp::set_mgr(Cudd mgr) {

    smcp::mgr_ = mgr;

}


SymbolicAction::SymbolicAction(const std::string &name)
        : name_(name),
          precondition_(smcp::mgr().bddOne()),
          effect_(smcp::mgr().bddOne()),
          changes_(smcp::mgr().bddOne()){

}


BDD SymbolicAction::precondition() {
    std::cout << "Get precondition" << std::endl;
    return precondition_;
}

void SymbolicAction::set_precondition(BDD prec) {
    std::cout << "Set precondition" << std::endl;
    precondition_ = prec;
}

void SymbolicAction::set_effect(BDD eff) {
    std::cout << "Set effect" << std::endl;
    effect_ = eff;
    // TODO define changes
    changes_ = smcp::mgr().bddOne();
//    ExistAbstract

}

BDD SymbolicAction::effect() {
    std::cout << "Get effect" << std::endl;
    return effect_;
}

BDD SymbolicAction::changes() {
    std::cout << "Get changes" << std::endl;
    return changes_;
}

std::string  SymbolicAction::name() {
    return name_;
}
