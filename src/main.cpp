#include "ofAppGLFWWindow.h"
#include "ofMain.h"
#include "cloth_glm.h"

class xApp : public ofBaseApp{

	public:
		ofEasyCam camera;
		ofLight pLight,sLight,dLight;
		ofMaterial material;
	        float _posX,_posY,_posZ;
	        float xPos,yPos,zPos;
		float Btime = 0;
		bool wire = false;
		bool stop = true;
		bool wind = false;
		int w,h;

		void setup() {
			w=ofGetScreenWidth();
			h=ofGetScreenHeight();
		        ofSetFrameRate(60);
		        ofSetVerticalSync(true);

			ofSetSmoothLighting(true);
    			pLight.setDiffuseColor( ofColor(0.f, 255.f, 0.f));
        		pLight.setSpecularColor( ofColor(255.f, 255.f, 0.f));
		        pLight.setPointLight();
			sLight.setDiffuseColor( ofColor(255.f, 0.f, 0.f));
        		sLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    			sLight.setSpotlight();
    			sLight.setSpotlightCutOff( 50 );
    			sLight.setSpotConcentration( 45 );
			dLight.setDiffuseColor(ofColor(0.f, 0.f, 255.f));
		        dLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
		        dLight.setDirectional();
        		dLight.setOrientation( ofVec3f(0, 90, 0) );
        		material.setShininess( 120 );
        		material.setSpecularColor(ofColor(255, 255, 255, 255));
			camera.setNearClip(.1);

			cloth_glm::init(34,30,35,35);

                        cloth_glm::BLOCKpoints( 1, ofVec3f(0.5,0.0,0.0) ) ;
		        cloth_glm::BLOCKpoints( cloth_glm::getSizePlaneWidth()-1, ofVec3f(-0.5,0.0,0.0) ) ;
			cloth_glm::setRadiusBall(5);

			xPos=15;
			yPos=-20;
			zPos=20;
		}

		void update() {
		        ofSetWindowTitle(ofToString(ofGetFrameRate(), 0));
		        Btime++;
	                _posX=(float)xPos;
	                _posY=(float)yPos;
			if(stop) _posZ=(float)cos(Btime/50.0f)*zPos;
				
	                cloth_glm::setPosBall(ofVec3f(_posX,_posY,_posZ));
	                cloth_glm::update();
	                cloth_glm::ADDforce( ofVec3f(0,-0.2,0), 1.5f*0.5f );

			if(wind) cloth_glm::WINDforce( ofVec3f(0.6,0,0.3), 0.8f*0.8f );
			
	                ofVec3f pos(_posX,_posY,_posZ);
	        	cloth_glm::BALLcollision( pos, cloth_glm::getRadiusBall() );
		}

		void draw() {
		        ofBackgroundGradient( ofColor(210), ofColor(10));

			ofPushStyle();
			ofDrawBitmapStringHighlight( ofToString(ofGetFrameRate(), 0),20,20 );
			ofPopStyle();

		        camera.begin();

			ofEnableLighting();
        		material.begin();
        		pLight.enable();
		        sLight.enable();
		        dLight.enable();
			ofEnableDepthTest();
        	        ofTranslate(-6.5,6,-9.0f);

	                cloth_glm::drawCloth(wire);
			if(wire)
				ofNoFill();
			else
				ofFill();
	                cloth_glm::drawSphere(ofColor(40,180,50), cloth_glm::getPosBall());

			ofDisableLighting();
        		material.end();
        		pLight.disable();
		        sLight.disable();
		        dLight.disable();

		        camera.end();
		}

		void keyPressed(int key) {
		        switch (key) {
				case OF_KEY_UP:
					break;
				case OF_KEY_DOWN:
					break;
				case 'f':
					ofToggleFullscreen();
					break;
				case 'w':
					wind=!wind;
					break;
				case 'd':
					wire=!wire;
					break;
				case 's':
					stop=!stop;
					break;
				case 'i':
					cloth_glm::init(34,30,55,50);
					cloth_glm::setRadiusBall(5);
					xPos=14;
		                        yPos=-10;
                		        zPos=14;
					break;

		                default:
		                        break;
		        }
		}
};

int main(){
       ofAppGLFWWindow window;
       ofSetupOpenGL(&window, 1024,768, OF_WINDOW);
       ofRunApp( new xApp());
}
