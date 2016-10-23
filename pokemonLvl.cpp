#include "header.h"
vector<float> lvlAngles;
float nearestLvl(vector<float> angles,float angle);

float pokemonLvl(int trainerLvl, float angle)
{
	if (lvlAngles.empty())
	{	
		float maxPokeLvl = min(40.0, trainerLvl+1.5);	
		for(float i=1; i<=maxPokeLvl; i=i+0.5)
		{
			int pokeI = 2*i-2;
			lvlAngles.push_back((CPMs[pokeI]-CPMs[0])*180/(CPMs[min(78, trainerLvl*2+2)]-CPMs[0]));
		}
	}
	return nearestLvl(lvlAngles, angle);
}

float nearestLvl(vector<float> angles,float angle)
{
	float dif = abs(angle - angles[0]);
	int closestIndex = angles[0];
	for (int i = 0; i < angles.size(); i++)
	{
	    if(dif > abs(angle - angles[i]))
	    {
		dif = abs(angle - angles[i]);
		closestIndex = i;
	    }
	}
	if (dif > .3)
	{
		cout << "\tWarning, angle \"" << angle << "\" is " << dif << " degrees from nearest level." << endl;
	}
	return ((float)closestIndex+2)/2;
}

