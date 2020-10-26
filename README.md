# tesstsv2map
Convert the tsv ouput of the tesseract to map in C++. Then we could get the Tesseract OCR results like image_to_data with Ouput.DICT in pytesseract.

# Usage
1. Download the tesstsv2map.cpp and tesstsv2map.h, put them in our project folder. Make sure that the project could call the Tesseract(>3.05) normally.

2. Add the tesstsv2map.h to the test file that we want to get the Tesseract OCR results. 
```
#include "tesstsv2map.h"
```
3. Call the function tsv2map in our test file like this. There are four parameters in tsv2map:
```
std::map<std::string, std::vector<std::string>> results = tsv2map(testImg,1,"eng","tesseract-5.0\\tessdata\\eng/");

/*
std::map<std::string, std::vector<std::string>> tsv2map(cv::Mat tessImage, int magnifiRatio,const char* lang, const char* langPath)
   
cv::Mat tessImage: the image will be send to tesseract, Please make sure it is a RGB color image, or gray image ,or threshold image.

int magnifiRatio: image magnification. Sometimes larger the image may get better results, especially when the test image is a low dpi image.

const char* lang: the language of the tesseract. 

const char* langPath: the language path of the tesseract.
*/
```

4. Then we could get the results like this. All the results are "std::string", we could convert them to the format we needed.

```
string level = results["level"][i];//get level of index i

string block_num = results["block_num"][i];//get block_num of index i

string page_num = results["page_num"][i];//get page_num  of index i

string par_num = results["par_num"][i];//get par_num  of index i

string line_num = results["line_num"][i];//get line_num  of index i

string word_num = results["word_num"][i];//get word_num  of index i

string left = results["left"][i]; string top = results["top"][i];//the left-top corner of the OCR word coordinates

string width = results["width"][i]; string height = results["height"][i];//the width and height of the OCR word coordinates

string conf = results["conf"][i];//get the confidence of the OCR word.

string text = results["text"][i];//get the OCR word.
```
   
# More Information



