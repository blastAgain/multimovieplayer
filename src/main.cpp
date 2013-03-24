#include "testApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(int argc, char* argv[] ){
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1500,900, OF_WINDOW);			// <-------- setup the GL context
    long d;

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:

	if(argc==2)
            ofRunApp( new testApp( argv[1]));
    else ofRunApp( new testApp("2"));

}
