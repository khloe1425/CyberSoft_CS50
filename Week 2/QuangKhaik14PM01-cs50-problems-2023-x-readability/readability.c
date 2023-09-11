#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Nguyên mẫu các hàm
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Nhận văn bản từ người dùng
    string text = get_string("Text: ");

    // Đếm số lượng chữ cái, từ và câu
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Tính chỉ số Coleman-Liau
    float L = (float)letters / words * 100;
    float S = (float)sentences / words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // In kết quả
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
        printf("Grade %.0f\n", round(index));
    }

    return 0;
}

// Hàm đếm số lượng chữ cái trong văn bản
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

// Hàm đếm số lượng từ trong văn bản
int count_words(string text)
{
    int count = 1; // Khởi tạo số từ là 1 vì có ít nhất một từ
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            count++;
        }
    }
    return count;
}

// Hàm đếm số lượng câu trong văn bản
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}
