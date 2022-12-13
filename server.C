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
TASK3::World w(10,10,1,2,3,4);
TASK3::ShootResult res;


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
    int hit_;
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
    void runSinkShips();
    /**
	 *
	 * \brief setting the x coordinate of the shoot.
	 *
	 * \param x char the x coordinate from the client.
	 *
	 */
    void setCoordX(char x);
    /**
	 *
	 * \brief setting the y coordinate of the shoot.
	 *
	 * \param y char the y coordinate from the client.
	 *
	 */
    void setCoordY(char y);
    /**
	 *
	 * \brief server response to the client.
	 *
	 * \param input string from the client.
	 *
	 * \return string contains the response to the client.
	 *
	 */
    string myResponse(string input);
     /**
	 *
	 * \brief shows the card of the game.
	 *
	 */
    void Coord();
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
    hit_=0;
}

SinkShips::~SinkShips()
{
    x_=0;
    y_=0;
    hit_=0;
}

void SinkShips::runSinkShips()
{

        res = w.shoot(x_,y_);
		hit_= res;
		cout << "shoot: (" << x_ << ", " << y_ << ") --> " << res << endl;
	if(res == TASK3::GAME_OVER)
	{
        exit(0);
	}
	w.printBoard();
}

void SinkShips::setCoordX(char x)
{
        int ia= (int)x-48;
        x_=ia;

}
void SinkShips::setCoordY(char y)
{
        int ib= (int)y-48;
        y_=ib;
}

string SinkShips::myResponse(string input)
{
    Coord();
    runSinkShips();

    if(hit_== 0)
    {
        return string("BESIDES");
    }
    else
    {
        return string("Hit!");
    }


}
void SinkShips::Coord()
{
   if(dataRecv_[2]=='\0')
   {
        setCoordX(dataRecv_[0]);
        setCoordY(dataRecv_[1]);
   }
   else if((dataRecv_[2] !='\0')&&(dataRecv_[3] =='\0'))
   {
        if(dataRecv_[1]=='0')
        {
            x_=10;
            setCoordY(dataRecv_[2]);
        }
        else
        {
            y_=10;
            setCoordX(dataRecv_[0]);
        }
   }
   else if((dataRecv_[3] !='\0')&&(dataRecv_[4] =='\0'))
   {
        x_=10;
        y_=10;
   }
}

