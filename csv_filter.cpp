#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <sstream>
#include <map>
#include <algorithm>
#include <iomanip>
#include <regex>

// Function to modify map container. This will serve as our word counter.
void insert(std::map<std::string, int> &map1, std::string word)
{
     // Check if a (string) word is present on our map container.
     // We will be using the string word as our index on the map container (e.g map['word'] = word_count).
     if (map1.find(word) != map1.end()) // This will return as true if a word is already in our map container.
     {
          // Increment our counter by one for map['word'].
          map1[word]++;
     }
     else // This will be processed if word is not found on map container
     {
          // Add the word into our map container with value set to 1.
          map1.insert(std::map<std::string,int>::value_type(word,1));
     }
}

// Define variable string as a pair of string and integer.
typedef std::pair<std::string,int> pair;

int main () {
     // Declare variable line as string. This will serve as the container for each line of the file.
     std::string line;
     // Declare variable myfile as input file stream (ifstream) to open csv file.
     std::ifstream myfile ("jobs.csv");
     if (myfile.is_open()) // Check if csv file exists and is available for processing
     {
          // Create map container that accepts a string and an integer. This will serve as: (string) word, (int) word_count.
          std::map<std::string, int> myMap;
          // We will use the getline function to:
          // 1. Loop through the csv on a per line basis.
          // 2. Split each word with ',' as our delimiter.
          // 3. Store the value into variable 'line'.
          while ( getline (myfile, line, ',') )
          {
               // Perform the following string validations:
               // 1. Ensure that line variable is not empty.
               // 2. Ensure that line variable does not container any spaces before the word.
               // 3. Ensure that line variable size is not equal to zero.
               if (!(line.empty()) || !(line.find_first_not_of(' ') == std::string::npos) || !(line.size()))
               {
                    // The following regular expressions check and replace will filter the words in each line.
                    // Declare regular expressions variable to double check for missed new lines.
                    std::regex newlines_r1("\n");
                    // Declare regular expressions variable to handle '/' symbols.
                    std::regex newlines_r2("/");
                    // Declare regular expressions variable to handle '-' symbols.
                    std::regex newlines_r3("-");
                    // Replace new lines with space.
                    line = std::regex_replace(line, newlines_r1, " ");
                    // Replace '/' with space.
                    line = std::regex_replace(line, newlines_r2, " ");
                    // Replace '-' with space.
                    line = std::regex_replace(line, newlines_r3, " ");

                    // Loop through each word in the line.
                    std::stringstream ss(line);
                    std::istream_iterator<std::string> begin(ss);
                    std::istream_iterator<std::string> end;
                    // Store each word in line variable to vector container vstrings.
                    std::vector<std::string> vstrings(begin, end);

                    // Loop through vstrings vector container to process each word.
                    for(std::vector<std::string>::const_iterator i = vstrings.begin(); i != vstrings.end(); ++i)
                    {
                         // Store each word under string variable 'check_word'.
                         std::string check_word = *i;
                         // Remove non-alphanumeric characters on the string.
                         check_word.erase(std::remove_if(check_word.begin(), check_word.end(), [](char c) { return !std::isalnum(c); }), check_word.end());
                         std::for_each(check_word.begin(), check_word.end(), [](char & c) {c = ::tolower(c);});
                         // Pass our map container and the word to check to the insert function that we created.
                         insert(myMap, check_word);
                    }
               }
          }

          // Declare vector container.
          std::vector<pair> vec;
          // Copy each word in our map container to vec variable.
          std::copy(myMap.begin(), myMap.end(),std::back_inserter<std::vector<pair>>(vec));
          // Sort words in vec container in descending order.
          std::sort(vec.begin(), vec.end(), [](const pair& l, const pair& r) {
               if (l.second != r.second)
                    return l.second > r.second;
			return l.first > r.first;
		});

          // Function to display the word and word_count stored in vec variable.
          // setw will allow us to print the values in pretty format.
          using std::setw;
          for (auto const &pair: vec) {
               std::cout << "Word: " << std::left << setw(40) << pair.first << setw(7) << "Count: " << std::left << pair.second << '\n';
          }

          // Close file stream.
          myfile.close();
          return 0;
     }
     else
     {
          // Print if file is not available.
          std::cout << "Unable to open file" << std::endl; 
          return 1;
     }
}

