# Measurements in C++

Measurements made on `std::find` on `std::vector` for Bjarne Stroustrup's _Design Using C++_ course at Columbia.

## Running

For all optimization flags except `-O0`, my vectors were optimized into nothing.
Therefore, I decided to use `-O0` in all my tests.

```sh
make

./measurements

```

## Description

Let's do some microbenchmarks for simple linear search algorithms.

- std::find() on a vector<int>:
  Use a vector large enough to get meaningful values on your machine (1,000,000 elements are likely not enough). Measure the time needed to
  - Find the 7 in the middle of a vector<int> where all other elements are not 7.
  * Try to find a 7 in a vector<int> where no element is 7

* std::find_if() on a vector<int>:
  Use a vector large enough to get meaningful values on your machine. Measure the time needed to

  - Find the x < 7 in the middle of a vector<int> where all other elements are ≥7.

  * Try to find an x < 7 in a vector<int> where all elements are ≥7.

* std::find() on a vector<std::string>:
  Generate a vector<string> containing 1,000,000 random 20-letter strings (don’t bother timing this). Measure the time needed to

  - Try to find XXXXXXXXXXXXXXXXXXXX (20 Xs) in that vector using std::find().
    Was it there? Unlikely, but if so, try with another value. Alternatively (optional), ensure you never generate XXXXXXXXXXXXXXXXXXXX in the first place.

  * Place XXXXXXXXXXXXXXXXXXXX (or whatever value is not present) in the middle and find it using std::find().
    Do each measurement at least three times to check that the values are consistent (not perturbed by - say - browser activity).

* What was the results of your measurements? Is this surprising?
* How do these change based on the size of the vector (optional)?
* How do these change based on the optimisation level (optional)?

### Tips:

- Be sure to output a result or the optimizer may eliminate your code because you don’t use the result.

* For timing, use the chrono part of the standard library (Tour3 Ch16)

* For random numbers/characters, use the random part of the standard library (Tour3 Ch17)

* Remember to document what system you use, what OS, what compiler and what compiler options (-O2 is strongly recommended).

### Requirements

You may hand in multiple files.

- Text: upload these as separate .pdf files (do not bundle them with a .zip).

* Code: upload this as an archive (.zip) with a Readme explaining to the TAs what is where and how to compile and run your code.

Please make sure all filenames follow the format: yourUNI_name_whatever. Furthermore, remember to put your name and UNI at the top of your documents and include page numbers.
