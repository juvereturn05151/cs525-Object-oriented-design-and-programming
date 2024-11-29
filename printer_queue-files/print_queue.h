#ifndef PRINT_QUEUE_H
#define PRINT_QUEUE_H
#include <queue>
#include <map>
#include <iostream>
#include "command.h"
#include "printjob.h"
#include "simulator.h"

/* Comparison for PrintQueue::jobs_in_queue
 * - The queue stores std::pair<PrintJob, double>, where:
 *   - PrintJob: The job
 *   - double: Arrival time
 * - Jobs are ordered by priority (higher first), and if priorities are equal, by earlier arrival time.
 * - This custom comparator ensures correct ordering for the priority queue.
 */
namespace std {
	template <>
		class less<std::pair<PrintJob,double> > {
			public:
				bool operator() (
						const std::pair<PrintJob,double>& p1,
						const std::pair<PrintJob,double>& p2) const
				{
            		// Higher priority comes first; if equal, earlier time comes first
					return 	(p1.first<p2.first) ||  //priority is more important than time
						(!(p2.first<p1.first) && p1.second>p2.second);//if same priority, 
																													//then compare time 
				}
		};
}

/*
 * PrintQueue logic:
 * - Acts as a buffer between clients and printers.
 * - Jobs are prioritized by priority and arrival time.
 * - Logic:
 *   1. If a printer is available, assign the job immediately.
 *   2. If no printer is available, add the job to the queue.
 *   3. When a printer finishes, assign the next job from the queue.
 */
class PrintQueue 
{
    Simulator* psim; // Manages events
    int num_available_printers; // Count of available printers
public:
    PrintQueue(Simulator* _psim);
    void RegisterPrinter(int ID, double speed);
    void JobFinished(double current_time, int printerID, PrintJob job);
    void NewJobArrived(double current_time, PrintJob job);
private:
    typedef std::map<int, std::pair<bool, double>> ID2pair;
	// Stores printer availability and speed
    ID2pair printer_status; 
	// Job queue
    std::priority_queue<std::pair<PrintJob, double>> jobs_in_queue; 
};

/* "printer just finished a job" event
 * has information about completed job and printer
 */
class EventJobFinished : public TimedCommand 
{
private:
    void (PrintQueue::*p_method)(double, int, PrintJob); 
    int printerID;           // ID of the printer that finished the job
    PrintJob job;            // The job that was completed
    PrintQueue* p_print_queue; // Pointer to the PrintQueue
	
public:
	 // Updated constructor
    EventJobFinished(
        double when,
        const PrintJob& _job,
        PrintQueue* _p_print_queue,
        void (PrintQueue::*_p_method)(double, int, PrintJob),
        int _printerID
    ) : job(_job), p_print_queue(_p_print_queue), p_method(_p_method), printerID(_printerID)
    {
		SetWhen(when);
	}

    // Execute the event
    virtual void Execute() override 
	{
        // Call the provided method in PrintQueue with the given job, printer ID, and time
        (p_print_queue->*p_method)(When(), printerID, job);
    }

};

/* new job just arrived event, has information about the job*/
class EventNewJobArrived : public TimedCommand {
	PrintJob job;
	PrintQueue* p_print_queue;
	void (PrintQueue::*p_method)(double,PrintJob);
	public:
	EventNewJobArrived(
		double when, 
		const PrintJob& _job,
		PrintQueue* _p_print_queue, 
		void (PrintQueue::*_p_method)(double, PrintJob)
	) : job(_job), p_print_queue(_p_print_queue), p_method(_p_method)
	{
		SetWhen(when);
	}

	virtual void Execute() override
	{
		// Call the provided method in PrintQueue with the given job and time
    	(p_print_queue->*p_method)(When(), job);
	}
};

#endif