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
    int i=0;
	//connect to host
	c.conn(host , 2022);
    //Schießt Reihe für Reihe
    for(i=0;i<3;i++)
    {
        try
        {
            cout<< "clints sends: "<<"INIT"<<endl;
            c.sendData("INIT");
            msg = c.receive(32);
            cout << "got response: " << msg << endl;
            if(msg == "OK")     //Wenn der Server erfolgreich das Spielfeld geändert hat
            {
            int x[10] = {1,2,3,4,5,6,7,8,9,10};
            int y[10] = {1,2,3,4,5,6,7,8,9,10};
            int i= 0,k= 0,quantity = 0;
            for (i=0; i<=10;i++){
            for (k=0; k<=10;k++)
            {

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
                        else if(msg=="1")
                        {
                            cout << "got response: " << "hit" << endl;
                        }
                        else if(msg == "GAME_OVER")
                        {
                            quantity = (((x[i]-1)*10)+y[k]);
                            cout << "got response: " << "GAME_OVER" << endl;
                            cout<<"shoots: "<<quantity<<endl;
                            break ;
                        }else{throw string("unknown");}
            }}}else{ throw string("Server not initialized");}

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
    //Schuss nach Zufallszahlen
    for(i=0;i<3;i++)
    {
        try
        {
            srand(time(NULL));
            cout<< "clints sends: "<<"INIT"<<endl;
            c.sendData("INIT");
            msg = c.receive(32);
            if(msg == "OK")
            {
            cout << "got response: " << msg << endl;
            int quantity = 0;
            while(msg != "GAME_OVER")
            {
                    quantity++;
                    int x_rand=1+rand()%10;
                    int y_rand =1+rand()%10;
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
                    else if(msg=="1")
                    {
                        cout << "got response: " << "hit" << endl;
                    }
                    else if(msg == "GAME_OVER")
                    {
                            cout << "got response: " << "GAME_OVER" << endl;
                            cout <<"shoots: "<<quantity<<endl;
                            break ;
                    }else{throw string("Error");}

            }
            }else{ throw string("Server not initialized");}

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
	//Server closing
    c.sendData("CLOSE");

}


