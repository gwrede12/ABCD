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
    for(i=0;i<1;i++)
    {
        try
        {   cout<<"Strategie: Alle Felder der Reihe nach abschießen"<<endl;
            cout<< "clints sends: "<<"INIT"<<endl;
            c.sendData("INIT");
            msg = c.receive(32);
            cout << "got response: " << msg << endl;
            if(msg == "OK")     //Wenn der Server erfolgreich das Spielfeld geändert hat
            {
            int x[11];
            x[1]=1, x[2]=2,x[3]=3,x[4]=4,x[5]=5,x[6]=6,x[7]=7,x[8]=8,x[9]=9,x[10]=10;
            int y[11];
            y[1]=1, y[2]=2,y[3]=3,y[4]=4,y[5]=5,y[6]=6,y[7]=7,y[8]=8,y[9]=9,y[10]=10;
            int i= 0,k= 0,quantity = 0;
            for (i=1; i<=10;i++){
            for (k=1; k<=10;k++)
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
    for(i=0;i<1;i++)
    {
        try
        {
            cout<<"Strategie: Zufällig Schießen"<<endl;
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
	for(i=0;i<1;i++)
	{
            cout<<"Strategie: Bei Treffer, die Felder drum herum auch abschießen"<<endl;
            cout<< "clints sends: "<<"INIT"<<endl;
            c.sendData("INIT");
            sleep(0);
            msg = c.receive(32);
            cout << "got response: " << msg << endl;
            int quantity = 0;
            while(msg != "GAME_OVER"){

    int map[11][11] = {}; // Erzeuge Map zum Merken, wo bereits hin geschossen wurde. Jeder Eintrag ist 0. Map ist 1 Zeile und Spalte zu groß, um Umrechnung zu sparen

    int x=0;
    int y=0;
    for (int i=0; i<10; i++){
        y++;
        x=0;
        for (int j=0; j<10; j++){
            x++;
            if (y%2==1){
                if ((x%2==1) && (map[x][y]==0)){
                    cout << "x=" << x << "; y=" << y << endl;

                    quantity++;
                    cout << "client sends: " << x <<" and "<< y << endl;
                    stringstream Coords;
                    Coords<<"COORD["<<x<<","<<y<<"]";
                    string data = Coords.str();
                    c.sendData(data);
                    map[x][y]=1;
                    msg = c.receive(32);
                    if(msg=="0")
                    {
                        cout << "got response: " << "miss" << endl;
                    }
                    if(msg=="1")
                    {
                        cout << "got response: " << "hit" << endl;

                        //Suche nach in Umgebung XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


                        if  ((x-1>0) && (map[x-1][y]==0)){ // Schieße Links
                            quantity++;
                            cout << "client sends: " << x-1 <<" and "<< y << endl;
                            stringstream Coords;
                            Coords<<"COORD["<< x-1 <<","<< y <<"]";
                            string data = Coords.str();
                            c.sendData(data);
                            map[x-1][y]=1;
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


                        if  ((y-1>0) && (map[x][y-1]==0)){ // Schieße oben
                            quantity++;
                            cout << "client sends: " << x <<" and "<< y-1 << endl;
                            stringstream Coords;
                            Coords<<"COORD["<< x <<","<< y-1 <<"]";
                            string data = Coords.str();
                            c.sendData(data);
                            map[x][y-1]=1;
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


                        if  ((x+1<11) && (map[x+1][y]==0)){ // Schieße Rechts
                            quantity++;
                            cout << "client sends: " << x+1 <<" and "<< y << endl;
                            stringstream Coords;
                            Coords<<"COORD["<< x+1 <<","<< y <<"]";
                            string data = Coords.str();
                            c.sendData(data);
                            map[x+1][y]=1;
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


                        if  ((y+1<11) && (map[x][y+1]==0)){ // Schieße unten
                            quantity++;
                            cout << "client sends: " << x <<" and "<< y+1 << endl;
                            stringstream Coords;
                            Coords<<"COORD["<< x <<","<< y+1 <<"]";
                            string data = Coords.str();
                            c.sendData(data);
                            map[x][y+1]=1;
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
                                        cout <<quantity<<endl;
                                        break ;
                                    }
                                    sleep(0.5);
                        }
                        // FEUERN IN UMGEBUNG ABGESCHLOSSEN__________________________________________________________
                    }
                        if(msg == "GAME_OVER")
                        {
                            cout << "got response: " << "GAME_OVER" << endl;
                            cout << "Shoots: "<<quantity<<endl;
                            break ;
                        }
                        sleep(0.5);

                }else{
                    continue;
                }
            }else if (y%2==0){
                if ((x%2==0) && (map[x][y]==0)){
                    cout << "x=" << x << "; y=" << y << endl;

                    quantity++;
                    cout << "client sends: " << x <<" and "<< y << endl;
                    stringstream Coords;
                    Coords<<"COORD["<<x<<","<<y<<"]";
                    string data = Coords.str();
                    c.sendData(data);
                    map[x][y]=1;
                    msg = c.receive(32);
                    if(msg=="0")
                    {
                        cout << "got response: " << "miss" << endl;
                    }
                    if(msg=="1")
                    {
                        cout << "got response: " << "hit" << endl;

                        //Suche nach in Umgebung XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


                        if  ((x-1>0) && (map[x-1][y]==0)){ // Schieße Links
                            quantity++;
                            cout << "client sends: " << x-1 <<" and "<< y << endl;
                            stringstream Coords;
                            Coords<<"COORD["<< x-1 <<","<< y <<"]";
                            string data = Coords.str();
                            c.sendData(data);
                            map[x-1][y]=1;
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


                        if  ((y-1>0) && (map[x][y-1]==0)){ // Schieße oben
                            quantity++;
                            cout << "client sends: " << x <<" and "<< y-1 << endl;
                            stringstream Coords;
                            Coords<<"COORD["<< x <<","<< y-1 <<"]";
                            string data = Coords.str();
                            c.sendData(data);
                            map[x][y-1]=1;
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
                                        cout <<quantity<<endl;
                                        break ;
                                    }
                                    sleep(0.5);
                        }


                        if  ((x+1<11) && (map[x+1][y]==0)){ // Schieße Rechts
                            quantity++;
                            cout << "client sends: " << x+1 <<" and "<< y << endl;
                            stringstream Coords;
                            Coords<<"COORD["<< x+1 <<","<< y <<"]";
                            string data = Coords.str();
                            c.sendData(data);
                            map[x+1][y]=1;
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


                        if  ((y+1<11) && (map[x][y+1]==0)){ // Schieße unten
                            quantity++;
                            cout << "client sends: " << x <<" and "<< y+1 << endl;
                            stringstream Coords;
                            Coords<<"COORD["<< x <<","<< y+1 <<"]";
                            string data = Coords.str();
                            c.sendData(data);
                            map[x][y+1]=1;
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
                        // FEUERN IN UMGEBUNG ABGESCHLOSSEN__________________________________________________________

                    }
                        if(msg == "GAME_OVER")
                        {
                            cout << "got response: " << "GAME_OVER" << endl;
                            cout << "Shoots: "<<quantity<<endl;
                            break ;
                        }
                        sleep(0.5);

                }else{
                    continue;
                }
            }
        }
    }
    }
	}
	//Server closing
    c.sendData("CLOSE");

}


