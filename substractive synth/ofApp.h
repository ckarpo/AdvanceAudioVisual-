#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
    
    void audioOut(float * buffer,int bufferSize, int nChannels);
    int trigger;
    unsigned bufferSize, sampleRate;
    double outputs[2];
    
    maxiOsc osc1, LFO1, LFO2, phasor1; 
    maxiFilter filter1, filter2;
    double oscOut, filterOut, ampOut, LFO1Out, LFO2Out;
    
    int cutoff, currentCount;

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
		
};
