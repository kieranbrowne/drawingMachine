#include "ofMain.h"
#include "ofApp.h"
#include "ofAppNoWindow.h"

//========================================================================
int main(int argc, char *argv[] ){

    if(argc >1){
        if(*argv[1]=='v'){
            ofSetupOpenGL(800,600, OF_WINDOW);
            ofRunApp( new ofApp());
        }
    }else if(true){
        ofAppNoWindow window;
        ofSetupOpenGL(&window,1024,768,OF_WINDOW);
        ofRunApp( new ofApp());
    }else{
        ofApp * app = new ofApp();
        app->setup();
        while(1){
            app->update();
        }
    }

}
