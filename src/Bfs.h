//
// Created by liav on 22/11/16.
//

#ifndef EX11_BFS_H
#define EX11_BFS_H
#include <stack>
#include "AbstractNode.h"
#include <iostream>
#include <deque>
#include <iostream>
#include "AbstractNode.h"
#include "Point.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
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
#include <boost/serialization/deque.hpp>


using namespace std;
using namespace boost::archive;
/* class name : Bfs
 * class that implementation BFS algoritem
 */
class Bfs {


public:
    // return the shortest way from star point to the end in stack
    std::deque<AbstractNode*> theShortestWay(AbstractNode* start,
                                             AbstractNode* end);

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
    }

    ~Bfs();//destructor.
};


#endif //EX11_BFS_H
