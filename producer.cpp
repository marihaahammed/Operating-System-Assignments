//mariha ahammed
//cs33211
//producer.cpp

#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int sharedMemory;
    int* table;

    // allocate shared memory
    sharedMemory = shm_open("table", O_CREAT | O_RDWR, 0666); // create table which is a shared memory object
    ftruncate(sharedMemory, sizeof(int));// set size of shared memory
    table = static_cast<int*>(mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemory, 0));  // maps shared memory to address

    sem_t* full = sem_open("full", O_CREAT, 0666, 0); // creates semaphores
    sem_t* empty = sem_open("empty", O_CREAT, 0666, 3);
    sem_t* mutex = sem_open("mutex", O_CREAT, 0666, 1);

    std::cout << "a processes is running...\n" << std::endl;
    // loop through the operation 5 times
    for (int i = 0; i < 5; ++i) {
        sem_wait(empty);
        sleep(1); // sleep for 1 sec

        sem_wait(mutex);  // unlock mutex
        if (*table < 2) {   // if table isn't full: (that is, the table does not have 2 items))
            ++(*table);    // add new item in the table
            std::cout << "Produced an item." << std::endl << "Table contains: " << *table << " items\n";
        }
        else {
            std::cout << "Table is full!\n";
        }
        sem_post(mutex); // close the  mutex
        sem_post(full);
    }
    sleep(3);   // sleep for 1 sec
    std::cout << "Press enter to exit the completed  process.";

    // closes the semaphores
    sem_close(full);
    sem_close(empty);
    sem_close(mutex);

    // unlinks the semaphores
    sem_unlink("full");
    sem_unlink("empty");
    sem_unlink("mutex");

    // deallocates the shared memory
    munmap(table, sizeof(int));
    close(sharedMemory);
    shm_unlink("table");
    return 0;
}
