 #Known problems:
#	CP 110 copying as CP 10
#	Abra (psychic?) background makes OCR difficult.
import pytesseract
from PIL import Image
import re
import glob
import os

def correctDigits(str):
	str = re.sub('B', '8', str)
	str = re.sub('[DOoQ]', '0', str)
	str = re.sub('[Ss]', '5', str)
	str = re.sub('[Zz]', '2', str)
	return str
	
with open('./pokemon.csv', 'w') as spreadsheet:
	screenshots = glob.glob('./*.png')
	screenshots.sort(key=os.path.getmtime)

	for i, screenshot in enumerate(screenshots):
		print "Processing", i+1, "of", len(screenshots)
		
		img = Image.open(screenshot)
		cpCrop = img.crop((520, 180, 820, 280))
		nameCrop = img.crop((700, 1875, 1300, 1915))
		hpCrop = img.crop((550, 1360, 900, 1410))
		dustCrop = img.crop((800, 2050, 1000, 2100))

		nameStr = pytesseract.image_to_string(nameCrop)
		name = re.sub('[^a-zA-Z]+', '', nameStr)
		name = re.sub('candy|CANDY', '', name).title()

		cpStr = pytesseract.image_to_string(cpCrop)
		cp = correctDigits(cpStr)
		cp = re.sub('[^\d]+', '', cp)

		hpStr = pytesseract.image_to_string(hpCrop)
		hp = re.sub('[\s]*', '', hpStr)
		hp = re.sub('.*/', '', hp)
		
		hp = correctDigits(hp)

		dustStr = pytesseract.image_to_string(dustCrop)
		dust = correctDigits(dustStr)
		dust = re.sub('[^\d]', '', dust)
		
		spreadsheet.write(name+','+cp+','+hp+','+dust+'\n')
		#os.remove(screenshot)
	print "DONE"