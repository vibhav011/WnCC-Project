// By Vibhav Aggarwal
// To execute, write : ./a.out timestat.txt

#include <bits/stdc++.h>
using namespace std;

string changeFormat(double secs) {			// funtion to convert seconds to the time format
	int m = secs/60;
	double s = secs - m*60;

	return (to_string(m) + 'm' + to_string(s) + 's');
}

int main(int argc, char const *argv[]) {

	vector<double> real, user, sys;			// to store time in seconds for each run

	ifstream f(argv[1]);

	if (!f.is_open()) {
		cout << "Cannot read file" << endl;
		return 0;
	}

	string line;				// stores each line in a string

	while (getline(f, line)) {

		if (line == "") continue;

		stringstream line_stream(line);
		string a, b;						// a and b are first and second words of line
		line_stream >> a >> b;				// for example, a = "real" and b = "0m0.284s"

		int ind = b.find('m');				// for this file, ind is always 1 but I made it for any general testcase

		double m = stod(b.substr(0, ind));		// extract minutes from b
		double s = stod(b.substr(ind+1, b.size()-ind-2));		// extract seconds from b
		
		// appending the values to appropriate vector
		if (a == "real") real.push_back(60*m + s);
		else if (a == "user") user.push_back(60*m + s);
		else if (a == "sys") sys.push_back(60*m + s);
	}
	f.close();

	double avg[3] = {0, 0, 0};
	double dev[3] = {0, 0, 0};
	// avg stores averages and dev stores standard deviations
	int numRuns = real.size();

	for (int i = 0; i < numRuns; i++) {
		avg[0] += real[i]; dev[0] += real[i] * real[i];
		avg[1] += user[i]; dev[1] += user[i] * user[i];
		avg[2] += sys[i]; dev[2] += sys[i] * sys[i];

		// could have used a loop inside but there are only 3 elements
	}
	avg[0] /= numRuns; avg[1] /= numRuns; avg[2] /= numRuns;
	dev[0] = sqrt(dev[0]/numRuns - avg[0] * avg[0]);
	dev[1] = sqrt(dev[1]/numRuns - avg[1] * avg[1]);
	dev[2] = sqrt(dev[2]/numRuns - avg[2] * avg[2]);

	int inRange[3] = {0, 0, 0};			// stores no. of values in the range (avg-dev, avg+dev)

	for (int i = 0; i < numRuns; i++) {
		if (real[i] > avg[0]-dev[0] && real[i] < avg[0]+dev[0]) inRange[0]++;
		if (user[i] > avg[1]-dev[1] && user[i] < avg[1]+dev[1]) inRange[1]++;
		if (sys[i] > avg[2]-dev[2] && sys[i] < avg[2]+dev[2]) inRange[2]++;
	}

	cout << "Number of runs : " << numRuns << endl << endl;
	cout << "Average Time Statistics" << endl;
	cout << "real : " << changeFormat(avg[0]) << " user : " << changeFormat(avg[1]) << " sys : " << changeFormat(avg[2]) << endl << endl;
	cout << "Standard Deviation of Time Statistics" << endl;
	cout << "real : " << changeFormat(dev[0]) << " user : " << changeFormat(dev[1]) << " sys : " << changeFormat(dev[2]) << endl << endl;
	cout << "Number of runs within average - standard deviation to average + standard deviation" << endl;
	cout << "real : " << inRange[0] << " user : " << inRange[1] << " sys : " << inRange[2] << endl;

	return 0;
}