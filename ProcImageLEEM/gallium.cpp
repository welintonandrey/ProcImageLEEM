#include "gallium.h"

#include <QDebug>

Gallium::Gallium() {
}

Gallium::Gallium(QString arq) {
    //Convert QString to std::string
    string str = arq.toUtf8().constData();
    this->posVideo = 0;
    this->videoOri = readVideo(str);
}

Gallium::~Gallium() {
}

vector<Mat> Gallium::readVideo(string arq) {
    VideoCapture cap(arq);
    vector<Mat> video;

    if (!cap.isOpened()) {
        cout << "Cannot open the video file" << endl;
        return video;
    }

    //Get FPS video
    if(cap.get(CV_CAP_PROP_FPS) > 0 && !isnan(cap.get(CV_CAP_PROP_FPS))){
        fps = (int)round( cap.get(CV_CAP_PROP_FPS));
        qDebug() << "Frame Rate:" << fps;
    }
    else{
        qDebug() << "Frame Rate: Defaut";
        fps = 60;
    }


    //Get Frames video
    if(cap.get(CV_CAP_PROP_FRAME_COUNT) > 0 && !isnan(cap.get(CV_CAP_PROP_FRAME_COUNT))){
        this->frames = (int)round( cap.get(CV_CAP_PROP_FRAME_COUNT));
        qDebug() << "Count Frames:" << this->frames;
    }
    else
        qDebug() << "Count Frames: ERROR";



    while (true) {
        Mat frame;

        //Read all frames,
        bool bSuccess = cap.read(frame);

        //If don't sucess (end of file) break operation
        if (!bSuccess) {
            //cout << "End of the Video" << endl;
            break;
        }

        //Add frame on the list of frames
        video.push_back(frame);
    }

    return video;
}

void Gallium::writeVideo(string arq) {
    //Write video to file  - .AVI file
    VideoWriter outVideoW(arq, CV_FOURCC('P', 'I', 'M', '1'), this->fps, this->videoSeg.at(0).size(), true);
    for (unsigned int i = 0; i < this->videoSeg.size(); i++) {
        //Write one frame at a time
        outVideoW.write(this->videoSeg.at(i));
    }
}

void Gallium::segVideo(int threshCanny) {

    for (unsigned int i = 0; i < this->videoOri.size(); i++) {
        //Matrix Mat original frame - without changes
        Mat mNew;
        videoOri.at(i).copyTo(mNew);

        //Remove do Mat Frame as partes nao desejadas para segmentacao
        //rectangle(mNew, Point(180, 170), Point(248, 198), Scalar(255, 255, 255), -1, 8);
        //rectangle(mNew, Point(246, 0), Point(248, 198), Scalar(255, 255, 255), -1, 8);

        //Apply the MedianBlur filter to reduce noise
        medianBlur(mNew, mNew, 7);
        medianBlur(mNew, mNew, 7);

        //Convert Mat (RGB) to GRAYSCALE
        cvtColor(videoOri.at(i), videoOri.at(i), CV_BGR2GRAY);
        cvtColor(mNew, mNew, CV_BGR2GRAY);

        //Create matrix AUX for threshold
        Mat aux;
        threshold(mNew, aux, 65, 255, CV_THRESH_BINARY);
        //GaussianBlur(aux, aux, Size(7, 7), 1, 0);

        //Find edge with Canny
        //aux = applyCanny(mNew, videoOri.at(i), threshCanny);
        //aux = applyCanny(aux, mNew, threshCanny);
        aux = applyCanny(aux, mNew, threshCanny);

        //Add Mat AUX on the list of Mat segmented
        this->videoSeg.push_back(aux);
    }
}

Mat Gallium::applyCanny(Mat src_gray, Mat src, int thresh) {
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    //Detect edges using canny
    Canny(src_gray, canny_output, thresh, thresh * 2, 3);

    //Find contours
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    //Get the moments
    vector<Moments> mu(contours.size());
    for (unsigned int i = 0; i < contours.size(); i++) {
        mu[i] = moments(contours[i], false);
    }

    //Get the mass centers
    vector<Point2f> mc(contours.size());
    for (unsigned int i = 0; i < contours.size(); i++) {
        mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
    }

    //Draw contours
    Mat drawing;
    cvtColor(src, drawing, CV_GRAY2BGR);
    //cvtColor(src_gray, drawing, CV_GRAY2BGR);
    for (unsigned int i = 0; i < contours.size(); i++) {
        Scalar color = Scalar(0, 0, 255);
        drawContours(drawing, contours, i, color, 1, 8, hierarchy, 0, Point());
        circle(drawing, mc[i], 2, color, -1, 8, 0);
    }

    return drawing;
}


void Gallium::setVideoSeg(vector<Mat> video) {
    this->videoSeg = video;
}

vector<Mat> Gallium::getVideoSeg() {
    return this->videoSeg;
}

void Gallium::setVideoOri(vector<Mat> video) {
    this->videoOri = video;
}

vector<Mat> Gallium::getVideoOri() {
    return this->videoOri;
}

void Gallium::setFps(int f){
    this->fps = f;
}

int Gallium::getFps(){
    return this->fps;
}

void Gallium::setFrames(int f){
    this->frames = f;
}

int Gallium::getFrames(){
    return this->frames;
}

void Gallium::setPosVideo(int pos){
    this->posVideo = pos;
}

int Gallium::getPosVideo(){
    return this->posVideo;
}

void Gallium::setPosVideoAux(int posAux){
    this->posVideo = posAux;
}

int Gallium::getPosVideoAux(){
    return this->posVideoAux;
}
