#include <memory>
#include <vector>
#include "opencv2/opencv.hpp"

#define IMAGE_INPUT_WIDTH (400)
#define IMAGE_INPUT_HEIGHT (225)

#define IMAGE_SHOW_WIDTH (320)
#define IMAGE_SHOW_HEIGHT (240)

typedef struct {
	int x;
	int y;
	int width;
	int height;
	int angle;
} bbox;

#define hiar_mat cv::Mat