#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main ( )
{

    //----------------------------------------//
    //Create the variables that we need
    //----------------------------------------//
    
    // The number of stars we use 
    //int stars = 3; // For the simple three body problem  in symmetricThree.txt
    int stars = 100; //  Up to 10002 in system.txt

    // The variables used for keeping track of everything
    double xLoc[stars];
    double yLoc[stars];
    double zLoc[stars];
    double velX[stars];
    double velY[stars];
    double velZ[stars];
    double mass[stars];

    // Set up the time loop
    int timeStepCounter;
    double timeStep = 0.00001;
    int maxTimeSteps = 100000;
    
    // Set up the loops for cycling all the objects through each other
    int parCounter;
    int reaxCounter; 

    // Set up the variables needed to update the velocity
    double dx,dy,dz,dist;
    double force;
    float gravConst = 1;

    // Set up what we need for I/O
    FILE *inputFile;
    int outputFreq = 1000;
    char namer[5];
    FILE *fp;
    int lines;

    //----------------------------------------//
    // Initialize the variables with values 
    //----------------------------------------//
   
    // Simple asymmetric example
    //inputFile = fopen("./symmetricThree.txt","r");
    inputFile = fopen("./system.txt","r");
    
    // Check to be sure the file exists
    if (inputFile == NULL)
    {
        printf("Error opening the input file.\n");
        return 1;
    }

    // Read in the data
    for(lines = 0; lines < stars; lines++)
    {
        fscanf(inputFile, "%lf %lf %lf %lf %lf %lf %lf ", \
                &xLoc[lines] , &yLoc[lines], &zLoc[lines], &velX[lines], \
                &velY[lines], &velZ[lines], &mass[lines]);
        //printf("%f %f %f %f %f %f %f \n", xLoc[lines], \
                yLoc[lines], zLoc[lines], velX[lines], \
                velY[lines], velZ[lines], mass[lines]);
    }

    //----------------------------------------//
    // Update the velocites and locations
    //----------------------------------------//

    //----------------------------------------//
    // Cycle through the time-steps
    for(timeStepCounter=0;timeStepCounter<maxTimeSteps;timeStepCounter++)
    {

        //----------------------------------------//
        // Cycle through the different particles as the base
        for(parCounter=0; parCounter<stars; parCounter++)
        {
            //----------------------------------------//
            // Cycle through the reactionary points
            for(reaxCounter=parCounter+1; reaxCounter<stars; reaxCounter++)
            {
                //----------------------------------------//
                // Find the distance between each point
                dx = xLoc[parCounter]-xLoc[reaxCounter];
                dy = yLoc[parCounter]-yLoc[reaxCounter];
                dz = zLoc[parCounter]-zLoc[reaxCounter];
                
                dist = sqrt( pow(dx,2) + pow(dy,2) + pow(dz,2) );
                
                //----------------------------------------//
                // Calculate the forces  
                force = gravConst*mass[parCounter]*mass[reaxCounter]/pow(dist,2);
     
                //----------------------------------------//
	        // Print out some things for sanity sake   
                //printf("parCounter,reaxCounter= %d, %d\n",parCounter,reaxCounter);
                //printf("dx,dy,dz,dist = %f, %f, %f\n",dx,dy,dz);
                //printf("dist,force = %f, %f\n",dist,force);    
                 
                //printf("parCounter: vx,vy,vz = %f, %f, %f\n", velX[parCounter],velY[parCounter],velZ[parCounter]);
                //printf("reaxCounter: vx,vy,vz = %f, %f, %f\n", velX[reaxCounter],velY[reaxCounter],velZ[reaxCounter]);

                //----------------------------------------//
                // Update the velocities with the new forces 
                //----------------------------------------//
                
                //----------------------------------------//
                // Forward Euler
                velX[parCounter]  += -1*timeStep*force/mass[parCounter]*dx/dist;
                velX[reaxCounter] +=  1*timeStep*force/mass[reaxCounter]*dx/dist;
                
                velY[parCounter]  += -1*timeStep*force/mass[parCounter]*dy/dist;
                velY[reaxCounter] +=  1*timeStep*force/mass[reaxCounter]*dy/dist;
                
                velZ[parCounter]  += -1*timeStep*force/mass[parCounter]*dz/dist;
                velZ[reaxCounter] +=  1*timeStep*force/mass[reaxCounter]*dz/dist;


                //----------------------------------------//
                //printf("parCounter: vx,vy,vz = %f, %f, %f\n", velX[parCounter],velY[parCounter],velZ[parCounter]);
                //printf("reaxCounter: vx,vy,vz = %f, %f, %f\n", velX[reaxCounter],velY[reaxCounter],velZ[reaxCounter]);

            }
            //----------------------------------------//
            // Update the locations with the new velocites
            // Note we can do this inside this loop because reax>par - any parCounter now will never be re-used
            xLoc[parCounter] += velX[parCounter]*timeStep;
            yLoc[parCounter] += velY[parCounter]*timeStep;
            zLoc[parCounter] += velZ[parCounter]*timeStep;
            //printf("time,part =  %f, %d\n",timeStepCounter*timeStep,parCounter);
            //printf("vx,vy,vz, = %f, %f, %f\n", velX[parCounter],velY[parCounter],velZ[parCounter]);
            //printf("x,y,z = %f, %f, %f\n", xLoc[parCounter],yLoc[parCounter],zLoc[parCounter]);
            //printf("\n");
        }

        //printf("timestep= %d",timeStepCounter);
        //printf("X,Y,Z[1]= %f %f %f\n ",xLoc[1],yLoc[1],zLoc[1]);

        //----------------------------------------//
        // Write the output to a file for viewing every X steps
        //----------------------------------------//
        if(timeStepCounter%outputFreq == 0)
        {
            sprintf(namer,"%07d.txt",timeStepCounter);
            if((fp=fopen(namer, "wb"))==NULL) {
                printf("Cannot open output file.\n");
                return 1;
            }
    
            for(lines = 0; lines < stars; lines++)
            {
                fprintf(fp, "%f %f %f %f %f %f %f \n", xLoc[lines], \
                        yLoc[lines], zLoc[lines], velX[lines], \
                        velY[lines], velZ[lines], mass[lines]);
            }
            fclose(fp);
        }   
    }

    // Finish up
    return 0;
}
