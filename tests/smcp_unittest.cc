#include "gtest/gtest.h"
#include "smcp.h"

using namespace std;

#include <map>


class SymbolicActionTest : public ::testing::Test {

protected:

    SymbolicActionTest() {
        a1 = SymbolicAction("a1");
        a2 = SymbolicAction();
        a3 = SymbolicAction("a3", bdd_var[0], bdd_var[1]);
        a4 = SymbolicAction("a4", bdd_var[0], bdd_var[1] & bdd_var[2]);
        a5 = SymbolicAction("a4", bdd_var[0], bdd_var[1] | bdd_var[2]);
    }


//    virtual void SetUp() {
//    }
    static void SetUpTestCase() {
        test_mgr = smcp::mgr();

        for (int i = 0; i < 3; i++) {
            bdd_var[i] = test_mgr.bddVar();
        }


    }

//    virtual void TearDown() {
//    }

    static Cudd test_mgr;

    SymbolicAction a1, a2, a3, a4, a5;
    static BDD bdd_var[3];
};


Cudd SymbolicActionTest::test_mgr;
BDD SymbolicActionTest::bdd_var[];


TEST_F(SymbolicActionTest, ConstructorWithName) {
    EXPECT_EQ("a1", a1.name());
    EXPECT_EQ(test_mgr.bddOne(), a1.precondition());
}

TEST_F(SymbolicActionTest, ConstructorWithoutName) {
    EXPECT_EQ("", a2.name());
}

TEST_F(SymbolicActionTest, ConstructorWithPrecAndEffect) {
    EXPECT_EQ("a3", a3.name());
    EXPECT_EQ(bdd_var[0], a3.precondition());
    EXPECT_EQ(bdd_var[1], a3.effect());
}

TEST_F(SymbolicActionTest, TestChanges) {
    EXPECT_EQ(BDD_ONE, a1.changes());
    EXPECT_EQ(BDD_ONE, a2.changes());
    EXPECT_EQ(bdd_var[1], a3.changes());
    EXPECT_EQ(bdd_var[1] & bdd_var[2], a4.changes());
    EXPECT_EQ(bdd_var[1] & bdd_var[2], a5.changes());
}

TEST_F(SymbolicActionTest, SetName) {
    a2.set_name("a2");
    EXPECT_EQ("a2", a2.name());
}


TEST_F(SymbolicActionTest, WeakPreImageWorldTrue) {
    BDD world = BDD_ONE;
    BDD result = weak_pre_image(a1, world);
    EXPECT_EQ(a1.precondition(), result);

    result = weak_pre_image(a2, world);
    EXPECT_EQ(a2.precondition(), result);

    result = weak_pre_image(a3, world);
    EXPECT_EQ(a3.precondition(), result);

    result = weak_pre_image(a4, world);
    EXPECT_EQ(a4.precondition(), result);

    result = weak_pre_image(a5, world);
    EXPECT_EQ(a5.precondition(), result);
}

TEST_F(SymbolicActionTest, WeakPreImageWorldFalse) {
    BDD world = BDD_ZERO;
    BDD result = weak_pre_image(a1, world);
    EXPECT_EQ(BDD_ZERO, result);

    result = weak_pre_image(a2, world);
    EXPECT_EQ(BDD_ZERO, result);

    result = weak_pre_image(a3, world);
    EXPECT_EQ(BDD_ZERO, result);

    result = weak_pre_image(a4, world);
    EXPECT_EQ(BDD_ZERO, result);

    result = weak_pre_image(a5, world);
    EXPECT_EQ(BDD_ZERO, result);
}


TEST_F(SymbolicActionTest, WeakPreNoPreconditionNoEffect) {
    BDD world = bdd_var[1];
    BDD result = weak_pre_image(a1, world);
    EXPECT_EQ(world, result);

    world = bdd_var[1] & bdd_var[2];
    result = weak_pre_image(a1, world);
    EXPECT_EQ(world, result);

    world = bdd_var[1] | bdd_var[2];
    result = weak_pre_image(a1, world);
    EXPECT_EQ(world, result);
}

TEST_F(SymbolicActionTest, WeakPreImageSimpleEffect) {
    BDD world = bdd_var[1] & bdd_var[2];
    BDD result = weak_pre_image(a3, world);
    EXPECT_EQ(bdd_var[0] & bdd_var[2], result);

    world = bdd_var[1] | bdd_var[2];
    result = weak_pre_image(a3, world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] & ~bdd_var[2];
    result = weak_pre_image(a3, world);
    EXPECT_EQ(bdd_var[0] & ~bdd_var[2], result);

    world = ~bdd_var[1] & bdd_var[2];
    result = weak_pre_image(a3, world);
    EXPECT_EQ(BDD_ZERO, result);
}


TEST_F(SymbolicActionTest, WeakPreImageConjunction) {
    BDD world = bdd_var[1] & bdd_var[2];
    BDD result = weak_pre_image(a4, world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] | bdd_var[2];
    result = weak_pre_image(a4, world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] & ~bdd_var[2];
    result = weak_pre_image(a4, world);
    EXPECT_EQ(BDD_ZERO, result);

    world = ~bdd_var[1] & bdd_var[2];
    result = weak_pre_image(a4, world);
    EXPECT_EQ(BDD_ZERO, result);
}


TEST_F(SymbolicActionTest, WeakPreImageDisjunction) {
    BDD world = bdd_var[1] & bdd_var[2];
    BDD result = weak_pre_image(a5, world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] | bdd_var[2];
    result = weak_pre_image(a5, world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] & ~bdd_var[2];
    result = weak_pre_image(a5, world);
    EXPECT_EQ(bdd_var[0], result);

    world = ~bdd_var[1] & bdd_var[2];
    result = weak_pre_image(a5, world);
    EXPECT_EQ(bdd_var[0], result);
}



TEST_F(SymbolicActionTest, StrongPreImageWorldTrue) {
    BDD world = BDD_ONE;
    BDD result = strong_pre_image(a1, world);
    EXPECT_EQ(a1.precondition(), result);

    result = strong_pre_image(a2, world);
    EXPECT_EQ(a2.precondition(), result);

    result = strong_pre_image(a3, world);
    EXPECT_EQ(a3.precondition(), result);

    result = strong_pre_image(a4, world);
    EXPECT_EQ(a4.precondition(), result);

    result = strong_pre_image(a5, world);
    EXPECT_EQ(a5.precondition(), result);
}

TEST_F(SymbolicActionTest, StrongPreImageWorldFalse) {
    BDD world = BDD_ZERO;
    BDD result = strong_pre_image(a1, world);
    EXPECT_EQ(BDD_ZERO, result);

    result = strong_pre_image(a2, world);
    EXPECT_EQ(BDD_ZERO, result);

    result = strong_pre_image(a3, world);
    EXPECT_EQ(BDD_ZERO, result);

    result = strong_pre_image(a4, world);
    EXPECT_EQ(BDD_ZERO, result);

    result = strong_pre_image(a5, world);
    EXPECT_EQ(BDD_ZERO, result);
}

TEST_F(SymbolicActionTest, StrongPreImageSimpleEffect) {
    BDD world = bdd_var[1] & bdd_var[2];
    BDD result = strong_pre_image(a3, world);
    EXPECT_EQ(bdd_var[0] & bdd_var[2], result);

    world = bdd_var[1] | bdd_var[2];
    result = strong_pre_image(a3, world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] & ~bdd_var[2];
    result = strong_pre_image(a3, world);
    EXPECT_EQ(bdd_var[0] & ~bdd_var[2], result);

    world = ~bdd_var[1] & bdd_var[2];
    result = strong_pre_image(a3, world);
    EXPECT_EQ(BDD_ZERO, result);
}


TEST_F(SymbolicActionTest, StrongPreImageConjunction) {
    BDD world = bdd_var[1] & bdd_var[2];
    BDD result = strong_pre_image(a4, world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] | bdd_var[2];
    result = strong_pre_image(a4, world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] & ~bdd_var[2];
    result = strong_pre_image(a4, world);
    EXPECT_EQ(BDD_ZERO, result);

    world = ~bdd_var[1] & bdd_var[2];
    result = strong_pre_image(a4, world);
    EXPECT_EQ(BDD_ZERO, result);
}


TEST_F(SymbolicActionTest, StrongPreImageDisjunction) {
    BDD world = bdd_var[1] & bdd_var[2];
    BDD result = strong_pre_image(a5, world);

    //TODO think which is the expected result
    EXPECT_EQ(bdd_var[0] & bdd_var[1] & bdd_var[2], result);
    // EXPECT_NE(BDD_ZERO, result);

    world = bdd_var[1] | bdd_var[2];
    result = strong_pre_image(a5, world);
    EXPECT_EQ(bdd_var[0], result);

    world = bdd_var[1] & ~bdd_var[2];
    result = strong_pre_image(a5, world);
    EXPECT_EQ(BDD_ZERO, result);

    world = ~bdd_var[1] & bdd_var[2];
    result = strong_pre_image(a5, world);
    EXPECT_EQ(BDD_ZERO, result);
}

class TriangleTireWorldTest : public ::testing::Test {

protected:

    TriangleTireWorldTest() {
//        test_mgr = Cudd(0,0);
//        smcp::set_mgr(test_mgr);
        test_mgr = smcp::mgr();

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
                SymbolicAction("change_tire_n1", spare_in_n1 & vehicle_at_n1,
                               (not_flattire_ & ~spare_in_n1) | (spare_in_n1));

        change_tire_n2 =
                SymbolicAction("change_tire_n2", spare_in_n2 & vehicle_at_n2,
                               (~spare_in_n2 & not_flattire_) | (spare_in_n2));
        change_tire_n3 =
                SymbolicAction("change_tire_n3", spare_in_n3 & vehicle_at_n3,
                               (~spare_in_n3 & not_flattire_) | (spare_in_n3));
//
//        move_n1_n2 =
//                SymbolicAction("move_n1_n2", not_flattire_ & vehicle_at_n1,
//                               (~vehicle_at_n1 & vehicle_at_n2 & ~not_flattire_) | (~vehicle_at_n1 & vehicle_at_n2 & empty));


        move_n2_n3 = SymbolicAction("move_n2_n3", not_flattire_ & vehicle_at_n2,
                                    ~vehicle_at_n2 & vehicle_at_n3 & ((~not_flattire_) | empty)
        );
        move_n2_n3 = SymbolicAction("move_n2_n3", not_flattire_ & vehicle_at_n2,
                                    (~vehicle_at_n2 & vehicle_at_n3 & ~not_flattire_) |
                                    (~vehicle_at_n2 & vehicle_at_n3 & empty));

    }

//    virtual ~FooTest() {
//        }

    virtual void SetUp() { }

    virtual void TearDown() { }

    static Cudd test_mgr;

    BDD spare_in_n1, spare_in_n2, spare_in_n3, vehicle_at_n1, vehicle_at_n2, vehicle_at_n3, not_flattire_, empty;
    SymbolicAction change_tire_n1, change_tire_n2, change_tire_n3, move_n1_n2, move_n2_n3;


};


// TODO implement tests
Cudd TriangleTireWorldTest::test_mgr;

TEST_F(TriangleTireWorldTest, EmptyWeakPreImage) {
    BDD result = weak_pre_image(move_n1_n2, test_mgr.bddZero());
    EXPECT_EQ(smcp::mgr().bddZero(), result);
}



