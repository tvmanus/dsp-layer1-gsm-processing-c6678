/*
 * Timestamp.h
 *
 *  Created on: Aug 6, 2014
 *      Author: nachiappanr
 */

#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_


#define MAX_ITERATIONS 50

typedef struct Timestamp_obj {
	Char 	 name[32];
	uint32_t start_timestamp;
	uint32_t stop_timestamp;
	uint32_t timetaken;
	uint32_t min_time;
	uint32_t max_time;
	uint32_t avg_time;
	uint32_t startiteration;
	uint32_t stopiteration;
	char     reserved[40];
}Timestamp_obj;


void Init_timestamp_obj(Timestamp_obj *,char *);
void inline calc_min_time(Timestamp_obj *,uint32_t*);
void inline calc_max_time(Timestamp_obj *,uint32_t*);
void inline calc_avg_time(Timestamp_obj *,uint32_t*);
void inline Timestamp_flush_reset(Timestamp_obj *);

extern void START(Timestamp_obj *);
extern void STOP (Timestamp_obj *);



#endif /* TIMESTAMP_H_ */
