#include "cuddObj.hh"


#define BDD_ZERO smcp::mgr().bddZero()
#define BDD_ONE smcp::mgr().bddOne()

class smcp {
    static Cudd mgr_;
public:
    static void set_mgr(Cudd mgr);
    static Cudd mgr() { return mgr_; }
};



class SymbolicAction {
private:
    std::string name_;
    BDD precondition_;
    BDD effect_;
    BDD changes_;
    void update_changes();
public:
    SymbolicAction();
    SymbolicAction( const std::string& name );
    SymbolicAction( const std::string& name, BDD prec, BDD eff );

    std::string name();
    void set_name(std::string name);
    BDD precondition();
    void set_precondition(BDD prec);
    BDD effect();
    void set_effect(BDD eff);
    BDD changes();

};


class SymbolicActionList : public std::vector<SymbolicAction *>{};


BDD weak_pre_image(SymbolicAction * action, BDD world_state);

BDD strong_pre_image(SymbolicAction * action, BDD world_state);


BDD weak_pre_image(SymbolicActionList actions, BDD world_state);
BDD strong_pre_image(SymbolicActionList actions, BDD world_state);

