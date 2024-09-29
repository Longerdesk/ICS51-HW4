#include "catch_amalgamated.hpp"
#include "CrumpleTree.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>


namespace{




/* Remember, these are prerequisites to having us grade
    the related part of the assignment.  These are not
    worth points on their own, nor are they comprehensive.

    REMEMBER TO TEST YOUR OWN CODE COMPREHENSIVELY. 

*/

TEST_CASE("RemoveCase16", "[NOTRequiredBasicFunctionality]"){
    CrumpleTree<int, std::string> tree;
    tree.insert(-20, "20");
    tree.insert(-10, "10");
    tree.insert(-26, "26");
    tree.insert(-13, "13");
    tree.insert(-5, "5");
    tree.insert(-23, "23");
    tree.insert(-28, "28");
    tree.insert(-18, "18");
    tree.insert(-21, "21");
    tree.insert(-24, "24");
    tree.insert(-31, "31");
    tree.insert(-27, "27");
    tree.insert(-2, "2");
    tree.insert(-1, "1");
    tree.insert(-7, "7");
    tree.insert(-11, "11");
    tree.insert(-16, "16");
    tree.insert(-40, "40");
    tree.insert(-25, "25");
    tree.insert(-4, "4");
    tree.insert(-6, "6");
    tree.insert(-3, "3");
    tree.insert(-8, "8");
    tree.insert(-9, "9");


    tree.remove(-20);
    tree.remove(-13);
    tree.remove(-18);
    tree.remove(-16);
    tree.remove(-11);

    tree.find(-1);
    tree.find(-3);
    tree.find(-6);
    tree.find(-9);
    tree.find(-25);

    tree.getLevel(-10);
    tree.getLevel(-5);
    tree.getLevel(-26);
    tree.getLevel(-2);
    tree.getLevel(-7);
    tree.getLevel(-23);
    tree.getLevel(-28);
    tree.getLevel(-4);
    tree.getLevel(-8);
    tree.getLevel(-24);
    tree.getLevel(-31);
    tree.getLevel(-27);
    tree.getLevel(-1);
    tree.getLevel(-40);
    tree.getLevel(-21);
    tree.getLevel(-25);
    tree.getLevel(-3);
    tree.getLevel(-6);
    tree.getLevel(-9);

    REQUIRE(tree.size() == 19);
}


TEST_CASE("RemoveCase14", "[NOTRequiredBasicFunctionality]"){
    CrumpleTree<int, std::string> tree;
    tree.insert(10, "10");
    tree.insert(15, "15");
    tree.insert(5, "5");
    tree.insert(18, "18");
    tree.insert(2, "2");
    tree.insert(12, "12");
    tree.insert(20, "20");
    tree.insert(7, "7");
    
    tree.getLevel(10);
    tree.getLevel(15);
    tree.getLevel(5);
    tree.getLevel(18);
    tree.getLevel(2);
    tree.getLevel(7);
    tree.getLevel(12);
    tree.getLevel(20);
    tree.find(2);
    tree.find(12);
    tree.find(20);

    tree.remove(5);
    
    tree.getLevel(7);
    tree.getLevel(15);
    tree.getLevel(10);
    tree.getLevel(18);
    tree.getLevel(2);
    tree.getLevel(12);
    tree.getLevel(20);
    tree.find(2);
    tree.find(12);
    tree.find(20);

    REQUIRE( tree.size() == 7 );
}



TEST_CASE("RemoveCase15", "[NOTRequiredBasicFunctionality]"){
    CrumpleTree<int, std::string> tree;
    tree.insert(-10, "10");
    tree.insert(-15, "15");
    tree.insert(-5, "5");
    tree.insert(-12, "12");
    tree.insert(-20, "20");
    tree.insert(-2, "2");
    tree.insert(-11, "11");
    tree.insert(-13, "13");
    
    tree.getLevel(-10);
    tree.getLevel(-15);
    tree.getLevel(-5);
    tree.getLevel(-12);
    tree.getLevel(-2);
    tree.getLevel(-11);
    tree.getLevel(-13);
    tree.getLevel(-20);
    tree.find(-2);
    tree.find(-11);
    tree.find(-13);
    tree.find(-20);

    tree.remove(-2);
    
    tree.getLevel(-12);
    tree.getLevel(-10);
    tree.getLevel(-15);
    tree.getLevel(-5);
    tree.getLevel(-11);
    tree.getLevel(-13);
    tree.getLevel(-20);
    tree.find(-5);
    tree.find(-11);
    tree.find(-13);
    tree.find(-20);

    REQUIRE( tree.size() == 7 );
}


TEST_CASE("Remove Case3", "[NOTRequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(44, "44");
    tree.insert(78, "78");
    tree.insert(17, "17");
    tree.insert(50, "50");
    tree.insert(87, "87");
    tree.insert(32, "32");
    tree.insert(62, "62");
    tree.insert(48, "48");
    tree.getLevel(44);
    tree.getLevel(78);
    tree.getLevel(17);
    tree.getLevel(50);
    tree.getLevel(32);
    tree.getLevel(48);
    tree.getLevel(62);
    tree.getLevel(87);
    
    tree.remove(48);
    tree.remove(62);
    
    tree.getLevel(44);
    tree.getLevel(78);
    tree.getLevel(17);
    tree.getLevel(50);
    tree.getLevel(32);
    tree.getLevel(87);
    tree.find(32);
    tree.find(50);
    tree.find(87);

    
    tree.remove(87);
    
    tree.getLevel(44);
    tree.getLevel(78);
    tree.getLevel(17);
    tree.getLevel(50);
    tree.getLevel(32);
    tree.find(32);
    tree.find(50);

    tree.remove(50);
    
    tree.getLevel(44);
    tree.getLevel(17);
    tree.getLevel(78);
    tree.getLevel(32);
    tree.find(32);
    tree.find(78);


    REQUIRE( tree.size() == 4 );
}


TEST_CASE("Remove Case2", "[NOTRequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(44, "44");
    tree.insert(78, "78");
    tree.insert(17, "17");
    tree.insert(50, "50");
    tree.insert(87, "87");
    tree.insert(32, "32");
    tree.insert(62, "62");
    tree.insert(48, "48");
    tree.getLevel(44);
    tree.getLevel(78);
    tree.getLevel(17);
    tree.getLevel(50);
    tree.getLevel(32);
    tree.getLevel(48);
    tree.getLevel(62);
    tree.getLevel(87);
    
    tree.remove(62);
    tree.remove(87);
    
    tree.getLevel(44);
    tree.getLevel(50);
    tree.getLevel(17);
    tree.getLevel(78);
    tree.getLevel(32);
    tree.getLevel(48);
    tree.find(78);
    tree.find(32);
    tree.find(48);
    
    REQUIRE( tree.size() == 6 );
}


TEST_CASE("Remove Case1", "[NOTRequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(44, "44");
    tree.insert(78, "78");
    tree.insert(17, "17");
    tree.insert(50, "50");
    tree.insert(87, "87");
    tree.insert(32, "32");
    tree.insert(62, "62");
    tree.insert(48, "48");
    tree.getLevel(44);
    tree.getLevel(78);
    tree.getLevel(17);
    tree.getLevel(50);
    tree.getLevel(32);
    tree.getLevel(48);
    tree.getLevel(62);
    tree.getLevel(87);
    
    tree.remove(87);
    
    tree.getLevel(44);
    tree.getLevel(78);
    tree.getLevel(17);
    tree.getLevel(50);
    tree.getLevel(32);
    tree.getLevel(48);
    tree.getLevel(62);
    
    REQUIRE( tree.size() == 7 );
}


TEST_CASE("Remove Case0", "[NOTRequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(20, "20");
    tree.insert(18, "18");
    tree.insert(22, "22");
    tree.find(18);
    tree.find(22);
    tree.getLevel(20);
    tree.getLevel(18);
    tree.getLevel(22);

    tree.remove(20);
    tree.find(18);
    tree.find(22);
    tree.getLevel(18);
    tree.getLevel(22);


    tree.remove(22);
    tree.getLevel(18);
    
    tree.insert(22, "22");

    tree.remove(18);
    tree.getLevel(22);
    tree.remove(22);
    REQUIRE( tree.size() == 0 );
}



TEST_CASE("CanAddFive", "[NOTRequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    std::cout << "----Try insert 20---------" << std::endl;
    tree.insert(20, "foo");
    std::cout << "----Done insert 20---------" << std::endl;
    std::cout << "----Try insert 19---------" << std::endl;
    tree.insert(19, "sna");
    std::cout << "----Done insert 19---------" << std::endl;
    tree.find(19);
    std::cout << "----Try insert 18---------" << std::endl;
    tree.insert(18, "bar");
    std::cout << "----Done insert 18--------" << std::endl;
    tree.find(18);
    tree.find(20);
    std::cout << "----Try insert 12---------" << std::endl;
    tree.insert(12, "twelve");
    std::cout << "----Done insert 12--------" << std::endl;
    tree.find(12);
    tree.getLevel(19);
    std::cout << "----Try insert 9---------" << std::endl;
    tree.insert(9, "nine");
    std::cout << "----Done insert 9--------" << std::endl;
    tree.find(9);
    tree.find(18);
    tree.find(20);
    std::cout << "----Try insert 17---------" << std::endl;
    tree.insert(17, "seventeen");
    std::cout << "----Done insert 17--------" << std::endl;
    tree.find(17);
    tree.find(20);
    tree.find(9);
    std::cout << "----Try insert 7----------" << std::endl;
    tree.insert(7, "seven");
    std::cout << "----Done insert 7--------" << std::endl;
    tree.find(7);
    std::cout << "----Try insert 5----------" << std::endl;
    tree.insert(5, "five");
    std::cout << "----Done insert 5--------" << std::endl;
    tree.find(5);
    tree.find(9);
    tree.find(17);
    tree.find(20);
    std::cout << "----Try insert 13----------" << std::endl;
    tree.insert(13, "thirteen");
    std::cout << "----Done insert 13--------" << std::endl;
    tree.find(13);
    std::cout << "----Try insert 15----------" << std::endl;
    tree.insert(15, "fifteen");
    std::cout << "----Done insert 15--------" << std::endl;
    tree.find(13);
    tree.find(17);
    std::cout << "----Try insert 6----------" << std::endl;
    tree.insert(6, "six");
    std::cout << "----Done insert 6--------" << std::endl;
    tree.find(6);
    tree.find(17);
    std::cout << "----Try insert 16----------" << std::endl;
    tree.insert(16, "sixteen");
    std::cout << "----Done insert 16--------" << std::endl;
    tree.find(16);
    tree.find(13);
    std::cout << "----Try insert 14----------" << std::endl;
    tree.insert(14, "fourteen");
    std::cout << "----Done insert 14--------" << std::endl;
    tree.find(14);
    tree.find(16);
    tree.find(20);
    tree.find(6);
    tree.find(9);

    tree.getLevel(12);
    tree.getLevel(18);
    tree.getLevel(7);
    tree.getLevel(15);
    tree.getLevel(5);
    tree.getLevel(13);
    tree.getLevel(17);
    tree.getLevel(19);
    tree.getLevel(6);
    tree.getLevel(9);
    tree.getLevel(14);
    tree.getLevel(16);
    tree.getLevel(20);

    
    auto inTrav = tree.inOrder();
    std::vector<int> inExpected = {5, 6, 7, 9, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    REQUIRE(inTrav == inExpected);
    auto preTrav = tree.preOrder();
    std::vector<int> preExpected = {12, 7, 5, 6, 9, 18, 15, 13, 14, 17, 16, 19, 20};
    REQUIRE(preTrav == preExpected);
    auto postTrav = tree.postOrder();
    std::vector<int> postExpected = {6, 5, 9, 7, 14, 13, 16, 17, 15, 20, 19, 18, 12,};
    REQUIRE(postTrav == postExpected);
    

    REQUIRE( tree.size() == 13 );
}

TEST_CASE("Mirror", "[NOTRequiredBasicFunctionality]"){
    CrumpleTree<int, std::string> tree;
    std::cout << "----Try insert 20---------" << std::endl;
    tree.insert(-20, "foo");
    std::cout << "----Done insert 20---------" << std::endl;
    std::cout << "----Try insert 19---------" << std::endl;
    tree.insert(-19, "sna");
    std::cout << "----Done insert 19---------" << std::endl;
    tree.find(-19);
    std::cout << "----Try insert 18---------" << std::endl;
    tree.insert(-18, "bar");
    std::cout << "----Done insert 18--------" << std::endl;
    tree.find(-18);
    tree.find(-20);
    std::cout << "----Try insert 12---------" << std::endl;
    tree.insert(-12, "twelve");
    std::cout << "----Done insert 12--------" << std::endl;
    tree.find(-12);
    tree.getLevel(-19);
    std::cout << "----Try insert 9---------" << std::endl;
    tree.insert(-9, "nine");
    std::cout << "----Done insert 9--------" << std::endl;
    tree.find(-9);
    tree.find(-18);
    tree.find(-20);
    std::cout << "----Try insert 17---------" << std::endl;
    tree.insert(-17, "seventeen");
    std::cout << "----Done insert 17--------" << std::endl;
    tree.find(-17);
    tree.find(-20);
    tree.find(-9);
    std::cout << "----Try insert 7----------" << std::endl;
    tree.insert(-7, "seven");
    std::cout << "----Done insert 7--------" << std::endl;
    tree.find(-7);
    std::cout << "----Try insert 5----------" << std::endl;
    tree.insert(-5, "five");
    std::cout << "----Done insert 5--------" << std::endl;
    tree.find(-5);
    tree.find(-9);
    tree.find(-17);
    tree.find(-20);
    std::cout << "----Try insert 13----------" << std::endl;
    tree.insert(-13, "thirteen");
    std::cout << "----Done insert 13--------" << std::endl;
    tree.find(-13);
    std::cout << "----Try insert 15----------" << std::endl;
    tree.insert(-15, "fifteen");
    std::cout << "----Done insert 15--------" << std::endl;
    tree.find(-13);
    tree.find(-17);
    std::cout << "----Try insert 6----------" << std::endl;
    tree.insert(-6, "six");
    std::cout << "----Done insert 6--------" << std::endl;
    tree.find(-6);
    tree.find(-17);
    std::cout << "----Try insert 16----------" << std::endl;
    tree.insert(-16, "sixteen");
    std::cout << "----Done insert 16--------" << std::endl;
    tree.find(-16);
    tree.find(-13);
    std::cout << "----Try insert 14----------" << std::endl;
    tree.insert(-14, "fourteen");
    std::cout << "----Done insert 14--------" << std::endl;
    tree.find(-14);
    tree.find(-16);
    tree.find(-20);
    tree.find(-6);
    tree.find(-9);

    tree.getLevel(-12);
    tree.getLevel(-18);
    tree.getLevel(-7);
    tree.getLevel(-15);
    tree.getLevel(-5);
    tree.getLevel(-13);
    tree.getLevel(-17);
    tree.getLevel(-19);
    tree.getLevel(-6);
    tree.getLevel(-9);
    tree.getLevel(-14);
    tree.getLevel(-16);
    tree.getLevel(-20);

    REQUIRE( tree.size() == 13 );
}

TEST_CASE("FindTheRoot", "[RequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    REQUIRE( tree.contains(5) );
}

TEST_CASE("FindOneHop", "[RequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(10, "bar");

    REQUIRE( tree.contains(10) );
}

TEST_CASE("FindTwoHops", "[RequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");

    REQUIRE( tree.contains(12) );
}



TEST_CASE("CanAddAFew", "[RequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");
    tree.insert(15, "fifteen");

    REQUIRE( tree.size() == 5 );
}




TEST_CASE("DoAPostOrder", "[RequiredBasicFunctionality]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    auto trav = tree.postOrder();
    std::vector<int> expected = {3, 10, 5};
    REQUIRE(trav == expected);

}



TEST_CASE("RemoveDoesARemove", "[RequiredCrumpleTree]")
{
    CrumpleTree<int, std::string> tree;
    tree.insert(20, "are");
    tree.insert(19, "you");
    tree.insert(18, "following");
    tree.insert(12, "from");
    tree.insert(9, "lecture?");
    REQUIRE( tree.contains( 20 ) );
    REQUIRE( tree.contains( 19 ) );
    REQUIRE( tree.contains( 18 ) );
    REQUIRE( tree.contains( 12 ) );
    REQUIRE( tree.contains( 9 ) );
    tree.remove(9);
    tree.remove(18);
    // What happens?  12 is now a leaf and must fall.  But 19 is a (2,2) and remains at level 3.
    REQUIRE( ! tree.contains(9));
    REQUIRE( ! tree.contains(18));
    REQUIRE( tree.getLevel(20) == 1);
    REQUIRE( tree.getLevel(12) == 1);
    REQUIRE( tree.getLevel(19) == 3);

}


                        
} // end namespace

