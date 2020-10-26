#pragma once
#pragma once
#ifndef TESSTSV2MAP_H
#define	TESSTSV2MAP_H
#include <string>
#include <vector>
#include <map>
#include <opencv2/imgproc/imgproc.hpp>

std::vector<std::string> splitString(const std::string &str,const char* delimiter);
std::map<std::string, std::vector<std::string>> tsv2map(cv::Mat tessImage, int magnifiRatio, const char* lang, const char* langPath, int psmVal);


#endif	
/*TESSTSV2MAP_H */