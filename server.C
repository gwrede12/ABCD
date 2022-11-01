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


class SinkShips:public TCPserver
{
public:
    int x_;
    int y_;
    int hit_;
public:
    SinkShips();
    ~SinkShips();
    void runSinkShips();
    void setCoordX();
    void setCoordY();
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
}

SinkShips::~SinkShips()
{
    x_=0;
    y_=0;
}

void SinkShips::runSinkShips()
{

        res = w.shoot(x_,y_);
		hit_= res;
		cout << "shoot: (" << x_ << ", " << y_ << ") --> " << res << endl;
	if(res != TASK3::GAME_OVER)
	{
        exit(0);
	}
	w.printBoard();
}

void SinkShips::setCoordX()
{
    char a = dataRecv_[0];
    int ia= (int)a-48;
    x_=ia;
}
void SinkShips::setCoordY()
{
    char b = dataRecv_[1];
    int ib= (int)b-48;
    y_=ib;
}

string SinkShips::myResponse(string input)
{

    setCoordX();
    setCoordY();
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


