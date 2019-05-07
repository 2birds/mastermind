#ifndef _MASTERMIND_H_
#define _MASTERMIND_H_

#include <string>
#include <cstdlib>
#include <vector>

extern int rounds, row_width;

extern std::string validCharacters;

extern std::string black;
extern std::string red;
extern std::string green;
extern std::string yellow;
extern std::string blue;
extern std::string white;
extern std::string colour_end;

extern std::string peg;

extern std::string master_row;

std::string getFormattedPegString(const std::string & pegString);
std::string assessGuess(const std::string & guess);
void printRows(std::vector<std::string> &rows);
bool validateGuess(const std::string & guess);

#endif // _MASTERMIND_H_
