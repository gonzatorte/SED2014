#include "anthiteticMT19937.h"
#include <climits>
#include <cmath>

using namespace eosim::dist;


anthiteticMT19937::anthiteticMT19937() {
    setSeed(251182);
}

anthiteticMT19937::~anthiteticMT19937() {
}

double anthiteticMT19937::nextDouble()
	{ return 1- (double(nextLong()) * (1.0/4294967295.0)); }


unsigned long anthiteticMT19937::nextLong()
{
	// Pull a 32-bit integer from the generator state
	// Every other access function simply transforms the numbers extracted here

	if( left == 0 ) reload();
	--left;

	register unsigned long s1;
	s1 = *pNext++;
	s1 ^= (s1 >> 11);
	s1 ^= (s1 <<  7) & 0x9d2c5680UL;
	s1 ^= (s1 << 15) & 0xefc60000UL;
	return ( s1 ^ (s1 >> 18) );
}

void anthiteticMT19937::setSeed( const unsigned long oneSeed )
{
	// Seed the generator with a simple uint32
	initialize(oneSeed);
	reload();
}

void anthiteticMT19937::initialize( const unsigned long seed )
{
	// Initialize generator state with seed
	// See Knuth TAOCP Vol 2, 3rd Ed, p.106 for multiplier.
	// In previous versions, most significant bits (MSBs) of the seed affect
	// only MSBs of the state array.  Modified 9 Jan 2002 by Makoto Matsumoto.
	register unsigned long *s = state;
	register unsigned long *r = state;
	register int i = 1;
	*s++ = seed & 0xffffffffUL;
	for( ; i < N; ++i )
	{
		*s++ = ( 1812433253UL * ( *r ^ (*r >> 30) ) + i ) & 0xffffffffUL;
		r++;
	}
}

void anthiteticMT19937::reload()
{
	// Generate N new values in state
	// Made clearer and faster by Matthew Bellew (matthew.bellew@home.com)
	register unsigned long *p = state;
	register int i;
	for( i = N - M; i--; ++p )
		*p = twist( p[M], p[0], p[1] );
	for( i = M; --i; ++p )
		*p = twist( p[M-N], p[0], p[1] );
	*p = twist( p[M-N], p[0], state[0] );

	left = N, pNext = state;
}
