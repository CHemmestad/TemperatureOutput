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

//Precondition ; Checking to see if the file we want exists or can be found
//Postcondition ; Creating the file we need if it cant be found
int createFile ( ) ;

//Precondition ; We dont have the number we need to make the chart the correct scale when printed
//Postcondition ; Doing math to get the numbver we need for making the chart
int findTempChartMin ( int tempMin ) ;

//Precondition ; We dont have the number we need to make the chart the correct scale when printed
//Postcondition ; Doing math to get the numbver we need for making the chart 
int findTempChartMax ( int tempMax ) ;

//Precondition ; We dont have any information to display on the chart yet
//Postcondition ; Getting information from the file to use on the chart
void getInfoFromFile ( double &tempNumber , bool done , int tempMin , int tempMax , int tempChartMin ) ;

//Precondition ; There isnt a bottom to the chart
//Postcondition ; Making the bottom of the chart with the temp min and max displayed for clarity
void makeChartBottom ( int tempMax , int tempMin , int tempChartMax , int tempChartMin ) ;

int main(int argc, char **argv)
{
	//Checking if the file exists first and creating it if it doesnt
	ifstream infile ;
	infile.open("TempInput.dat") ; //Opening the file we want the information from
	if ( !infile ) { //Checking if the file exists or can be found
		createFile ( ) ; //Creating the file if it doesnt
	}
	infile.close ( ) ; //Closing the file
	
	//Variables
	int tempMin = -35 ; //Variable to change the range of the minimum temp for the chart
	int tempMax = 120 ; //Variable to chang the range of the maximum temp for the chart
	double tempNumber ; //Used to store the values from the file and use whithin the loop
	bool done = false ; //Used to tell the loop when to stop (kind of useless)
	int tempChartMin = findTempChartMin ( tempMin ) ; //Variable used for changing the actual size of the chart with the values given
	int tempChartMax = findTempChartMax ( tempMax ) ; //Variable used for changing the size of the chart
	
	system ("clear") ; //Making it look cleaner
	
	//Printing the heading for the scale of the chart
	cout << "\t\t\t    " << tempMin << " - " << tempMax << " degrees hourly" << endl << endl ;
	
	//Taking numbers from inside the file and then printing the chart
	getInfoFromFile ( tempNumber , done , tempMin , tempMax , tempChartMin ) ;
	
	//Creating the bottom line for the bottom of the chart with the range displayed for clarity
	makeChartBottom ( tempMax , tempMin , tempChartMax , tempChartMin ) ;
		
	return 0;
}

void makeChartBottom ( int tempMax , int tempMin , int tempChartMax , int tempChartMin ) {
	cout << "\t   " ;
	cout << tempMin ;
	for ( int x = 0 ; x < tempChartMax+tempChartMin ; x++ ) {
		cout << '_' ;
	}
	cout << tempMax ;
}

int createFile ( ) {
	char yesNo ; //Variable used for asking user to create file if file not found
	
	//Asking if they want the program to create the file for them
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
	return 0 ;
}

int findTempChartMin ( int tempMin ) { 
	int chartMin ;
	chartMin = (tempMin*-1)/3+1 ; 
	return chartMin ;
}

int findTempChartMax ( int tempMax ) { 
	int chartMax ; 
	chartMax = tempMax/3+1 ;
	return chartMax ;
}

void getInfoFromFile ( double &tempNumber , bool done , int tempMin , int tempMax , int tempChartMin ) {
	//Creating a loop to take all the information from the file
	ifstream infile ;
	infile.open("TempInput.dat") ; //Opening the file we want the information from
	
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
			cout << "\t" << setw(4) << setprecision(3) << tempNumber ; //Setting the width of the numbers to four so they line up on the right and look nicer
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
	infile.close ( ) ;
}

