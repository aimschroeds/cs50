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
victory;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
victory winners[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void merge_sort(int start, int end);
void merged(int start, int end, int mid);

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
    // TODO if name is in candidates array, update ranks array at rank
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            printf("%s\n", candidates[i]);
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Iterate through each candidate contained in ranks; recording a +1 in preference where one candidate outranks another
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Update the preferences array
            preferences[ranks[i]][ranks[j]] ++;;
            printf("ri:%i rj:%i p:%i\n", ranks[i], ranks[j], preferences[ranks[i]][ranks[j]] );
        }

    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
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
    printf("Pair count: %i\n", pair_count);
    for (int i = 0; i < pair_count; i++)
    {
        printf("Winner: %i\n Loser: %i\n",pairs[i].winner,pairs[i].loser);
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO Calc margin of victory for each pair
    int diff;
    for (int i = 0; i < pair_count; i++)
    {
        diff = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        printf("diff: %i\n", diff);
        winners[i].margin = diff;
        winners[i].winner = pairs[i].winner;
        winners[i].loser = pairs[i].loser;
    }
    printf("about to call merge_sort first time with pair count -1 = %i\n", pair_count - 1);
    merge_sort(0, pair_count - 1);
    for (int i = 0; i < pair_count; i++)
    {
        printf("Margin %i, Winner %i, Loser %i\n",winners[i].margin, winners[i].winner, winners[i].loser);
    }
    return;
}
// TODO Compare margin for each pair
void merge_sort(int start, int end)
{
    if (start < end)
    {
        int mid;
        mid = (end + start) / 2;
        printf("mrge_sort recursion will start: s%i m%i e%i\n", start, mid, end);
        merge_sort(start, mid);
        merge_sort(mid + 1, end);

        // TODO call merged
        printf("merged about to start: s%i m%i e%i\n", start, mid, end);
        merged(start, mid, end);
    }

}

void merged(int start, int end, int mid)
{
    // Calculate length of respective arrays
    int len1 = mid - start + 1;
    int len2 = end - mid;

    // Structs for temp arrays
    typedef struct
    {
        int winner;
        int loser;
        int margin;
    }
    lefty;

    typedef struct
    {
        int winner;
        int loser;
        int margin;
    }
    righty;
    // Arrays to work with in merging
    lefty left[len1];
    righty right[len2];

    // Populate arrays
    for (int i = 0; i < len1; i ++)
    {
        left[i].margin = winners[start + i].margin;
        left[i].winner = winners[start + i].winner;
        left[i].loser = winners[start + i].loser;
    }
    for (int j = 0; j < len2; j ++)
    {
        right[j].margin = winners[mid + 1 + j].margin;
        right[j].winner = winners[mid + 1 + j].winner;
        right[j].loser = winners[mid + 1 + j].loser;
    }

    int k = start;
    int i = 0;
    int j = 0;
    while (i < len1 && j < len2)
    {
        if (left[i].margin <= right[j].margin)
        {
            winners[k].margin = left[i].margin;
            winners[k].winner = left[i].winner;
            winners[k].loser = left[i].loser;
            i++;
        }
        else
        {
            winners[k].margin = right[j].margin;
            winners[k].winner = right[j].winner;
            winners[k].loser = right[j].loser;
            j++;
        }
    k++;
    }
    while (i < len1)
    {
            winners[k].margin = left[i].margin;
            winners[k].winner = left[i].winner;
            winners[k].loser = left[i].loser;
            i++;
            k++;
    }

    while (j < len2)
    {
            winners[k].margin = right[j].margin;
            winners[k].winner = right[j].winner;
            winners[k].loser = right[j].loser;
            j++;
            k++;
    }

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}