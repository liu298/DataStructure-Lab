/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;
using std::sort;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{ 
    ifstream wordsFile(filename); 
    string cur_str;
	if (wordsFile.is_open()) 
	{
	/* Reads a line from `wordsFile` into `cur_str` until the file ends. */
	while(getline(wordsFile, cur_str))
	{
		string sorted = cur_str;
    	sort(sorted.begin(),sorted.end());

    	auto lookup = dict.find(sorted);
    	if(lookup != dict.end())    //sorted exist in the dict
    	{
    		vector<string> cur_vec = lookup->second;
    		if (std::find(cur_vec.begin(), cur_vec.end(), cur_str) == cur_vec.end())//anagrams exist in the dict
    		lookup->second.push_back(cur_str);
    	}
    	else dict[sorted].push_back(cur_str); 
	}
	}
}
/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
	for(auto & cur_str : words)
	{
		string sorted = cur_str;
    	sort(sorted.begin(),sorted.end());

    	auto lookup = dict.find(sorted);
    	if(lookup != dict.end())    //sorted exist in the dict
    	{
    		vector<string> cur_vec = lookup->second;
    		if (std::find(cur_vec.begin(), cur_vec.end(), cur_str) == cur_vec.end())//anagrams exist in the dict
    		(lookup->second).push_back(cur_str);
    	}
    	else 
    	{
			vector<string> ret_vec;
			ret_vec.push_back(cur_str);
            dict.insert(make_pair(sorted, ret_vec));


    	} //sorted did not exist in the dict


	}
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    if(word.length()<1) return vector<string>();
    string sorted = word;
    sort(sorted.begin(),sorted.end());

    auto lookup = dict.find(sorted);
    if(lookup != dict.end())
    	return lookup->second;
    else return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
	vector<vector<string>> ret;
    for(auto & cur_str : dict)
    {
    	string sorted = cur_str.first;
    	sort(sorted.begin(),sorted.end());
    	auto lookup = dict.find(sorted);
    	vector<string> cur_ret = lookup->second;
    	if(cur_ret.size()>1)
    		ret.push_back(cur_ret);
    }
    return ret;
}
