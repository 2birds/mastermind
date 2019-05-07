/* M A S T E R M I N D ! ! !
*
*
* A game of pegs and cunning.
*
*/

#include <iostream>
// #include <cstdlib>
#include <ctime>

#include <boost/program_options.hpp>

#include "Mastermind.h"

namespace po = boost::program_options;

int rounds, row_width;
// 
// std::string validCharacters("BWRGYC");
// 
// std::string black     ("\033[45;30m");
// std::string red       ("\033[45;31m");
// std::string green     ("\033[45;32m");
// std::string yellow    ("\033[45;33m");
// std::string blue      ("\033[45;34m");
// std::string white     ("\033[45;37m");
// std::string colour_end("\033[0m");
// 
// std::string peg("O ");
// 
// std::string master_row("");

// std::string getFormattedPegString(const std::string & pegString)
// {
//     std::stringstream ss;
// 
//     for(std::string::const_iterator it = pegString.begin(); it != pegString.end(); it++)
//     {
//         switch ((char) *it)
//         {
//             case 'B':
//                 ss << black << peg << ' ';
//                 break;
//             case 'W':
//                 ss << white << peg << ' ';
//                 break;
//             case 'R':
//                 ss << red << peg << ' ';
//                 break;
//             case 'Y':
//                 ss << yellow << peg << ' ';
//                 break;
//             case 'G':
//                 ss << green << peg << ' ';
//                 break;
//             case 'C':
//                 ss << blue << peg << ' ';
//                 break;
//         }
//     }
//     ss << colour_end;
//     return ss.str();
// }
// 
// std::string assessGuess(const std::string & guess)
// {
//     std::stringstream marks;
// 
//     std::vector<int> discardedMaster;
//     std::vector<int> discardedGuess;
// 
//     // Check for right place, right colour
//     for(std::string::size_type i = 0; i < guess.size(); i++)
//     {
//         if(master_row[i] == guess[i])
//         {
//             marks << "X";
//             discardedMaster.push_back(i);
//             discardedGuess.push_back(i);
//         }
//     }
// 
//     // Check for right colour, wrong place.
//     for(std::string::size_type i = 0; i < guess.size(); i++)
//     {
//         if(std::find(discardedMaster.begin(), discardedMaster.end(), i) == discardedMaster.end())
//         {
//             for(std::string::size_type j = 0; j < guess.size(); j++)
//             {
//                 if((i != j) && 
//                     (std::find(discardedGuess.begin(), discardedGuess.end(), j) == discardedGuess.end()))
//                 {
//                     if(master_row[i] == guess[j])
//                     {
//                         marks << "/";
//                         discardedGuess.push_back(j);
//                     }
//                 }
//             }
//         }
//     }
// 
//     return marks.str();
// }
// 
// void printRows(std::vector<std::string> &rows)
// {
//     int i = 0;
//     for(std::vector<std::string>::iterator row = rows.begin(); row != rows.end(); row++)
//     {
//         i++;
//         std::cout << i << ": " << getFormattedPegString(*row) << " = " << assessGuess(*row) << std::endl;
//     }
// }
// 
// bool validateGuess(const std::string & guess)
// {
//     if(guess.size() == row_width)
//     {
//         for(std::string::size_type i = 0; i != guess.size(); i++)
//         {
//             if(validCharacters.find(guess[i]) == std::string::npos)
//             {
//                 return false;
//             }
//         }
//         return true;
//     }
//     return false;
// }

int main(int argc, char*argv[])
{
    srand(time(NULL));

    rounds = 10;
    row_width = 4;


    std::vector<std::string> rows;

    try
    {
        po::options_description desc("M A S T E R M I N D - options");
        desc.add_options()
        ("help,h", "Help screen")
        ("rounds", po::value<int>()->default_value(10), "Rounds")
        ("row-width", po::value<int>()->default_value(4), "Row width");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if(vm.count("help"))
        {
            std::cout << desc << std::endl;
            return 0;
        }

        if(vm.count("rounds"))
        {
            rounds = vm["rounds"].as<int>();
        }
        if(vm.count("row-width"))
        {
            row_width = vm["row-width"].as<int>();
        }

        std::cout << "Using row width of " << row_width << " for " << rounds << " rounds." << std::endl;
        std::cout << "Available colours are: " << std::endl;

        std::cout << black  << "BLACK(B), ";
        std::cout << red    << "RED(R),";
        std::cout << green  << "GREEN(G), ";
        std::cout << yellow << "YELLOW(Y), ";
        std::cout << blue   << "BLUE(C), ";
        std::cout << white  << "WHITE(W).";
        std::cout << colour_end << '\n' << std::endl;

        std::cout << "Enter your guess like\n\"YYGC\". That will result in \n"; 
        std::cout 
            << yellow << peg
            << yellow << peg
            << green << peg
            << blue << peg
            << colour_end << std::endl;

        std::cout << "=====================================" << std::endl;
        std::cout << "Generating peg combination..";

        for(int i = 0; i < row_width; i++)
        {
            switch(rand() % 6)
            {
                case 0: // Black
                    master_row += "B";
                    break;
                case 1: // Red
                    master_row += "R";
                    break;
                case 2: // Green
                    master_row += "G";
                    break;
                case 3: // Yellow
                    master_row += "Y";
                    break;
                case 4: // Blue
                    master_row += "C";
                    break;
                case 5: // White
                    master_row += "W";
                    break;
            }
        }

        std::cout << "done!" << std::endl;
        // std::cout << getFormattedPegString(master_row) << std::endl;

        std::string guess;
        for(int i = 0; i < rounds; i++)
        {
            do
            {
                std::cout << "Your guess: ";
                std::cin >> guess;
                if(not validateGuess(guess))
                {
                    std::cout << "Your guess must be made up of " << row_width << " pegs." << std::endl;
                }
            }
            while(not validateGuess(guess));

            rows.push_back(guess);
            printRows(rows);

            if(rows.back().compare(master_row) == 0)
            {
                break;
            }
        }

        if(rows.back().compare(master_row) == 0)
        {
            std::cout << "You win!" << std::endl;
        }
        else
        {
            std::cout << "You lose!" << std::endl;
        }
    }
    catch(const po::error &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 0;
}
