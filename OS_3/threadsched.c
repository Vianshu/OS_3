#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sched.h>
#include<time.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/resource.h>

void countA(){
	for (unsigned long i=0; i<4294967296; i++){
		continue;
	}
}
void countB(){
	for (unsigned long i=0; i<4294967296; i++){
		continue;
	}
}
void countC(){
	for (unsigned long i=0; i<4294967296; i++){
		continue;
	}
}

void *ThrA(void *args){
	long long int p=(long long int)args;
	struct timespec fr;
	struct sched_param* r=(struct sched_param*)malloc(sizeof(struct sched_param));
	if (r != NULL){
		r->sched_priority=p;
	}
	pthread_setschedparam(pthread_self(), SCHED_RR, r);
	struct timespec sr;
	clock_gettime(CLOCK_MONOTONIC, &sr);
	countA();
	clock_gettime(CLOCK_MONOTONIC, &fr);
	double rm=0;
	rm+=(fr.tv_sec-sr.tv_sec)+(fr.tv_sec-sr.tv_nsec)/1000000000.0;
	FILE *f;
	f=fopen("RR.txt","a");
	fprintf(f, "%lld %lf\n",p,rm);
	fclose(f);
	double *x=(double *)malloc(sizeof(double));
	*x=rm;
}
void *ThrB(void *args){
	long long int p =(long long int)args;
	struct timespec ffi;
	struct sched_param* fi=(struct sched_param*)malloc(sizeof(struct sched_param));
	if (fi != NULL){
		fi->sched_priority=p;
	}
	pthread_setschedparam(pthread_self(), SCHED_FIFO, fi);
	struct timespec sfi;
	clock_gettime(CLOCK_MONOTONIC, &sfi);
	countB();
	clock_gettime(CLOCK_MONOTONIC, &ffi);
	double rm=0;
	rm+=(ffi.tv_sec-sfi.tv_sec)+(ffi.tv_sec-sfi.tv_nsec)/1000000000.0;
	FILE *f;
	f=fopen("FIFO.txt","a");
	fprintf(f , "%lld %lf\n",p,rm);
	fclose(f);
	double *x=(double *)malloc(sizeof(double));
	*x=rm;
}
void *ThrC(void *args){
	struct timespec foth;
	struct sched_param* oth=(struct sched_param*)malloc(sizeof(struct sched_param));
	if (oth != NULL){
		oth->sched_priority=0;
	}
	pthread_setschedparam(pthread_self(), SCHED_OTHER, oth);
	struct timespec soth;
	clock_gettime(CLOCK_MONOTONIC, &soth);
	countC();
	clock_gettime(CLOCK_MONOTONIC, &foth);
	double rm=0;
	rm+=(foth.tv_sec-soth.tv_sec)+(foth.tv_sec-soth.tv_nsec)/1000000000.0;
	FILE *f;
	f=fopen("OTHER.txt","a");
	fprintf(f, "%lld %lf\n",0,rm);
	fclose(f);
	double *x=(double *)malloc(sizeof(double));
	*x=rm;
}

int main(int argc, char *argv[]){
	pthread_t thr1;
	pthread_t thr2;
	pthread_t thr3;
	long long int p1=0;
	long long int p2=30;
	long long int p3=0;
	
	pthread_create(&thr1, NULL, ThrA, (void *)p1);
	pthread_create(&thr2, NULL, ThrB, (void *)p2);
	pthread_create(&thr3, NULL, ThrC, (void *)p3);

	pthread_join(thr1, NULL);
	pthread_join(thr2, NULL);
	pthread_join(thr3, NULL);

	return 0;
}

