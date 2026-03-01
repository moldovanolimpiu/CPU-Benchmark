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
  -Vendor (Intel or AMD)
  -Brand String 




  
