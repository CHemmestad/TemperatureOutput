/*
Caleb Hemmestad
C++ 2021
Due: 9/29/21
Lab 4 Temperature Output

Design and write a C++ program that inputs
a series of hourly temperature from a file, 
and outputs a bar chart (using stars) of the 
temperatures.
*/


#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std ; //So I dont have to do std::

int main(int argc, char **argv)
{
	
	char yesNo ; //Variable used for asking user to create file if file not found
	
	//Opening the file and creating a new one if needed
	ifstream infile ;
	infile.open("TempInput.dat") ; //Opening the file we want the information from
	if ( !infile ) { //Checking if the file exists or can be found
		cout << "File not found" << endl ;
		cout << "Do you want to create the file? Y/N : " ;
		cin >> yesNo ; //Asking the user if they want the program to create the file for them
		if ( yesNo == 'N' || yesNo == 'n' ) {
			return 1 ;
		} else if ( yesNo == 'Y' || yesNo == 'y' ) {
			ofstream outfile ; 
			outfile.open("TempInput.dat");
			outfile << "(Enter hourly temperatures in this file)" ;
			outfile.close( );
		} else {
			cout << "Invalid input. Program ended." ;
			return 2 ;
		}
	}
	
	
	int tempMin = -35 ; //Variable to change the range of the minimum temp for the chart
	int tempMax = 120 ; //Variable to chang the range of the maximum temp for the chart
	double tempNumber ; //Used to store the values from the file and use whithin the loop
	bool done = false ; //Used to tell the loop when to stop
	
	system ("clear") ; //Making it look cleaner
	
	//Printing the heading for the scale of the chart
	cout << "\t\t\t    " << tempMin << " - " << tempMax << " degrees hourly" << endl << endl ;
	
	int tempChartMin = (tempMin*-1)/3+1 ; //Variable used for changing the actual size of the chart with the values given
	int tempChartMax = tempMax/3+1 ; //Variable used for changing the size of the chart
	
	//Creating a loop to take all the information from the file
	while ( done == false ) {
		if ( infile != '\0' ) {
			infile >> tempNumber ;
			if ( !infile ) { //If there is no input then itll end the loop (I guess that makes the bool useless but whatever)
				break ; //Breaks the loop to move on
			}
			//Making sure all the inputs from the file are within the range of the chart
			if ( tempNumber > tempMax ) {  //Checking for numbers greater than the max temp
				tempNumber = tempMax ; //Equalling it to the max temp for the chart
			}
			if ( tempNumber < tempMin ) { //Checking for numbers less than the min temp
				tempNumber = tempMin ; //qualling it to the min temp for the chart
			}
			//Adding to the look of the chart
			cout << "\t" << setw(4) << tempNumber ; //Setting the width of the numbers to four so they line up on the right and look nicer
			cout << ' ' ; //Adding an extra space for looks
			cout << '|'; //Adding a line for the left part of the chart to add clarity
			
			//Creating the chart with the bars as stars
			if ( tempNumber <= 0 ) {
				tempNumber = tempNumber * -1 ; //Multiplying by -1 to change negative numbers to positive
				tempNumber = round(tempNumber/3) ; //Dividing it by 3 and rounding it up or down
				for ( int x = 0 ; x < tempChartMin-tempNumber ; x++ ) { //Subracting inputted number
				//by the mininum number to find how many spaces need to be outputted before stars
					cout << ' ' ; //Outputting spaces
				}
				for ( int x = 0 ; x < tempNumber ; x++ ) {
					cout << '*' ; //Outputting the stars after the spaces
				}
				cout << '|' ; //Creating the center bar to seperate negative and positive
			} else if ( tempNumber > 0 ) {
				for ( int x = 0 ; x < tempChartMin ; x++ ) {
					cout << ' ' ; //Outputting all spaces for the negative side to keep chart lined up
				}
				tempNumber = round(tempNumber/3) ;
				cout << '|' ; //Adding the center bar before stars
				for ( int x = 0 ; x < tempNumber ; x++ ) {
					cout << '*' ; //Adding the stars on the right side for the positive numbers
				}
			}
			cout << endl ;
		} else {
			done = true ;
		}
	}
	
	//Creating the bottom line for the bottom of the chart with the range displayed for clarity
	cout << "\t   " ;
	cout << tempMin ;
	for ( int x = 0 ; x < tempChartMax+tempChartMin ; x++ ) {
		cout << '_' ;
	}
	cout << tempMax ;
	
	infile.close () ; //Closing the file
	
	return 0;
}

