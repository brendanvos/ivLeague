#include "header.h"

Point lvlCoords(string filename)
{
	Mat src= imread(filename);
	if (!src.data) 
	{
		throw std::runtime_error("Issue reading image \"" + filename + "\"");
	}
	
	Mat src_gray2;
	cvtColor(src, src_gray2, CV_BGR2GRAY );
	GaussianBlur( src_gray2, src_gray2, Size(9, 9), 2, 2 );

	vector<Vec3f> circles;

	HoughCircles(src_gray2, circles, CV_HOUGH_GRADIENT,
          2,   // accumulator resolution (size of the image / 2)
          100,  // minimum distance between two circles
          20, // Canny high threshold
          25, // minimum number of votes
          17, 20); // min and max radius

	//cout << circles.size() << endl;
	//cout << "end of test" << endl;

	vector<Vec3f>::const_iterator itc= circles.begin();
	vector<Point> validPoints;
	while (itc!=circles.end()) 
	{	
		Scalar colour = src.at<Vec3b>(Point((*itc)[0], (*itc)[1]));
		Scalar colour2 = src.at<Vec3b>(Point((*itc)[0]+5, (*itc)[1]+5));
		Scalar colour3 = src.at<Vec3b>(Point((*itc)[0]+5, (*itc)[1]-5));
		Scalar colour4 = src.at<Vec3b>(Point((*itc)[0]-5, (*itc)[1]+5));
		Scalar colour5 = src.at<Vec3b>(Point((*itc)[0]-5, (*itc)[1]-5));
		if(colour.val[0]==255 && colour.val[1]==255 && colour.val[2]==255 &&
		   colour2.val[0]==255 && colour2.val[1]==255 && colour2.val[2]==255 &&
		   colour3.val[0]==255 && colour3.val[1]==255 && colour3.val[2]==255 &&
	           colour4.val[0]==255 && colour4.val[1]==255 && colour4.val[2]==255 &&
		   colour5.val[0]==255 && colour5.val[1]==255 && colour5.val[2]==255)
		{	
			validPoints.push_back(Point((*itc)[0], (*itc)[1]));
			line(src, Point(140, 915), Point(720, 915), Scalar(124), 2);
			line(src, Point(720, 915), Point((*itc)[0], (*itc)[1]), Scalar(124), 2);
			circle(src,
			Point((*itc)[0], (*itc)[1]), // circle centre
			(*itc)[2],       // circle radius
			Scalar(124),	 // color
			2);              // thickness
		}
		++itc;
	}
	//namedWindow("image",CV_WINDOW_NORMAL);
	//imshow("image",src);
	//waitKey(0);
	if (validPoints.size()!=1)
		{
		//cout << "Filename: " << filename << endl;
		//cout << "Num valid: " << validPoints.size() << "\n" << endl;
		invalidCount++;
		return Point(-1, -1);
		}
	else
	{
		//circle(all,
		//	Point(validPoints[0].x, validPoints[0].y), // circle centre
		//	17,       // circle radius
		//	Scalar(124),	 // color
		//	2);              // thickness		
		return Point(validPoints[0].x, validPoints[0].y);
	}
}

