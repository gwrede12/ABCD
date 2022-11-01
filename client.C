/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants

#include "SIMPLESOCKET.H"

using namespace std;

int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg,x,y,data;

	//connect to host
	c.conn(host , 2022);

	int i=0;
	while(1)
	{ // send and receive data
        cout<<"Please enter the Coords!"<<endl;
        cout<<"X: ";
        cin>>x;
        cout<<"Y: ";
        cin>>y;
		cout << "client sends: " << x <<" and "<<y<< endl;
        data= x+y;
		c.sendData(data);
		msg = c.receive(32);
		cout << "got response:" << msg << endl;
		sleep(1);

	}
}


