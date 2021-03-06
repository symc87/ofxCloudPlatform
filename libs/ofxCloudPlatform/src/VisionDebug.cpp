// =============================================================================
//
// Copyright (c) 2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofx/CloudPlatform/VisionDebug.h"
#include "ofGraphics.h"



namespace ofx {
namespace CloudPlatform {


void VisionDebug::draw(const std::string& label,
                       float value,
                       float x,
                       float y,
                       float width,
                       float height)
{
    ofPushStyle();
    
    ofFill();
    ofSetColor(0, 200);
    ofDrawRectangle(x, y, width, height);

    ofFill();
    ofSetColor(127, 200);
    ofDrawRectangle(x, y, width * value, height);



    ofSetColor(255);
    ofDrawBitmapString(label + "(" + ofToString(value, 2) + ")", x + 5, y + 14);

    ofNoFill();
    ofSetColor(255, 200);
    ofDrawRectangle(x, y, width, height);


    ofPopStyle();
}


void VisionDebug::draw(const std::string& label,
                       const Likelihood& likelihood,
                       float x,
                       float y,
                       float width,
                       float height)
{
    draw(label + ": " + likelihood.name(), likelihood.value(), x, y, width, height);
}


void VisionDebug::draw(const FaceAnnotation::Landmark& landmark)
{
    ofColor background= ofColor(0, 80);
    ofColor foreground = ofColor(0, 0);

    if (ofVec2f(ofGetMouseX(), ofGetMouseY()).distance(landmark.position()) < 5)
    {
        foreground = ofColor(255);
        background = ofColor(0);
    }

    ofDrawBitmapStringHighlight(landmark.name(), landmark.position(), foreground, background);
    ofNoFill();
    ofDrawEllipse(landmark.position().x, landmark.position().y, 10, 10);
}


void VisionDebug::draw(const FaceAnnotation& annotation)
{
    ofRectangle r = annotation.boundingPoly().getBoundingBox();


    annotation.boundingPoly().draw();
    annotation.fdBoundingPoly().draw();

    for (auto& landmark : annotation.landmarks())
    {
        draw(landmark);
    }

//    /// \sa rollAngle()
//    float _rollAngle;
//
//    /// \sa panAngle()
//    float _panAngle;
//
//    /// \sa tiltAngle()
//    float _tiltAngle;

    if (r.inside(ofGetMouseX(), ofGetMouseY()))
    {
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(ofGetMouseX(), ofGetMouseY());

        int height = 25;
        int yPosition = 10;

        draw("         JOY", annotation.joyLikelihood(), 10, yPosition+=height);
        draw("      SORROW", annotation.sorrowLikelihood(), 10, yPosition+=height);
        draw("       ANGER", annotation.angerLikelihood(), 10, yPosition+=height);
        draw("    SURPRISE", annotation.surpriseLikelihood(), 10, yPosition+=height);
        draw("UNDEREXPOSED", annotation.underExposedLikelihood(), 10, yPosition+=height);
        draw("     BLURRED", annotation.blurredLikelihood(), 10, yPosition+=height);
        draw("    HEADWARE", annotation.headwearLikelihood(), 10, yPosition+=height);

        yPosition += height;

        draw("   Detection confidence: ", annotation.detectionConfidence(), 10, yPosition+=height);
        draw(" Landmarking confidence: ", annotation.landmarkingConfidence(), 10, yPosition+=height);

        ofPopStyle();
        ofPopMatrix();
    }

}


void VisionDebug::draw(const EntityAnnotation& annotation)
{
    ofRectangle r = annotation.boundingPoly().getBoundingBox();
    annotation.boundingPoly().draw();
    ofDrawBitmapString(annotation.description(), r.x + 14, r.y + 14);
}


void VisionDebug::draw(const SafeSearchAnnotation& annotation)
{
}


void VisionDebug::draw(const ImagePropertiesAnnotation& annotation)
{
}


void VisionDebug::draw(const std::vector<FaceAnnotation>& annotations)
{
    for (auto& annotation: annotations) draw(annotation);
}


void VisionDebug::draw(const std::vector<EntityAnnotation>& annotations)
{
    for (auto& annotation: annotations) draw(annotation);
}


void VisionDebug::draw(const AnnotateImageResponse& response)
{
    draw(response.faceAnnotations());
    draw(response.landmarkAnnotations());
    draw(response.logoAnnotations());
    draw(response.labelAnnotations());
    draw(response.textAnnotations());
    draw(response.safeSearchAnnotation());
    draw(response.imagePropertiesAnnotation());
}


} } // namespace ofx::CloudPlatform
