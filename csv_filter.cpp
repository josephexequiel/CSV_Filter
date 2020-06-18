#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <sstream>
#include <map>
#include <algorithm>
#include <locale>

void insert(std::map<std::string, int> &map1, std::string word)
{
     if (map1.find(word) != map1.end())
          map1[word]++;
     else
          map1.insert(std::map<std::string,int>::value_type(word,1));
}

int main () {
     std::string line;
     std::ifstream myfile ("jobs.csv");
     if (myfile.is_open())
     {
          std::map<std::string, int> myMap;
          while ( getline (myfile, line, ',') )
          {
               if (!(line.empty()) || !(line.find_first_not_of(' ') == std::string::npos))
               {
                    std::stringstream ss(line);
                    std::istream_iterator<std::string> begin(ss);
                    std::istream_iterator<std::string> end;
                    std::vector<std::string> vstrings(begin, end);
                    for(std::vector<std::string>::const_iterator i = vstrings.begin(); i != vstrings.end(); ++i)
                    {
                         std::string check_word = *i;
                         check_word.erase(std::remove_if(check_word.begin(), check_word.end(), [](char c) { return !std::isalnum(c); }), check_word.end());
                         std::for_each(check_word.begin(), check_word.end(), [](char & c) {c = ::tolower(c);});
                         insert(myMap, check_word);
                    }
               }
          }

          for (auto x : myMap)
          {
               std::cout << "Word: " << x.first << "\tCount: " << x.second << std::endl;
          }

          myfile.close();
     }
     else std::cout << "Unable to open file"; 
     return 0;
}

