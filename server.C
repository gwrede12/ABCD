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
/**
 *
 *  \class SinkShips
 *  \brief The class defining the  game of sink ships.
 *
 */
class SinkShips:public TCPserver
{
private:
    /**
     *
     *  \brief Member for the x-coordinate
     *
     */
    int x_;
    /**
     *
     *  \brief Member for the y-coordinate
     *
     */
    int y_;
    /**
     *
     *  \brief Member for the result of the shoot
     *
     */
    int res_;
    /**
     *
     *  \brief Member for the game world
     *
     */
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
	 * \brief runs the game sink ships and sendend the results back to the client
	 *
	 */
    string myResponse(string input);

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
    try
    {
    int x, y;
    //server is creating a new World for game
    if(input.compare(0,4,"INIT") == 0)
    {
        delete w;
        w = new TASK3::World;
        return string("OK");
    }
    //Server is closing
    else if(input.compare(0,5,"CLOSE") == 0)
    {
        delete w;
        exit(0);
    }
    //Server evaluate the shoot
    else if (input.compare(0,6,"COORD[") == 0){
        sscanf(input.c_str(), "COORD[%i,%i]", &x,&y);
        if(x<1)
        {
            return string("Wrong x parameter");
        }
        else if(y<1)
        {
            return string("Wrong y parameter");
        }
        else if(x>10)
        {
            return string("Wrong x parameter");
        }
        else if(y>10)
        {
            return string("Wrong y parameter");
        }
        x_=x;
        y_=y;
        int res = w->shoot(x_,y_);
        res_=res;
        if(res_ == TASK3::GAME_OVER)
        {
            cout << "shot: (" << x_ << ", " << y_ << ") --> " << "GAME_OVER" << endl;
            w->printBoard();
            return string("GAME_OVER");
        }
        else
        {
            cout << "shot: (" << x_ << ", " << y_ << ") --> " << res_ << endl;
            if(res_ == 0)
            {
            w->printBoard();
            return string("0");
            }
            else
            {
            w->printBoard();
            return string("1");
            }
        }

    }else
    {
        return string("unknown command");
    }
    }
    catch(...)
        {
            cout<<"Error: unknown"<<endl;
        }

}
