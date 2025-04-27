#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;

string getCurrentDate()
{
    time_t now = time(0);            // Get current time
    tm *localTime = localtime(&now); // Convert to local time structure

    // Extract day, month, and year
    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1;          // Months are 0-based in tm structure
    int year = localTime->tm_year % 100 + 2000; // Get last two digits of the year

    // Format into "DD-MM-YY" using stringstream
    stringstream dateStream;
    dateStream << (day < 10 ? "0" : "") << day << "-"
               << (month < 10 ? "0" : "") << month << "-"
               << year;

    return dateStream.str();
}

int daysBetweenDates(const string &start, const string &end)
{
    struct tm startDate = {}, endDate = {};
    sscanf(start.c_str(), "%d-%d-%d", &startDate.tm_mday, &startDate.tm_mon, &startDate.tm_year);
    sscanf(end.c_str(), "%d-%d-%d", &endDate.tm_mday, &endDate.tm_mon, &endDate.tm_year);

    startDate.tm_year -= 1900;
    startDate.tm_mon -= 1;
    endDate.tm_year -= 1900;
    endDate.tm_mon -= 1;

    time_t start_time = mktime(&startDate);
    time_t end_time = mktime(&endDate);
    return (end_time - start_time) / (60 * 60 * 24); // Convert seconds to days
}