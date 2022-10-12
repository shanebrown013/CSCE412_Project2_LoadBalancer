# CSCE412_Project2_LoadBalancer

## Project Description
My implementation of this project first gets 2 inputs from the user (number of servers to create and amount of clock cycles to run the load balancer). It will then to proceed to create an initial queue with the (number of servers to create) * 2. At the same time the program will open, or create, an output file , LoadBalancerLog.txt, to output the process and critical information. Next, it will create the amount of webservers the user defined. It will then assign the newly created webservers with a request. Every clock cycle, the load balancer will iterate to a webserver and check if the request at that webserver is completed. If it is completed, the webserver will be given a new request and that completed request will provide a log in the output file. If the request is not yet completed, it will proceed to the next clock cycle and iterate to the next webserver where it will continue to perform the same actions. The load balanacer will proceed in a cycle like this until the queue is empty, or the amount of cycles the user inputted is reached.

## Execution
To execute the project, compile first with

"g++ loadbalancer.cpp requests.cpp webserver.cpp"

Then type:

"./a.out"

## Documentation
The documentation for this project is provided by doxygen.

