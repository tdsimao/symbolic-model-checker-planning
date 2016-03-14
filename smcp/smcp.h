#include "cuddObj.hh"


class smcp {
    static Cudd mgr_;
public:
    static void set_mgr(Cudd mgr);
    static Cudd mgr() { return mgr_; }
};



class SymbolicAction {
    std::string name_;
    BDD precondition_;
    BDD effect_;
    BDD changes_;
public:
    SymbolicAction( const std::string& name );
    SymbolicAction();

    std::string name();
    void set_name(std::string name);
    BDD precondition();
    void set_precondition(BDD prec);
    BDD effect();
    void set_effect(BDD eff);
    BDD changes();
};


