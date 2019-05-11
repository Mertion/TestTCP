#pragma once

#include "stdafx.h"

#include <algorithm>
#include <cvaux.h>
#include <math.h>  
#include <cv.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv.hpp>

#include <process.h> 
#include <cvaux.h>
#include <cv.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv.hpp>
#include "cxcore.hpp"
#include "build\include\opencv2\core\core.hpp"
#include <cxcore.h>
#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include <opencv2/ml/ml.hpp>

using namespace cv;

typedef struct _GrayRings
{
	//��Բ�뾶
	int InsideCirclReadius;
	//��Բ�뾶
	int OuterCircleReadius;
	//ƽ���Ҷ�
	int AvgGray;
	//���ظ���
	int PixelCount;
	//���ĵ�
	CvPoint Center;
	//Բ��ʵ��Ҷ�ͼ
	Mat RingsGrayImage;
	//�������
	int HighLightArea;

	_GrayRings()
	{
		InsideCirclReadius = 0;
		OuterCircleReadius = 0;
		AvgGray = 0;
		PixelCount = 0;
		HighLightArea = 0;

		Center.x = 0;
		Center.y = 0;
	}
}GrayRings;



class RecognitionFunction
{
public:
	RecognitionFunction();
	~RecognitionFunction();

	//����ͼ���ж������Բ�����ԵĻҶ�
	int GetMultiRingsGray(Mat p_matSrc, GrayRings** p_arrGrayRings, int p_RingsCount, Mat* p_pmatDebug);

	//����ͼ��������������Բ���ⲿ�����ȣ�����������Բͼ��
	static int GetAvgLight(IN Mat p_mRecognitionImage, OUT Mat* p_pCircleImage);
};

