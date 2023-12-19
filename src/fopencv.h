
#ifndef FOPENCV_H
#define FOPENCV_H
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include "sysCommands.h"


enum typeMat { Color, Gray, notype };

struct Coords {
	int x, y;
	Coords() {
		x = y = 0;
	}
	Coords(const Coords&Co) {
		*this = Co;
	}
	Coords(int x1, int y1) {
		x = x1;
		y = y1;
	}
	Coords(double x1, double y1) {
		x = (int)x1;
		y = (int)y1;
	}
	Coords(int x1, double y1) {
		x = x1;
		y = (int)y1;
	}
	Coords(double x1, int y1) {
		x = (int)x1;
		y = y1;
	}
	void showCoords() {
		std::cout << "{X: " << x << " Y: " << y << "}" << std::endl;
	}
	bool isNull() {
		return x ==0 && y == 0;
	}
	bool operator==(const Coords& other) const {
		return x == other.x && y == other.y;
	}

	Coords& operator=(const Coords& other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	Coords operator+(const Coords& other) const {
		return Coords(x + other.x, y + other.y);
	}

	Coords operator-(const Coords& other) const {
		return Coords(x - other.x, y - other.y);
	}

	Coords operator*(const Coords& other) const {
		return Coords(x * other.x, y * other.y);
	}
};

struct Zone {
	Coords C1, C2;
	int width, height, right, left, top, bottom;
	Zone() {
		C1 = C2 = Coords();
		width = height = right = left = top = bottom = 0;
	}
	Zone(const Coords& c1, const Coords& c2) {
		C1 = c1;
		C2 = c2;
		width = abs(C2.x - C1.x);
		height = abs(C2.y - C1.y);
		right = C2.x;
		left = C1.x;
		top = C1.y;
		bottom = C2.y;
	}
	Zone(const Zone& Z) {
		*this = Z;
	}
	void showZone() {
		std::cout << "C1";
		C1.showCoords();
		std::cout << "C2";
		C2.showCoords();
	}
	bool operator==(const Zone& other) const {
		return C1 == other.C1 && C2 == other.C2;
	}

	Zone& operator=(const Zone& other) {
		C1 = other.C1;
		C2 = other.C2;
		width = other.width;
		height = other.height;
		right = other.right;
		left = other.left;
		top = other.top;
		bottom = other.bottom;
		return *this;
	}

	Zone operator+(const Zone& other) const {
		return Zone(C1 + other.C1, C2 + other.C2);
	}

	Zone operator-(const Zone& other) const {
		return Zone(C1 - other.C1, C2 - other.C2);
	}

	bool isNull() {
		return C1.isNull() && C2.isNull();
	}
};

struct Template {
	Coords C;
	cv::Mat mat, graymat;
	typeMat type;
	std::string id;
	float score;
	int width, height;
	Template() {
		score = 0;
		C = Coords();
		id.clear();
		type = notype;
		width = height = 0;
		mat = graymat=cv::Mat();
	}
	Template(const std::string namemat) {
		*this = Template();
		id = namemat;
		mat = cv::imread(id, cv::IMREAD_COLOR);
		graymat = cv::imread(id, cv::IMREAD_GRAYSCALE);
		width = mat.cols;
		height = mat.rows;

	}
	Template(const std::string id, typeMat type) {
		*this = Template(id);
		 this->type = type;
	}
	Template(const Template& other) {
		*this = Template(other.id, other.type);
		score = other.score;
		C = other.C;
	}
	void setType(typeMat type) {
		this->type = type;
	}
};




class fopencv
{
public:
	fopencv();
	~fopencv();
	cv::Mat CreateMat(const std::string& path, typeMat color);
	bool intersects(const Template& templ1, const Template& templ2);
	bool intersects(const Zone& rect1, const Zone& rect2);
	void messageFound(const Template& templ,bool found);
	void messageFound(const std::vector<Template>& Tresult, bool found);
	bool cvmtfTemplate(const Template& tempimg, const Template& backgroundimage, Template& Tresult,Zone Z=Zone());
	bool cvmtfMultipleTemplate(const Template& tempimg,const Template& background, std::vector<Template>& Tresult,Zone Z=Zone());
	bool cvmtfMultipleTemplate(const std::vector<Template>& allTempl, const Template& background, std::vector<Template>& Tresult, Zone Z = Zone());

	bool cvmtfOneTemplate(const std::vector<Template>& allTempl, const Template& background, Template& Tresult, Zone Z = Zone());
	bool cvmtfCompareOneTemplate(const std::vector<Template>& allTempl, const Template& background, const std::vector<Template>& similartemplates, Template& Tresult, Zone Z = Zone());
	bool cvmtfOneMultipleTemplate(const std::vector<std::vector<Template>>& allTempl, const Template& background, std::vector<Template>& Tresult, Zone Z = Zone());
	bool cvmtfAllTemplate(const std::vector<Template>& allTempl, const Template& background, std::vector<Template>& Tresult, Zone Z = Zone());
	bool cvmtfCompareTemplate(const Template& goodTemplate, const Template& background, const Template& similartemplate, Template& Tresult,Zone Z=Zone());
	bool cvmtfCompareMultipleTemplate(const Template& goodTemplate, const Template& background, const std::vector<Template>& similartemplates, Template& Tresult,Zone Z=Zone());
	bool cvmtfMultipleTemplateCompareMultipleTemplate(const Template& goodTemplate, const Template& background, const std::vector<Template>& similartemplates, std::vector<Template>& Tresult,Zone Z=Zone());
	bool cvmtfMultipleTemplateCompareMultipleTemplate(const std::vector<Template>& goodTemplate, const Template& background, const std::vector<Template>& similartemplates, std::vector<Template>& Tresult, Zone Z = Zone());
	bool multipleMatchTemplate(const Template& templateImg, const Template& background, std::vector<Template>& Tresult);
	bool oneMatchTemplate(const Template& templateImg, const Template& background, Template& Tresult);
	Template extractZone(const Template& image, Zone Z);


	cv::Vec3b getPixel(cv::Mat img, int x, int y);
	void showImg(std::string path);
	void showMat(const cv::Mat& img);
	cv::Mat DetectContours(cv::Mat img);
	void getContours(std::string pathImg);
	void showImgtest(std::string path);
	void performCannyEdgeDetectionFromLiveCamera();
	cv::Mat performCannyEdgeDetectionFromPicture(const std::string& imagePath);
	void CannyEdgeVideo(std::string videoPath);
	void SaveCannyEdgeVideo(const std::string& videoPath, const std::string& outputPath);
	sysCommands sys;
	double precision = 0.8;
private:


};
#endif
