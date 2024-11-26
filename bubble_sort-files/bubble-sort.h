template < typename ForwardIt >
void bubblesort( ForwardIt begin, ForwardIt end )
{
    // nothing to sort.
    if (begin == end) return; 

    bool swapped;

    do 
    {
        swapped = false;
        ForwardIt current = begin;
        ForwardIt next = std::next(next);

        // tracks the last modified position in this pass.
        ForwardIt newEnd = begin; 

        while (next != end) 
        {
            if (*next < *current) 
            {
                std::swap(*current, *next);
                swapped = true;
                // update the last modified position.
                newEnd = next; 
            }
            ++current;
            ++next;
        }
        // update the end of the unsorted section.
        end = newEnd; 
    } 
    while (swapped);
}
