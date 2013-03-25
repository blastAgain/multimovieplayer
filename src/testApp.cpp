#include "testApp.h"



//--------------------------------------------------------------
testApp::testApp(char *w){
    int wt;


    multimovielist=string("multimovie.txt");

    wt = ofToInt(w);
    wt = (wt>0 && wt< 30)? wt :2;


//    bznumber = ofToInt(numbz);
//    bznumber = (bznumber>0 && bznumber< 10)? bznumber :1;// from 1 to 9



    udpsetup();

    ctlthread.app = this;
    ctlthread.wait = wt;
    ctlthread.startThread(false,false);

    readmovielist();

}

//--------------------------------------------------------------

void testApp::readmovielist(){

    vector <string> words;

    //Load file placed in bin/data
    ofFile file(multimovielist);

    if(!file.exists()){
        ofLogError("The file " + multimovielist + " is missing");
        exit();
    }

    ofBuffer buffer(file);
    int mcount=0;


    //Read file line by line
    while (!buffer.isLastLine()) {
        string line = buffer.getNextLine();

        //Split line into strings
        //Store strings into a custom container
        vector<string> words = ofSplitString(line, ",");

        if(words.size()>=4){

            multiMovie mm;

            mm.id=mcount;
            mm.grid = ofToInt(words[0]);
            mm.moviefilename = string(words[1]);
            mm.transparency= ofToInt(words[2]);
            mm.loopstate= ofToInt(words[3]);

            mm.myMovie.loadMovie(mm.moviefilename);
            mm.myMovie.play();
            mm.endframe=mm.myMovie.getTotalNumFrames();
            mm.myMovie.setLoopState((ofLoopType)mm.loopstate);

            //Save multiMovie
            mmovie.push_back(mm);

            //Debug output
            ofLog(OF_LOG_ERROR,"id: "+ofToString(mcount) +" moviefile: "+ mm.moviefilename + " grid: "+ ofToString(mm.grid)+ " trans: "+ ofToString(mm.transparency));

            mcount++;
        }
        else{
            ofLog(OF_LOG_ERROR,"no cmd: "+ line);

        }

    }
    if(mcount>0&&mmovie.size()==mcount){
        mov_num=mcount;
        bznumber = mcount;
        ofLog(OF_LOG_ERROR,"read movie count: " + ofToString(mcount));
    }else{
        ofLog(OF_LOG_ERROR,multimovielist +" error");
        exit();
    }

}

//--------------------------------------------------------------

void testApp::udpsetup(){
    //receiving socket
    if(!udpconnection.Create()){
        ofLog(OF_LOG_ERROR,"Socket create failed");
        exit();
    }
    ofLog(OF_LOG_ERROR,"Socket create success");

    if(!udpconnection.BindMcast("230.0.0.1",4446)){
        ofLog(OF_LOG_ERROR,"Socket ConnectMcast failed");
        udpconnection.Close();
        exit();
    }
    ofLog(OF_LOG_ERROR,"Socket ConnectMcast success");

    ctlthread.connection = udpconnection;


    //sending socket
    if(!udpconnection_s.Create()){
        ofLog(OF_LOG_ERROR,"Socket create failed");
        exit();
    }
    ofLog(OF_LOG_ERROR,"Socket create success");

    if(!udpconnection_s.ConnectMcast("230.0.0.1",4446)){
        ofLog(OF_LOG_ERROR,"Socket ConnectMcast failed");
        udpconnection_s.Close();
        exit();
    }
    ofLog(OF_LOG_ERROR,"Socket ConnectMcast success");

}



//--------------------------------------------------------------

void testApp::exit(){

    ctlthread.stopThread();

    /** \brief
    if(udpconnection.Close())
        ofLog(OF_LOG_ERROR,"Receive Socket closed");
    else
        ofLog(OF_LOG_ERROR,"Receive Socket close fail");

    if(udpconnection_s.Close())
        ofLog(OF_LOG_ERROR,"Sending Socket closed");
    else
        ofLog(OF_LOG_ERROR,"Sending Socket close fail");
     */


}


//--------------------------------------------------------------
void testApp::setup(){

    ofSetVerticalSync(true);
	ofSetFrameRate(60);

    for(int i=0;i<mov_num;i++)
        mmovie[i].myMovie.play();

    bz.resize(bznumber); // allocate space for bz

	// grid resolution of the warp (10x10 is good)

	for(int i =0; i<bznumber; i++){
        bz[i].setup(mmovie[i].grid);
        bz[i].id=i;
        bz[i].setPresetfilename();
        bz[i].keyPressed('C');//hide anchors
        bz[i].keyPressed('p');//show preset
        bz[i].calcbezier=false;;//dont calc bezier when presentation
	}
		//hk
	ofEnableAlphaBlending();

    ofBackground(0, 0,0);
    ofSetColor(255,255,255);
    ofSetFullscreen(true);


}

//--------------------------------------------------------------
void testApp::update(){
    for(int i; i<bznumber;i++)
        mmovie[i].myMovie.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	//serie of homographies forming a bezier surface texture warp
//hk change for multi bz and omit calc for bezier points when presentation
/*
	bz.draw(myMovie.getTextureReference());
*/
    for(int i=0; i<bznumber; i++){
        if(bz[i].show){
            ofEnableBlendMode((ofBlendMode) mmovie[i].transparency );
            bz[i].draw(mmovie[i].myMovie.getTextureReference());
        }
    }

    if(memo)
        status();

}

//--------------------------------------------------------------
void testApp::status(){
    string ss1;

        // infos about controls
        ofDrawBitmapString("c: show/hide controls", 10,10);
        ofDrawBitmapString("a: corner/anchor controls", 10,20);
        ofDrawBitmapString("s: save", 10,30);
        ofDrawBitmapString("d: default", 10,40);
        ofDrawBitmapString("p: preset (last saved)", 10,50);

        ss1="grid "+ofToString(mmovie[curbz].grid)+" filename "+mmovie[curbz].moviefilename;
        ofDrawBitmapString( ss1, 10,60);
        ss1="current BezierSurface "+ofToString(curbz+1)+" /"+ ofToString(bznumber);
        ofDrawBitmapString( ss1, 10,70);

//        ss1="premouseX: "+ofToString(bz[curbz].premousePosX)+" mousePosX: "+ ofToString(bz[curbz].mousePosX);
//        ofDrawBitmapString( ss1, 10,80);

//        ss1="cornerselected: "+ofToString(bz[curbz].cornerselected ? "true":"false")+" mousePosX: ";
//        ofDrawBitmapString( ss1, 10,90);


}

//--------------------------------------------------------------

void testApp::keyPressed(int key){
    int f;

    switch(key) {
        //for point editing
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            for(int i; i<bznumber;i++){
                bz[i].keyPressed('C');
            }
            curbz = (key-0x30)<=(bznumber) ? key-0x31:bznumber-1;
            curbz = (curbz<0) ? 0:curbz;
            bz[curbz].keyPressed('c');
            break;
        case '0'://show all
            for(int i; i<bznumber;i++){
                bz[i].show=true;
                bz[i].keyPressed('C');
            }
            break;

        case OF_KEY_BACKSPACE://show and hide BezierWarp
            bz[curbz].show=bz[curbz].show? false :true;
            break;

		case 'm':
			memo=true;// show memo
            bz[curbz].keyPressed('c');//show anchors
			break;
		case 'M':
			memo = false;// hide memo
            bz[curbz].keyPressed('C');//hide anchors
			break;

		case 'b'://set background black
            ofBackground(0, 0,0);
            ofSetColor(255,255,255);
			break;

		case 'B'://set background white
            ofBackground(255, 255,255);
            ofSetColor(0,0,0);
			break;

		case 'S'://save all bezierposition
            for(int i; i<bznumber;i++)
                bz[i].save();
			break;


            //for movie control
        case 'g':// PAUSE
            mmovie[0].myMovie.setPaused(true);
            f=mmovie[0].myMovie.getCurrentFrame();
            sendCmdAll( (char *)("A"+ofToString(f)).c_str() );
            break;
        case 'G':// UNPAUSE
            mmovie[0].myMovie.setPaused(false);
            sendCmdAll( "FOWARD" );
            break;

        case OF_KEY_DOWN:// PAUSE_STARTPOS
            mmovie[0].myMovie.setPaused(true);
            mmovie[0].myMovie.setPosition(0);
            sendCmdAll( "STARTM" );
            break;

        case OF_KEY_UP://PAUSE_ENDPOS
            mmovie[0].myMovie.setPaused(true);
            mmovie[0].myMovie.setFrame(mmovie[0].endframe);
            sendCmdAll( "ENDPOS" );
            break;

		case 'F':
			ofSetFullscreen(false);

			fullscreen=false;
			break;

        case 'f':
			ofSetFullscreen(true);

			fullscreen = true;
			break;


        default:
            bz[curbz].keyPressed(key);


    }

}



//--------------------------------------------------------------
void testApp::keyPressed(int key, bool inner){
    ofLog(OF_LOG_ERROR,"Inner key press");

    switch(key) {

        case 'g':// PAUSE
            mmovie[0].myMovie.setPaused(true);
            break;
        case 'G':// UNPAUSE
            mmovie[0].myMovie.setPaused(false);
            break;

        case OF_KEY_DOWN:// PAUSE_STARTPOS
            mmovie[0].myMovie.setPaused(true);
            mmovie[0].myMovie.setPosition(0);
            break;

        case OF_KEY_UP://PAUSE_ENDPOS
            mmovie[0].myMovie.setPaused(true);
            mmovie[0].myMovie.setFrame(mmovie[0].endframe);
            break;

		case 'F':
			ofSetFullscreen(false);

			fullscreen=false;
			break;
		case 'f':
			ofSetFullscreen(true);

			fullscreen = true;
			break;

		case 'm':
			memo=true;// show memo
            bz[curbz].keyPressed('c');//show anchors
			break;
		case 'M':
			memo = false;// hide memo
            bz[curbz].keyPressed('C');//hide anchors
			break;

        default:
            bz[curbz].keyPressed(key);


    }

}
//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if(bz[curbz].show)bz[curbz].mouseDragged(x, y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(bz[curbz].show)bz[curbz].mousePressed(x, y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------

void testApp::sendCmdAll( char* ds ){

    if(!udpconnection_s.SendAll( ds, (int)strlen(ds)))
        ofLog(OF_LOG_ERROR,"sendCmdAll: "+ ofToString(ds)+" failed");
    else
        ofLog(OF_LOG_ERROR,"sendCmdAll: "+ ofToString(ds)+" success");


}

//--------------------------------------------------------------

void testApp::pauseAt( int f ){

    mmovie[0].myMovie.setPaused(true);
    mmovie[0].myMovie.setFrame(f);
    ofLog(OF_LOG_ERROR,"pauseAt: "+ ofToString(f));
}
