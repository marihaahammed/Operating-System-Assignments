# Operating-System-Assignments
Mariha Ahammed's submission for the first Operating systems Assignment. 


The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

# Compiling commands

$ g++ producer.cpp -pthread -lrt -o producer
$ g++ consumer.cpp -pthread -lrt -o consumer
$ ./producer & ./consumer &

# Implementation

I have two files, 'consumer.cpp' and 'producer.cpp.' Producer creates two items in the table, while consumer takes an item from table. They work synchronously and share memory and sephamores. "int * table" is set to 0, and is incremented in value everytime an item production is called. stops taking item when value is 2. the consumer.cpp decrements '* table' but stops when its value is 0. Program is set to exit when user pressed enter. 

# Example
![image](https://user-images.githubusercontent.com/94094992/199385168-b1ae3566-bd14-4a07-b83d-273395defb3c.png)
