 /*
  Eric Meehan
  2020-11-19
  
  Queue To Do
 */

#include <iostream>

// Function Prototypes
int SequentialXOR(int);
int * Table(int, int);
int XORRows(int, int);


int main(int argc, const char * argv[]) {
    int * table = Table(17, 4);
    int CumulativeXOR = 0;
    for (int i = 0; i < 4; i++)
    {
        CumulativeXOR ^= XORRows((17 + (4 * i)), table[i]);
    }
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
