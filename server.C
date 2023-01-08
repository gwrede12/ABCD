/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include "SIMPLESOCKET.H"
#include "TASK3.H"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
//TASK3::World w(10,10,1,2,3,4);
//TASK3::ShootResult res;


/**
 *
 *  \class SinkShips
 *  \brief The class defining the  game of sink ships.
 *
 */
class SinkShips:public TCPserver
{
public:
    int x_;
    int y_;
    int res_;
    TASK3::World *w;
public:

    /**
	 *
	 * \brief constructor
	 *
	 */
    SinkShips();

    /**
	 *
	 * \brief destructor
	 *
	 */
    ~SinkShips();
    /**
	 *
	 * \brief runs the game sink ships
	 *
	 */

    string myResponse(string input);
     /**
	 *
	 * \brief shows the card of the game.
	 *
	 */
};

int main(){
	srand(time(nullptr));
	SinkShips SS;
    SS.run();
}

SinkShips::SinkShips():TCPserver(2022,25)
{
    x_=0;
    y_=0;
    res_=0;
    w=new TASK3::World;
}

SinkShips::~SinkShips()
{
    x_=0;
    y_=0;
    res_=0;
    delete w;
}


string SinkShips::myResponse(string input)
{
    int x, y;
    if(input == "INIT")
    {
        delete w;
        w = new TASK3::World;
        return string("OK");
    }
    else;
        sscanf(input.c_str(), "COORD[%i,%i]", &x,&y);
        x_=x;
        y_=y;
        int res = w->shoot(x_,y_);
        res_=res;
        cout << "shoot: (" << x_ << ", " << y_ << ") --> " << res_ << endl;
        w->printBoard();


	if(res_ == TASK3::GAME_OVER)
	{
        return string("GAME_OVER");
	}

    if(res_ == 0)
    {
        return string("0");
    }
    else
    {
        return string("1");
    }


}
