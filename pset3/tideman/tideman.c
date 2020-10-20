// Submission been failing
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Each pair including margin of victory
typedef struct
{
    int winner;
    int loser;
    int margin;
}
pair_with_marg;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair_with_marg winners[MAX * (MAX - 1) / 2];
pair_with_marg temp[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void swap_elems(int *a, int *b);
void pair_tree(int a, int b);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
            }
        }
        // for (int j = 0; j < candidate_count; j++)
        //     {
        //         printf("%i\n", ranks[j] );
        //     }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // If name is in candidates array, update ranks array at rank
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // printf("record pref started\n");
    // Iterate through each candidate contained in ranks; recording a +1 in preference where one candidate outranks another
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Update the preferences array
            preferences[ranks[i]][ranks[j]] ++;;
        }

    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // printf("add pairs started\n");
    // Add each candidates to a pair head-to-head vs every other candidate where there is no tie
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
                    if (preferences[i][j] > preferences[j][i])
                    // Add pairs to pairs struct
                    {
                        pairs[pair_count].winner = i;
                        pairs[pair_count].loser = j;
                        pair_count++;
                    }
                    else if (preferences[i][j] < preferences[j][i])
                    {
                        pairs[pair_count].winner = j;
                        pairs[pair_count].loser = i;
                        pair_count++;
                    }

        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // printf("sort pairs started\n");
    // Calc margin of victory for each pair and save to winners struct
    int diff;
    for (int i = 0; i < pair_count; i++)
    {
        diff = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        winners[i].margin = diff;
        winners[i].winner = pairs[i].winner;
        winners[i].loser = pairs[i].loser;
    }

    // Declare vars to help determine when to stop sorting
    bool swaps_left = true;
    int consec_no_swap = 0;

    while (swaps_left == true)
    {
        for (int i = 0; i < pair_count; i++)
        {
            // Move large numbers to left and small numbers to right (also move the details of who the pair is)
            if (winners[i].margin < winners[i+1].margin )
            {
                swap_elems(&winners[i].winner, &winners[i+1].winner);
                swap_elems(&winners[i].loser, &winners[i+1].loser);
                swap_elems(&winners[i].margin, &winners[i+1].margin);
                // Return consec swap counter back to 0 as there was a swap
                consec_no_swap = 0;
            }

            // If numbers are already in correct order, record a no swap occurred
            else
            {
                consec_no_swap++;
            }

            // If no swaps occur on entire sweep through the pairs, we can assume the pairs are all sorted
            if (consec_no_swap == pair_count)
            {
                swaps_left = false;
            }
        }

    }

    for (int i = 0; i < pair_count; i++)
        {
            pairs[i].winner = winners[i].winner;
            pairs[i].loser = winners[i].loser;
        }

    return;
}

// Swap (can be used to swap winner, loser and margin)

void swap_elems(int *a, int *b)
{
    // printf("swap elems started\n");
    int temp_margin = *a;
    *a = *b;
    *b = temp_margin;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // printf("lock pairs started\n");
    // TODO locked[i][j] being true represents the existence of an edge pointing from candidate i to candidate j
    for (int i = 0; i < pair_count; i++)
    {
       pair_tree(pairs[i].winner, pairs[i].loser);
    }

    return;
}

void pair_tree(int x, int y)
{
    // printf("pair tree started\n");
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[y][j])
        {
            if (j == x)
            {
                locked[x][y] = false;
                return;
            }
            else
            {
                pair_tree(x, j);
            }
        }
        else
        {
            locked[x][y] = true;
            return;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // printf("print winner started\n");
    for (int i = 0; i < pair_count; i++)
    {
        bool has_edge = false;
        for (int j = 0; j < pair_count; j++)
        {
            if (locked[j][i])
            {
                has_edge = true;
                break;
            }

        }
        if (has_edge ==  false)
        {
            string winner = candidates[i];
            printf("%s\n", winner);
        }
    }
    return;
}