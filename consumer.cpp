//mariha ahammed
//cs33211
//consumer.cpp


#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    //create variables for shared memory and a table to hold items
    int sharedMemory;
    int* table;
    // allocate a shared memory
    sharedMemory = shm_open("table", O_CREAT | O_RDWR, 0666); // create table which is a shared memory object
    ftruncate(sharedMemory, sizeof(int)); // set size of shared memory
    table = static_cast<int*>(mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemory, 0)); // maps object to the address
    sem_t* full = sem_open("full", O_CREAT, 0666, 0); // creates semaphores
    sem_t* empty = sem_open("empty", O_CREAT, 0666, 3);
    sem_t* mutex = sem_open("mutex", O_CREAT, 0666, 1);

    // iterate through the operation five times
    for (int i = 0; i < 5; ++i) {
        sem_wait(full);
        sleep(1); // sleep for 1 second
        sem_wait(mutex); // unlock mutex
        if (*table > 0) { // if the table has exisiting items and is not empty:
            --(*table);// consume an item in the table
            std::cout << "An item was consumed from the table." << std::endl << "The table now contains " << *table << " items\n";
        }
        else {
            std::cout << "Table is empty!\n";
        }
        sem_post(mutex); // close the mutex
        sem_post(empty);
    }
    // close the semaphores
    sem_close(full);
    sem_close(empty);
    sem_close(mutex);

    // unlink the semaphores
    sem_unlink("full");
    sem_unlink("empty");
    sem_unlink("mutex");

    // deallocate the shared memory
    munmap(table, sizeof(int));
    close(sharedMemory);
    shm_unlink("table");
    return 0;
}


