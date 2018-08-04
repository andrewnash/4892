#include <iostream>
#include <cassert>      // for using assert
#include <algorithm>
#include "SocialNetwork.h"
#include "User.h"
#include <chrono>
using namespace std;

int main()
{
    //!Start Basic Tests
    SocialNetwork Term4;

    //test addUser()
    User::ID Glyn_George   = Term4.addUser("Glyn H. George");
    User::ID Liang         = Term4.addUser("Xiaodong Liang");
    User::ID Andrew_Vardy  = Term4.addUser("Andrew Vardy");
    User::ID Quaicoe       = Term4.addUser("John E. Quaicoe");
    User::ID Mashrura      = Term4.addUser("Mashrura Musharraf");
    User::ID Anderson      = Term4.addUser("Jonathan R. Anderson");
    User::ID Daniela       = Term4.addUser("Daniela Silvesan");


    /*                                         |---------------------------|
     *                                         |                           |
     *    Glyn_George           /-----------Mashrura---------\             |
     *        |       \        /               |              \            |
     *        |        \------/----------------|-------------- Daniela     |
     *        |              /                 |                 |         |
     *        |    /----Liang       /--------- + ----------------|         |
     *        |   /                /           |                           |
     *        |  //---------------/            |                           |
     *     Quaicoe ------------------------Andrew_Vardy ------- Anderson   |
     *        |                                                            |
     *        |------------------------------------------------------------|
     */


    //test addFriendship
    Term4.addFriendship(Andrew_Vardy, Anderson);
    Term4.addFriendship(Glyn_George,  Daniela);
    Term4.addFriendship(Liang,        Mashrura);
    Term4.addFriendship(Mashrura,     Daniela);
    Term4.addFriendship(Glyn_George,  Quaicoe);
    Term4.addFriendship(Andrew_Vardy, Quaicoe);
    Term4.addFriendship(Liang,        Quaicoe);
    Term4.addFriendship(Mashrura,     Quaicoe);
    Term4.addFriendship(Daniela,      Quaicoe);
    Term4.addFriendship(Andrew_Vardy, Mashrura);


    //test id()
    assert(Glyn_George  == Term4.getUser(Glyn_George).id());
    assert(Liang        == Term4.getUser(Liang).id());
    assert(Andrew_Vardy == Term4.getUser(Andrew_Vardy).id());
    assert(Quaicoe      == Term4.getUser(Quaicoe).id());
    assert(Mashrura     == Term4.getUser(Mashrura).id());
    assert(Anderson     == Term4.getUser(Anderson).id());
    assert(Daniela      == Term4.getUser(Daniela).id());


    //test degree()
    assert(Term4.getUser(Glyn_George).degree()  == 2);
    assert(Term4.getUser(Quaicoe).degree()      == 5);
    assert(Term4.getUser(Liang).degree()        == 2);
    assert(Term4.getUser(Mashrura).degree()     == 4);
    assert(Term4.getUser(Andrew_Vardy).degree() == 3);
    assert(Term4.getUser(Anderson).degree()     == 1);
    assert(Term4.getUser(Daniela).degree()      == 3);


    //test distance
    assert(Term4.getUser(Anderson).distance(Term4.getUser(Andrew_Vardy)) == 1);
    assert(Term4.getUser(Anderson).distance(Term4.getUser(Quaicoe))      == 2);
    assert(Term4.getUser(Anderson).distance(Term4.getUser(Mashrura))     == 2);
    assert(Term4.getUser(Anderson).distance(Term4.getUser(Daniela))      == 3);
    assert(Term4.getUser(Anderson).distance(Term4.getUser(Liang))        == 3);
    assert(Term4.getUser(Anderson).distance(Term4.getUser(Glyn_George))  == 3);


    //test SocialNetwork Iterator
    int j = 1;
    for(auto i = Term4.begin(); i != Term4.end(); i++)
    {
        if(j < 8)
        {
            assert((*i).id()     == Term4.getUser((*i).id()).id());
            assert((*i).degree() == Term4.getUser((*i).id()).degree());
            j++;
        }
    }


    //test find()
    auto i = Term4.find("Glyn H. George");
    assert((*i).id() == Term4.getUser(Glyn_George).id());

    i = Term4.find("J");
    assert((*i).id() == Term4.getUser(Anderson).id() or (*i).id() == Term4.getUser(Quaicoe).id());
    i++;
    assert((*i).id() == Term4.getUser(Anderson).id() or (*i).id() == Term4.getUser(Quaicoe).id());


    //test User Iterator
    j = 1;
    for(auto i = Term4.getUser(Quaicoe).begin(); i != Term4.getUser(Quaicoe).end(); i++)
    {
        if(j < 6)
        {
            assert((*i).id()     == Term4.getUser((*i).id()).id());
            assert((*i).degree() == Term4.getUser((*i).id()).degree());
            j++;
        }
    }


    //test User friendsOfFriends()
    j = 1;
    for(auto i = Term4.getUser(Quaicoe).friendsOfFriends(); i != Term4.getUser(Quaicoe).end(); i++)
    {
        if(j < 7)
        {
            assert((*i).id()     == Term4.getUser((*i).id()).id());
            assert((*i).degree() == Term4.getUser((*i).id()).degree());
            j++;
        }
    }

    j = 1;
    std::vector<User::ID> friendsFriends1;
    std::vector<User::ID> friendsFriends2;
    friendsFriends1.push_back(Andrew_Vardy);
    friendsFriends1.push_back(Quaicoe);
    friendsFriends1.push_back(Mashrura);
    for(auto i = Term4.getUser(Anderson).friendsOfFriends(); i != Term4.getUser(Anderson).end(); i++)
    {
        if(j < 4)
        {
            friendsFriends2.push_back((*i).id());
            j++;
        }
    }
    std::sort(friendsFriends1.begin(), friendsFriends1.end());
    std::sort(friendsFriends2.begin(), friendsFriends2.end());
    assert(friendsFriends1 == friendsFriends2);
    //!End Basic Tests


    //!Start Medium Tests
    SocialNetwork Term3;

    Glyn_George        = Term3.addUser("Glyn H. George");
    Quaicoe            = Term3.addUser("John E. Quaicoe");
    User::ID Darlene   = Term3.addUser("Darlene Spracklin-Reid");
    User::ID Susan     = Term3.addUser("Susan Caines");
    User::ID Venky     = Term3.addUser("Ramachandran Venkatesan");
    User::ID House     = Term3.addUser("Andrew House");
    User::ID Misha     = Term3.addUser("Mykhaylo Evstigneev");

    /*
     *   Venky                                   House
     *        \                                 /
     *         Darlene - Quaico      Glyn_George
     *        /
     *   Susan                                        Misha
     *
     */
    Term3.addFriendship(Venky, Darlene);
    Term3.addFriendship(Susan, Darlene);
    Term3.addFriendship(Quaicoe, Darlene);
    Term3.addFriendship(House, Glyn_George);

    assert(Term3.getUser(Venky).distance(Term3.getUser(Darlene))     == 1);
    assert(Term3.getUser(Venky).distance(Term3.getUser(Quaicoe))     == 2);
    assert(Term3.getUser(Venky).distance(Term3.getUser(Susan))       == 2);
    assert(Term3.getUser(Glyn_George).distance(Term3.getUser(House)) == 1);
    assert(Term3.getUser(Venky).distance(Term3.getUser(House))       == SIZE_MAX);
    assert(Term3.getUser(Misha).distance(Term3.getUser(Glyn_George)) == SIZE_MAX);


    /*
     *   Venky                                 House
     *        \                               /
     *         Darlene - Quaicoe - Glyn_George
     *        /                               \
     *   Susan                                  Misha
     *
     */
    Term3.addFriendship(Quaicoe, Glyn_George);
    Term3.addFriendship(Misha, Glyn_George);

    assert(Term3.getUser(Venky).distance(Term3.getUser(House))         == 4);
    assert(Term3.getUser(Venky).distance(Term3.getUser(Misha))         == 4);
    assert(Term3.getUser(Misha).distance(Term3.getUser(Venky))         == 4);
    assert(Term3.getUser(Venky).distance(Term3.getUser(Glyn_George))   == 3);
    assert(Term3.getUser(Quaicoe).distance(Term3.getUser(House))       == 2);
    assert(Term3.getUser(Quaicoe).distance(Term3.getUser(Venky))       == 2);
    assert(Term3.getUser(Quaicoe).distance(Term3.getUser(Misha))       == 2);
    assert(Term3.getUser(Quaicoe).distance(Term3.getUser(Susan))       == 2);
    assert(Term3.getUser(Quaicoe).distance(Term3.getUser(Glyn_George)) == 1);
    assert(Term3.getUser(Quaicoe).distance(Term3.getUser(Glyn_George)) == 1);
    //!End Medium Tests


    //!Start Hard Tests
    SocialNetwork ECE;

    Glyn_George            = ECE.addUser("Glyn H. George");  //Yes, Glyn George is in fact a part of the ECE Faculty
    Liang                  = ECE.addUser("Xiaodong Liang");
    Andrew_Vardy           = ECE.addUser("Andrew Vardy");
    Quaicoe                = ECE.addUser("John E. Quaicoe");
    Mashrura               = ECE.addUser("Mashrura Musharraf");
    Anderson               = ECE.addUser("Jonathan R. Anderson");
    Venky                  = ECE.addUser("Ramachandran Venkatesan");
    House                  = ECE.addUser("Andrew House");
    User::ID DPetes        = ECE.addUser("Dennis Peters");
    User::ID Shehata       = ECE.addUser("Mohamed Shehata");
    User::ID Lori_Hogan    = ECE.addUser("Lori Hogan");
    User::ID Howard_Heys   = ECE.addUser("Howard Heys");
    User::ID Brian_Kidney  = ECE.addUser("Brian Kidney");
    User::ID Brian_Pretty  = ECE.addUser("Brian Pretty");
    User::ID Greg_OLeary   = ECE.addUser("Greg O'Leary");

    ECE.addFriendship(House,        Andrew_Vardy);
    ECE.addFriendship(House,        Andrew_Vardy);
    ECE.addFriendship(House,        Andrew_Vardy);
    ECE.addFriendship(House,        Andrew_Vardy);
    ECE.addFriendship(House,        Andrew_Vardy);
    ECE.addFriendship(House,        Andrew_Vardy);
    ECE.addFriendship(House,        Andrew_Vardy);
    ECE.addFriendship(House,        Andrew_Vardy);
    ECE.addFriendship(Andrew_Vardy, House);
    ECE.addFriendship(Andrew_Vardy, House);
    ECE.addFriendship(Andrew_Vardy, House);
    ECE.addFriendship(Andrew_Vardy, House);
    ECE.addFriendship(Andrew_Vardy, House);
    ECE.addFriendship(Andrew_Vardy, House);
    ECE.addFriendship(Andrew_Vardy, House);
    ECE.addFriendship(Andrew_Vardy, House);

    ECE.addFriendship(Shehata,      Andrew_Vardy);
    ECE.addFriendship(Andrew_Vardy, Anderson);
    ECE.addFriendship(Brian_Pretty, Lori_Hogan);
    ECE.addFriendship(Brian_Kidney, Lori_Hogan);
    ECE.addFriendship(Lori_Hogan,   Anderson);
    ECE.addFriendship(Anderson,     DPetes);
    ECE.addFriendship(DPetes,       Quaicoe);
    ECE.addFriendship(Glyn_George,  Quaicoe);
    ECE.addFriendship(Liang,        Glyn_George);
    ECE.addFriendship(Howard_Heys,  Glyn_George);
    ECE.addFriendship(Mashrura,     Venky);
    ECE.addFriendship(Greg_OLeary,  Venky);
    ECE.addFriendship(Venky,        Quaicoe);

    /*
     *
     *       House                                                           Liang
     *            \                                                         /
     *             Vardy                                         Glyn_George
     *            /      \                                      /           \
     *     Shehata        \                                    /             Howard_Heys
     *                     \                                  /
     *                      Anderson --- D Peters --- Quaicoe
     *                     /                                  \
     *  Brian_Pretty      /                                    \       Mashrura
     *              \    /                                      \     /
     *               Lori                                        Venky
     *              /                                                 \
     *  Brian_Kidney                                                   Greg O'Leary
     */

    //Distance()
    assert(ECE.getUser(House).distance(ECE.getUser(Andrew_Vardy)) == 1);
    assert(ECE.getUser(House).distance(ECE.getUser(Anderson))     == 2);
    assert(ECE.getUser(House).distance(ECE.getUser(DPetes))       == 3);
    assert(ECE.getUser(House).distance(ECE.getUser(Lori_Hogan))   == 3);
    assert(ECE.getUser(House).distance(ECE.getUser(Quaicoe))      == 4);
    assert(ECE.getUser(House).distance(ECE.getUser(Brian_Kidney)) == 4);
    assert(ECE.getUser(House).distance(ECE.getUser(Brian_Pretty)) == 4);
    assert(ECE.getUser(House).distance(ECE.getUser(Glyn_George))  == 5);
    assert(ECE.getUser(House).distance(ECE.getUser(Venky))        == 5);
    assert(ECE.getUser(House).distance(ECE.getUser(Liang))        == 6);
    assert(ECE.getUser(House).distance(ECE.getUser(Howard_Heys))  == 6);
    assert(ECE.getUser(House).distance(ECE.getUser(Greg_OLeary))  == 6);
    assert(ECE.getUser(House).distance(ECE.getUser(Mashrura))     == 6);

    assert(ECE.getUser(DPetes).distance(ECE.getUser(Anderson))     == 1);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Quaicoe))      == 1);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Glyn_George))  == 2);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Andrew_Vardy)) == 2);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Lori_Hogan))   == 2);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Venky))        == 2);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(House))        == 3);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Shehata))      == 3);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Brian_Kidney)) == 3);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Brian_Pretty)) == 3);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Greg_OLeary))  == 3);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Mashrura))     == 3);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Liang))        == 3);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Howard_Heys))  == 3);

    //SocialNetwork Iterator()
    j = 1;
    std::vector<User::ID> ECESocialNetwork1;
    std::vector<User::ID> ECESocialNetwork2;
    ECESocialNetwork1.push_back(House);
    ECESocialNetwork1.push_back(Andrew_Vardy);
    ECESocialNetwork1.push_back(Anderson);
    ECESocialNetwork1.push_back(DPetes);
    ECESocialNetwork1.push_back(Lori_Hogan);
    ECESocialNetwork1.push_back(Quaicoe);
    ECESocialNetwork1.push_back(Shehata);
    ECESocialNetwork1.push_back(Brian_Kidney);
    ECESocialNetwork1.push_back(Brian_Pretty);
    ECESocialNetwork1.push_back(Glyn_George);
    ECESocialNetwork1.push_back(Venky);
    ECESocialNetwork1.push_back(Liang);
    ECESocialNetwork1.push_back(Howard_Heys);
    ECESocialNetwork1.push_back(Greg_OLeary);
    ECESocialNetwork1.push_back(Mashrura);
    for(auto i = ECE.begin(); i != ECE.end(); i++)
    {
        if(j < 16)
        {
            ECESocialNetwork2.push_back((*i).id());
            j++;
        }
    }
    std::sort(ECESocialNetwork1.begin(), ECESocialNetwork1.end());
    std::sort(ECESocialNetwork2.begin(), ECESocialNetwork2.end());
    assert(ECESocialNetwork1 == ECESocialNetwork2);

    //test find()
    i = ECE.find("Brian");
    assert((*i).id() == ECE.getUser(Brian_Kidney).id() or (*i).id() == ECE.getUser(Brian_Pretty).id());
    i++;
    assert((*i).id() == ECE.getUser(Brian_Kidney).id() or (*i).id() == ECE.getUser(Brian_Pretty).id());
    i++;
    assert(i == ECE.end());

    i = ECE.find("Andrew");
    assert((*i).id() == ECE.getUser(Andrew_Vardy).id() or (*i).id() == ECE.getUser(House).id());
    i++;
    assert((*i).id() == ECE.getUser(Andrew_Vardy).id() or (*i).id() == ECE.getUser(House).id());
    i++;
    assert(i == ECE.end());


    //User Iterator()
    j = 1;
    std::vector<User::ID> DPetesFriends1;
    std::vector<User::ID> DPetesFriends2;
    DPetesFriends1.push_back(Anderson);
    DPetesFriends1.push_back(Quaicoe);
    for(auto i = ECE.getUser(DPetes).begin(); i != ECE.getUser(DPetes).end(); i++)
    {
        if(j < 3)
        {
            DPetesFriends2.push_back((*i).id());
            j++;
        }
    }
    std::sort(DPetesFriends1.begin(), DPetesFriends1.end());
    std::sort(DPetesFriends2.begin(), DPetesFriends2.end());
    assert(DPetesFriends1 == DPetesFriends2);

    j = 1;
    DPetesFriends1.clear();
    DPetesFriends2.clear();
    DPetesFriends1.push_back(Anderson);
    DPetesFriends1.push_back(Quaicoe);
    DPetesFriends1.push_back(Andrew_Vardy);
    DPetesFriends1.push_back(Lori_Hogan);
    DPetesFriends1.push_back(Glyn_George);
    DPetesFriends1.push_back(Venky);
    for(auto i = ECE.getUser(DPetes).friendsOfFriends(); i != ECE.getUser(DPetes).end(); i++)
    {
        if(j < 7)
        {
            DPetesFriends2.push_back((*i).id());
            j++;
        }
    }
    std::sort(DPetesFriends1.begin(), DPetesFriends1.end());
    std::sort(DPetesFriends2.begin(), DPetesFriends2.end());
    assert(DPetesFriends1 == DPetesFriends2);

    //Test adding friends twice and adding yourself
    ECE.addFriendship(DPetes, House);
    ECE.addFriendship(DPetes, Shehata);
    ECE.addFriendship(DPetes, Andrew_Vardy);
    ECE.addFriendship(DPetes, Brian_Kidney);
    ECE.addFriendship(DPetes, Brian_Pretty);
    ECE.addFriendship(DPetes, Lori_Hogan);
    ECE.addFriendship(DPetes, Anderson);
    ECE.addFriendship(DPetes, DPetes);
    ECE.addFriendship(DPetes, Quaicoe);
    ECE.addFriendship(DPetes, Glyn_George);
    ECE.addFriendship(DPetes, Liang);
    ECE.addFriendship(DPetes, Howard_Heys);
    ECE.addFriendship(DPetes, Venky);
    ECE.addFriendship(DPetes, Mashrura);
    ECE.addFriendship(DPetes, Greg_OLeary);
    assert(ECE.getUser(DPetes).degree() == 14);

    assert(ECE.getUser(DPetes).distance(ECE.getUser(Anderson))     == 1);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Quaicoe))      == 1);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Glyn_George))  == 1);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Andrew_Vardy)) == 1);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Lori_Hogan))   == 1);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Venky))        == 1);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(House))        == 1);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Shehata))      == 1);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Brian_Kidney)) == 1);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Brian_Pretty)) == 1);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Greg_OLeary))  == 1);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Mashrura))     == 1);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Liang))        == 1);
    assert(ECE.getUser(DPetes).distance(ECE.getUser(Howard_Heys))  == 1);
    //!End Hard Tests

    //!Start Advanced Tests

   SocialNetwork Splatoon;
   std::vector<User::ID> kids1;
   std::vector<User::ID> squids1;
   int n = 5000;
   for(int i = 0; i != n; i++)
   {
       std::string kid = "kid";
       kid = kid + std::to_string(i);
       kids1.push_back(Splatoon.addUser(kid));

       std::string squid = "squid";
       squid = squid + std::to_string(i);
       squids1.push_back(Splatoon.addUser(squid));
   }

   auto start = chrono::high_resolution_clock::now();

   for(auto i = Splatoon.begin(); i != Splatoon.end(); i++)
   {
       //!..
   }

   auto squidItr = Splatoon.find("squid");
   auto kidItr = Splatoon.find("kid");
   std::vector<User::ID> kids2;
   std::vector<User::ID> squids2;

   for(auto i = kidItr; i != Splatoon.end(); kidItr++, squidItr++, i++)
   {
       kids2.push_back((*kidItr).id());
       squids2.push_back((*squidItr).id());
   }
   std::sort(kids1.begin(), kids1.end());
   std::sort(kids2.begin(), kids2.end());

   std::sort(squids1.begin(), squids1.end());
   std::sort(squids2.begin(), squids2.end());

   assert(kids1 == kids2);
   assert(squids1 == squids2);
   auto end = chrono::high_resolution_clock::now();

   cout << "Found and iterated " << n << " times "
        << "in " << ((end - start).count())/1000000000 << " s\n";
   //!End Advanced Tests
//
//    SocialNetwork itTest;
//    int val;
//    int testSize = 50000;
//    for (int i = 0; i < testSize; i++) {
//        val = rand() % 10000;
//        itTest.addUser(to_string(val));
//    }
//    //ASSERT_EQ(itTest.userCount_, 50000);
//
//    for (int i = 0; i < val; i += 1) {
//        for (int j = 0; j < 1000; j++) {
//            if (i < val - 1) {
//                itTest.addFriendship(i, rand() % val);
//            }
//        }
//    }
//
//    itTest.getUser(12).distance(itTest.getUser(48234));
//    itTest.getUser(48234).distance(itTest.getUser(12));
//    itTest.getUser(25678).distance(itTest.getUser(33992));
//    itTest.getUser(17324).distance(itTest.getUser(0));
//
    std::cout << "Congrats, you did it." << std::endl;

//    cout << "\nDa da da dah, da da da dah ....Spoilers Ahead\n\n";
//
//    SocialNetwork GoT;
//    GoT.addUser("Ned Stark"); // 0
//    GoT.addUser("John Snow"); // 1
//    GoT.addUser("Rob Stark"); // 2
//    GoT.addUser("Sansa Stark"); // 3
//    GoT.addUser("Arya Stark"); // 4
//    GoT.addUser("Cerci Lannister"); // 5
//    GoT.addUser("Jamie Lannister"); // 6
//    GoT.addUser("Tyrian Lannister"); // 7
//
//    //GoT.getUser(20);
//
//    cout << GoT.getUser(0).name_ << " = Ned Stark (ans)\n";
//    cout << GoT.getUser(5).name_ << " = Cerci Lannister (ans)\n\n";
//    assert(GoT.getUser(0).name_ == "Ned Stark");
//    assert(GoT.getUser(5).name_ == "Cerci Lannister");
//
//    GoT.addFriendship(0, 1);
//    cout << "Friendship added from Among th Starks: 4 friends each" << endl << endl;
//    GoT.addFriendship(0, 2);
//    GoT.addFriendship(0, 3);
//    GoT.addFriendship(0, 4);
//    GoT.addFriendship(2, 1);
//    GoT.addFriendship(3, 2);
//    GoT.addFriendship(4, 3);
//    GoT.addFriendship(2, 4);
//    GoT.addFriendship(1, 3);
//    GoT.addFriendship(1, 4);
//    cout << "Friendship added among Lannisters: 2 friend each" << endl << endl;
//    GoT.addFriendship(5, 6);
//    GoT.addFriendship(5, 7);
//    GoT.addFriendship(6, 7);
//
//    assert(GoT.getUser(5).degree() ==  2);
//    assert(GoT.getUser(0).degree() == 4);
//    assert(GoT.getUser(1).degree() == 4);
//
//    cout << "Printing cast thus far: number of friends" << endl;
//    SocialNetwork::Iterator it = GoT.begin();
//    it++;
//    for (SocialNetwork::Iterator i = GoT.begin(); i != GoT.end(); i++) {
//        cout << (*i).name_ << " : " << (*i).degree() << endl;
//    }
//
//    User JohnSnow = GoT.getUser(1);
//    User CerciLannister = GoT.getUser(5);
//    User RobStark = GoT.getUser(2);
//    cout << "Distance from Jon Snow and Rob through friends? "
//         << JohnSnow.distance(RobStark) << endl << endl;
//    cout << "Distance from Jon Snow and Cerci through friends? "
//         << JohnSnow.distance(CerciLannister) << endl << endl;
//
//    assert(JohnSnow.distance(RobStark) == 1);
//    assert(JohnSnow.distance(CerciLannister) == SIZE_MAX);
//
//
//    cout << "But Tyrian and Sansa are friends!" << endl;
//    GoT.addFriendship(7, 3);
//    for (SocialNetwork::Iterator i = GoT.begin(); i != GoT.end(); i++) {
//        cout << (*i).name_ << " : " << (*i).degree() << endl;
//    }
//
//    cout << "Distance from Jon Snow and Cerci through friends now? 3(ans) = "
//         << JohnSnow.distance(CerciLannister) << endl << endl;
//
//    assert(JohnSnow.distance(CerciLannister) == 3);
//
//
//    cout << "Printing Sansa's friends of friends:" << endl;
//    User sansa = GoT.getUser(3);
//    auto i = sansa.friendsOfFriends();
//    auto j = sansa.end();
//    int sanFriendsFriends = 0;
//    while(i != j){
//        cout << (*i).name_ << endl;
//        i++;
//        sanFriendsFriends++;
//    }
//    cout << endl;
//    assert(sanFriendsFriends == 7);
//
//
//    cout << "The Mountain is only friends with Cersi, relationship added.\n" << endl;
//    cout << "Added Little Finger too." << endl;
//
//    GoT.addUser("The Mountain");
//    GoT.addFriendship(5, 8);
//    GoT.addUser("Little Finger");
//    User TheMountain = GoT.getUser(8);
//    cout << "Distance from Jon Snow and The Mountain through friends now? 4(ans) = "
//         << JohnSnow.distance(TheMountain) << endl << endl;
//    User LittleFinger = GoT.getUser(9);
//    cout << "Distance from Jon Snow and Little Finger through friends now? 0(ans) = "
//         << JohnSnow.distance(LittleFinger) << ".\nCuz Little Finger has no Friends!" << endl << endl;
//
//    assert(JohnSnow.distance(TheMountain) == 4);
//    assert(JohnSnow.distance(LittleFinger) == SIZE_MAX);
//
//    size_t count = 0;
//    string tempStr = "Arya";
//    SocialNetwork::Iterator itFind = GoT.find(tempStr);
//    for(auto i = itFind; i != GoT.end(); i++){
//        count ++;
//    }
//    cout << "How many Arya's are there? " << count
//         << " = 1 (ans)" << endl << endl;
//    assert(count == 1);
//
//    count = 0;
//    GoT.addUser("Arya Nobody");
//    SocialNetwork::Iterator it2 = GoT.find(tempStr);
//    for(auto i = it2; i != GoT.end(); i ++){
//        count ++;
//    }
//    cout << "How about now? this one is also nobody. " << count <<  " = 2 (ans)" << endl << endl;
//    assert(count == 2);
//
//    cout << "\nEveryone dies, Bronn gets a castle" << endl;
    return 0;
}
