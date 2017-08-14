#ifndef PROJECT_PAVEMENTTOMARKER_H
#define PROJECT_PAVEMENTTOMARKER_H

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sensor_msgs/Image.h>

void vypis();
void putPavementFragmentIntoMarker(int map[100000],cv::Point startLineLeft, cv::Point endLineLeft, cv::Point startLineRight, cv::Point endLineRight);
void putPavementLineIntoMarker(int map[100000], int lineRealCoordStartX, int lineRealCoordStartY, int lineRealCoordEndX, int lineRealCoordEndY); //real coordinates in mm

#endif //PROJECT_PAVEMENTTOMARKER_H