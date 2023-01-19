#pragma once

#include <cstdlib>
#include <random>
#include <cmath>
#include <math.h>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

class myHelper{
public:

	template <typename T>
	static T uniformDistribution(T a, T b){
		T max, min;
		if(a>b){
			max = a; min = b;
		}else{
			max = b; min = a;
		}
		random_device rd;
		mt19937 gen(rd());
	    uniform_real_distribution<double> distr(min, max);

		return (T) distr(gen);
	}
	template <typename T>
	static T normalDistribution(T u, T o){
		srand(time(0));
		double u1 = uniformDistribution<double>(0.0,1.0);
		double u2 = uniformDistribution<double>(0.0,1.0);

		double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
		double z1 = sqrt(-2.0 * log(u1)) * sin(2.0 * M_PI * u2);

		double res = z0 * o + u;

		return (T) res;

	}
	
	static int randomInt(int a, int b){
		if(a>b){
			int temp = a;
			a = b;
			b = temp;
		}
		return (int) uniformDistribution<int>(a,b);
	}
	static int getRandomInt(int a, int b){
		return randomInt(a,b);
	}
	template <typename T>
	static T getRandomItemFrom(vector<T> arr){
		int index = randomInt(0, arr.size());

		return arr[index];
	}
	static double randomDouble(double a, double b){
		if(a>b){
			double temp = a;
			a = b;
			b = temp;
		}
		return (double) uniformDistribution<double>(a,b);
	}
	static string randomString(int len = 9) {
		const char alphanum[] =
	        "0123456789"
	        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	        "abcdefghijklmnopqrstuvwxyz";
	    int stringLen = sizeof(alphanum) - 1;

	    string str;
	    for (int i = 0; i < len; i++) {
	    	int rnd = randomInt(0, stringLen);
	     	str += alphanum[rnd % stringLen];
	    }
	    return str;
	}

	static int coinFlip(){
		return randomInt(0,2);
	}
	static int diceRoll(){
		return randomInt(1,7);
	}
	static int diceRoll(int size){
		return randomInt(1,size+1);
	}
	
};