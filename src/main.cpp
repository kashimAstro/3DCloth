#include "ofAppGLFWWindow.h"
#include "ofMain.h"
#include "cloth_glm.h"

class xApp : public ofBaseApp{

	public:
		ofEasyCam camera;
		ofLight pLight,sLight,dLight;
		ofMaterial material;
	        float _posX,_posY,_posZ;
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

			cloth_glm::setRadiusBall(2);
		}

		void update() {
		        ofSetWindowTitle(ofToString(ofGetFrameRate(), 0));
		        Btime++;
	                _posX=(float)7;
	                _posY=(float)-5;
			if(stop)
		                _posZ=(float)cos(Btime/50.0f)*7;
				
	                cloth_glm::setPosBall(ofVec3f(_posX,_posY,_posZ));
	                cloth_glm::update();
	                cloth_glm::ADDforce( ofVec3f(0,-0.2,0), 0.5f*0.5f );

			if(wind) {
				cloth_glm::WINDforce( ofVec3f(0.6,0,0.3), 0.8f*0.8f );
			}
			
	                ofVec3f pos(_posX,_posY,_posZ);
	                cloth_glm::BALLcollision( pos, cloth_glm::getRadiusBall() );
		}

		void draw() {
		        ofBackgroundGradient( ofColor(210), ofColor(10));
			ofDrawBitmapStringHighlight( ofToString(ofGetFrameRate(), 0),20,20 );
		        camera.begin();

			ofEnableLighting();
        		material.begin();
        		pLight.enable();
		        sLight.enable();
		        dLight.enable();
			ofEnableDepthTest();
        	        ofTranslate(-6.5,6,-9.0f);

	                cloth_glm::drawCloth(wire);
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
