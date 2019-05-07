#include "Mastermind.h"

#include <algorithm>
#include <iostream>
#include <sstream>

std::string validCharacters("BWRGYC");

std::string black     ("\033[45;30m");
std::string red       ("\033[45;31m");
std::string green     ("\033[45;32m");
std::string yellow    ("\033[45;33m");
std::string blue      ("\033[45;34m");
std::string white     ("\033[45;37m");
std::string colour_end("\033[0m");

std::string peg("O ");

std::string master_row("");

std::string getFormattedPegString(const std::string & pegString)
{
    std::stringstream ss;

    for(std::string::const_iterator it = pegString.begin(); it != pegString.end(); it++)
    {
        switch ((char) *it)
        {
            case 'B':
                ss << black << peg << ' ';
                break;
            case 'W':
                ss << white << peg << ' ';
                break;
            case 'R':
                ss << red << peg << ' ';
                break;
            case 'Y':
                ss << yellow << peg << ' ';
                break;
            case 'G':
                ss << green << peg << ' ';
                break;
            case 'C':
                ss << blue << peg << ' ';
                break;
        }
    }
    ss << colour_end;
    return ss.str();
}

std::string assessGuess(const std::string & guess)
{
    std::stringstream marks;

    std::vector<int> discardedMaster;
    std::vector<int> discardedGuess;

    // Check for right place, right colour
    for(std::string::size_type i = 0; i < guess.size(); i++)
    {
        if(master_row[i] == guess[i])
        {
            marks << "X";
            discardedMaster.push_back(i);
            discardedGuess.push_back(i);
        }
    }

    // Check for right colour, wrong place.
    for(std::string::size_type i = 0; i < guess.size(); i++)
    {
        if(std::find(discardedMaster.begin(), discardedMaster.end(), i) == discardedMaster.end())
        {
            for(std::string::size_type j = 0; j < guess.size(); j++)
            {
                if((i != j) && 
                    (std::find(discardedGuess.begin(), discardedGuess.end(), j) == discardedGuess.end()))
                {
                    if(master_row[i] == guess[j])
                    {
                        marks << "/";
                        discardedGuess.push_back(j);
                    }
                }
            }
        }
    }

    return marks.str();
}

void printRows(std::vector<std::string> &rows)
{
    int i = 0;
    for(std::vector<std::string>::iterator row = rows.begin(); row != rows.end(); row++)
    {
        i++;
        std::cout << i << ": " << getFormattedPegString(*row) << " = " << assessGuess(*row) << std::endl;
    }
}

bool validateGuess(const std::string & guess)
{
    if(guess.size() == row_width)
    {
        for(std::string::size_type i = 0; i != guess.size(); i++)
        {
            if(validCharacters.find(guess[i]) == std::string::npos)
            {
                return false;
            }
        }
        return true;
    }
    std::cout << "guess.size() " << guess.size() << std::endl;
    std::cout << "row_width " << row_width << std::endl;
    return false;
}
