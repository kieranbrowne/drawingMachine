#include "ofMain.h"
#include "ofApp.h"
#include "ofAppNoWindow.h"

//========================================================================
int main(int argc, char *argv[] ){

    bool visual = false;
    bool hasWindow = true;
    
    if(argc>1) {
        if(*argv[1]=='v') visual = true;
        if(*argv[1]=='x') hasWindow = false;
    }

    // setup window
    if(hasWindow){
        ofSetupOpenGL(800,600, OF_WINDOW);
    }else{
        ofAppNoWindow window;
        ofSetupOpenGL(&window,1024,768,OF_WINDOW);
    }
    ofApp *app = new ofApp();
    app->visual = visual;
    ofRunApp( app );
}
