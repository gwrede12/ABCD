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
	string msg,data;
    int x, y;
	//connect to host
	c.conn(host , 2022);

	int i=0;
	while(1)
	{ // send and receive data

        try
        {
            cout<<"Please enter the Coords!"<<endl;
            cout<<"X: ";
            cin>>x;
            cout<<"Y: ";
            cin>>y;
            if(((x<1)||(x>10))||((y<1)||(y>10)))
            {
                throw string("wrong values");
            }
            cout << "client sends: " << x <<" and "<<y<< endl;
            string SendX = to_string(x);
            string SendY = to_string(y);
            data= SendX+SendY;
            c.sendData(data);
            msg = c.receive(32);
            cout << "got response:" << msg << endl;
            sleep(1);
        }
        catch(string clientExeption )
            {
                cout<<"Error: "<<clientExeption<<endl;
            }
        catch(...)
            {
                cout<<"Error: unknown"<<endl;
            }
	}
}


