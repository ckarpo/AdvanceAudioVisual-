#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxOsc.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
    
    void audioOut(float * buffer,int bufferSize, int nChannels);
    int trigger;
    unsigned bufferSize, sampleRate;
    double outputs[2];
    double currentSample;
    
    ofxMaxiSample beat1,pan, shake, bell;
    
    maxiMix mix;
    maxiFilter myFilter, myFilter2;
    
    maxiOsc timer, osc1,osc2,osc3, myPhasor, myPhasor2;
    double myOsc1,myOsc2,myOsc3;
    int currentCount,lastCount,playHead;
    int beat1trigger, panTrigger,shakeTrigger,bellTrigger ;
    int hit[16]={1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0};
    int panHit[16]={0,1,1,1,1,1,0,1,0,0,1,1,0,0,0,1};
    int shakeHit[16]={0,1,0,1,1,0,1,0,1,0,1,0,1,0,0,0};
    int bellHit[16]={0,0,0,1,0,1,1,0,0,1,0,0,0,1,1,0};
    double sample;
    
    
};
