/* --------------------------------------------------------
* author: livezingy
*
* BLOG: livezingy.com
*
* Development Environment:
*      Visual Studio V2019
*      opencv4.3
*
* Version:
*      V1.0    20201026
--------------------------------------------------------- */

#include "tesstsv2map.h"
#include "tesseract\baseapi.h"
#include "leptonica\allheaders.h"

using namespace std;
using namespace cv;


/*
 Input:
 tessImage: the image will be send to tesseract, Please make sure it is a RGB color image, or gray image ,or threshold image
 magnifiRatio: image magnification Sometimes enlarge the image may get better results, especially the small dpi image.
 lang: the language of the tesseract
 langPath: the language path of the tesseract
  
Output: 
std::map<std::string, std::vector<std::string>> result
results["level"][i]     get level
results["block_num"][i]  get block_num
results["page_num"][i]  get page_num
results["par_num"][i]   get par_num
results["line_num"][i]  get line_num
results["word_num"][i]  get word_num
results["left"][i], results["top"][i], results["width"][i], results["height" ][i],the coordinates of the upper left corner, width and height.
results["conf"][i] to get the confidence of the OCR word.
results["text"][i] to get the OCR word.
*/
std::map<std::string, std::vector<std::string>> tsv2map(cv::Mat tessImage, int magnifiRatio,const char* lang, const char* langPath)
{   
    tesseract::TessBaseAPI *ocrObj;
	map<string, vector<string>> result;
	
	ocrObj = new tesseract::TessBaseAPI();
	if (ocrObj->Init(langPath, lang) == -1)
	{
		return result;
	}	

	if (tessImage.data != NULL)
	{
		if (magnifiRatio > 1)
		{
			resize(tessImage, tessImage, Size(tessImage.cols * magnifiRatio, tessImage.rows * magnifiRatio), 0, 0, INTER_CUBIC);
		}
		ocrObj->SetImage(tessImage.data, tessImage.cols, tessImage.rows, tessImage.elemSize(), tessImage.step1());

		// Get the OCR output as  tsv with coordinates of each word
		char* charTsvResult = ocrObj->GetTSVText(0);

		//split the content by the "\n"
		vector<string> tsvVec = splitString(charTsvResult, "\n");

		int Len = tsvVec.size();

		//the tsv file from GetTSVText()  don't contains the tsv header, so initial the head here
		vector<string> headVec = { "level","page_num","block_num","par_num","line_num","word_num","left","top","width","height","conf","text" };
		
		//result size. 
		int hLen = headVec.size();

		if (Len > 1)
		{
			//the last line in tsv file is null, so ignore it
			Len = Len - 1;
			for (int i = 0; i < Len; i++)
			{

				string lineStr = tsvVec[i];
				vector<string> lineVec = splitString(lineStr, "\t");

				int tmpLen = lineVec.size();

				for (int j = 0; j < tmpLen; j++)
				{
					result[headVec[j]].push_back(lineVec[j]);
				}
				if (tmpLen < hLen)
				{
					result[headVec[hLen - 1]].push_back("");
				}
			}
		}
			
	}
	
	return result;
}


std::vector<std::string> splitString(const std::string &str,const char* delimiter) 
{
	std::vector<std::string> splited;
	std::string s(str);
	size_t pos;

	while ((pos = s.find(delimiter)) != std::string::npos) 
	{
		std::string sec = s.substr(0, pos);

		if (!sec.empty()) 
		{
			splited.push_back(s.substr(0, pos));
		}

		s = s.substr(pos + 1);
	}

	splited.push_back(s);

	return splited;
}
