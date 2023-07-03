#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt user to input some text
    string user_text;

    do
    {
        user_text = get_string("Text: ");
    }
    while (strlen(user_text) < 1);

    // Calculate total words
    int W = count_words(user_text);

    // If no word is found, program exits with code 1
    if (W < 1)
    {
        printf("No text found. Exiting\n");
        return 1;
    }

    // Calculate average letters per 100 words
    float L = (float) count_letters(user_text) * 100 / W;

    // Calculate average sentences per 100 words
    float S = (float) count_sentences(user_text) * 100 / W;

    printf("Words: %i Letters: %.2f Sentences: %f\n", W, L, S);

    // Calculate Coleman-Liau index
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Output grade depending on index value
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

    return 0;
}

// Function to count total letters
int count_letters(string text)
{
    int len = strlen(text);
    int letters = 0;

    for (int i = 0; i < len; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }

    return letters;
}

// Function to count total words
int count_words(string text)
{
    int len = strlen(text);

    // If single character was inputted, either return 0 or 1 depending on its type
    if (len == 1)
    {
        return !!isalpha(text[0]);
    }

    int words = 0;

    // Search into the string for spaces
    for (int i = 1; i < len; i++)
    {
        if (isspace(text[i]) && (isalpha(text[i - 1]) || ispunct(text[i - 1])))
        {
            words++;
        }
    }
    // Check if an extra word needs to be added at the end
    if (isalpha(text[len - 1]) || ispunct(text[len - 1]) || text[len - 1] == '?')
    {
        words++;
    }

    return words;
}

// Function to count total sentences
int count_sentences(string text)
{
    int len = strlen(text);
    int sentences = 0;

    for (int i = 0; i < len; i++)
    {
        // Check if char is '.', '!' or '?'
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sentences++;
        }
    }

    return sentences;
}
