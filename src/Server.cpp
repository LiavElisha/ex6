//
// Created by yoav on 01/01/17.
//

#include "Menu.h"
#include "Udp.h"
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include "Socket.h"
#include "Udp.h"
#include "Driver.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include "TaxiCenter.h"
#include "Tcp.h"
#include "Socket.h"


using namespace std;
using namespace boost::archive;

//BOOST_CLASS_EXPORT(StandardCab);
//BOOST_CLASS_EXPORT(LuxuryCab);

int main(int argc, char* argv[]){
    TaxiCenter* taxiCenter = new TaxiCenter();
    Socket* socket = new Tcp(1,atoi(argv[1]));
    Menu menu(taxiCenter, socket);
    menu.getInput();
    delete(taxiCenter);
    delete (socket);
}