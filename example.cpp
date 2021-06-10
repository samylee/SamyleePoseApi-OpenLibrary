/*
author: samylee
github: https://github.com/samylee
date: 06/10/2021
*/

#include "SamyleePoseApi.h"

using namespace cv;
using namespace std;

int main()
{
	// initial pose function
	string model_path = "model/samylee_pose.bin";
	float pose_thresh = 0.3;
	PoseHandle ph = SamyleePoseApiInit(model_path, pose_thresh);
	if (ph == NULL)
		return -1;

	while (true)
	{
		// image input
		Mat src = imread("test.jpg");
		if (src.empty())
			return -1;

		// person rect define
		Rect person_rect1(171, 0, 126, 310);
		Rect person_rect2(252, 0, 212, 290);
		Rect person_rect3(304, 97, 153, 206);
		Rect person_rect4(0, 195, 286, 117);

		// person_rects input
		vector<Rect> person_rects;
		person_rects.push_back(person_rect1);
		person_rects.push_back(person_rect2);
		person_rects.push_back(person_rect3);
		person_rects.push_back(person_rect4);

		// process function
		bool draw = true;
		vector<vector<Point> > keypoints;

		clock_t start_t = clock();
		int pose_check = SamyleePoseApiRun(ph, src, person_rects, keypoints, draw);
		cout << "check id: " << pose_check << "\tperson num:" << person_rects.size() << "\tcost time: " << clock() - start_t << endl;

		imshow("dst", src);
		if (waitKey(1) > 1)
			break;
	}

	// release function
	SamyleePoseApiRel(ph);

	return 0;
}