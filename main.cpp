#include "opencv2/opencv.hpp"
#include <cstdio>
using namespace std;
//using namespace cv;
int main()
{
	int number = 0 , i = 0, temp, file_number = 0; //temp for control later, 
	bool show = 0; //show for showing images=1 or not=0.

	//grab the frames and put them into a video
	cv::VideoCapture cap;
	cap.open("C:\\Projects\\video_blob\\x64\\Debug\\imgs\\0001.jpg");

	//determine the number of pictures that will be processed.
	cout << "enter the number of pictures that will be processed: " << endl; //specify the number of images in the directory
	cin >> number;

	for (;;)
	{
		/*
		*infinite loop IF statement, 
		*everytime the number of images is 
		*reached by i, reload the images
		*count the number of images processed
		*everytime the number of images is reached by i, reload the images.
		*/
		if(i == number){ 	
		cout << "first loop is done, permission to go further;\npress any key to enter the infinite loop " << endl;
		cin >> temp;
		}
		i++; // count the number of images processed 	
		if (i % number == 0 ){  	
		cap = cv::VideoCapture("C:\\Projects\\video_blob\\x64\\Debug\\imgs\\0001.jpg"); //reload
		}		
		file_number++;

		/*do image processing*/
		cv::Mat frame,frame_p;	// frame is the original image frame_p processed									
		cap >> frame;		// place frame into cap for streaming
		cv::resize(frame,frame, cv::Size(640, 480)); // resize the image


		/*Prepare images for the contour*/
		cv::cvtColor(frame, frame_p, CV_BGR2GRAY); // convert to gray image
		cv::threshold(frame_p, frame_p, 250, 255, 3); // take the gray image add treshold function

		/*Find Contours*/
		vector<vector<cv::Point> > contours; //create the vectors where the contours are drawn
		cv::findContours(frame_p, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE); //find the contours of the tresholded image output to contours v<v<Points>>


		/*
		*only keep the largest contour 
		*by selecting the index
		*/
		int c_idx = 0,largestContour = 0;
		for( int i = 0; i< contours.size(); i++ )
		{
    		if(contours[i].size() > largestContour){
        	largestContour = contours[i].size();
        	c_idx = i;
			}
		}
		/*
		*convert to bitwise to
		*later find the centroid
		*draw contours on both
		*processed and show frames
		*/
		bitwise_not(frame_p, frame_p);
		cv::drawContours(frame, 	contours, c_idx, cv::Scalar(0,0,0)); //draw the contours
		cv::drawContours(frame_p, 	contours, c_idx, cv::Scalar(0,0,0)); //draw the contours

		/*
		*get the moment
		*of the largest contour
		*/
		vector<cv::Moments> mu(contours.size());
		mu[c_idx] = moments(contours[c_idx], false);

		/*
		*Get the mass center
		*of the moment of the contour
		*/
		vector<cv::Point2f> mc(contours.size());
		mc[c_idx] = cv::Point2f(mu[c_idx].m10 / mu[c_idx].m00, mu[c_idx].m01 / mu[c_idx].m00);

		/*
		*draw a circle on the 
		*center of the contour
		*radius of radius on 
		*the show frame
		*/
		int radius = 5;
		cv::circle(frame, cvPoint(mc[c_idx].x, mc[c_idx].y), radius, CV_RGB(100, 0, 0), -1, 8, 0);
		/*
		*output xy coordinates
		*for each frame
		*/
			cout << "x" << file_number << " " << mc[c_idx].x << endl;
			cout << "y" << file_number << " " << mc[c_idx].y << endl;
			cout << endl;
		/*
		*Show the frames
		*/
		if(show) cv::imshow("img_cont", frame);

		if (cv::waitKey(1) == 27)
			exit(0);
	}
	return 0;
}
