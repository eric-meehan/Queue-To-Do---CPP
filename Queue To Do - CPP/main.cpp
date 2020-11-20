 /*
  Eric Meehan
  2020-11-19
  
  Queue To Do
 */

#include <iostream>
#include <string>

// Function Prototypes
int SequentialXOR(int);
int * Table(int, int);
int XORRows(int, int);


int main(int argc, const char * argv[]) {
    // Required parameters
    int Start;
    int Length;
    // Users may specify the start position and line length through command line arguments
    if (argc > 1)
    {
        // These arguments will need to be cast as integers
        std::string arg;
        // Get Start from the first argument
        arg = argv[1];
        try
        {
            Start = std::stoi(arg);
        }
        catch(std::invalid_argument)
        {
            std::cout << "Invalid argument" << std::endl;
            return 1;
        }
        // Get the Length from the second argument
        arg = argv[2];
        try
        {
            Length = std::stoi(arg);
        }
        catch (std::invalid_argument)
        {
            std::cout << "Invalid argument" << std::endl;
            return 1;
        }
    }
    // Alternatively, a default Start and Length of 17 and 4 will be used respectively
    else
    {
        Start = 17;
        Length = 4;
    }
    // Generate the table endpoints
    int * table = Table(Start, Length);
    // Create the CumulativeXOR checksum
    int CumulativeXOR = 0;
    // Use the SequentialXOR function on each row, combining the result with the CumulativeXOR
    for (int i = 0; i < Length; i++)
    {
        CumulativeXOR ^= XORRows((Start + (Length * i)), table[i]);
    }
    // Output the result
    std::cout << CumulativeXOR << std::endl;
    return 0;
}

int SequentialXOR(int n)
{
    // Executing an XOR over sequential numbers starting with 1 returns a pattern of n, 1, n+1, 0
    // This function simulates this pattern
    int PatternPosition = std::abs(n % 4);
    // Return the result based on the previous calculation
    switch (PatternPosition)
    {
        case 0:
            return n;
        case 1:
            return 1;
        case 2:
            return n + 1;
        case 3:
            return 0;
        default:
            // This should never occur
            return -1;
    }
}

int * Table(int Start, int Length)
{
    // Defines the end points for each row of the table
    int * table = new int[Length];
    for (int i = 0; i < Length; i++)
    {
        table[i] = Start + (Length * (i + 1) - (i + 1));
    }
    return table;
}

int XORRows(int Start, int End)
{
    // Finds the XOR for a row by performing the operation XOR(XOR(1 - StartOfRow), XOR(1 - EndOfRow))
    /*
     Given that an XOR between any number and itself is 0, and an XOR between any number and 0 is itself, This function finds the cumulative XOR quickly by using the pattern defined in SequentialXOR to XOR the Start and End of each row - the results of which are a negation of the overlapping numbers (1 - Start).
     */
    if (Start > 0)
    {
        // Unless the Start position is zero, decrement Start by one to include that number in the SequentialXOR result
        Start -= 1;
    }
    return SequentialXOR(Start) ^ SequentialXOR(End);
}
