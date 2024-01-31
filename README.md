# UniversalConverter
FTL Practice :)

![image](https://github.com/LKolinko/UniversalConverter/assets/131384241/4ffb01a8-9387-4ef7-ac5e-56db885ff726)

## What is this for?
How often do you convert to different number systems? never ;)
But sometimes you have to.

Converting from 10 to any other is not difficult, but from other systems it can be problematic, and periodic fractions are generally terrible.

UniversalConverter solves this problem!!!!

## Long arithmetic
The project uses it)

Addition - $O(n)$ - base

Subtraction - $O(n)$ - base

Multiplication - $O(n^{1.6})$ - karatsuba algorithm [wiki](https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%9A%D0%B0%D1%80%D0%B0%D1%86%D1%83%D0%B1%D1%8B)

Division - $O(n^{1.6}log(n))$ - binsearch :(

The BigInteger class performs calculations in the number system

## Translation of fractions and periods
Example:

$1110001101.10(1001)$ - problem ((((

To solve this problem the fraction class is used.

Also, when translating, the program catches periods. This is done using `std::map` and the fraction class.

## FileManager

You have access to file input and output

## Installation

1) Clone the repo

   ```bash
   git clone https://github.com/LKolinko/UniversalConverter
   ```

4) Use cmake

   ```bash
   cd ./UniversalConverter
   cmake .
   cmake --build ./
   ```

3) Launch and enjoy :)

   ```bash
   ./UniversalConverter
   ```

## Screenshots

![image](https://github.com/LKolinko/UniversalConverter/assets/131384241/c2d46f6d-e55a-4464-87d5-8bbaad103078)
![image](https://github.com/LKolinko/UniversalConverter/assets/131384241/b71473ba-6153-448b-891f-d44bfc73293d)


