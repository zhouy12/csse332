/* Copyright 2018 Rose-Hulman */

#include <float.h>
#include "./shm.h"
double computeSlope(sharedMemoryStruct *ShmPTR);
double computeIntercept(sharedMemoryStruct *ShmPTR);

/* An instance of this program will run in a child 
 * process spawned by the main program.  The key to
 * the shared memory region created by the main program
 * is stored in the shm.h header file.
 * 
 * (1 points)
 * Use the key to locate and attach the shared memory 
 * region to the address space of this process. 
 * 
 * (1 point)
 * Display to the console the points representing the 2
 * pairs of coordinates stored in the shared memory region.
 *
 * (4 points)
 * Use the coordinates to compute the slope and intercept of
 * the line segment that joins the points defined by the 
 * coordinate. It might he beneficial to declare and use a 
 * separate function to compute each.
 * 
 * Just a reminder:
 * - Linear equation: y = mx + c
 * - Slope equation: m = (y2 -y1)/(x2 - x1)
 * - Intercept is represented as 'c' in the linear equation 
 * 
 * Save the slope and intercept in the shared memory region.
 * 
 * (1 point)
 * Detach the shared memory region from this process's
 * address space.
 * */
int main(int argc, char *argv[]) {
    sharedMemoryStruct *ShmPTR;
    // STUDENTS
    int ShmID = locateSharedMemory(SHM_KEY);
    ShmPTR = attachSharedMemoryRegion(ShmID);
    printf("Receive points (%.2f, %.2f), (%.2f, %.2f)\n",
        ShmPTR->x1, ShmPTR->y1, ShmPTR->x2, ShmPTR->y2);
    ShmPTR->m = computeSlope(ShmPTR);
    ShmPTR->c = computeIntercept(ShmPTR);
    printf("Saving slope and intercept...\n");
    detachSharedMemory(ShmPTR);
    return 0;
}

// STUDENTS
double computeSlope(sharedMemoryStruct *ShmPTR) {
    double slope = 0;
    if (ShmPTR->x1 == ShmPTR->x2) {
        return DBL_MAX; /* or quit with division by zero error. */
    }
    slope = (ShmPTR->y2 - ShmPTR->y1)/(ShmPTR->x2 - ShmPTR->x1);
    return slope;
}

// STUDENTS
double computeIntercept(sharedMemoryStruct *ShmPTR) {
    return ShmPTR->y1 - (ShmPTR->m * ShmPTR->x1);
}