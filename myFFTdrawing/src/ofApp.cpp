#include "ofApp.h"
#include "maximilian.h" // include the miximilian library


//-------------------------------------------------------------
ofApp::~ofApp() {
}

//--------------------------------------------------------------
void ofApp::setup(){

    ofEnableAlphaBlending();
    ofSetupScreen();
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    ofSetCircleResolution(60);
    threshold=60;
    option=0;

   
    //audio setup
    /* This is stuff you always need.*/
    sampleRate = 44100; /* Sampling Rate */
    int initialBufferSize = 512;    /* Buffer Size. you have to fill this buffer with sound*/
    
    //fft setup
    fftSize = 1024;
    mfft.setup(fftSize, 512, 256);
    ifft.setup(fftSize, 512, 256);
    
    nAverages = 12;
    oct.setup(sampleRate, fftSize / 2, nAverages);
    
    mfccs = (double*)malloc(sizeof(double) * 13);
    mfcc.setup(512, 42, 13, 20, 20000, sampleRate);
    
    ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);
    
    ofSoundStreamSettings settings;
    
    auto devices = soundStream.getMatchingDevices("default");
    if (!devices.empty()) {
        settings.setInDevice(devices[0]);
    }
    
    settings.setInListener(this);
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 2;
    settings.bufferSize = initialBufferSize;
    soundStream.setup(settings);
    
   // samp.load("/Users/christinakarpodini/Desktop/of_v0.10.0_osx_release/apps/myApps/myFFTdrawing/bin/data/beat2.wav");
    // i am keeping this sound for debug 
    
    samp.load("/Users/christinakarpodini/Desktop/of_v0.10.0_osx_release/apps/myApps/myFFTdrawing/bin/data/joy_mono_16.wav");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //box drawing
    int point1X=ofGetWidth()/3+100;
    int point1Y=ofGetHeight()/3+100;
    int point1Z=ofGetHeight()/2;
    
    float fftTop = 250;
    float mfccTop = 350;
    float chromagramTop = 450;
    
  
    
    for (int i = 0; i < fftSize / 2; ++i) {
        //magnitudesDB took out
        float radius = mfft.magnitudes[i] * 10;
        float color = mfccs[i] *100 ;
        
        float  octave = oct.averages[i] / 20.0 * 100;
        
        
        if (option==1){
            ofSetColor(100,radius*10,color,color);
            offSet1= ofRandom(100,200);
            offSet2= ofRandom(100,200);
        }
        if (option==0){
            ofSetColor(100,radius*10,100,octave);
            offSet1= 0;
            offSet2= 0;
        }
        ofNoFill();
        
       
        
        if (radius < threshold){
            
        
            ofDrawBox(mouseX+offSet1, mouseY+offSet2, point1Z, octave, octave, octave);
           
        }
       
    }
    
    
 
    
}

void ofApp::audioOut(ofSoundBuffer& output) {
    std::size_t outChannels = output.getNumChannels();
    for (size_t i = 0; i < output.getNumFrames(); ++i) {
        sample=samp.play();
        
        //all this cide is from the class example
        if (mfft.process(sample)) {
            
            mfft.magsToDB();
            oct.calculate(mfft.magnitudesDB);
            
            float binFreq = 44100.0 / fftSize;
            float sumFreqs = 0;
            float sumMags = 0;
            float maxFreq = 0;
            int maxBin = 0;
            
            for (int i = 0; i < fftSize / 2; i++) {
                sumFreqs += (binFreq * i) * mfft.magnitudes[i];
                sumMags += mfft.magnitudes[i];
                if (mfft.magnitudes[i] > maxFreq) {
                    maxFreq = mfft.magnitudes[i];
                    maxBin = i;
                }
            }
            centroid = sumFreqs / sumMags; // ...or mfft.spectralCentroid();
            peakFreq = (float)maxBin * ( 44100/ fftSize);
            
            mfcc.mfcc(mfft.magnitudes, mfccs);
        }
        
        
        
        output[i * outChannels] = sample;
        output[i * outChannels + 1] = sample;
    
    }
}

void  ofApp::keyPressed(int key){
    if (key=='1'){
        
        option = 1;
       
        ofSetBackgroundAuto(false);
        
    }
}
void  ofApp::keyReleased(int key){
    if (key=='1'){
        option =0;
        ofSetBackgroundAuto(true);
        ofBackground(0);
        
    }
}
