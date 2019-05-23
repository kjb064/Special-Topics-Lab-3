#include <stdio.h>
#include <stdlib.h>
#include "geoInfo.h" 

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

    float sphereRadius, sphereVol, sphereSurface;
    printf("Enter the radius of the sphere: ");
    scanf("%f", &sphereRadius);
       
    sphere(sphereRadius, &sphereSurface, &sphereVol);

    printf("Sphere Surface area: %f\n", sphereSurface);
    fprintf(outFile, "Sphere Surface area: %f\n", sphereSurface);
    printf("Sphere volume = %f\n", sphereVol);
    fprintf(outFile, "Sphere volume = %f\n", sphereVol);

    
    float cylRadius, cylHeight, cylVol;
    printf("Enter the radius of the cylinder: ");
    scanf("%f", &cylRadius); 
    printf("Enter the height of the cylinder: ");
    scanf("%f", &cylHeight);
 
    cylVol = volCylinder(cylRadius, cylHeight);

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
    sum = sumFloats(floatArray, numFloats);

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
        sinResult = Sin(angle);					
        printf("Sin(%f): %f\n", angle, sinResult);
        fprintf(outFile, "Sin(%f): %f\n", angle, sinResult); 
    }
 
   fclose(outFile);
}
