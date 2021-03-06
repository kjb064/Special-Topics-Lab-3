/*
Lab 3 ("A"): Program to test functions in dynamic library 

Author: Kevin Barry

Last Updated: 3/16/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include "geoInfo.h" 
#include <dlfcn.h>

int main(){
    FILE *outFile;
    char outFileName[21];
    
    printf("Enter the name of the output file (max 20 chars.): ");
    scanf("%s", outFileName);

    char choice;
    outFile = fopen(outFileName, "r");
    if(outFile != NULL){
	printf("The output file already exists. Would you like to overwrite it? (Y/N): ");
        scanf(" %c", &choice);
        if(choice == 'n' || choice == 'N'){
	    printf("Terminating program to prevent overwrite.\n");
	    exit(1);
        }
    }
    outFile = fopen(outFileName, "w");

    // For dynamic library use
    void *handle;
    char *err;

    // Define function pointers for dynamic lib.
    void (*sphere_d)(float radius, float *surface, float *volume);
    float (*volCylinder_d)(float radius, float height);
    float (*sumFloats_d)(float x[], int numFloats);
    double (*Sin_d)(float angle);

    // Obtain handle to dynamic library
    handle = dlopen("./libGeoInfo.so", RTLD_LAZY);
    if(handle == (void*)0){
	fputs(dlerror(), stderr);
	exit(-1);
    }

    // Check availability of dynamic functions
    sphere_d = dlsym(handle, "sphere");
    err = dlerror();
    if(err != NULL){
	fputs(err, stderr);
        exit(-1);
    }

    volCylinder_d = dlsym(handle, "volCylinder");
    err = dlerror();
    if(err != NULL){
   	fputs(err, stderr);
	exit(-1);
    }

    sumFloats_d = dlsym(handle, "sumFloats");
    err = dlerror();
    if(err != NULL){
	fputs(err, stderr);
        exit(-1);
    }  

    Sin_d = dlsym(handle, "Sin");
    err = dlerror();
    if(err != NULL){
	fputs(err, stderr);
	exit(-1);
    }

    float sphereRadius, sphereVol, sphereSurface;
    printf("Enter the radius of the sphere: ");
    scanf("%f", &sphereRadius);
       
    (*sphere_d)(sphereRadius, &sphereSurface, &sphereVol);

    printf("Sphere Surface area: %f\n", sphereSurface);
    fprintf(outFile, "Sphere Surface area: %f\n", sphereSurface);
    printf("Sphere volume = %f\n", sphereVol);
    fprintf(outFile, "Sphere volume = %f\n", sphereVol);

    
    float cylRadius, cylHeight, cylVol;
    printf("Enter the radius of the cylinder: ");
    scanf("%f", &cylRadius); 
    printf("Enter the height of the cylinder: ");
    scanf("%f", &cylHeight);
 
    cylVol = (*volCylinder_d)(cylRadius, cylHeight);

    printf("Cylinder volume = %f\n", cylVol);
    fprintf(outFile, "Cylinder volume = %f\n", cylVol);

    
    int numFloats;
    printf("Enter the number of floats to sum: ");
    scanf("%d", &numFloats);

    float sum, floatArray[numFloats];
    for(int i = 0; i < numFloats; i++){
        printf("Enter float %d: ", i+1);
        scanf("%f", &floatArray[i]); 
    }
 
    printf("The array prior to sorting:\n");
    fprintf(outFile, "The array prior to sorting:\n");
    for(int i = 0; i < numFloats; i++){
        printf("%f\n", floatArray[i]);
        fprintf(outFile, "%f\n", floatArray[i]);
    }
    
    printf("\n");
    fprintf(outFile, "\n");
    sum = (*sumFloats_d)(floatArray, numFloats);

    printf("The array after sorting:\n");
    fprintf(outFile, "The array after sorting:\n");
    for(int i = 0; i < numFloats; i++){
        printf("%f\n", floatArray[i]);
        fprintf(outFile, "%f\n", floatArray[i]);
    }

    printf("The sum of the floats is: %f\n", sum);
    fprintf(outFile, "The sum of the floats is: %f\n", sum);


    int numAngles;
    float angle;
    double sinResult;
 
    printf("Enter the number of angles: ");
    scanf("%d", &numAngles);
    for(int i = 0; i < numAngles; i++){
	printf("\nEnter angle %d: ", i+1);
        scanf("%f", &angle);
        sinResult = (*Sin_d)(angle);					
        printf("Sin(%f): %f\n", angle, sinResult);
        fprintf(outFile, "Sin(%f): %f\n", angle, sinResult); 
    }
   
   dlclose(handle);
   fclose(outFile);
}
