#include <fstream>
#include <facedetector_haar.h>
#include "Hifd.h"

const char* haar_model_list = "/storage/emulated/0/Android/data/com.hiscene.dy.echoviewer/files/haar_models.txt";
bool canRun = true;
std::vector<std::string> models;
std::string one_model;
std::ifstream infile;
std::vector<std::unique_ptr<haar_face_detector>> face_detectors_haar;
std::vector<bbox> faces;
int cnt = 0;

bool comp(const bbox &a, const bbox &b)
{
    return (a.width * a.height) > (b.width * b.height);
}

int fdCreate()
{
    // init haar
    infile.open(haar_model_list);
    if (!infile.is_open()) {
        std::cout << "HiScene Log: can not open model list file!" << std::endl;
        canRun = false;
        return -1;
    }

    while (std::getline(infile, one_model)) {
        models.push_back(one_model);
    }

    for (auto p:models) {
        face_detectors_haar.push_back(create_haar_face_detector(p.c_str()));
    }
    infile.close();
    return 1;
}

int fdRun(char *data, int datalength, int w, int h, cReturn *rt)
{
    int rtv = 0;
    int dimSize = 0;
    std::vector<uchar> imgData(data, data + datalength);
    cv::Mat img = cv::imdecode(imgData, CV_LOAD_IMAGE_COLOR);
    if (1 && canRun && !img.empty()){
        float ratioW = float(w) / IMAGE_INPUT_WIDTH;
        float ratioH = float(h) / IMAGE_INPUT_HEIGHT;
        cv::Mat dst;
        cv::Mat image_gray;
        cv::Size dstSize(IMAGE_INPUT_WIDTH, IMAGE_INPUT_HEIGHT);
        cv::cvtColor(img, image_gray, CV_BGR2GRAY);
        cv::resize(image_gray, dst, dstSize);
        // haar
        rt->h[0] = 1;
        rt->l[0] = 1;
        rt->t[0] = 1;
        rt->w[0] = 1;

        rt->hs = 1;
        rt->ls = 1;
        rt->ts = 1;
        rt->ws = 1;

        face_detectors_haar[0]->detect(dst, faces);
        sort(faces.begin(), faces.end(), comp);

        uchar facesLimit = 0;
//        for (auto p:faces) {
//            if (dimSize < p.height * p.width){
//                dimSize = p.height * p.width;
//                rt->hs = p.height * ratioH;
//                rt->ls = p.x * ratioW;
//                rt->ts = p.y * ratioH;
//                rt->ws = p.width * ratioW;
//            }else{
//                ;
//            }
//        }
        for (auto p:faces) {
            rt->h[facesLimit] = p.height * ratioH;
            rt->l[facesLimit] = p.x * ratioW;
            rt->t[facesLimit] = p.y * ratioH;
            rt->w[facesLimit] = p.width * ratioW;

//            if (0 == (cnt++) % 30){
//                cv::rectangle(img, {rt->l, rt->t, rt->w, rt->h}, cv::Scalar(255, 255, 255), 3);
//                cv::imwrite("/storage/emulated/0/Android/data/com.hiscene.dy.echoviewer/files/dy.jpg", img);
//            }

            facesLimit++;
            rtv++;
            if (2 < facesLimit){
                break;
            }else{
                ;
            }
        }
    }else{
        cv::imwrite("/storage/emulated/0/Android/data/com.hiscene.dy.echoviewer/files/dy.jpg", img);
        rt->h[0] = 450;
        rt->l[0] = 0;
        rt->t[0] = 0;
        rt->w[0] = 450;
        rtv = -2;
    }
    return rtv;
}

/// return 0 if no error
int fdDestroy()
{

    return 3;
}