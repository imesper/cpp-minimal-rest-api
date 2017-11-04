# Minimal Microservice Rest API

A minimal microservice rest api with only two get (/authenticate and /posts) methods using cpprestsdk <https://github.com/Microsoft/cpprestsdk>

## Getting Started

This project was developed and test on Linux. Windows and Apple may run the program, but might need some corrections.
This project uses CMAKE to build and is dependent of CPPRESTSDK, which is dependable of Boost, SSL and Crypt. The tests are dependent of GTest <https://github.com/google/googletest>.

### Installing

Make sure all libraries are installed and in PATH environment.

On shell:

$> cd minimal-rest-api
$minimal-rest-api/> de debug (or release)
$minimal-rest-api/debug/> cmake ..
$minimal-rest-api/debug/> make
$minimal-rest-api/debug/> make install

## Running the tests

To run the tests
$minimal-rest-api/debug/> make test

Or

$minimal-rest-api/debug/>cd ../bin/debug/
$minimal-rest-api/bin/debug/> ./run_rest_api_test

## Running the server

$minimal-rest-api/debug/>cd ../bin/debug/

$minimal-rest-api/bin/debug/> ./run_minial-rest-api <options>

Usage:
  run_minimal-rest-api [OPTION...]

  -h, --host arg  Hostname (default: localhost)
  -p, --port arg  port to listen on (default: 2000)
      --help      Print help


## Built With

* [CPPRESTSDK](https://github.com/Microsoft/cpprestsdk) - The C++ REST SDK from Microsoft

## Authors

* **Ian Esper** - *Initial work* - [Minimal-Rest-API](https://bitbucket.org/imesper/minimal-rest-api)

## License

This project is licensed under the GPL License


