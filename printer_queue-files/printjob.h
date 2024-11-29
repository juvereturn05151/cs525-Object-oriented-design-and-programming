#ifndef PRINTJOB_H
#define PRINTJOB_H

/* simple print job structure */
struct PrintJob 
{
	enum Priority {LOW,MEDIUM,HIGH};
	/* an ID - assigned by user. doesn't have to be unique, 
								 but it'll help if it is. */
	int jobID;  
	Priority priority; 
	/* number of pages */
	double size; 
	PrintJob( int _jobID, Priority _priority = LOW, double _size = 100);	
	bool operator< (const PrintJob& rhs) const;
};
#endif
