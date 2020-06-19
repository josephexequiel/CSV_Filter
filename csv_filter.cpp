#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <sstream>
#include <map>
#include <algorithm>
#include <locale>
#include <regex>

void insert(std::map<std::string, int> &map1, std::string word)
{
     if (map1.find(word) != map1.end())
          map1[word]++;
     else
          map1.insert(std::map<std::string,int>::value_type(word,1));
}

typedef std::pair<std::string,int> pair;

int main () {
     std::string line;
     std::ifstream myfile ("jobs.csv");
     if (myfile.is_open())
     {
          std::map<std::string, int> myMap;
          while ( getline (myfile, line, ',') )
          {
               if (!(line.empty()) || !(line.find_first_not_of(' ') == std::string::npos) || !(line.size()))
               {
                    std::regex newlines_r1("\n");
                    line = std::regex_replace(line, newlines_r1, "");
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

          std::vector<pair> vec;
          std::copy(myMap.begin(), myMap.end(),std::back_inserter<std::vector<pair>>(vec));
          std::sort(vec.begin(), vec.end(), [](const pair& l, const pair& r) {
               if (l.second != r.second)
                    return l.second > r.second;
			return l.first > r.first;
		});

          for (auto const &pair: vec) {
               std::cout << "Word: " << pair.first << "\tCount: " << pair.second << '\n';
          }

          myfile.close();
     }
     else std::cout << "Unable to open file"; 
     return 0;
}

