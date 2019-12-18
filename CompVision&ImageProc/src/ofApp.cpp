
#include "ofApp.h"


//-------------------------------------------------------------
ofApp::~ofApp() {
    
  
    
}


//--------------------------------------------------------------
void ofApp::setup(){
 
    //audio setup 
    sampleRate             = 44100; /* Sampling Rate */
    initialBufferSize    = 512;    /* Buffer Size. you have to fill this buffer with sound*/
    ofBackground(0,0,0);
    
   
    //image processing setup
    myTexture.allocate(320,240,GL_RGB);
    pixelout.allocate(320, 240, 1);
    lastPixels.allocate(320,240,3);
    myImage.load("rsz_dsc_0037.jpg"); 
    
    
    //camera setup
    myGrabber.listDevices();
    
    myGrabber.initGrabber(320,240);
    
    //audio
    ofSoundStreamSetup(2,0,this, sampleRate, initialBufferSize, 4);/* Call this last ! */
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofPixels pix;
    ofPixels myPixels;
    ofPixels myPixels2;
    
 
    //start of computer vision code
    myGrabber.update();
    
    //only try and process video when we have a new frame.
    if (myGrabber.isFrameNew()) {
        
        
        pixels = myGrabber.getPixels();
        
        
        for (int i = 0; i < 320*240*3; i+=3){
            
            //      pixelout[i]=pixels[i]* fabs(sample) * 10;//change brightness based on audio
            
        }
        //scan all pixels with x, y loops 
        for (int i = 0; i < 320; i++){
            for (int j = 0; j < 240; j++) {
                
                
                //Frame Difference
                pixelout[(j*320+i)]=abs((lastPixels[(j*320+i)*3])-(pixels[(j*320+i)*3]));
                
                lastPixels[(j*320+i)*3]=pixels[(j*320+i)*3];
         //    Thresholding- use of frame difference pixels to activate sound and image processing 
                if (pixels[(j*320+i)*3]>ofGetWidth()/8){
                                    freq=pixelout[(j*320+i)];
                                    pixelout[(j*320+i)]=255;// we dont see that because we see the image but I leave it here for debug 
                                    
                                } else {
                                    pixelout[(j*320+i)]=0;
                                }
                
            
            }
        }
        //image processing 
        pix =myImage.getPixels();
        myPixels2.allocate(myImage.getWidth(),myImage.getHeight(),3);
        int blur = ofMap(freq,0, 200, 0, 400);//we map the freq/pixelout to rgb threshold
       
        
        myPixels2= myImageProc.threshRBG(pix, myPixels2,blur); // processing of image pixels 
        
        
        myTexture.allocate(myPixels2);
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
   
    
    ofSetColor(255, 255, 255,255);
    
    
    
    
    ofSetColor(255, 255, 255);
    
    myTexture.draw(0, 0,ofGetWidth(),ofGetHeight());
    
    
    
}

//--------------------------------------------------------------
void ofApp::audioOut     (float * output, int bufferSize, int nChannels){
    
    
    for (int i = 0; i < bufferSize; i++){
        
        
        osc= sine1.sinewave(freq*10); //simple sinewave the frequency is influenced by the thresholdfed "pixelout" pixels 
        mymix.stereo(osc, outputs, 0.5);
        
        
        output[i*nChannels    ] = outputs[0]; /* You may end up with lots of outputs. add them here */
        output[i*nChannels + 1] = outputs[1];
    }
    
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == 's') {
        
        myGrabber.videoSettings();
    }
   
    
}

