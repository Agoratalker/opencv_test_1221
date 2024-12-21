#include <iostream>
#include<string>
#include<vector>
#include<map>
#include"opencv2/opencv.hpp"
#include <opencv2/highgui/highgui_c.h>”
#pragma comment(lib, "opencv_world480d.lib")
using namespace cv;
using namespace std;

Mat change_16bit_to_8bit(Mat& img)//%2线性拉伸_取前百分之2的像素赋25_后百分之2的像素赋0_其余按原计划执行
{
	double width = img.cols;//图片宽度
	double height = img.rows;//图片高度
	double sum = width * height;//像素总数

	//cout <<endl<< sum << endl;

	ushort* p_img;
	uchar* p_dst;

	vector<ushort> array;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; ++j)
		{
			array.push_back(img.at<ushort>(i, j));
		}
	}




	sort(array.begin(), array.end());
	int up2_num = sum - sum * 0.02;
	int down2_num = sum * 0.02;

	//cout << endl << up2_num << endl << down2_num << endl;

	ushort up2 = array[up2_num-1];
	ushort down2 = array[down2_num - 1];

	//cout << endl << array[sum - 1] << endl << array[0] << endl;
	//cout << endl << up2 << endl << down2 << endl;

	Mat dst = Mat::zeros(height, width, CV_8UC1);//先生成空的目标图片
	double minv = 0.0, maxv = 0.0;
	double* minp = &minv;
	double* maxp = &maxv;
	minMaxIdx(img, minp, maxp);  //取得像素值最大值和最小值

	for (int i = 0; i < height; i++)
	{
		p_img = img.ptr<ushort>(i);
		p_dst = dst.ptr<uchar>(i);
		for (int j = 0; j < width; ++j)
		{
			if (double(p_img[j]) >= double(up2))
			{
				p_dst[j] = 255;
			}
			else if(double(p_img[j])<=double(down2))
			{
				p_dst[j] = 0;
			}
			else if(double(down2)<double(p_img[j])<double(up2))
			{
				p_dst[j] = (double(p_img[j]) - double(down2)) / (double(up2) - double(down2)) * 255;
			}

		}
	}
	return dst;
}
int main()
{
	//图像预处理
	Mat test_01 = imread("C:\\软件D\\OneDrive\\桌面\\数图实习\\实验用图\\实验用图\\GF2-whu-mss.tif",-1);
	Mat test_02 = imread("C:\\软件D\\OneDrive\\桌面\\数图实习\\实验用图\\实验用图\\GF2-whu-pan.tif",-1);
	//vector<Mat>test_01_r_g_b_ir;
	//split(test_01, test_01_r_g_b_ir);
	//Mat test_01_r = change_16bit_to_8bit(test_01_r_g_b_ir[3]);
	//Mat test_01_g = change_16bit_to_8bit(test_01_r_g_b_ir[0]);
	//Mat test_01_b = change_16bit_to_8bit(test_01_r_g_b_ir[1]);
	//vector<Mat>test_bgr;
	//test_bgr.push_back(test_01_b);
	//test_bgr.push_back(test_01_g);
	//test_bgr.push_back(test_01_r);
	//Mat test_01_bgr;
	//Mat test_02_bgr = change_16bit_to_8bit(test_02);
	//merge(test_bgr, test_01_bgr);
	//namedWindow("test", WINDOW_FREERATIO);
	//imshow("test", test_01_bgr);


	vector<Mat>test_01_r_g_b_ir;
	split(test_01, test_01_r_g_b_ir);
	Mat test_01_r = change_16bit_to_8bit(test_01_r_g_b_ir[0]);
	Mat test_01_g = change_16bit_to_8bit(test_01_r_g_b_ir[1]);
	Mat test_01_b = change_16bit_to_8bit(test_01_r_g_b_ir[2]);
	vector<Mat>test_bgr;
	test_bgr.push_back(test_01_b);
	test_bgr.push_back(test_01_g);
	test_bgr.push_back(test_01_r);
	Mat test_01_bgr;
	Mat test_02_bgr = change_16bit_to_8bit(test_02);
	merge(test_bgr, test_01_bgr);
	namedWindow("test", WINDOW_FREERATIO);
	imshow("test", test_01_bgr);


	


	
	

	
	waitKey(0);

}