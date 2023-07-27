# Primomata
## Properties of Prime Numbers in Finite State Automata

Primomata is a project that explores the properties of prime numbers within the context of finite state automata. It provides a set of tools to convert regular expressions to NFAs (Non-deterministic Finite Automata), NFAs to DFAs (Deterministic Finite Automata), minimize DFAs, combine DFAs, and even create DFAs that accept multiples of a given number. Additionally, Primomata includes a function to generate DOT files from DFAs or NFAs that can be converted to SVG format.

## Tools

1. Regular Expression to NFA Converter - Converts a regular expression into a Non-deterministic Finite Automaton (NFA).
2. NFA to DFA Converter - Transforms a Non-deterministic Finite Automaton (NFA) into a Deterministic Finite Automaton (DFA).
3. DFA Minimizer - Minimizes a Deterministic Finite Automaton (DFA) by removing redundant states.
4. DFA Combiners - Combines multiple DFAs into a single DFA.
5. Prime DFA Creator - Generates a DFA that recognizes prime numbers.

## Usage

- `make all`: Compiles all the Primomata tools.
- `make tests`: Runs examples of each tool sequentially to demonstrate their functionality.
- `make main`: Executes a command showing how prime numbers cannot be compressed when minimized as DFAs.

## Results

![composites.dfa.dot.svg](tests%2Fcomposites.dfa.dot.svg)
![primes.dfa.dot.svg](tests%2Fprimes.dfa.dot.svg)

As can be seen, the minimized DFAs for both the multiples of 15 and for the multiples of both 3 and 5 have the same number of states. With this technique of combining prime DFAs, the potential of determining the primality of a given number 'n' was explored. By constructing a DFA that combines all prime DFAs up to the square of the largest known prime, a theoretical complexity of 'log2(n)' for primality testing can be achieved. However, due to the fact that primes do not compress, this is an impractical solution due to the size of such a DFA. 