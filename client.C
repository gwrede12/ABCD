/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants
#include <sstream>
#include <cstdio>
#include <time.h>

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

	while(1)
	{ // send and receive data

        try
        {
        cout<< "clints sends: "<<"INIT"<<endl;
            c.sendData("INIT");
            sleep(5);
            msg = c.receive(32);
            cout << "got response: " << msg << endl;
            int x[10] = {1,2,3,4,5,6,7,8,9,10};
            int y[10] = {1,2,3,4,5,6,7,8,9,10};
            int i= 0;
            int k= 0;
            int quantity = 0;
            for (i=0; i<=10;i++)
            {for (k=0; k<=10;k++)
            {
                    if(((x[i]<1)||(x[i]>10))||((y[k]<1)||(y[k]>10)))
                    {
                        //throw string("wrong values");
                        continue;
                    }
                        cout << "client sends: " << x[i] <<" and "<<y[k]<< endl;
                        stringstream Coords;
                        Coords<<"COORD["<<x[i]<<","<<y[k]<<"]";
                        string data = Coords.str();
                        c.sendData(data);
                        msg = c.receive(32);
                        if(msg=="0")
                        {
                            cout << "got response: " << "miss" << endl;
                        }
                        if(msg=="1")
                        {
                            cout << "got response: " << "hit" << endl;
                        }
                        if(msg == "GAME_OVER")
                        {
                            quantity = (((x[i]-1)*10)+y[k]);
                            cout << "got response: " << "GAME_OVER" << endl;
                            cout << "Shoots: "<<quantity<<endl;
                            break ;
                        }
                        sleep(0.5);
            }
            }


        }
        catch(string clientExeption )
            {
                cout<<"Error: "<<clientExeption<<endl;
            }
        catch(...)
            {
                cout<<"Error: unknown"<<endl;
            }


    //Zufallszahlen

    try
        {
            srand(time(NULL));
            cout<< "clints sends: "<<"INIT"<<endl;
            c.sendData("INIT");
            sleep(5);
            msg = c.receive(32);
            cout << "got response: " << msg << endl;
            int quantity = 0;
            while(msg != "GAME_OVER")
            {
                    quantity++;
                    int x_rand=1+rand()%11;
                    int y_rand =1+rand()%11;
                    cout << "client sends: " << x_rand <<" and "<<y_rand<< endl;
                    stringstream Coords;
                    Coords<<"COORD["<<x_rand<<","<<y_rand<<"]";
                    string data = Coords.str();
                    c.sendData(data);
                    msg = c.receive(32);
                    if(msg=="0")
                    {
                        cout << "got response: " << "miss" << endl;
                    }
                    if(msg=="1")
                    {
                        cout << "got response: " << "hit" << endl;
                    }
                        if(msg == "GAME_OVER")
                        {
                            cout << "got response: " << "GAME_OVER" << endl;
                            cout << "Shoots: "<<quantity<<endl;
                            break ;
                        }
                        sleep(0.5);
            }
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


