#include "print_queue.h"

/* constructor 
 * pointer to a simulator that's running it
 */ 
PrintQueue::PrintQueue(Simulator* _psim) : 
	psim(_psim),num_available_printers(0),printer_status(), jobs_in_queue()    
{}

/* to use a printer we need to register it with the print queue first */
void PrintQueue::RegisterPrinter(int ID, double speed) 
{
	// add the printer to the printer_status map.
    // key: Printer ID.
    // value: Pair of availability (true by default) and speed.
    printer_status[ID] = std::make_pair(true, speed);
    
    // increment the count of available printers.
    ++num_available_printers;
}

void PrintQueue::JobFinished( double current_time, int printerID, PrintJob job)
{
	// find the printer by ID in the map
    ID2pair::iterator it = printer_status.find(printerID);

    // throw an exception if the printer ID is invalid
	if ( it == printer_status.end() ) throw "invalid printerID";

    std::cout << "Printer " << printerID << " finished job " 
              << job.jobID << " at time " << current_time << std::endl;

    if (!jobs_in_queue.empty()) 
	{
        // get the next job from the queue
        std::pair<PrintJob, double> next_job = jobs_in_queue.top();
		// remove the job from the queue
        jobs_in_queue.pop(); 

        // assign the new job to this printer
        PrintJob new_job = next_job.first;

        // mark as unavailable
        it->second.first = false;

        // calculate job completion time
        double completion_time = current_time + (new_job.size / it->second.second);

        // schedule the next job completion event in the simulator
        psim->AddEvent(new EventJobFinished( completion_time, new_job, this, &PrintQueue::JobFinished, printerID));

        std::cout << "Printer " << printerID << " assigned new job " << new_job.jobID << " at time " << current_time << std::endl;
    } 
    else 
	{ 
        ++num_available_printers;
        // no jobs in the queue; mark printer as available
        it->second.first = true; 
    }
}

void PrintQueue::NewJobArrived( double current_time, PrintJob job )
{
    std::cout << "New job " << job.jobID  << " at time " << current_time << std::endl;

    if (num_available_printers > 0) 
	{
        // find an available printer
        ID2pair::iterator it = printer_status.begin();
        while (it != printer_status.end() && it->second.first == false) 
		{
            ++it;
        }

        // if no available printer is found despite num_available_printers > 0
        if (it == printer_status.end()) 
		{
            throw "Corrupted data: num_available_printers is inconsistent with printer status.";
        }

        // assign the job to the available printer by marking them as unavailable
        it->second.first = false; 
        --num_available_printers;

        // calculate job completion time
        double completion_time = current_time + (job.size / it->second.second);

        // schedule the next job completion event in the simulator
        psim->AddEvent(new EventJobFinished( completion_time, job, this, &PrintQueue::JobFinished, it->first));

		std::cout << "Job assigned to printer " << it->first << " at time " << current_time << std::endl;
    } 
    else {
        // no available printers: add the job to the print queue
        std::cout << "No available printers - put in print queue\n";
		jobs_in_queue.push(std::make_pair(job, current_time));
    }
}