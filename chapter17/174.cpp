//
// Created by fiberhome on 2021/3/11.
//
#include "string"
#include "random"
#include "iostream"
#include "memory"

using namespace std;
// Random Numbers
// random-number engines and random-number distribution classes
// Engine: types that generate a sequence of random unsigned integers
// Distribution: types that use an engine to return numbers according to a particular probability distribution

// Note: C++ programs should not use the library rand. Instead, they should use the default_random_engine along with
// appropriate distribution object

vector<unsigned> bad_randVec() {
    default_random_engine e;
    uniform_int_distribution<unsigned> u(0, 9);
    vector<unsigned> ret;
    for (size_t i = 0; i < 100; ++i)
        ret.push_back(u(e));
    return ret;
}

vector<unsigned> good_randVec() {
    // because engine and distribution retain state, they usually should be defined as static so that new numbers are
    // generated on each call
    static default_random_engine e;
    static uniform_int_distribution<unsigned> u(0, 9);
    vector<unsigned>(ret);
    for (size_t i = 0; i < 100; ++i)
        ret.push_back(u(e));
    return ret;
}


int main() {
    // 174.1 Random-number engines and distribution
    default_random_engine e;    // generates random unsigned integers
    for (size_t i = 0; i < 10; ++i)
        // e() calls the object to produce the next random number
        cout << e() << endl;

    // Distribution Types and Engines
    // uniformly distributed from 0 to 9 inclusive
    uniform_int_distribution<unsigned> u(0, 9);
    for (size_t i = 0; i < 10; ++i)
        cout << u(e) << endl;
    // results may be: 0 1 7 4 5 2 0 6 6 9
    // note: when we refer to a random-number generator, we mean the combination of a distribution object with an engine

    // Comparing Random Engine and the rand function
    // C library: rand. the output of calling a default_xxx is similar to the output of rand
    // The range for rand is 0 to RAND_MAX. ... engine is calling the min and max
    cout << "min: " << e.min() << " max: " << e.max() << endl;

    // Engines generate a sequence of numbers
    // for example, generate a vector of 100 random integers
    // almost surely the wrong way to generate a vector of random integers
    // output from this function will be the same 100 numbers on every call
    // see func before main
    // this will return the same vector ever time it's called
    vector<unsigned> v1(bad_randVec());
    vector<unsigned> v2(bad_randVec());
    cout << (v1 == v2 ? "equal" : "not equal") << endl;
    // The right way is to make the engine and distribution static
    // see above
    v1 = good_randVec();
    v2 = good_randVec();
    cout << (v1 == v2 ? "equal" : "not equal") << endl;

    // seeding a generator
    // A seed is a value that an engine can use to cause it to start generating numbers at a new point in its sequence
    // two ways: provide it when create engine; or call the seed member
    default_random_engine e1;   // uses the default seed
    default_random_engine e2(21212);    // given seed
    // e3 and e4 will generate the same sequence since they use the same seed
    default_random_engine e3;
    e3.seed(32333);
    default_random_engine e4(32333);
    for (size_t i = 0; i != 100; ++i) {
        if (e1() == e2())
            cout << "unseeded match at iteration: " << i <<
                 endl;
        if (e3() != e4())
            cout << "seeded differs at iteration: " << i <<
                 endl;
    }
    // picking a good seed, is surprisingly hard. The most common approach is to call the time, which defined in ctime
    default_random_engine el(time(0));

    // Other kinds of Distributions

    // Generating random real numbers
    // uniformly distributed from 0 to 1 inclusive
    uniform_real_distribution<double> u2(0, 1);
    for (size_t i = 0; i < 10; ++i)
        cout << u2(el) << endl;

    // using the distribution's default result type
    // either double or int
    // empty <> signify we want the default type

    // Generating numbers that are not uniformly distributed
    // normal distribution
    normal_distribution<> n(4, 1.5);
    vector<unsigned> vals(9);
    for (size_t i = 0; i != 200; ++i) {
        unsigned v = lround(n(el));  // round to nearest integer
        if (v < vals.size())  // if this result in range
            ++vals[v];
    }
    for (size_t j = 0; j != vals.size(); ++j)
        cout << j << ": " << string(vals[j], '*') << endl;


    // The bernoulli_distribution class
    // bernoulli_distribution doesn't take a template parameter. Always return a bool.
    // suppose a program that plays a game with a user. one of both go fist.
    string resp;
    bernoulli_distribution b;   // 50/50 odds by default
    do {
        bool first = b(e);   // if ture, the program will go first
        cout << (first ? "We go first"
                       : "You get to go first") << endl;
        // play the game passing the indicator of who goes first
        cout << ((play(first)) ? "sorry, you lost"
                               : "congrats, you won") << endl;
        cout << "play again? Enter 'yes' or 'no'" << endl;
    } while (cin >> resp && resp[0] == 'y');
    // the probability can be reset
    bernoulli_distribution b2(0.6); // default is 0.5



}
