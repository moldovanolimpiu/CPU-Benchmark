# Description

This is a program that benchmarks the performance of a computer's CPU. Various characteristics are evaluated across four types of tests: Memory Transfer, Memory Access, Integer Operations and Floating Point Operations. Each tests' parameters are customizable (to a certain extent), and at the end of the test, the result is displayed in the form of a graph, plus the result of the most demanding test. The project also has a CPU grading option, which besides the graphs, also gives a grade, and an option to save the charts (mostly used when asking people to run the tests and send back the results). Besides the tests, there is also a CPU Identification function, which displays essential info about the processor.

### Two versions
  I've made this project with QT creator, which has the ability to deploy projects in such a way that no other dependencies are needed to run the project. As such, i've uploaded both the source code and the deployed version for easy use

### Baseline results
  The final grade from the Grader has been calculated using a weighted geometric mean, with respect to a baseline result, which I obtained from running the tests on a laptop with the following (relevant) specifications:  
  -AMD Ryzen 5 7535HS with Radeon Graphics (3.3 GHz)  
  -16 GB of DDR5 RAM at 4800MHz  

# Details & User guide

### Running the program

In the [CPUBenchmark_deployed directory](CPUBenchmark_deployed), run the CPUBenchmarkQT.exe executable. And done, it's open and ready to run. The interface should show six buttons: _CPU Identification_, _Memory Transfer Tests_, _Memory Access Tests_, _Integer Operations Tests_, _Floating Point Operations Tests_ and _Grade PC_.

### CPU Identification

This opens a window which displays relevant information about the CPU of the computer on which the program is ran on. Both ```CPUID``` and ```SYSTEM_INFO``` instructions have been used to retrieve the data. 
Displayed info:  
  - Vendor (Intel or AMD)
  - Brand String (AMD Ryzen 5 7535HS with Radeon Graphics for example)
  - Architecture
  - Stepping
  - Type
  - Family & extended family
  - Model & extended model
  - Architecture
  - Page Size
  - Cores & Threads
  - Cache Memory info (for each level, size and associative ways)
  - Base, Max and Bus frequency (only available on Intel CPUs)

### Memory Transfer Tests

Opening this, a window with the test parameters is displayed. This test consists of transfering a block of memory from an address to another using ```memcpy```. The size of the memory is iterated from a minimum size, to a maximum size, and the same size is copied for a specific number of times (runs) to obtain an average. As such, the user can customize the lower index, the upper index, the step, and the number of runs per size. The autofill button will input a dataset, skipping this step altogether. Once the parameters are in, ```Start Test``` can be pressed to begin the test (It might take a while, depending on the computer and the parameters). The results show graphs for the average execution time, and transfer rate, for each memory size, as well as the individual result of the most demanding test, separate from the graphs.

### Memory Access Tests

This test evaluates the number of memory accesses per second, using a matrix. The matrix is traversed twice, once in a row-by-row mode (best case scenario) and once in a column-by-column mode (worst case scenario, to go against cache predictions). The evaluation works the same way, from a lower index, to a higher index. For this test, the index is represented by the matrix size. The user can choose the lower and upper size, as well as the chart type: linear (step can be customized) or logarithmic (base 2, cannot be changed). The end results are the execution time and accesses per second for both the best case and worst case scenario. They are displayed in the same way (graphs and most demanding result).

### Integer Operations Tests








  
