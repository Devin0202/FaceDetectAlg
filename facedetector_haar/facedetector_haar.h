#pragma once

/*******************************************************************************************
* Copyright 2018, HiScene
*
* This file is HiScene's property. It contains HiScene's proprietary and confidential
* information and trade secret. The information and code contained in this file is only
* intended for authorized HiScene employees and customers.
*
* DO NOT DISTRIBUTE, DUPLICATE OR TRANSMIT IN ANY FORM WITHOUT PROPER AUTHORIZATION FROM
* HISCENE.
*
* If you are not an intended recipient of this file, you must not copy, distribute, modify,
* or take any action in reliance on it. If you have received this file in error, please
* immediately notify HiScene, and permanently delete the original and any copy of it and
* any printout thereof.
*
******************************************************************************************/

#include "../facedetector_types.h"

/*******************************************************************************************
Utility functions
*******************************************************************************************/

class haar_face_detector
{
public:

	virtual ~haar_face_detector() {}

	/**
	* detect faces
	* @param image_gray         [input] gray 1 channel input image
	* @param faces              [output] faces bounding boxes
	*/
	virtual void detect(const hiar_mat& image_gray, std::vector<bbox>& faces) = 0;
};

std::unique_ptr<haar_face_detector> create_haar_face_detector(const char* modeldir);