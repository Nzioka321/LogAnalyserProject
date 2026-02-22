#include <iostream> // For console input/output
#include <fstream>  // For file handling
#include <string>   // For string manipulation
#include <sstream>  // For string stream operations
#include <vector>   // For using vector to store error events

using namespace std;

/*
    Stores the time (in seconds since midnight)
    of an ERROR event.
*/
struct ErrorEvent {
    int timeInSeconds;
};

/*
    Converts a time string (HH:MM:SS)
    into total seconds since midnight.
*/
int convertTimeToSeconds(const string& timeText) {
    int hours, minutes, seconds;
    char separator;

    stringstream ss(timeText);
    ss >> hours >> separator >> minutes >> separator >> seconds;

    return ((hours * 3600) + (minutes * 60) + seconds);
}

// Main function to analyze log file and detect error bursts
int main(int argc, char* argv[]) {

	// 1. Validate input file path
    if (argc < 2) {
        cout << "ERROR: Log file path not provided\n";
        return 1;
    }

	// 2. Open log file for reading
    ifstream logFile(argv[1]);
    if (!logFile.is_open()) {
        cout << "ERROR: Unable to open log file\n";
        return 1;
    }

	// 3. Initialize counters and data structures for analysis
    int totalLineCount = 0;
    int infoCount = 0;
    int warningCount = 0;
    int errorCount = 0;

	// Store timestamps of ERROR events for burst detection
    vector<ErrorEvent> errorEvents;

	// 4. Read log file line by line and analyze
    string logLine;
    while (getline(logFile, logLine)) {

        totalLineCount++;

        if (logLine.find("INFO") != string::npos) {
            infoCount++;
        }
        else if (logLine.find("WARNING") != string::npos) {
            warningCount++;
        }
        else if (logLine.find("ERROR") != string::npos) {
            errorCount++;

			// Extract time from format: YYYY-MM-DD HH:MM:SS - ERROR - Message
            if (logLine.length() >= 19) {
                string timeText = logLine.substr(11, 8);
                int seconds = convertTimeToSeconds(timeText);
                errorEvents.push_back({ seconds });
            }
        }
    }

    logFile.close();

	// 5. Detect burst of ERROR events (5 or more within 10 seconds)
    bool burstFound = false;
    int burstStartTime = 0;
    int burstEndTime = 0;
	// Check nested loops to find 5 or more ERROR events within a 10-second window
    for (size_t i = 0; i < errorEvents.size(); i++) {

		int eventsInWindow = 1;// Count first event at index i

        for (size_t j = i + 1; j < errorEvents.size(); j++) {

            int timeDifference =
                errorEvents[j].timeInSeconds -
                errorEvents[i].timeInSeconds;

			if (timeDifference <= 10) { // Within 10 seconds
                eventsInWindow++;

				if (eventsInWindow >= 5) { // Found burst of 5 or more ERROR events
                    burstFound = true;
                    burstStartTime = errorEvents[i].timeInSeconds;
                    burstEndTime = errorEvents[j].timeInSeconds;
                    break;
                }
            }
            else {
				break; // No need to check further if time difference exceeds 10 seconds
            }
        }

        if (burstFound) {
			break; // Exit outer loop if burst is found
        }
    }

	// 6. Print analysis report to console
	cout << "========================================================\n";
    cout << "LOG ANALYSIS REPORT\n";
	cout << "PROJECT 55 - LOG ANALYSER\n"; 
    cout << "========================================================\n";
    cout << "Total lines: " << totalLineCount << "\n";
    cout << "INFO: " << infoCount << "\n";
    cout << "WARNING: " << warningCount << "\n";
    cout << "ERROR: " << errorCount << "\n\n";
	cout << "========================================================\n";

    if (burstFound) {
		cout << "========================================================\n";
        cout << " ERROR BURST DETECTED!!!!!!\n";
        cout << "Time window (seconds): "
            << burstStartTime << " - "
            << burstEndTime << "\n";
		cout << "Number of ERROR events in burst: 5 or more\n";
		cout << "========================================================\n";
    }
    else {
        cout << "No error bursts detected\n";
    }

	return 0;// Exit with success
}
