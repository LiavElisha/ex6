//
// Created by liav on 02/12/16.
//

#include "DriverTest.h"
#include "../src/Driver.h"
#include "../src/StandardCab.h"

TEST(DriverTests, getAvailable) {

    Driver driver(123, 32, 'M');

    EXPECT_EQ(driver.getAvailable(), true) << "the driver is not available, every new driver available! ";
}

TEST(DriverTests, setAvailable) {

    Driver driver(123, 32, 'M');
    driver.setAvailable(false);

    EXPECT_EQ(driver.getAvailable(), false) << "the driver is available";
}
TEST(DriverTests, getAge) {

    Driver driver(123, 32, 'M');

    EXPECT_EQ(32, driver.getAge()) << "the age I defined at constructor and the age of driver are not equal! ";
}

TEST(DriverTests, setAge) {

    Driver driver(123, 32, 'M');
    driver.setAge(40);

    EXPECT_EQ(40, driver.getAge()) << "the new age I defined and the age of driver are not equal! ";
}
TEST(DriverTests, getYearsOfExperience) {

    Driver driver(123, 32, 'M');

    EXPECT_EQ(0, driver.getYearsOfExperience()) << "the years of experience has to be 0 if doesnt define otherwise ";
}
TEST(DriverTests, setYearsOfExperience) {

    Driver driver(123, 32, 'M');
    driver.setYearsOfExperience(3);

    EXPECT_EQ(3, driver.getYearsOfExperience()) << "the yearsOfExperience of driver is different of my new definition ";
}
TEST(DriverTests, getMaritalStatus) {

    Driver driver(123, 32, 'M');

    EXPECT_EQ('M', driver.getMaritalStatus()) << "the martial status of driver is different of my definition ";
}

TEST(DriverTests, setMaritalStatus) {

    Driver driver(123, 32, 'M');
    driver.setMaritalStatus('W');

    EXPECT_EQ('W', driver.getMaritalStatus()) << "the martial status of driver is different of my new definition ";
}


TEST(DriverTests , getVehicleId) {
    Driver driver(123, 30, 'M', 12345, 10);
    EXPECT_EQ(12345,driver.getVehicleId())<<"the vehicle id should be different";
}

TEST(DriverTests , SetVehicleId) {
    Driver driver(123, 30, 'M', 12345, 10);
    driver.setVehicleId(1234567);
    EXPECT_EQ(1234567,driver.getVehicleId())<<"the vehicle id should be different";
}

TEST(DriverTests , getDriverId) {
    Driver driver(123, 30, 'M', 12345, 10);
    EXPECT_EQ(123,driver.getDriverId())<<"the driver id should be different";
}


TEST(DriverTests , getAndSetCab) {
    Matrix matrix(10,10);
    NodePoint* p =new NodePoint(0,0);
    AbstractNode* abstractNode = matrix.getNode(p);
    delete p;
    StandardCab* standardCab= new StandardCab(1234567,20,'H','G',abstractNode);
    Driver driver(123, 30, 'M', 12345, 10);
    driver.setCab((AbstractCab*&)standardCab);
    EXPECT_EQ(driver.getCab()->getCabId(),1234567 )
                        <<"the vehicle id should be different there was a problem with "
                        "the set cab method";
    delete (standardCab);
}


TEST(DriverTests , getAndSetTripInfo) {
    Driver driver(123, 30, 'M', 12345, 10);
    TripInformation* trip = new TripInformation(123,0,0,0,2,2,1.4,3);
    driver.setCurrentTrip(trip);
    EXPECT_EQ(driver.getCurrentTrip()->getRideId(),123)
                        <<"the trip id should be different there was a problem with "
                        "the set trip method";
    delete(trip);
}

TEST(DriverTests , startDriving) {
    Matrix* matrix = new Matrix(10,10);
    NodePoint* p =new NodePoint(0,0);
    AbstractNode* abstractNode = matrix->getNode(p);
    delete p;
    StandardCab* standardCab= new StandardCab(1234567,20,'H','G',abstractNode);
    Driver driver(123, 30, 'M', 12345, 10);
    driver.setCab((AbstractCab*&)standardCab);
    TripInformation* trip = new TripInformation(123,0,0,0,2,2,1.4,3);
    driver.setCurrentTrip(trip);
    NodePoint* startingLocation =(NodePoint*)driver.getCab()->getLocation();
    driver.startDriving(matrix);
    NodePoint* endingLocation =(NodePoint*)driver.getCab()->getLocation();
    ASSERT_EQ(*startingLocation!= *endingLocation, true )
                                <<"the vehicle didn't move,  there was a problem with"
                        "the driving method";
    ASSERT_EQ(*endingLocation, NodePoint(2,2))
                                <<"the vehicle didn't move as i should have  there was "
                                        "a problem with"
                        "the driving method";

    delete(standardCab);
    delete(matrix);

}