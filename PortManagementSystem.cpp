#include<time.h>
#include<iostream>
#include <cstdlib>
#include <ctime>
#include<cmath>
#include <chrono>
#include <thread>
#include <windows.h>
using namespace std;



char shiptypes[6][30] = { "Ferry","Barge","Battleship","Ferry","Cargo carriers" ,"Trawler" };
class ship
{
	int arrivaltime;
	int departuretime;
	int timeonport;
	bool selectedingene;
	char typeofship[30];
	int startOfGivenTimeSlot;
public:
	ship()
	{
		do
		{
			arrivaltime = 1 + rand() % (6 - 1 + 1);    //the port gets opened at 1 oclock and closes at 6 oclock
			departuretime = 1 + arrivaltime;
		} while (departuretime > 6);

		int randind = 0 + rand() % (5 - 0 + 1);
		strcpy(typeofship, shiptypes[randind]);

		// timeonport is in accordnace to the size of the ship
		// size of the ship has been incorporated in timeonport. Greater is the cargo/no of passengers that
		//need to be unloaded/loaded into the ship, it means graeter is the size of the ship becasue it holds more cargo/passengers and 
		// thus requires more time on port


		// According to port policy, a slot given to any ship is 1 hour long. 
		// The maximum time for unloading/laoding is 45 mins for maximum sized ship
		// a ship can take 45 mins or less on the port. However, 15 mins are given to the ships for docking, starting the ship, fueling etc.
		//Thus the biggest sized ship will take 1 hour (45 mins for loading/unlaoding and 15 mins for other things mentioned above)
		// Smaller sized ships will take time < 1 hour accordingly.



		//random values given from 1min-60mins. However the value should be <=45 mins. If it is >45 mins, the ship will 
		//disrupt the ship in the next slot on the same dockyard 

		timeonport = 1 + rand() % (60 - 1 + 1);

		selectedingene = false;
		startOfGivenTimeSlot = -1;
	}


	ship(int at, int dt, int top, bool sig, int sogts, char tos[])
	{
		this->arrivaltime = at;
		this->departuretime = dt;
		this->timeonport = top;
		selectedingene = sig;
		startOfGivenTimeSlot = sogts;
		if (tos == NULL)
			strcpy(typeofship, "\0");
		else
			strcpy(typeofship, tos);



	}

	ship(const ship& s)
	{
		this->arrivaltime = s.arrivaltime;
		this->departuretime = s.departuretime;
		this->timeonport = s.timeonport;
		selectedingene = s.selectedingene;
		startOfGivenTimeSlot = s.startOfGivenTimeSlot;
		int len = strlen(s.typeofship);
		strcpy(typeofship, s.typeofship);
	}

	int getat()
	{
		return this->arrivaltime;
	}

	int getdt()
	{
		return this->departuretime;
	}

	int gettop()
	{
		return this->timeonport;
	}

	bool getsig()
	{
		return this->selectedingene;
	}


	char* gettos()
	{
		char* arr = new char[30];
		strcpy(arr, this->typeofship);
		return arr;
	}


	void operator = (const ship& D)
	{
		arrivaltime = D.arrivaltime;
		departuretime = D.departuretime;
		timeonport = D.timeonport;
		selectedingene = D.selectedingene;
		startOfGivenTimeSlot = D.startOfGivenTimeSlot;
		int len = strlen(D.typeofship);
		strcpy(typeofship, D.typeofship);
	}




	int gettimeslot()
	{
		return startOfGivenTimeSlot;
	}


	void setarrivaltime_departuretime()
	{
		do
		{
			arrivaltime = 1 + rand() % (6 - 1 + 1);    //the port gets opened at 1 oclock and closes at 6 oclock
			departuretime = 1 + arrivaltime;
		} while (departuretime > 6);

	}


	void setselectedingene(bool x)
	{
		selectedingene = x;
	}

	void settimeslot(int x)
	{
		startOfGivenTimeSlot = x;
	}

	void settop()
	{
		timeonport = 1 + rand() % (60 - 1 + 1);  //random values for 1min-60 mins
	}


	void settos()
	{

		int randind = 0 + rand() % (5 - 0 + 1);
		strcpy(typeofship, shiptypes[randind]);
	}

};





bool diversityinfitness(float* arr)
{
	bool flag = true;
	for (int i = 0;i < 19;i++)
	{
		if (arr[i] != arr[i + 1])
			flag = false;
	}
	return flag;
}


void printing(ship*** a)
{
	//srand(time(NULL));
	for (int i = 0; i < 20; i++)
	{
		cout << "in chromosome " << i + 1 << endl;
		for (int j = 0; j < 5; j++)
		{
			cout << "in gene " << j + 1 << endl;
			for (int k = 0; k < 3; k++)
			{
				cout << "for dock " << k + 1 << endl;
				cout << "Arrival time of ship:  " << a[i][j][k].getat() << " o' clock " << endl;
				cout << "Departure time of ship: " << a[i][j][k].getdt() << " o' clock" << endl;
				cout << "Time required for uploading/downlaoding cargo: " << a[i][j][k].gettop() << " minutes " << endl;
				char* arr2;
				arr2 = a[i][j][k].gettos();
				cout << "Type of ship: " << arr2 << endl;
			}
			cout << endl;
		}
		cout << endl;
	}
}


void refresh_availabe_ships(ship* arr)
{
	for (int i = 0;i < 50;i++)
	{
		arr[i].setselectedingene(false);
	}

}

//more fitness means 1 hour or less time on port. Also, fitness depends upon whether the timings of that ship match the given time slot 

float fitnessfun(ship** obj)
{
	float fitnessofchromosome = 0.0f;
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			if (obj[i][j].gettop() <= 45)  //The remaining 15 mins of the slot given to startung engines of ship, docking of ship etc.
				fitnessofchromosome = fitnessofchromosome + 1;
			if (obj[i][j].gettimeslot() == obj[i][j].getat() && obj[i][j].getdt() == obj[i][j].gettimeslot() + 1)
				fitnessofchromosome = fitnessofchromosome + 1;
		}
	}
	return fitnessofchromosome;

}


//one point given to each satisfied constraint. Three docks in one gene (3*1=3). 5 genes per chromosome (5*3=15). 2 constraints (15*2=30)
bool fitnessreached(float* arr, int size)
{
	for (int i = 0;i < size;i++)
	{
		if (arr[i] >= 30)    //the max fitness according to our system
			return true;
	}
	return false;
}




int finalsolution(float* arr, int size)
{
	for (int i = 0;i < size;i++)
	{
		if (arr[i] >= 30)    //the max fitness according to our system
			return i;
	}

}

int main()
{
	// 3d array
	srand(time(NULL));


	ship* shipsavailable = new ship[50];
	for (int i = 0;i < 50;i++)
	{
		shipsavailable[i] = ship();
	}

	ship*** s = new ship * *[20];   //pop size
	for (int i = 0;i < 20;i++)
	{
		s[i] = new ship * [5];
		int timing = 1;
		for (int j = 0;j < 5;j++)
		{
			s[i][j] = new ship[3];
			for (int k = 0;k < 3;k++)  //for docks
			{
				int index = 0 + rand() % (49 - 0 + 1);
				if (shipsavailable[index].getsig() == false)   //one ship can be in 1 chromose just once 
				{
					s[i][j][k] = shipsavailable[index];
					shipsavailable[index].setselectedingene(true);
					s[i][j][k].settimeslot(timing);
				}
				else
					k--;

			}
			timing++;
		}
		refresh_availabe_ships(shipsavailable);
	}


	float fitnessvalues[20] = { -1 };
	int noofite = 0;   //To limit the number of iterations if best fitness is not being reached 
	//srand(time(NULL)); //////////////////////////////////

	while (fitnessreached(fitnessvalues, 20) == false && noofite < 500)
	{
		float roulettewheel[20];
		float sumofallfitnessvalues = 0.0f;
		float temp = 0;
		bool flag = false;
		for (int i = 0;i < 20;i++)
		{

			fitnessvalues[i] = fitnessfun(s[i]);
			if (fitnessvalues[i] >= 30)
				flag = true;
			sumofallfitnessvalues = sumofallfitnessvalues + fitnessvalues[i];
		}
		if (flag == true)   //Most Fit solution found
			break;
		int fparentind;
		int sparentind;

		noofite++;
		// we use proportionate selection algorithm
		for (int i = 0;i < 20;i++)
		{
			cout << "fitness value before division: " << fitnessvalues[i] << endl;
			fitnessvalues[i] = (fitnessvalues[i] / sumofallfitnessvalues);
		}


		float number = 0.0f;
		for (int i = 0;i < 20;i++)
		{
			cout << "Realtive fitness value: " << fitnessvalues[i] << endl;
			number = fitnessvalues[i] * 200;
			roulettewheel[i] = temp + number;     //mapping the roulette by mutiplying a factor of 200. Probabilties remain the same 
			//Done to avoid the selection of only 0 and 1 chromosomes as selection probability is VERY small 
			temp = roulettewheel[i];
			cout << "roulette wheel value: " << roulettewheel[i] << endl;
		}


		double  firstparent;
		double  secondparent;
		fparentind = -1;
		sparentind = -1;
		//srand(time(NULL));

		do
		{
			double max = roulettewheel[19];  //the upper bound of value 
			cout << roulettewheel[19] << endl;
			double min = roulettewheel[0];
			firstparent = 1 + rand() % (long long(max) - 1 + 1);

			secondparent = 1 + rand() % (long long(max) - 1 + 1);
			cout << "1st parent value selected randomly: " << firstparent << "   " << "2nd parent value selected randomly: " << secondparent << endl;
			for (int i = 1;i < 20;i++)
			{
				if (firstparent <= min)
					fparentind = 0;

				else if (firstparent <= roulettewheel[i] && firstparent > roulettewheel[i - 1])
					fparentind = i; //chromosome number

				if (secondparent <= min)
					sparentind = 0;

				else if (secondparent <= roulettewheel[i] && secondparent > roulettewheel[i - 1])
					sparentind = i; //chromosome number
			}

		} while (fparentind == sparentind);
		cout << "1st parent ind: " << fparentind << "   " << "2nd parent ind: " << sparentind << endl;
		printing(s);


		//We do two step crossover

		ship** newchromosome1 = new ship * [5];
		ship** newchromosome2 = new ship * [5];
		for (int i = 0;i < 5;i++)
		{
			newchromosome1[i] = new ship[3];
			newchromosome2[i] = new ship[3];

			for (int j = 0;j < 3;j++)
			{
				newchromosome1[i][j] = ship(-1, -1, -1, false, -1, NULL);
				newchromosome2[i][j] = ship(-1, -1, -1, false, -1, NULL);

			}

		}



		int cut1 = 1;
		int cut2 = 3;
		for (int i = 0;i < 5;i++)  //for new chromoseom 1
		{
			if (i < cut1)
			{
				for (int j = 0;j < 3;j++)
				{
					newchromosome1[i][j] = s[fparentind][i][j];
				}
			}

			else if (i >= cut1 && i < cut2)
			{

				for (int j = 0;j < 3;j++)
				{
					newchromosome1[i][j] = s[sparentind][i][j];
				}
			}

			else if (i >= cut2)
			{
				for (int j = 0;j < 3;j++)
				{
					newchromosome1[i][j] = s[fparentind][i][j];
				}
			}
		}



		for (int i = 0;i < 5;i++)  //for new chromoseom 2
		{
			if (i < cut1)
			{
				for (int j = 0;j < 3;j++)
				{
					newchromosome2[i][j] = s[sparentind][i][j];
				}
			}

			else if (i >= cut1 && i < cut2)
			{

				for (int j = 0;j < 3;j++)
				{
					newchromosome2[i][j] = s[fparentind][i][j];
				}
			}
			else if (i >= cut2)
			{
				for (int j = 0;j < 3;j++)
				{
					newchromosome2[i][j] = s[sparentind][i][j];
				}
			}

		}



		float newfitnessvalues[22];
		for (int i = 0;i < 20;i++)
		{
			newfitnessvalues[i] = fitnessfun(s[i]);
		}
		newfitnessvalues[20] = fitnessfun(newchromosome1);
		newfitnessvalues[21] = fitnessfun(newchromosome2);


		//finding minimum fit chromoseomes
		int minfitness = newfitnessvalues[0];
		int secondminfitness = INT_MAX;
		int minfitnessind = 0;
		int secondminfitnessind = -1;
		for (int i = 1; i < 22; i++)
		{
			if (newfitnessvalues[i] < minfitness)
			{
				minfitness = newfitnessvalues[i];
				minfitnessind = i;
			}
		}
		cout << "min fitness: " << minfitness << " at index: " << minfitnessind << endl;

		for (int i = 0; i < 22; i++)
		{
			if (newfitnessvalues[i] < secondminfitness && (newfitnessvalues[i] >= minfitness && i != minfitnessind))   //>= in case od dupliacte values 
			{
				secondminfitness = newfitnessvalues[i];
				secondminfitnessind = i;
			}
		}
		cout << "second min fitness: " << secondminfitness << " at index: " << secondminfitnessind << endl;
		cout << "new chromosome 1 fitness  " << newfitnessvalues[20] << endl;
		cout << "new chromosome 2 fitness  " << newfitnessvalues[21] << endl;



		//We do this to avoid copying the entire population into a new population of 22 size
		if (minfitnessind == 20 || secondminfitnessind == 20)
		{
			for (int i = 0; i < 5; ++i)
			{
				delete[] newchromosome1[i];
			}
			delete[] newchromosome1;
		}

		if (minfitnessind == 21 || secondminfitnessind == 21)
		{
			for (int i = 0; i < 5; ++i)
			{
				delete[] newchromosome2[i];
			}
			delete[] newchromosome2;
		}

		if (minfitnessind <= 19 && secondminfitnessind <= 19)   //population size is 20
		{
			for (int i = 0;i < 5;i++)
			{
				for (int j = 0;j < 3;j++)
				{
					s[minfitnessind][i][j] = newchromosome1[i][j];
					s[secondminfitnessind][i][j] = newchromosome2[i][j];
				}
			}

		}

		if (minfitnessind <= 19 && secondminfitnessind == 20)
		{

			for (int i = 0;i < 5;i++)
			{
				for (int j = 0;j < 3;j++)
				{
					s[minfitnessind][i][j] = newchromosome2[i][j];
				}
			}

		}

		else if (minfitnessind <= 19 && secondminfitnessind == 21)
		{

			for (int i = 0;i < 5;i++)
			{
				for (int j = 0;j < 3;j++)
				{
					s[minfitnessind][i][j] = newchromosome1[i][j];
				}
			}

		}

		else if (secondminfitnessind <= 19 && minfitnessind == 20)
		{
			for (int i = 0;i < 5;i++)
			{
				for (int j = 0;j < 3;j++)
				{
					s[secondminfitnessind][i][j] = newchromosome2[i][j];
				}
			}
		}

		else if (secondminfitnessind <= 19 && minfitnessind == 21)

		{
			for (int i = 0;i < 5;i++)
			{
				for (int j = 0;j < 3;j++)
				{
					s[secondminfitnessind][i][j] = newchromosome1[i][j];
				}
			}
		}


		//now we have a new population 
		int limit = 20, j = 0;
		for (int i = 0;i < limit;i++)
		{
			if (i != minfitnessind && i != secondminfitnessind)
			{
				fitnessvalues[j] = newfitnessvalues[i];
				j++;
			}
			else
			{
				limit++;
			}

		}


		//////////////



		///////////////////////

		cout << "All fitness values (not in order) for our NEW population after removing 2 least fit solutions are: " << endl;
		for (int i = 0;i < 20;i++)
		{
			cout << "Fitness : " << fitnessvalues[i] << endl;
		}

		cout << "The new population is: " << endl;
		printing(s);

		bool flag2 = diversityinfitness(fitnessvalues);
		if (flag2 == true)
		{
			cout << endl << endl;
			cout << "No diversity left in the population " << endl;
			cout << "Maximum POSSIBLE fitness reached is: " << fitnessvalues[0] << endl;  //as all values are same 
			cout << "All posiible solutions for maximum POSSIBLE fitness are : " << endl;
			printing(s);
			return 0;
		}

	}

	if (fitnessreached(fitnessvalues, 20) == true)
	{
		cout << "Maximum fitness reached with ships at the dockyards as follows: " << endl;
		int max_fitness = 30;
		int final_chromoseome_ind = -1;
		for (int i = 0;i < 20;i++)
		{
			if (fitnessfun(s[i]) >= 30)
			{
				final_chromoseome_ind = i;
				break;
			}
		}
		for (int i = 0;i < 5;i++)
		{
			cout << "in gene:  " << endl;
			for (int j = 0;j < 3;j++)
			{
				cout << "for dock number " << j + 1 << " :" << endl;
				cout << "Arrival time of ship at the dock: " << s[final_chromoseome_ind][i][j].getat() << " o' clock" << endl;
				cout << "Departure time of ship at the dock: " << s[final_chromoseome_ind][i][j].getdt() << " o' clock " << endl;
				cout << "Time for downloading/uploading for the ship at the dock: " << s[final_chromoseome_ind][i][j].gettop() << " minutes " << endl;
				char* arr;
				arr = s[final_chromoseome_ind][i][j].gettos();  //shallow copy becasue we do not need to store it anywhere. Just need to show
				cout << "Type of ship is: " << arr << endl;


			}
		}

	}
	else
	{
		cout << "ITERATIONS UPPER BOUND REACHED " << endl;

		float max_fitness = fitnessfun(s[0]);
		int final_chromoseome_ind = 0;
		for (int i = 1;i < 20;i++)
		{
			if (fitnessfun(s[i]) > max_fitness)
			{
				final_chromoseome_ind = i;
				max_fitness = fitnessfun(s[i]);
			}
		}
		cout << "Maximum fitness raeched with 500 iterations: " << max_fitness << endl;
		cout << "Maximum possible fitness reached with 500 iterations with ships at the dockyards as follows: " << endl;

		for (int i = 0;i < 5;i++)
		{
			cout << "in gene:  " << endl;
			for (int j = 0;j < 3;j++)
			{
				cout << "for dock number " << j + 1 << " :" << endl;
				cout << "Arrival time of ship at the dock: " << s[final_chromoseome_ind][i][j].getat() << " o' clock" << endl;
				cout << "Departure time of ship at the dock: " << s[final_chromoseome_ind][i][j].getdt() << " o' clock " << endl;
				cout << "Time for downloading/uploading for the ship at the dock: " << s[final_chromoseome_ind][i][j].gettop() << " minutes " << endl;
				char* arr;
				arr = s[final_chromoseome_ind][i][j].gettos();  //shallow copy becasue we do not need to store it anywhere. Just need to show
				cout << "Type of ship is: " << arr << endl;


			}
		}





		system("pause");
	}
}
