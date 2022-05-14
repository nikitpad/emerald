#ifndef __EMERALD_H__
#define __EMERALD_H__

#define ROUNDS 32

template<class T> inline T rol(T left, int right)
{
	return left << right | left >> (sizeof(T) * 8 - right);
}

template<class T> inline T ror(T left, int right)
{
	return left >> right | left << (sizeof(T) * 8 - right);
}

void crypt(
	std::vector<char>& data, 
	std::array<std::uint64_t, 4> key)
{
	std::uint8_t *block = (std::uint8_t*)&key[0];
	std::uint32_t 
			&a = ((std::uint32_t*)block)[0],
			&b = ((std::uint32_t*)block)[1],
			&c = ((std::uint32_t*)block)[2],
			&d = ((std::uint32_t*)block)[3],
			&e = ((std::uint32_t*)block)[4],
			&f = ((std::uint32_t*)block)[5],
			&g = ((std::uint32_t*)block)[6],
			&h = ((std::uint32_t*)block)[7];
				
	std::uint64_t 
			&q1 = ((std::uint64_t*)block)[0],
			&q2 = ((std::uint64_t*)block)[1],
			&q3 = ((std::uint64_t*)block)[2],
			&q4 = ((std::uint64_t*)block)[3];
				
	std::uint64_t i1, i2, i3, i4;
	for (int i = 0; data.size() > i; i += 32)
	{
		i1 = q1, i2 = q2, i3 = q3, i4 = q4;
		
		q1 ^= rol(q2, 15) + 0x5041F8FDE7D1;
		q1 *= 3072;
		q2 ^= ror(q3, 19) + 0x54973B6AC405;
		q2 *= 513;
		q3 ^= rol(q4, 23) + 0xE80BAF84E781;
		q3 *= 2049;
		q4 ^= ror(q1, 27) + 0xD4031960C3C5;
		q4 *= 65;
			
		for (int i = 0; ROUNDS - 1 > i; i++)
		{				
			a += ror(b, 12) ^ (c >> 5)  ^ (d << 4)  ^ (e >> 1);
			b -= ror(e, 8)  ^ (f >> 14) ^ (g << 13) ^ (h >> 1);
			c += ror(h, 9)  ^ (b >> 7)  ^ (c << 8)  ^ (d >> 12);
			d -= ror(d, 10) ^ (e >> 9)  ^ (f << 8)  ^ (g >> 1);
			e += ror(g, 6)  ^ (h >> 2)  ^ (c << 3)  ^ (d >> 5);
			f -= ror(e, 3)  ^ (f >> 9)  ^ (g << 8)  ^ (h >> 1);
			g += ror(h, 4)  ^ (d >> 8)  ^ (e << 9)  ^ (f >> 11);
			h -= ror(g, 5)  ^ (h >> 3)  ^ (e << 5)  ^ (f >> 7);
			q1 = rol(q1, 3), q2 = ror(q2, 9),
			q3 = ror(q3, 7), q4 = rol(q4, 5);
		}
		
		q1 += i1, q2 += i2, q3 += i3, q4 += i4;
		
		for (int j = 0; 32 > j; j++)
			data[i + j] ^= block[j];
	}
}

#endif
