#include "serialblock.h"

int serialblock::num_set_bits() const
{
	// see following for algorithm source
	// http://stackoverflow.com/questions/109023/how-to-count-the-number-of-set-bits-in-a-32-bit-integer
	uint32_t i = following;
	i = i - ((i >> 1) & 0x55555555);
	i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
	return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

int serialblock::bit_num_for_letter(char letter) const
{
	if (letter == 0) return 31; // MSB for null
	return letter - 'a';
}

void serialblock::set_char(char letter)
{
	following |= (uint32_t(1) << bit_num_for_letter(letter));
}

void serialize(std::ostream& os, const LetterNode& nd)
{
	serialblock block;

	if (nd.letter == '\0')
	{
		block.set_char('\0');
	}

	for (const auto kv: nd.following)
	{
		block.set_char(kv.first);
	}

	os << block.following;

	for (const auto kv : nd.following)
	{
		if (kv.first != '\0')
		{
			serialize(os, kv.second);
		}
	}
}