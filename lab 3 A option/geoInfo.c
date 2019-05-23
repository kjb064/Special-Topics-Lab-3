// File geoInfo.c

#include <math.h>

void sphere(float radius, float *surface, float *volume){
    *surface = 4 * M_PI * (pow(radius, 2));
    *volume = (4.0/3.0) * M_PI * (pow(radius, 3));
}

float volCylinder(float radius, float height){
    float volume = M_PI * (radius * radius) * height;
    return volume;
}

float sumFloats(float x[], int numFloats){
    int K;
    float temp;

// Sort by selection
    for(int i = 0; i < numFloats - 1; i++){
        int j = i;
	int *Pt = &j;  // Pt is pointer of lowest float
        K = i + 1;
	while(K < numFloats){
	    if(x[*Pt] > x[K]){
		*Pt = K;
	    }
	    K++;
	}

        temp = x[i];
	x[i] = x[*Pt];
	x[*Pt] = temp;
     }


// after sorting, add all floats
    float sum = 0.0;
    for(int i = 0; i < numFloats; i++)
	sum += x[i];

    return sum;
}

int factorial(int num){
    int nfact = 1;

    for( ; num > 0; num--)
        nfact = nfact * num;

    return nfact;
}

double Sin(float angle){

    #define EPSILON 0.0000001
    int n = 0;
    int fact;
    float oldGuess, newGuess = 0.0;

    angle = (M_PI / 180) * angle;	// convert to radians

    fact = factorial(2*n + 1);
    newGuess += (pow(-1, n) / fact) * pow(angle, 2*n + 1);
    n++;

    do{
	oldGuess = newGuess;
	fact = factorial(2*n + 1);
	newGuess += (pow(-1, n) / fact) * pow(angle, 2*n + 1);
    	n++;
    }while(!(fabs(oldGuess - newGuess) < EPSILON));

    return newGuess;
}


