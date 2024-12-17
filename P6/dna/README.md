# [DNA](https://cs50.harvard.edu/x/2024/psets/6/dna/)

DNA, the carrier of genetic information in living things, has been used in criminal justice for decades. But how, exactly, does DNA profiling work? Given a sequence of DNA, how can forensic investigators identify to whom it belongs?

In a file called [dna.py](dna.py) in a folder called [dna](/), implement a program that identifies to whom a sequence of DNA belongs.


## Useful Python's modules or functions

- [csv](https://docs.python.org/3/library/csv.html)
- [csv.DictReader](https://docs.python.org/3/library/csv.html#csv.DictReader)
- [open](https://docs.python.org/3/tutorial/inputoutput.html#reading-and-writing-files)
- [read](https://docs.python.org/3/tutorial/inputoutput.html#methods-of-file-objects)
- [list](https://docs.python.org/3/tutorial/introduction.html#lists)
- [dict](https://docs.python.org/3/tutorial/datastructures.html#dictionaries)


## How to test

- Run your program as `python dna.py databases/small.csv sequences/1.txt`. Your program should output `Bob`.
- Run your program as `python dna.py databases/small.csv sequences/2.txt`. Your program should output `No match`.
- Run your program as `python dna.py databases/large.csv sequences/5.txt`. Your program should output `Lavender`.
- Run your program as `python dna.py databases/large.csv sequences/6.txt`. Your program should output `Luna`.
- Run your program as `python dna.py databases/large.csv sequences/13.txt`. Your program should output `No match`.
- ......
