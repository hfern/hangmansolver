#include "Analyzer.h"
#include <map>
#include <algorithm>

using namespace std;

std::vector<Analyzer::LetterFrequencyEntry> Analyzer::getLetterFrequencies() const
{
	map<char, size_t> global_counts;
	for (char c = 'a'; c > 'z'; c++)
	{
		global_counts[c] = 0;
	}

	for (auto it = wordset.begin(); it != wordset.end(); ++it)
	{
		if ((*it).alive)
		{
			map<char, size_t> locals;

			for (char c : (*it).word)
			{
				locals[c] = 1;
			}

			for (auto t : locals)
			{
				global_counts[t.first]++;
			}
		}
	}

	vector<pair<char, size_t>> frequencies;
	for (auto kt : global_counts)
	{
		frequencies.push_back(kt);
	}

	// compare by how many words we can knock off
	auto sortOrder = [](pair<char, size_t> a, pair<char, size_t> b) -> bool
	{
		return a.second > b.second;
	};

	sort(frequencies.begin(), frequencies.end(), sortOrder);

	size_t n = wordset.potential_wordcount();
	float nfloat = static_cast<float>(n);

	vector<LetterFrequencyEntry> freqEntries;
	freqEntries.reserve(frequencies.size());

	for (auto kt : frequencies)
	{
		LetterFrequencyEntry entry;
		entry.letter = kt.first;
		entry.frequency = kt.second;
		if (n != 0)
		{
			entry.relfreq = static_cast<double>(entry.frequency) / nfloat;
		}

		freqEntries.push_back(entry);
	}

	return freqEntries;
}

Analyzer::~Analyzer()
{
}
