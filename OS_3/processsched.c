#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/resource.h>
#include<time.h>
#include<sched.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc, char *argv[]){
	struct timespec sf,ff;
	struct timespec sr, fr;
	struct timespec so, fo;

	pid_t p1;
	pid_t p2;
	pid_t p3;

	int prio1=10;
	int prio2=20;

	struct sched_param f=(struct sched_param*)malloc(sizeof(struct sched_param));
	struct sched_param r=(struct sched_param*)malloc(sizeof(struct sched_param));
	struct sched_param o=(struct sched_param*)malloc(sizeof(struct sched_param));
	
	if (f != NULL){
		f->sched_priority=prio1;
	}
	
	if (r != NULL){
		r->sched_priority=prio2;
	}
	
	if (o != NULL){
		o->sched_priority=0;
	}
	clock_gettime(CLOCK_MONOTONIC,&sf);
	clock_gettime(CLOCK_MONOTONIC,&sr);
	clock_gettime(CLOCK_MONOTONIC,&so);

	if ((p1 == fork())==0){
		sched_setscheduler(p1, SCHED_FIFO, f);
		execlp("bash","bash","kern1.sh",NULL);
	}
	if ((p2 == fork())==0){
		sched_setscheduler(p2, SCHED_RR, r);
		execlp("bash","bash","kern2.sh",NULL);
	}
	
	if ((p3 == fork())==0){
		sched_setscheduler(p3, SCHED_OTHER, o);
		execlp("bash","bash","kern3.sh",NULL);
	}
	
	FILE *f1;
	FILE *f2;
	FILE *f3;
	f1=fopen("FIFO.txt","a");
	f2=fopen("RR.txt","a");
	f3=fopen("OTHER.txt","a");
	

	for (int g=0; g<3; g++){
		pid_t w= wait(NULL);
		if (w == p1){
			clock_gettime(CLOCK_MONOTONIC,&ff);
			double rmf=0;
			rmf+=(ff.tv_sec-sf.tv_sec)+((ff.tv_nsec-sf.tv_nsec)/1000000000.0);
			fprintf(f1,"%d %lf",prio1,rmf);
			fclose(f1);
		}
		else if (w == p2){
			clock_gettime(CLOCK_MONOTONIC,&fr);
			double rmr=0;
			rmr+=(fr.tv_sec-sr.tv_sec)+((fr.tv_nsec-sr.tv_nsec)/1000000000.0);
			fprintf(f2,"%d %lf",prio2,runtimer);
			fclose(f2);
		}
		else if (c == p3){
			clock_gettime(CLOCK_MONOTONIC,&fo);
			double rmo=0;
			rmo+=(fo.tv_sec-sot.tv_sec)+((fot.tv_nsec-sot.tv_nsec)/1000000000.0);
			fprintf(f3,"%d %lf",0,rmo);
			fclose(f3);
		}
		
	}	
	return 0;
}
