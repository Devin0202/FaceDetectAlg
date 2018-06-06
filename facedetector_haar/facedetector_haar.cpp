#include "facedetector_haar.h"

class haar_face_detector_impl : public haar_face_detector
{
public:
	haar_face_detector_impl(const char* modeldir);
	~haar_face_detector_impl();
	haar_face_detector_impl(const haar_face_detector_impl&) = delete;

	/**
	* detect faces
	* @param image_gray         [input] gray 1 channel input image
	* @param faces              [output] faces bounding boxes
	*/
	virtual void detect(const hiar_mat& image_gray, std::vector<bbox>& faces);

private:
	const int max_face_edge = std::min(IMAGE_INPUT_HEIGHT, IMAGE_INPUT_WIDTH);
	const int min_face_edge = 10;

private:
	cv::CascadeClassifier face_cascade;
	std::vector<cv::Rect> bboxes;
};

std::unique_ptr<haar_face_detector> create_haar_face_detector(const char* modeldir)
{
	return std::unique_ptr<haar_face_detector>(new haar_face_detector_impl(modeldir));
}

haar_face_detector_impl::haar_face_detector_impl(const char* modeldir)
{
	if (!face_cascade.load(modeldir)) {
		std::cout << "HiScene Log: model dir is incorrect!" << std::endl;
		return;
	}
}

haar_face_detector_impl::~haar_face_detector_impl()
{
}

void haar_face_detector_impl::detect(const hiar_mat& image_gray, std::vector<bbox>& faces)
{
	if (image_gray.rows != IMAGE_INPUT_HEIGHT || image_gray.cols != IMAGE_INPUT_WIDTH) {
		std::cout << "HiScene Log: image size is incorrect(640x480)!" << std::endl;
		return;
	}
	face_cascade.detectMultiScale(image_gray, bboxes,
		/*scaleFactor*/1.1, /*minNeighbors*/3, /*flags*/0,
		/*minSize*/cv::Size(min_face_edge, min_face_edge), /*maxSize*/cv::Size(max_face_edge, max_face_edge));
	faces.clear();
	for (auto p : bboxes) {
		faces.push_back({ p.x, p.y, p.width, p.height, 0 });
	}
}