//c++ PoGo_IV_OCR.cpp -o PoGo_IV_OCR -llept -ltesseract -lboost_system -lboost_filesystem -std=c++11
#include "header.h"
#include <regex>
#include <map>
namespace fs = boost::filesystem;
fs::path screenshots("./screenshots");

using namespace std;

string nameCase(string str)
{
	str[0] = toupper(str[0]);
	for(size_t i = 1 ; i < str.length() ; ++i )
        str[i] = tolower(str[i]);
	return str;
}

tuple<string, string, string, string> pokemonToText(string filename, tesseract::TessBaseAPI *api, ostream& csv)
{
	char *cpText, *nameText, *hpText, *stardustText;
	if (!csv)
	{
		cout << "Error opening file" << endl;
		return make_tuple("","","","");
	}
	Pix *image = pixRead(filename.c_str());
	api->SetImage(image);
	
	api->SetRectangle(390, 1165, 660, 120);	
	api->SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	api->SetPageSegMode(tesseract::PSM_SINGLE_WORD);
	nameText = api->GetUTF8Text();
	string name(nameText);
	name = regex_replace(name, (regex)"[^a-zA-Z]+", "");
	name = nameCase(name);
	
	api->SetRectangle(470, 180, 400, 100);
	api->SetVariable("tessedit_char_whitelist", "CP0123456789");
	api->SetPageSegMode(tesseract::PSM_SINGLE_WORD);
	cpText = api->GetUTF8Text();
	string cp(cpText);
	cp = regex_replace(cp, (regex)"[^0-9]+", "");
	
	api->SetRectangle(550, 1360, 350, 50);
	api->SetVariable("tessedit_char_whitelist", "HP/0123456789");
	api->SetPageSegMode(tesseract::PSM_SINGLE_WORD);
	hpText = api->GetUTF8Text();
	string hp(hpText);
	hp = regex_replace(hp, (regex)"[[:space:]]*", "");
	hp = regex_replace(hp, (regex)".*/", "");
	
	api->SetRectangle(800, 2050, 200, 50);
	api->SetVariable("tessedit_char_whitelist", "0123456789");
	api->SetPageSegMode(tesseract::PSM_SINGLE_WORD);
	stardustText = api->GetUTF8Text();
	string stardust(stardustText);
	stardust = regex_replace(stardust, (regex)"[[:space:]]*", "");
	csv << name << ',' << cp << ',' << hp << ',' << stardust << endl;

	// Destroy used object and release memory
	delete [] cpText, nameText, hpText, stardustText;
	pixDestroy(&image);
	return make_tuple(name, cp, hp, stardust);
}
