


#include "ofMain.h"
#include "ofThread.h"

    class testApp;

    class MyThread : public ofThread{

    public:

        // Timing properties
        int notes;
        int notesPerPhrase;

        // Methods
        void start(testApp* p, bool bl, bool logging);
        void stop();
        void threadedFunction();

        // Parent application
        testApp* app;
        ofxUDPManager connection;

        char buf[100];
        bool inner=true;

        int wait=2;

    };


