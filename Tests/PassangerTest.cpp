//
// Created by liav on 02/12/16.
//

#include "PassangerTest.h"
#include "../src/Passanger.h"

TEST(PassangerTest, satisfactionFromRide){

    NodePoint* start = new NodePoint(2,5);
    NodePoint* end = new NodePoint (4,7);
    Passanger passanger(start, end);
    EXPECT_EQ(0 < passanger.satisfactionFromRide() < 6, true)
                        <<"the value of satisfaction from ride is not in range ";
    delete(start);
    delete(end);

}
