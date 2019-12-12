#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofSetFrameRate(60);
    ofSetCircleResolution(60);
    
    
    sampleRate=44100;
    bufferSize=512;
    
    trigger=0;
    ofSoundStreamSetup(2,0,this,sampleRate,bufferSize,4);
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0);
    ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,40 *currentCount);
    int y1= LFO1Out*100+50;
    int y2= LFO1Out*105+150;
    ofSetLineWidth(10);
    ofDrawLine(0, y1, ofGetWidth(), y1);
    ofDrawLine(0, y2, ofGetWidth(), y2);
    
    
}

void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    for (unsigned i=0; i<bufferSize; i++){
        currentCount=phasor1.phasor(0.8,1,9);
        int mySequence[9]={200,300,350,450,500,350,200,350,500};
        LFO1Out=LFO1.sinewave(3)*3;// the 50 is the intex it will go from -50 to +50 .
        
        LFO2Out=LFO2.sinewave(0.1)*1000;
        oscOut= osc1.sawn(filter2.lopass(mySequence[currentCount]+LFO1Out,0.001));
        cutoff=1500;
        
        filterOut=filter1.lores(oscOut,cutoff+LFO2Out,10);
        //ampOut=0.4;
        output[i * nChannels]=filterOut;//oscOutput;
        output[i * nChannels+1]=filterOut;//oscOutput;
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
