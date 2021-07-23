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
    
    var !0
    var !1
    var !2
    
    def fn1():
     ; Successors: bb.1(tag: true) 
     bb.0:
        var !0 = ADD var !1, var !2
     ; Successors: bb.2(tag: false) 
     bb.1:
        LOAD var !0
     bb.2:
        STORE var !1, var !2
    
    def fn2():
     bb.0:
     bb.1:
     bb.2:
    
    def fn3():
     bb.0:
        STORE var !1, var !2
     bb.1:
     bb.2:
    
    def fn4():
      empty function

    *** Module after the optimizations ***
    ModuleID: my-module.revLang
    
    var !0
    var !1
    var !2
    
    def fn1():
     ; Successors: bb.1(tag: true) 
     bb.0:
        var !0 = ADD var !1, var !2
     ; Successors: bb.2(tag: false) 
     bb.1:
        LOAD var !0
     bb.2:
        STORE var !1, var !2

The driver will produce `revLang-cfg.dot` file that will be used as an input for the `GraphViz`. We can create a PNG out of it as follows:

    $ dot -Tpng revLang-cfg.dot -o example.png

## The source code

The source code is divided into a few directories. The `src/` contains the code for a dummy driver (`revLANG.cpp`) for the API that has been implemented within `CodeGen/CodeGen.cpp`.
There is also the `tests/` directory which has the implementation of the testing framework (I've used CTest infrastructure for it).
The `examples/` contains `.dot` and `.png` files for the `GraphViz` example for the `Func5` from the `revLANG.cpp`.
