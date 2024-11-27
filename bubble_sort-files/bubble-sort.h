template < typename ForwardIt >
void bubblesort( ForwardIt begin, ForwardIt end )
{
    // nothing to sort.
    if (begin == end) return;

    bool swapped;
    do {
        swapped = false;
        ForwardIt current = begin;
        ForwardIt next = std::next(begin); // corrected initialization of `next`

        // tracks the last modified position in this pass.
        ForwardIt newEnd = begin;

        while (next != end) {
            if (*next < *current) {
                // swap logic
                auto temp = *current;
                *current = *next;
                *next = temp;

                swapped = true;
                // update the last modified position.
                newEnd = next;
            }
            ++current;
            ++next;
        }
        // update the end of the unsorted section.
        end = newEnd;
    } while (swapped);
}
