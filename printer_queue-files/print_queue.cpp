#include "print_queue.h"

////////////////////////////////////////////////////////////
/* PrintQueue implementation */
////////////////////////////////////////////////////////////

/* constructor 
 * pointer to a simulator that's running it
 */ 
PrintQueue::PrintQueue(Simulator* _psim) : 
	psim(_psim),num_available_printers(0) 
{}

/* to use a printer we need to register it with the print queue first */
void PrintQueue::RegisterPrinter(int ID, double speed) 
{
	// Add the printer to the printer_status map.
    // Key: Printer ID.
    // Value: Pair of availability (true by default) and speed.
    printer_status[ID] = std::make_pair(true, speed);
    
    // Increment the count of available printers.
    ++num_available_printers;
}

/* implements 2) from PrintQueue */
void PrintQueue::JobFinished( double current_time, int printerID, PrintJob job)
{
	// Find the printer by ID in the map
    ID2pair::iterator it = printer_status.find(printerID);

    // Throw an exception if the printer ID is invalid
    if (it == printer_status.end()) 
        throw "Invalid printerID";

    // Log the job completion
    std::cout << "Printer " << printerID << " finished job " 
              << job.jobID << " at time " << current_time << std::endl;

    // Check if there are jobs waiting in the queue
    if (!jobs_in_queue.empty()) 
	{
        // Get the next job from the queue
        std::pair<PrintJob, double> next_job = jobs_in_queue.top();
		// Remove the job from the queue
        jobs_in_queue.pop(); 

        // Assign the new job to this printer
        PrintJob new_job = next_job.first;
        double arrival_time = next_job.second;

        // Update printer status (mark as busy)
        it->second.first = false;

        // Calculate job completion time
        double completion_time = current_time + (new_job.size / it->second.second);

        // Schedule the next job completion event in the simulator
        psim->AddEvent(new EventJobFinished(
            completion_time,              // When the job will complete
            new_job,                      // The new job to complete
            this,                         // Pointer to the current PrintQueue
            &PrintQueue::JobFinished,     // Method pointer to JobFinished
            printerID                     // ID of the printer
        ));

        // Log the assignment of the new job
        std::cout << "Printer " << printerID << " assigned new job " 
                  << new_job.jobID << " at time " << current_time << std::endl;
    } 
    else 
	{ 
        // No jobs in the queue; mark printer as idle
        ++num_available_printers;
        it->second.first = true; // Mark printer as available
    }
}

/* implements 3) from PrintQueue */
void PrintQueue::NewJobArrived( double current_time, PrintJob job )
{
	// Log the arrival of a new job
    std::cout << "New job " << job.jobID 
              << " at time " << current_time << std::endl;

    // Check if there are any available printers
    if (num_available_printers > 0) {
        // Find an available printer
        ID2pair::iterator it = printer_status.begin();
        while (it != printer_status.end() && it->second.first == false) 
		{
            ++it;
        }

        // Sanity check: If no available printer is found despite num_available_printers > 0
        if (it == printer_status.end()) 
		{
            throw "Corrupted data: num_available_printers is inconsistent with printer status.";
        }

        // Assign the job to the available printer
        it->second.first = false; // Mark printer as busy
        --num_available_printers; // Decrement count of available printers

        // Calculate job completion time
        double completion_time = current_time + (job.size / it->second.second);

        // Schedule the job completion event in the simulator using the new EventJobFinished class
        psim->AddEvent(new EventJobFinished(
            completion_time,   // Event time
            job,               // PrintJob to complete
            this,              // Pointer to the current PrintQueue
            &PrintQueue::JobFinished, // Method pointer
            it->first          // Printer ID
        ));

        // Log the assignment
        std::cout << "Job " << job.jobID 
                  << " assigned to printer " << it->first 
                  << " at time " << current_time << std::endl;
    } 
    else {
        // No available printers: add the job to the print queue
        jobs_in_queue.push(std::make_pair(job, current_time));
        std::cout << "No available printers - job " << job.jobID 
                  << " added to print queue." << std::endl;
    }
}

////////////////////////////////////////////////////////////
/* EventJobFinished implementation */
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/* EventNewJobArrived implementation */
////////////////////////////////////////////////////////////

