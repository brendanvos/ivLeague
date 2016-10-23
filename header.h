// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <fstream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <string>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdexcept>
using namespace std;
using namespace cv;
namespace fs = boost::filesystem;

extern int invalidCount;
extern Mat all;
// This is the content of the .h file, which is where the declarations go
typedef map<time_t, fs::path> result_set_t;

result_set_t dirContents(string dir);
int parseOptions(int ac, char* av[]);
float pokemonLvl(int trainerLvl, float angle);
tuple<string, string, string, string> pokemonToText(string filename, tesseract::TessBaseAPI *api, ostream& csv);
Point lvlCoords(string filename);

const float CPMs[79]=	{
		0.0939999968,	//	1
		0.1351374321,	//	1.5
		0.1663978696,	//	2
		0.1926509132,	//	2.5
		0.2157324702,	//	3
		0.2365726514,	//	3.5
		0.2557200491,	//	4
		0.2735303721,	//	4.5
		0.2902498841,	//	5
		0.3060573814,	//	5.5
		0.3210875988,	//	6
		0.335445032,	//	6.5
		0.3492126763,	//	7
		0.3624577366,	//	7.5
		0.3752355874,	//	8
		0.3875924077,	//	8.5
		0.3995672762,	//	9
		0.4111935532,	//	9.5
		0.4225000143,	//	10
		0.4329264205,	//	10.5
		0.4431075454,	//	11
		0.4530599482,	//	11.5
		0.4627983868,	//	12
		0.4723360853,	//	12.5
		0.481684953,	//	13
		0.4908558072,	//	13.5
		0.499858439,	//	14
		0.508701749,	//	14.5
		0.5173939466,	//	15
		0.5259425161,	//	15.5
		0.5343543291,	//	16
		0.5426357538,	//	16.5
		0.5507926941,	//	17
		0.5588305845,	//	17.5
		0.5667545199,	//	18
		0.5745691281,	//	18.5
		0.5822789073,	//	19
		0.5898879079,	//	19.5
		0.5974000096,	//	20
		0.6048236487,	//	20.5
		0.6121572852,	//	21
		0.619404108,	//	21.5
		0.6265671253,	//	22
		0.6336491787,	//	22.5
		0.6406529546,	//	23
		0.6475809714,	//	23.5
		0.6544356346,	//	24
		0.6612192658,	//	24.5
		0.6679340005,	//	25
		0.6745818856,	//	25.5
		0.6811649203,	//	26
		0.6876849013,	//	26.5
		0.6941436529,	//	27
		0.700542901,	//	27.5
		0.7068842053,	//	28
		0.7131690749,	//	28.5
		0.7193990946,	//	29
		0.7255755869,	//	29.5
		0.7317000031,	//	30
		0.7347410386,	//	30.5
		0.7377694845,	//	31
		0.7407855797,	//	31.5
		0.7437894344,	//	32
		0.7467811972,	//	32.5
		0.749761045,	//	33
		0.7527290997,	//	33.5
		0.7556855083,	//	34
		0.7586303702,	//	34.5
		0.7615638375,	//	35
		0.7644860496,	//	35.5
		0.7673971653,	//	36
		0.7702972937,	//	36.5
		0.7731865048,	//	37
		0.7760649471,	//	37.5
		0.7789327502,	//	38
		0.7817900508,	//	38.5
		0.7846369743,	//	39
		0.7874736085,	//	39.5
		0.7903000116	//	40
		};
// This is the end of the header guard
#endif
