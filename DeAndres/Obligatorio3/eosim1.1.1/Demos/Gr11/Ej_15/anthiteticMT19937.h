#ifndef anthiteticMT19937_HPP_
#define anthiteticMT19937_HPP_
#include <eosim/dist/numbergenerator.hpp>

namespace eosim {

namespace dist {

// Not thread safe (unless auto-initialization is avoided and each thread has
// its own MTRand object)

    class anthiteticMT19937: public NumberGenerator {
    // Data
    public:
    	static const int N = 624;       // length of state vector
    	static const int SAVE = N + 1;  // length of array for save()

    private:
    	static const int M = 397;  // period parameter

    	unsigned long state[N];   // internal state
    	unsigned long *pNext;     // next value to get from state
    	int left;          // number of values left before reload needed


    //Methods
    public:
		/**
		* \brief The constructor of anthiteticMT19937.
		*/
    	anthiteticMT19937();  // initialize with a simple uint32
		/**
		* \brief The destructor of anthiteticMT19937.
		*/
    	~anthiteticMT19937();
		/**
		* \brief This operation assign seed to the generator�s seed.
		*/
    	void setSeed( const unsigned long oneSeed );
		/**
		* \brief This operation returns double between 0 and 1.
		*/
    	double nextDouble();                          // real number in [0,1]
		/**
		* \brief This operation returns unsigned long generated by the generator.
		*/
    	unsigned long nextLong();                       // integer in [0,2^32-1]

    protected:
    	void initialize( const unsigned long oneSeed );
    	void reload();
    	unsigned long hiBit( const unsigned long& u ) const { return u & 0x80000000UL; }
    	unsigned long loBit( const unsigned long& u ) const { return u & 0x00000001UL; }
    	unsigned long loBits( const unsigned long& u ) const { return u & 0x7fffffffUL; }
    	unsigned long mixBits( const unsigned long & u, const unsigned long & v ) const
    		{ return hiBit(u) | loBits(v); }
    	unsigned long  twist( const unsigned long & m, const unsigned long & s0, const unsigned long & s1 ) const
    		{ return m ^ (mixBits(s0,s1)>>1) ^ (-loBit(s1) & 0x9908b0dfUL); }
    };

}

}

/**
 * \@}
*/

#endif  // MERSENNETWISTERH