//
// Created by yoav on 03/12/16.
//
#include "gtest/gtest.h"
#include "../src/TaxiCenter.h"
#include "../src/LuxuryCab.h"





/*
 * the method checks the addDriver method.
 * an instance of taxiCenter is created, then a Driver instance is being creaed.
 * the driver instance is added to the taxicenter instance and if the taxicenter instance has an empty list of
 * drivers then it means something went wronf with the adding driver method.
 * also, there is a check for the map that holds some proper values- after the driver is added, we extract it
 * from the map and checks that its values are as they should be.
 */

TEST(TaxiCenterTest, addDriverTest){
    TaxiCenter t;
    Driver* d =new Driver(123, 32, 'M');
    t.addDriver(d);
    EXPECT_EQ(t.getDriversMap().empty(), false)
                        <<"the addDriver method had failed there should have been a driver ";
    EXPECT_EQ(t.getDriversMap()[123]->getAge(),32)
                        <<"the addDriver method had failed there should have been a driver"
                        "with the age of 32 inside of the map ";
    EXPECT_EQ(t.getTripDeque().empty(), true) <<"something went wrong with the extraction of the trip." ;
    delete(d);
}
/*
 * the method checks the addTrip method.
 * an instance of a tripInformation is being created, afterwards it is being
 * added to the trip deque of a taxicenter
 * instance and then we check if the trip deque is empty or not and if the
 * trip information values were chenaged
 * through the process of pushing it in the deque.
 */

TEST(TaxiCenterTest, addTripTest){
    NodePoint* start = new NodePoint(2,5);
    NodePoint* end= new NodePoint(4,7);
    TripInformation* ti= new TripInformation(1234, 3, start, end, 5.2,1);
    TaxiCenter tc;
    tc.addTrip(ti);
    EXPECT_EQ(tc.getTripDeque().size()!=0, true)
                        <<"the addTrip method had failed there should have been a trip ";
    TripInformation* t1 = tc.getTripDeque().front();
    EXPECT_EQ(t1->getRideId(), 1234)
                        << "the addTrip method had failed there should "
                                "have been a trip with the id of 1234"
                                "in it. ";
    tc.getTripDeque().pop_front();
    EXPECT_EQ(tc.getTripDeque().size() == 0, true)
                        << "something went wrong with the extraction of the trip.";
    delete(ti);
}

/*
 * the test checks the addCab method.
 * there is an instance of cab created, afterwards it
 * is pushed to th list of cabs that an instance of taxicenter is
 * holding and we check if the list is empty or not after pushing it into the list.
 */
TEST(TaxiCenterTest, addCabTest){
    TaxiCenter tc;
    NodePoint* p =new NodePoint(0,0);
    Matrix matrix(10,10);
    AbstractNode* abstractNode = matrix.getNode(p);
    delete p;
    LuxuryCab* luxuryCab = new LuxuryCab(12345678, 1000,'H', 'B',abstractNode);
    tc.addCab((AbstractCab*&)luxuryCab);
    EXPECT_EQ(tc.getCabVector().size()!=0, true)
                        <<"the addCab method had failed there should have been a Cab ";
    delete luxuryCab;
}


TEST(TaxiCenterTest, getLocationOfAdriverTest){
    TaxiCenter tc;
    NodePoint* p =new NodePoint(0,0);
    Matrix matrix(10,10);
    AbstractNode* abstractNode = matrix.getNode(p);
    delete p;
    LuxuryCab* luxuryCab = new LuxuryCab(12345678, 1000,'H', 'B',abstractNode);
    Driver* driver = new Driver(123,12,'M',12345678,2);
    tc.addCab((AbstractCab*&)luxuryCab);
    tc.addDriver(driver);
    NodePoint *location = (NodePoint *) tc.getDriverLocation(123);
    EXPECT_EQ(*location,NodePoint(0,0))
                        <<"the addCab method had failed there should have been a Cab ";
    delete (luxuryCab);
    delete (driver);

}



/* is a mark because we still didn't handle this method.
 * the test checks the answerCall method - the answerCall method adds a new trip and therfor the
 * trip deque shouln't be emty if it is that means something went wrong with the method.
 */
/*
TEST(TaxiCenterTest, answerCallTest){
TaxiCenter t;
    t.answerCalls();
EXPECT_EQ(t.getTripDeque().empty()!=0, true) <<"the answerCalls method had failed there should have been a trip " ;
    if(!t.getTripDeque().empty()) {
        t.getTripDeque().pop_front();
    }
    EXPECT_EQ(t.getTripDeque().empty()==0, true) <<"something went wrong with the extraction of the trip." ;
}
*/