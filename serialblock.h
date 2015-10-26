#pragma once
#include <stdint.h>
#include "letter.h"
#include <iostream>

struct serialblock
{
	uint32_t following = 0;

	int num_set_bits() const;
	int bit_num_for_letter(char letter) const;

	void set_char(char letter);
};

void serialize(std::ostream& os, const LetterNode& nd);

