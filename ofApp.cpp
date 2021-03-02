#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto noise_seed = ofRandom(1000);

	for (int radius = 100; radius <= 300; radius += 50) {

		auto deg_start = ofMap(ofNoise(noise_seed, ofGetFrameNum() * 0.005 + radius * 0.005), 0, 1, -180, 180);
		auto next_deg = ofMap(ofNoise(noise_seed, (ofGetFrameNum() + 1) * 0.005 + radius * 0.005), 0, 1, -180, 180);
		auto deg_gap = next_deg - deg_start;

		for (int deg = deg_start; deg < deg_start + 360; deg += 15) {

			this->draw_arrow(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)), glm::vec2(radius * cos((deg + deg_gap) * DEG_TO_RAD), radius * sin((deg + deg_gap) * DEG_TO_RAD)), ofMap(radius, 100, 300, 13, 35));
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 next_location, float size) {

	auto angle = std::atan2(next_location.y - location.y, next_location.x - location.x);

	ofFill();
	ofSetColor(39);

	ofBeginShape();
	ofVertex(location + glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
	ofEndShape(true);

	ofBeginShape();
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25);
	ofEndShape(true);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}