#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

//    ofBackground(255);
   ofSetFrameRate(60);
//    ofSetCircleResolution(50);
    
    
    sampleRate=44100;
    bufferSize=512;
    
    trigger=0;
    ofSoundStreamSetup(2,0,this,sampleRate,bufferSize,4);
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    

    beat1.load("/Users/christinakarpodini/Desktop/Maximilian-master/blip.wav");
    pan.load("/Users/christinakarpodini/Desktop/Maximilian-master/mono samples /cow_bell_mid4mono.wav");
    shake.load("/Users/christinakarpodini/Desktop/Maximilian-master/mono samples /stick_shaker2mono.wav");
    bell.load("/Users/christinakarpodini/Desktop/Maximilian-master/mono samples /triangle1mono.wav");

    
}
void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    for (unsigned i=0; i<bufferSize; i++){

        currentCount=(int)timer.phasor(8);


        if (lastCount!=currentCount){
            beat1trigger=hit[playHead%16];
            panTrigger=panHit[playHead%16];
            shakeTrigger=shakeHit[playHead%16];
            bellTrigger=bellHit[playHead%16];
            playHead++;
            lastCount=0;
        }
        if (beat1trigger==1){
            beat1.trigger();
        }

        if (panTrigger==1){
            pan.trigger();
        }
        if (shakeTrigger==1){
            shake.trigger();
        }
        if (bellTrigger==1){
            bell.trigger();
        }

        myOsc1=osc1.phasor(0.025,0.2,0.9);
        myOsc2=osc2.sinewave(0.2);

        if(playHead==0){
            
            
            currentSample=hit[playHead]*beat1.playOnce()+
            panHit[playHead]*pan.playOnce()+
            shakeHit[playHead]*shake.playOnce()+
            bellHit[playHead]*bell.playOnce();
        }
        else{
            currentSample=(myFilter.lopass(beat1.playOnce(),myPhasor.phasor(0.08))+
                    pan.play(myOsc2,0,pan.length)+
                    shake.playOnce()*myOsc1+
                    myFilter2.lopass(bell.playOnce(),myPhasor2.phasor(0.2)));

        }

        //currentSample=beat1.playOnce();
//        currentSample= osc3.sinewave(440);
        //mix.stereo(currentSample, outputs, 0.5);
        
        output[i *nChannels]=currentSample;
        output[i *nChannels+1]=currentSample;
        
    }
}
//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
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
