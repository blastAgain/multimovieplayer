//
    #include "testApp.h"

    //--------------------------------------------------------------
    void MyThread::start(testApp* p, bool bl, bool logging)
    {

        // Get parent app
        app = p;

        // Initialize note count
        notes = 0;

        // Start thread -- blocking, venbose
        startThread(bl, logging);

    }

    //--------------------------------------------------------------
    void MyThread::stop()
    {

        // Stop thread
        stopThread();

    }

    //--------------------------------------------------------------
    void MyThread::threadedFunction()
    {

        // Thread is running
        while (isThreadRunning() != 0)
        {
            connection.Receive(buf, 50);
            ofLog(OF_LOG_ERROR,buf);
            switch(buf[0]){
                case 'f':
                case 'F':
                    //forward play
                    app->keyPressed('G',inner);
                    break;

                case 'p':
                case 'P':
                    //PAUSE
                    app->keyPressed('g',inner);
                    break;

                case 'A':
                    //Pause at frame
                    app->pauseAt(atoi(&buf[1]));
                    break;

                case 'e':
                case 'E':
                    //end frame
                    app->keyPressed(OF_KEY_UP,inner);
                    break;

                case 'S':
                case 's':
                    //start frame
                    app->keyPressed(OF_KEY_DOWN,inner);
                    break;

                case 'L':
                    //Fullscreen
                    app->keyPressed('f',inner);
                    break;

            }
            sleep(wait);


        }

    }
