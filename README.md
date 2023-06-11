# Simulation of COVID-19 Spreading Model

This code simulates the spreading of the COVID-19 virus. Under the premise of different population densities, the closed system and the open system are simulated separately to obtain different transmission models. They serve as reference models in studying, analyzing and predicting the spreading of COVID-19. 

The code is still being continuously improved, and interested developers are welcome to contribute to and collaborate on the code.

In Linux, the compilation and execution process for the code is as follows:

```shell
$ g++ -std=c++17 -o sim sim.cpp

$ ./sim > output.txt 
```

Running the code produces an output file called ```output.txt```, which contains the following data: each line consists of two integers, representing the number of simulated days and the number of people infected with COVID-19, respetively.

```
0       1
1       0
2       0
3       1
4       5
5       1
6       2
7       10
8       6
9       11
10      39
11      32
12      45
13      71
14      94
15      118
16      121
17      134
18      130
19      159
20      175
21      204
...
```

These data can be imported into Excel to create a distribution graph illustrating the spreading of COVID-19 infection.



The code is under Apache 2 License.

