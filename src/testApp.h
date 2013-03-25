#pragma once

#include "ofMain.h"
#include "ofxBezierWarp.h"

#include "ofxNetwork.h"
#include "ofxNetworkUtils.h"
//#include "ofxUDPManager.h"



// this h file has the definition for an object that uses the threaded addon:
#include "MyThread.h"

class multiMovie{
    public:

    ofVideoPlayer myMovie;
    int id;
    int grid;
    string moviefilename;
    int transparency;
    int endframe;
    int loopstate;



};

class testApp : public ofBaseApp{

	public:
	    testApp(  char *w);
		void setup();
		void update();
		void draw();

		void readmovielist();
		void status();
		void udpsetup();
		void sendCmdAll(char * dString);
		void pauseAt( int frame );

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit();

		void keyPressed  (int key, bool inner);


	vector <ofxBezierWarp> bz;
	int bznumber=1;
	int curbz=0;

    vector <multiMovie> mmovie;
    int mov_num;
    int cur_mov;
	string multimovielist;


	bool fullscreen=true;
	bool memo=false;
	ofxUDPManager udpconnection;
	ofxUDPManager udpconnection_s;
 //   Byte buf[100];

    MyThread ctlthread;

};
