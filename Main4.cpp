/* 
Author: Joshua Erwin 
Date: 11/12/2022
Instructor: Professor Diana Rabah
Description: This is the main for the Flat plane simluation project
*/

//will not need all of these but i thought i would atleast list them so i remember them
#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>

//We will put the incliding of every other file we make here



using namespace std;

// Global veriables 

int main ()
{
	//The project mentions something about it doing this automaticly, I dont remember how to do that at the moment, but will prob fix it
	string fileName;

	cout << "Enter the name of the file containing the simulation configuration" << endl;
	cin >> fileName;


	//Opening the file to retreave the simulation configuration
	ifstream fin;	
	fin.open(fileName);
	if(fin.fail())
	{
			cout<<"Could not read the file."<<endl;
			exit(1);
	}
	

	//these are verables that will be grabbed from the file to use for the simulation
	int coordinates;
	int numOfCycles;
	int refreshRate;

	//Here are some other veriables that will be used for the simulation
	int upperTemp = 200;
	int lowerTemp = 5;
	double gMin = .0001;

	//Tempature Equations
	double thermalD = (.00122/.000111);
	double equationA;
	double equationG;
	double totalG;

	


	while (!fin.eof())
	{   
		fin >> fileName; 
		fin >> coordinates;
		fin >> numOfCycles;
		fin >> refreshRate;
	}

	/* 
	used this to make sure that it was pulling the info propperly, and it was

	cout << fileName << endl;
	cout << coordinates << endl;
	cout << numOfCycles << endl;
	cout << refreshRate << endl;
	*/

	//always make sure to close the file you are reading
	fin.close();

	//The program can reach into the file and grab the information it needs, so this part is good so far
	//Everything after should be where the new errors are


	//allocate memory for x coordinate
	double** heatArray;
	heatArray = new double* [coordinates];

	double** heatArrayAfter;
	heatArrayAfter = new double* [coordinates];

	for (int i = 0; i < coordinates; i++)
	{
		// allocate memory for y coordinate and filling in the grid
		heatArray[i] = new double[coordinates];
	}

	for (int i = 0; i < coordinates; i++)
	{
		// allocate memory for y coordinate and filling in the grid
		heatArrayAfter[i] = new double[coordinates];
	}

	//setting the array to the cold temp
	for (int i = 0; i < coordinates; i++)
	{
		for (int j = 0; j < coordinates; j++)
		{
			heatArray[i][j] = lowerTemp;
		}
	}
	
	
	//finding the center and making the heat zone
	int center = coordinates / 2;
	
	for (int i = (center-15); i < (center+15); i++)
	{
		for (int j = (center - 15); j < (center + 15); j++)
		{
			heatArray[i][j] = upperTemp;
		}
	}

	heatArrayAfter = heatArray;

	//equationG = (upperTemp - ( 1 + (2 * equationA))* lowerTemp)/(2 * thermalD);

	//testing the equation center
	for (int t= 0; t < numOfCycles; t++)
	{
		
		for (int i = 0; i < coordinates; i++)
		{
			for (int j = 0; j < coordinates; j++)
			{
				equationA = (1-(2 * thermalD * gMin))/ (2 * (heatArray[i][j] - 1));
				totalG = 0;

				//checks the Top
				if (i > 0)
				{
					if (heatArray[i][j] != heatArray[i - 1][j])
					{
						if (heatArray[i][j] > heatArray[i - 1][j])
						{
							totalG -= (heatArray[i][j] - (1 + (2 * equationA)) * heatArray[i - 1][j]) / (2 * thermalD);
						}
						else
						{
							totalG += (heatArray[i - 1][j] - (1 + (2 * equationA)) * heatArray[i][j]) / (2 * thermalD);
						}
					}
				}
				//checks the Bottom
				if (i < coordinates - 1)
				{
					if (heatArray[i][j] != heatArray[i + 1][j])
					{
						if (heatArray[i][j] > heatArray[i + 1][j])
						{
							totalG -= (heatArray[i][j] - (1 + (2 * equationA)) * heatArray[i + 1][j]) / (2 * thermalD);
						}
						else
						{
							totalG += (heatArray[i + 1][j] - (1 + (2 * equationA)) * heatArray[i][j]) / (2 * thermalD);
						}
					}
				}

				//checks the Left
				if (j > 0)
				{
					if (heatArray[i][j] != heatArray[i][j - 1])
					{
						if (heatArray[i][j] > heatArray[i][j - 1])
						{
							totalG -= (heatArray[i][j] - (1 + (2 * equationA)) * heatArray[i][j - 1]) / (2 * thermalD);
						}
						else
						{
							totalG += (heatArray[i][j - 1] - (1 + (2 * equationA)) * heatArray[i][j]) / (2 * thermalD);
						}
					}
				}

				//checks the Right
				if (j < coordinates - 1)
				{
					if (heatArray[i][j] != heatArray[i][j + 1])
					{
						if (heatArray[i][j] > heatArray[i][j + 1])
						{
							totalG -= (heatArray[i][j] - (1 + (2 * equationA)) * heatArray[i][j + 1]) / (2 * thermalD);
						}
						else
						{
							totalG += (heatArray[i][j + 1] - (1 + (2 * equationA)) * heatArray[i][j]) / (2 * thermalD);
						}
					}
				}
				heatArrayAfter[i][j] = heatArray[i][j] + totalG;
			}
		}
		heatArray = heatArrayAfter;



		//this will display after t iterations (can later set this to give us a display every 100 interations or so) (fixed)
		//making a fake GUI
		if (t % refreshRate == 0 || t == 0)
		{
			if (t == 0)
			{
				cin.get();
			}

			system("clear");
			for (int i = 0; i < coordinates; i++)
			{
				for (int j = 0; j < coordinates; j++)
				{
					//cout << heatArray[i][j] << " ";
					if (heatArray[i][j] < 6) {
						cout << " ";
					}
					if (heatArray[i][j] >= 6 && heatArray[i][j] < 51) {
						cout << ".";
					}
					if (heatArray[i][j] >= 51 && heatArray[i][j] < 101) {
						cout << "o";
					}
					if (heatArray[i][j] >= 101 && heatArray[i][j] < 151) {
						cout << "O";
					}
					if (heatArray[i][j] >= 151 && heatArray[i][j] < 199) {
						cout << "0";
					}
					if (heatArray[i][j] > 199) {
						cout << "@";
					}
				}
				cout << endl;
			}
			cout << endl;
			cout << "KEY: 5 = [ ], 6-50 = [.], 51-100 = [o], 101-150 = [O], 151-199 = [0], 200 = [@]" << endl;
			cout << "Press enter to see next iteration...";
			cin.get();
		}
	}


	//always make sure to free data after everthing is done
	for (int i = 0; i < coordinates; i++)
	{
		delete[] heatArray[i];
	}
	delete[] heatArray;

		
    return 0;
}

