# GREMLINS
GREMLINS stands for "GeREnciador de Memória com LIsta eNcadeada Simples" it is a memory manager with single linked lists, in this project our objective is to build a GREMLINS library for C++.

### Disclaimer
We're having problems using the test file, althought most of everything seems to be working.

### Dependencies
* `cmake`
* `make`
* `g++`
* `Doxygen` (to gerenate code documentation)

### Usage
To use the GREMLINS, you will need to import the `mpool.h` and `mempool_common.h` files located on the `include` folder to your project. Look the documentation for a more detailed explanation about the GREMLINS.

### Generate Documentation
Go to the project directory and type

```bash
doxygen config
```

Then, open in your browser the `index.html` file, located on the `docs/html/` folder.

### Run Tests

#### Compile
To test the `GREMLINS` library, go to the project directory and type

```bash
mkdir build
cd build
cmake ../
make
```

#### Run
Type `./run_tests` and see the results.

## Authorship
Program developed by [Matheus de Andrade](https://github.com/matheusmas132) and [Felipe Colares](https://github.com/felipecolares22), 2019.1


