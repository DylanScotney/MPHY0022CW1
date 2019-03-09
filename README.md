MPHY0022CW1
------------------

Purpose
-------

This project contains a linear regression command line app that fits 
coefficients to data from an input file.

Credits
-------

This project was developed as part of a coursework for the MPHY0022 
module at UCL during the 2018/2019 academic season and was developed by:
- Dylan Scotney (dylan.scotney.18@ucl.ac.uk)

Build Instructions
------------------

Windows:\
Along side MPHY0022CW1 create MPHY0022CW1-Build.\
In CMake GUI add path to source code "MPHY0022CW1" and path to build 
folder "MPHY0022CW1-Build".\
Click "configure".\
In the pop-up, specifiy generator for this project e.g. "Visual Studio 
15 2017" and click finish.\
Once configured click "generate".\
Open solution and build as normal in Visual Studio.

Linux:\
Along side MPHY0022CW1:
``` 
cd MPHY0022CW1-Build
cmake ../MPHY0022CW1
make
```

Implementation
--------------
To linearly fit 2D data corresponding to a set of x and y points use:
```
fitLinearData.exe <filename> <solve type>
```
```filename``` must be a standard text file\
```solve type``` arguments:\
 Fit via the solution the Normal Equation using:\
 -n, --normSolve \
 Fit via gradient descent method using:\
 -g, --gradDescent\
 
Note: data is loaded from file assuming 2 values per line.

