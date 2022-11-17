// Source(s) of logic assistance:  
// Gaddis, T. (2018). Starting out with C++:
// From control structures through objects. Pearson. 

#include <iostream> // To use cin/cout
#include <iomanip>  // To access setw, setprecision for output width
#include <fstream>  // To utilize ifstream, ofstream, fstream
#include <ctime>    // To access random number generator
using namespace std;

// Global Constant Initialization
const string TITLE = "Voting Ballot Array Functions Program";
const string AUTHOR_LINE = "By Forrest Moulin";
const string DIRECTORY = "C:\\Users\\Username\\Path\\To\\Directory\\";
const int ARRAY_SIZE = 19;

// Create output file stream object
// fout to print to file
// cout to print to console
ofstream fout;

// Function prototypes to notify compiler
// Use fin reference param 
// Note: variable names not needed for array in prototype
void readFile(ifstream& fin, string []);
void simulateVotes(int []);
void getPoints(const int [], double []);
void printResults(const string candidates[],
	const int votes[], const double points[]);

int main()
{	// Seed random number generator using current time
	srand(time(NULL));

	// Dynamic Variable Initialization
	string inFilePath = DIRECTORY + "Candidates.txt";
	string outFilePath = DIRECTORY + "ElectionResults.txt";

	// Declare array objects of size 19 (number of candidates)
	string candidates[ARRAY_SIZE];
	int votes[ARRAY_SIZE];
	double points[ARRAY_SIZE];

	// Create input file stream object
	ifstream fin;

	// Open input/output file streams using file paths
	fin.open(inFilePath);
	fout.open(outFilePath);

	// End program in event of file read/write failures
	if (fin.fail())
	{
		cout << "File open failure:" << endl
			<< inFilePath << endl;
		fin.close();
		fout.close();
		return 0;
	}
	if (fout.fail())
	{
		cout << "File output failure:" << endl
			<< outFilePath << endl;
		fin.close();
		fout.close();
		return 0;
	}
	cout << fixed << setprecision(2) << TITLE << endl
		<< AUTHOR_LINE << endl << endl;

	fout << fixed << setprecision(2) << TITLE << endl
		<< AUTHOR_LINE << endl << endl;

	// Call functions, using fin/3 arrays as parameters
	readFile(fin, candidates);
	simulateVotes(votes);
	getPoints(votes, points);

	// Print results to console and output file
	printResults(candidates, votes, points);

	// Close the file stream objects and exit program
	fin.close();
	fout.close();
	return 0;
}
// Reads the input file and fills the candidates array
void readFile(ifstream& fin, string candidates[])
{
	string candidate;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		fin >> candidate;
		candidates[i] = candidate;
	}
}
// Simulates random vote number 1500-25000 per candidate,
// fills the votes array located in main
void simulateVotes(int votes[]) {
	int randomNumber;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{	// 1500-25000 
		// (23501 possibilities  0-23500 + 1500 = 1500-25000)
		randomNumber = rand() % 23501 + 1500;
		votes[i] = randomNumber;
	}
}
// Fills points array using read-only const int array
void getPoints(const int votes[], double points[])
{	// Points represent vote percentage as a double
	double point;
	int voteTotal = 0;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{	// Find sum of all votes
		voteTotal += votes[i];
	}
	for (int i = 0; i < ARRAY_SIZE; i++)
	{	// Calculate points percentage
		points[i] = 100.0 * votes[i] / voteTotal;
	}
}
// Prints the read-only results to console and output file
void printResults(const string candidates[], 
	const int votes[], const double points[])
{
	int winningVotes, winnerIndex;
	cout << left << setw(10) << "Candidate"
		<< right << setw(7) << "Votes" << " "
		<< right << setw(12) << "Percentage" << endl
		<< setw(30) << setfill('-') << "-" 
		<< setfill(' ') << endl;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		cout << left << setw(10) << candidates[i]
			<< right << setw(7) << votes[i]
			<< right << setw(12) << points[i] << "%" << endl;
		if (i == 0)
		{	// Set first value as winning vote count
			winningVotes = votes[i];
			winnerIndex = i;
		}	// Then set winning vote count to largest number
		else if (votes[i] > winningVotes)
		{
			winningVotes = votes[i];
			winnerIndex = i;
		}
	}

	fout << left << setw(10) << "Candidate"
		<< right << setw(7) << "Votes" << " "
		<< right << setw(12) << "Percentage" << endl
		<< setw(30) << setfill('-') << "-"
		<< setfill(' ') << endl;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (i == 0) winningVotes = votes[i];
		else
		{	// Find candidate with the most votes
			if (votes[i] > winningVotes)winningVotes = votes[i];
			fout << left << setw(10) << candidates[i]
				<< right << setw(7) << votes[i]
				<< right << setw(12) << points[i] << "%" << endl;
		}
	}
	cout << endl << "The simulated election winner is " << candidates[winnerIndex]
		<< ", with " << winningVotes << " votes." << endl;
	fout << endl << "The simulated election winner is " << candidates[winnerIndex]
		<< ", with " << winningVotes << " votes." << endl;
}
/*
* CONSOLE/ELECTION_RESULTS.TXT OUTPUT
* Voting Ballot Array Functions Program
* By Forrest Moulin
*
* Candidate   Votes   Percentage
* ------------------------------
* Rubio       16180        7.29%
* Bush        17661        7.95%
* Christie     3705        1.67%
* Paul        12207        5.50%
* O'Malley     6223        2.80%
* Cruz         2954        1.33%
* Clinton      4930        2.22%
* Trump        9077        4.09%
* Kasich      13787        6.21%
* Sanders     22054        9.93%
* Carson       8225        3.70%
* Gilmore     15821        7.13%
* Fiorina     18681        8.41%
* Santorum    13772        6.20%
* Huckabee     9841        4.43%
* Graham       3720        1.68%
* Jindal       7021        3.16%
* Walker      14525        6.54%
* Perry       21649        9.75%
*
* The simulated election winner is Sanders, with 22054 votes (9.93%).
*/
