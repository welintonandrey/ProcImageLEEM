#ifndef GALLIUM_H
#define GALLIUM_H

#include <vector>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QString>

using namespace std;
using namespace cv;

class Gallium
{
public:
    Gallium();
    Gallium(QString arq);
    virtual ~Gallium();

    //Functions
    vector<Mat> readVideo(string arq);
    void writeVideo(string arq);
    void segVideo(int threshCanny);
    Mat applyCanny(Mat src_gray, Mat src, int thresh);
    void uniVideo();

    //Gets e Sets
    void setVideoSeg(vector<Mat> video);
    vector<Mat> getVideoSeg();
    void setVideoOri(vector<Mat> video);
    vector<Mat> getVideoOri();
    void setFps(int f);
    int getFps();
    void setFrames(int f);
    int getFrames();
    void setPosVideo(int pos);
    int getPosVideo();
    void setPosVideoAux(int posAux);
    int getPosVideoAux();

private:
    vector<Mat> videoOri;
    vector<Mat> videoSeg;
    int fps;
    int frames;
    int posVideo;
    int posVideoAux;
};

#endif // GALLIUM_H
