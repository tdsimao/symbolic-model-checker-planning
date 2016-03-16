#include "gtest/gtest.h"
#include "smcp.h"

using namespace std;


class SymbolicActionTest : public ::testing::Test {

protected:
    BDD bdd_var[3];
    SymbolicActionList actions;

    virtual void SetUp() {
        Cudd test_mgr_(0, 0);
        smcp::set_mgr(test_mgr_);

        for (int i = 0; i < 3; i++) {
            bdd_var[i] = smcp::mgr().bddVar();
        }

        actions.push_back(new SymbolicAction("a1"));
        actions.push_back(new SymbolicAction());
        actions.push_back(new SymbolicAction("a3", bdd_var[0], bdd_var[1]));
        actions.push_back(new SymbolicAction("a4", bdd_var[0], bdd_var[1] & bdd_var[2]));
        actions.push_back(new SymbolicAction("a5", bdd_var[0], bdd_var[1] | bdd_var[2]));
    }
};


TEST_F(SymbolicActionTest, ConstructorWithName) {
    EXPECT_EQ("a1", actions[0]->name());
    EXPECT_EQ(BDD_ONE, actions[0]->precondition());
}

TEST_F(SymbolicActionTest, ConstructorWithoutName) {
    EXPECT_EQ("", actions[1]->name());
}

TEST_F(SymbolicActionTest, ConstructorWithPrecAndEffect) {
    EXPECT_EQ("a3", actions[2]->name());
    EXPECT_EQ(bdd_var[0], actions[2]->precondition());
    EXPECT_EQ(bdd_var[1], actions[2]->effect());
}

TEST_F(SymbolicActionTest, TestChanges) {
    EXPECT_EQ(BDD_ONE, actions[0]->changes());
    EXPECT_EQ(BDD_ONE, actions[1]->changes());
    EXPECT_EQ(bdd_var[1], actions[2]->changes());
    EXPECT_EQ(bdd_var[1] & bdd_var[2], actions[3]->changes());
    EXPECT_EQ(bdd_var[1] & bdd_var[2], actions[4]->changes());
}

TEST_F(SymbolicActionTest, SetName) {
    actions[1]->set_name("a1");
    EXPECT_EQ("a1", actions[1]->name());
    actions[1]->set_name("");
}


TEST_F(SymbolicActionTest, WeakPreImageWorldTrue) {
    BDD world = BDD_ONE;
    BDD result = weak_pre_image(actions[0], world);
    EXPECT_EQ(actions[0]->precondition(), result);

    result = weak_pre_image(actions[1], world);
    EXPECT_EQ(actions[1]->precondition(), result);

    result = weak_pre_image(actions[2], world);
    EXPECT_EQ(actions[2]->precondition(), result);

    result = weak_pre_image(actions[3], world);
    EXPECT_EQ(actions[3]->precondition(), result);

    result = weak_pre_image(actions[4], world);
    EXPECT_EQ(actions[4]->precondition(), result);
}

TEST_F(SymbolicActionTest, WeakPreImageWorldFalse) {
    BDD world = BDD_ZERO;
    BDD result = weak_pre_image(actions[0], world);
    EXPECT_EQ(BDD_ZERO, result);

    result = weak_pre_image(actions[1], world);
    EXPECT_EQ(BDD_ZERO, result);

    result = weak_pre_image(actions[2], world);
    EXPECT_EQ(BDD_ZERO, result);

    result = weak_pre_image(actions[3], world);
    EXPECT_EQ(BDD_ZERO, result);

    result = weak_pre_image(actions[4], world);
    EXPECT_EQ(BDD_ZERO, result);
}


TEST_F(SymbolicActionTest, WeakPreNoPreconditionNoEffect) {
    BDD world = bdd_var[1];
    BDD result = weak_pre_image(actions[0], world);
    EXPECT_EQ(world, result);

    world = bdd_var[1] & bdd_var[2];
    result = weak_pre_image(actions[0], world);
    EXPECT_EQ(world, result);

    world = bdd_var[1] | bdd_var[2];
    result = weak_pre_image(actions[0], world);
    EXPECT_EQ(world, result);
}

TEST_F(SymbolicActionTest, WeakPreImageSimpleEffect) {
    BDD world = bdd_var[1] & bdd_var[2];
    BDD result = weak_pre_image(actions[2], world);
    EXPECT_EQ(bdd_var[0] & bdd_var[2], result);

    world = bdd_var[1] | bdd_var[2];
    result = weak_pre_image(actions[2], world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] & ~bdd_var[2];
    result = weak_pre_image(actions[2], world);
    EXPECT_EQ(bdd_var[0] & ~bdd_var[2], result);

    world = ~bdd_var[1] & bdd_var[2];
    result = weak_pre_image(actions[2], world);
    EXPECT_EQ(BDD_ZERO, result);
}


TEST_F(SymbolicActionTest, WeakPreImageConjunction) {
    BDD world = bdd_var[1] & bdd_var[2];
    BDD result = weak_pre_image(actions[3], world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] | bdd_var[2];
    result = weak_pre_image(actions[3], world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] & ~bdd_var[2];
    result = weak_pre_image(actions[3], world);
    EXPECT_EQ(BDD_ZERO, result);

    world = ~bdd_var[1] & bdd_var[2];
    result = weak_pre_image(actions[3], world);
    EXPECT_EQ(BDD_ZERO, result);
}


TEST_F(SymbolicActionTest, WeakPreImageDisjunction) {
    BDD world = bdd_var[1] & bdd_var[2];
    BDD result = weak_pre_image(actions[4], world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] | bdd_var[2];
    result = weak_pre_image(actions[4], world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] & ~bdd_var[2];
    result = weak_pre_image(actions[4], world);
    EXPECT_EQ(bdd_var[0], result);

    world = ~bdd_var[1] & bdd_var[2];
    result = weak_pre_image(actions[4], world);
    EXPECT_EQ(bdd_var[0], result);
}


TEST_F(SymbolicActionTest, StrongPreImageWorldTrue) {
    BDD world = BDD_ONE;
    BDD result = strong_pre_image(actions[0], world);
    EXPECT_EQ(actions[0]->precondition(), result);

    result = strong_pre_image(actions[1], world);
    EXPECT_EQ(actions[1]->precondition(), result);

    result = strong_pre_image(actions[2], world);
    EXPECT_EQ(actions[2]->precondition(), result);

    result = strong_pre_image(actions[3], world);
    EXPECT_EQ(actions[3]->precondition(), result);

    result = strong_pre_image(actions[4], world);
    EXPECT_EQ(actions[4]->precondition(), result);
}

TEST_F(SymbolicActionTest, StrongPreImageWorldFalse) {
    BDD world = BDD_ZERO;
    BDD result = strong_pre_image(actions[0], world);
    EXPECT_EQ(BDD_ZERO, result);

    result = strong_pre_image(actions[1], world);
    EXPECT_EQ(BDD_ZERO, result);

    result = strong_pre_image(actions[2], world);
    EXPECT_EQ(BDD_ZERO, result);

    result = strong_pre_image(actions[3], world);
    EXPECT_EQ(BDD_ZERO, result);

    result = strong_pre_image(actions[4], world);
    EXPECT_EQ(BDD_ZERO, result);
}

TEST_F(SymbolicActionTest, StrongPreImageSimpleEffect) {
    BDD world = bdd_var[1] & bdd_var[2];
    BDD result = strong_pre_image(actions[2], world);
    EXPECT_EQ(bdd_var[0] & bdd_var[2], result);

    world = bdd_var[1] | bdd_var[2];
    result = strong_pre_image(actions[2], world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] & ~bdd_var[2];
    result = strong_pre_image(actions[2], world);
    EXPECT_EQ(bdd_var[0] & ~bdd_var[2], result);

    world = ~bdd_var[1] & bdd_var[2];
    result = strong_pre_image(actions[2], world);
    EXPECT_EQ(BDD_ZERO, result);
}


TEST_F(SymbolicActionTest, StrongPreImageConjunction) {
    BDD world = bdd_var[1] & bdd_var[2];
    BDD result = strong_pre_image(actions[3], world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] | bdd_var[2];
    result = strong_pre_image(actions[3], world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] & ~bdd_var[2];
    result = strong_pre_image(actions[3], world);
    EXPECT_EQ(BDD_ZERO, result);

    world = ~bdd_var[1] & bdd_var[2];
    result = strong_pre_image(actions[3], world);
    EXPECT_EQ(BDD_ZERO, result);
}


TEST_F(SymbolicActionTest, StrongPreImageDisjunction) {
    BDD world = bdd_var[1] & bdd_var[2];
    BDD result = strong_pre_image(actions[4], world);
    EXPECT_EQ(BDD_ZERO, result);

    world = bdd_var[1] | bdd_var[2];
    result = strong_pre_image(actions[4], world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] & ~bdd_var[2];
    result = strong_pre_image(actions[4], world);
    EXPECT_EQ(BDD_ZERO, result);

    world = ~bdd_var[1] & bdd_var[2];
    result = strong_pre_image(actions[4], world);
    EXPECT_EQ(BDD_ZERO, result);
}


TEST_F(SymbolicActionTest, WeakPreImageSet) {
    BDD world = bdd_var[1] & bdd_var[2];
    BDD result = weak_pre_image(actions, world);
    EXPECT_EQ(bdd_var[0] | bdd_var[1] & bdd_var[2], result);
}


TEST_F(SymbolicActionTest, StrongPreImageSet) {
    BDD world = bdd_var[1] & bdd_var[2];
    BDD result = strong_pre_image(actions, world);
    EXPECT_EQ(bdd_var[0] | bdd_var[1] & bdd_var[2], result);

    SymbolicActionList actionList;
    actionList.push_back(actions[2]);
    actionList.push_back(actions[4]);
    result = strong_pre_image(actionList, world);
    EXPECT_EQ(bdd_var[0] & bdd_var[2], result);
}


class TriangleTireWorldTest : public ::testing::Test {

protected:

    BDD spare_in_n1, spare_in_n2, spare_in_n3, vehicle_at_n1, vehicle_at_n2, vehicle_at_n3, not_flattire_, empty;
    SymbolicAction *change_tire_n1, *change_tire_n2, *change_tire_n3, *move_n1_n2, *move_n2_n3;

    virtual void SetUp() {
//    TriangleTireWorldTest() {
        Cudd test_mgr = Cudd(0, 0);
        smcp::set_mgr(test_mgr);
//        test_mgr = smcp::mgr();

        std::map<string, BDD> v;
        string fluente[8] = {"spare_in_n1", "spare_in_n2", "spare_in_n3", "vehicle_at_n1", "vehicle_at_n2",
                             "vehicle_at_n3",
                             "not_flattire_", "_empty"};
        for (int i = 0; i < 8; i++)
            v[fluente[i]] = test_mgr.bddVar();


        spare_in_n1 = v["spare_in_n1"];
        spare_in_n2 = v["spare_in_n2"];
        spare_in_n3 = v["spare_in_n3"];
        vehicle_at_n1 = v["vehicle_at_n1"];
        vehicle_at_n2 = v["vehicle_at_n2"];
        vehicle_at_n3 = v["vehicle_at_n3"];
        not_flattire_ = v["not_flattire_"];
        empty = v["_empty"];


        change_tire_n1 =
                new SymbolicAction("change_tire_n1", spare_in_n1 & vehicle_at_n1,
                                   (not_flattire_ & ~spare_in_n1) | (spare_in_n1));

        change_tire_n2 =
                new SymbolicAction("change_tire_n2", spare_in_n2 & vehicle_at_n2,
                                   (~spare_in_n2 & not_flattire_) | (spare_in_n2));
        change_tire_n3 =
                new SymbolicAction("change_tire_n3", spare_in_n3 & vehicle_at_n3,
                                   (~spare_in_n3 & not_flattire_) | (spare_in_n3));

        move_n1_n2 =
                new SymbolicAction("move_n1_n2", not_flattire_ & vehicle_at_n1,
                                   (~vehicle_at_n1 & vehicle_at_n2 & ~not_flattire_) |
                                   (~vehicle_at_n1 & vehicle_at_n2 & empty));


        move_n2_n3 =
                new SymbolicAction("move_n2_n3", not_flattire_ & vehicle_at_n2,
                                   (~vehicle_at_n2 & vehicle_at_n3 & ~not_flattire_) |
                                   (~vehicle_at_n2 & vehicle_at_n3 & empty));

    }

//    virtual ~FooTest() {
//        }


    virtual void TearDown() { }


};


// TODO implement tests

TEST_F(TriangleTireWorldTest, EmptyWeakPreImage) {
    BDD result = weak_pre_image(move_n1_n2, BDD_ZERO);
    EXPECT_EQ(BDD_ZERO, result);
}



