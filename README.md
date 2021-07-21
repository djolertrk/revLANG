# revLANG
This is an infrastructure for the revLANG IR (toy) language.

The revLANG is an intermediate-level representation of code implemented as a coding exercise.

## Get the source code

    $ git clone git@github.com:djolertrk/revLANG.git

## Build the project

Please follow the steps below for building the code. There are some dependencies that should be installed so please do install:

    1) llvm/clang packages (version 11 is recommended)
    2) CMake 3.x
    3) GNU Make tool

Steps to build the project:

    $ mkdir build && cd build
    $ CXX=clang++-11 CC=clang-11 cmake ../revLANG/
    $ make && make test

## Running the dummy driver

    $ build/bin/revLANG
    === revLang interpreter ===
    *** Module before the optimizations ***
    ModuleID: my-module.revLang
    
    def fn1():
     ; Successors: bb.1(tag: true)
     bb.0:
     ; Successors: bb.2(tag: false)
     bb.1:
     bb.2:
    
    def fn2():
     bb.0:
     bb.1:
     bb.2:

    def fn3():
     bb.0:
     bb.1:
     bb.2:

    def fn4():
      empty function

    *** Module after the optimizations ***
    ModuleID: my-module.revLang

    def fn1():
     ; Successors: bb.1(tag: true)
     bb.0:
     ; Successors: bb.2(tag: false)
     bb.1:
     bb.2:
    
    def fn2():
     bb.0:
     bb.1:
     bb.2:
    
    def fn3():
     bb.0:
     bb.1:

## The source code

The source code is divided into a few directories. The `src/` contains the code for a dummy driver (`revLANG.cpp`) for the API that has been implemented within `CodeGen/CodeGen.cpp`.
There is also the `tests/` directory which has the implementation of the testing framework (I've used CTest infrastructure for it).
