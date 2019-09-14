#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    Eigen::MatrixXd V(4,2);
    V<<0,0,
    1,0,
    1,1,
    0,1;
    Eigen::MatrixXi F(2,3);
    F<<0,1,2,
    0,2,3;
    Eigen::SparseMatrix<double> L;
    igl::cotmatrix(V,F,L);
    std::cout<<"Hello, mesh: "<<std::endl<<L*V<<std::endl;
    ofExit();
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
