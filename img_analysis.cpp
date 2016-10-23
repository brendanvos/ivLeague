//c++ img_analysis.cpp lvlCoords.cpp dirContents.cpp parseOptions.cpp pokemonLvl.cpp -o img_analysis -lboost_system -lboost_filesystem -lboost_program_options -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect -lopencv_imgcodecs -std=c++11

#include "header.h"
const double pi = 3.1415926535897;
vector<double> angles;
int invalidCount = 0;

Mat all= imread("screenshots/20160825_210835.png"); //temporary for test overlay

int main(int ac, char* av[])
{
	int playerLvl = parseOptions(ac, av);
	if (!playerLvl)
	{
		return -1;
	}
	result_set_t contents = dirContents("screenshots");
	

	remove("pokemon.csv");
	ofstream csv("pokemon.csv", ios::out);
	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	cout<<"Page segmentation mode: " << api->GetPageSegMode()<<endl<<endl;
	//api->SetPageSegMode(tesseract::PSM_SINGLE_WORD);
	// Initialize tesseract-ocr with English, without specifying tessdata path
	if (api->Init(NULL, "eng")) 
	{
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}

	Point p;
	double angle;
	float lvl;
	string name, cp, hp, stardust;
	for (auto const &it : contents)
	{	
		try
		{
			p = lvlCoords(it.second.string());
			if(p.y != -1 && p.x != -1)
			{				
				angle = 180*atan2(915-p.y, 720-p.x)/pi;
				angles.push_back(angle);
				lvl = pokemonLvl(playerLvl, angle);
			}
			else { lvl = 0; }
			String filename = it.second.string();
			Mat src= imread(filename);
			for (int x = 470; x < 871; ++x)
			for (int y = 180; y < 281; ++y)
			{	
				Vec3b color = src.at<Vec3b>(Point(x,y));
				if (color[0]==0 && color[1]==0 && color[2]==0)
				{
					color[0] = 125;
					color[1] = 125;
					color[2] = 125;
				}
				if (color[0]>240 && color[1]>240 && color[2]>240)
				{
					color[0] = 0;
					color[1] = 0;
					color[2] = 0;
				}
				if (color[0]!=0 || color[1]!=0 || color[2]!=0)
				{
					color[0] = 255;
					color[1] = 255;
					color[2] = 255;
				}
				src.at<Vec3b>(Point(x,y))=color;
			}
			for (int x = 390; x < 1051; ++x)
			for (int y = 1165; y < 1286; ++y)
			{	
				Vec3b color = src.at<Vec3b>(Point(x,y));
				if (color[0]==color[1] && color[1]==color[2])
				{
					color[0] = 255;
					color[1] = 255;
					color[2] = 255;
				}				
				else if (color[0]<240 && color[1]<240 && color[2]<240)
				{
					color[0] = 0;
					color[1] = 0;
					color[2] = 0;
				}
				else
				{
					color[0] = 255;
					color[1] = 255;
					color[2] = 255;
				}
				src.at<Vec3b>(Point(x,y))=color;
			}
			cv::imwrite(filename, src);

			std::tie(name, cp, hp, stardust) = pokemonToText(it.second.string(), api, csv);
			cout << name << endl;
			if (lvl)
			{
				cout << "Level: " << lvl << endl;
			}
			cout << "CP: " << cp << endl;
			cout << "HP: " << hp << endl;
			cout << "Stardust: " << stardust << endl << endl;
		}
		catch(const std::exception& e) 
		{
			std::cout << "Exception: " << e.what() << '\n';
		}
	}
	cout << "Unable to determine level for " << invalidCount << " pokemon" << endl;
	cout <<  contents.size() << " total pokemon were analyzed" << endl;
	//namedWindow("image",CV_WINDOW_NORMAL);
	//imshow("image",all);
	//waitKey(0);

	api->End();
	csv.close();
}
