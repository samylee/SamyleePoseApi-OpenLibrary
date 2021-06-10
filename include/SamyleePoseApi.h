/*
author: samylee
github: https://github.com/samylee
date: 06/10/2021
*/

#pragma once

#ifdef _SAMYLEEPOSEAPI
#define SAMYLEEPOSEAPI _declspec(dllexport)
#else
#define SAMYLEEPOSEAPI _declspec(dllimport)
#endif

// define opencv (opencv420 will be tested)
#include <opencv2/opencv.hpp>

typedef void* PoseHandle;

/*initial function
(input)	model_path: path/to/model
(input)	thresh: 0.05-1.0 (usually set to 0.3)

return:
NULL: initial failure(check model path please)
Handle: initial success
*/
SAMYLEEPOSEAPI PoseHandle SamyleePoseApiInit(std::string &model_path, float thresh);

/*process function
(input)	handle: pose handle
(input)	src: input image(whole image)
(input)	person_rects: input person rects
(output)keypoints: output person keypoints (Point(-1, -1) will be set when the point is invisible)
(input)	draw: draw keypoints or not

keypoint list:
	0-nose, 1-neck,
	2-right_shoulder, 3-right_elbow, 4-right_wrist,
	5-left_shoulder, 6-left_elbow, 7-left_wrist,
	8-right_hip, 9-right_knee, 10-right_ankle,
	11-left_hip, 12-left_knee, 13-left_ankle,
	14-right_eye, 15-left_eye,
	16-right_ear, 17-left_ear

return:
0(success)
-1(image is empty)
-2(image channel is not 3)
-3(person_rects are empty)
-4(one of person_rects is out of range)
-5(handle is NULL)
*/
SAMYLEEPOSEAPI int SamyleePoseApiRun(PoseHandle handle, cv::Mat &src, std::vector<cv::Rect> &person_rects, 
	std::vector<std::vector<cv::Point> > &keypoints, bool draw);

/*release fuction
(input)	handle: pose handle

return: void
*/
SAMYLEEPOSEAPI void SamyleePoseApiRel(PoseHandle handle);