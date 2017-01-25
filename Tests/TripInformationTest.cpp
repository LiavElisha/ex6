
//
// Created by liav on 02/12/16.
//

#include "TripInformationTest.h"
#include "../src/Point.h"
#include "../src/TripInformation.h"

TEST(TripInformationTests, getRideId){

    NodePoint* start = new NodePoint(2,5);
    NodePoint* end= new NodePoint(4,7);
    TripInformation trip(1234, 3, start, end, 5.2,1);
    EXPECT_EQ(1234, trip.getRideId())
                        <<"the ride id is not equal to the parameters in the constructor " ;
}

TEST(TripInformationTests, getmetersPassed){
    NodePoint* start = new NodePoint(2,5);
    NodePoint* end= new NodePoint(4,7);
    TripInformation trip(1234, 3, start, end, 5.2,1);
    EXPECT_EQ(3, trip.getMetersPassed())
                        <<"the meterpassed is not equal to the parameters in the constructor";

}

TEST(TripInformationTests, setmetersPassed){
    NodePoint* start = new NodePoint(2,5);
    NodePoint* end= new NodePoint(4,7);
    TripInformation trip(1234, 3, start, end, 5.2,1);
    trip.setMetersPassed(17);
    EXPECT_EQ(17, trip.getMetersPassed())
                        <<"the meterpassed is not equal to my new meterpassed definition ";

}

TEST(TripInformationTests, getSource){
    NodePoint* start = new NodePoint(2,5);
    NodePoint* end= new NodePoint(4,7);
    TripInformation trip(1234, 3, start, end, 5.2,1);
    NodePoint* location = (NodePoint*)trip.getSource();
    ASSERT_NE(*location,NodePoint(0,0)) <<"the source point is wrong";


}

TEST(TripInformationTests, getDestination){

    NodePoint* start = new NodePoint(2,5);
    NodePoint* end= new NodePoint(4,7);
    TripInformation trip(1234, 3, start, end, 5.2,1);
    NodePoint* location = (NodePoint*)trip.getDestination();
    ASSERT_NE(*location,NodePoint(0,0)) <<"there is no destination point to the trip";
    ASSERT_EQ(*location,NodePoint(4,7)) <<"the destination point is wrong";

}


TEST(TripInformationTests, getTariff){

    NodePoint* start = new NodePoint(2,5);
    NodePoint* end= new NodePoint(4,7);
    TripInformation trip(1234, 3, start, end, 5.2,1);

    EXPECT_EQ(5.2, trip.getTariff())
                        <<"the tariff of trip is not equal to the parameters in the constructor";

}
TEST(TripInformationTests, setTariff){
    NodePoint* start = new NodePoint(2,5);
    NodePoint* end= new NodePoint(4,7);
    TripInformation trip(1234, 3, start, end, 5.2,1);

    trip.setTariff(3.7);
    EXPECT_EQ(3.7, trip.getTariff())
                        <<"the tariff of trip is not equal to my new tariff definition";

}