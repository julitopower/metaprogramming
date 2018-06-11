#ifndef SEQUENCES_HPP
#define SEQUENCES_HPP

#include <cstdio>

/*!
 * \brief Type to hold the sequence <0, 1, ...>
 */
template<int... I>
class sequence {};

/*!
 * \brief Natural integer Sequence type generator (i >= 0)
 *
 * The set of recursive calls will look something like:
 *
 * sequence_gen<4>
 * sequence_gen<3, 3>
 * sequence_gen<2, 2, 3>
 * sequence_gen<1, 1, 2, 3>
 * sequence_gen<0, 0, 1, 2, 3>::type -> sequence<0, 1, 2, 3>
 */
template<int Idx, int... I>
class sequence_gen {
public:
    using type =
        typename sequence_gen<Idx - 1, // Elements left to add for recursive call
                              Idx - 1, // Element to prepend in this recursive call
                              I...>::type;
};

/*
 * Base case to end recursion.
 *
 * Discard the first template argument, which indicates that there are
 * zero elements left to add, and wrap the rest in a sequence type
 */
template<int... I>
class sequence_gen<0, I...> {
public:
    using type = sequence<I...>;
};

/*
 * Dummy function used to benefit from the func<T>()... mechanism, which
 * expands the expression to func<T1>(), func<T2>(), .... The expansion
 * needs to be consumed as an argument, which is why we use this function
 */
template<typename... T>
void print(T...) {
}

/*
 * To print one integer passed as a template
 */
template<int V>
int print_get() {
    printf("%d ", V);
    return V;
}

/*!
 * \brief Print the sequence
 *
 * This is the method that consumers of this library should use to
 * print sequences.
 */
template<int... I>
void printSequence(sequence<I...>) {
    print(print_get<I>()...);
}

#endif // SEQUENCES_HPP
