#include <stdio.h>
#include <string.h>
#include <locale.h>
enum menu_define { length_name_students = 50, length_file = 1000 };

struct students {
    char firstName[length_name_students];
    char lastName[length_name_students];
    unsigned short physics_score;
    unsigned short math_score;
    unsigned short story_score;
    unsigned short informatics_score;
};
///
void read_from_file(struct students *students_array, int *count) {
    FILE *file = fopen("marks.csv", "r");
    if (file == NULL) {
        perror("marks.csv");
        return;
    }

    char line[length_file];
    *count = 0;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%hu,%hu,%hu,%hu",
               students_array[*count].lastName,
               students_array[*count].firstName,
               &students_array[*count].physics_score,
               &students_array[*count].math_score,
               &students_array[*count].story_score,
               &students_array[*count].informatics_score);
        (*count)++;
    }

    fclose(file);
}
///
void middle_score_lessons(struct students *students_array, int count) {
    printf("average score in each subject\n");
    double physics_score_average_score = 0;
    double math_score_average_score = 0;
    double story_score_average_score = 0;
    double informatics_average_score = 0;

    for (int i = 0; i < count; i++) {
        physics_score_average_score += students_array[i].physics_score;
        math_score_average_score += students_array[i].math_score;
        story_score_average_score += students_array[i].story_score;
        informatics_average_score += students_array[i].informatics_score;
    }
    printf("average score physics: %.2f\n", physics_score_average_score / count);
    printf("average score math: %.2f\n", math_score_average_score / count);
    printf("average score story: %.2f\n", story_score_average_score / count);
    printf("average score informatics: %.2f\n", informatics_average_score / count);
}
///
int maximum_amount_score(struct students *students_array, int count) {
    printf("the maximum amount of points received by the student\n");
    int total = 0;

    for (int i = 0; i < count; i++) {
        int max_score = students_array[i].informatics_score + students_array[i].math_score + students_array[i].physics_score + students_array[i].story_score;
        if (max_score > total) {
            total = max_score;
        }
    }
    printf("%d\n", total);
    return total;
}
///
void list_maximum_amount(struct students *students_array, int count, int total) {
    printf("list of students (surnames and first names) who scored the maximum amount of points\n");
    for (int i = 0; i < count; i++) {
        if ((students_array[i].informatics_score + students_array[i].math_score + students_array[i].physics_score + students_array[i].story_score) >= total) {
            printf("Last Name: %s, First Name: %s\n", students_array[i].lastName, students_array[i].firstName);
        }
    }
}
///
void students_score_above_is_4(struct students *students_array, int count) {
    printf("number of students whose average score is above 4\n");
    for (int i = 0; i < count; i++) {
        if (((students_array[i].informatics_score + students_array[i].math_score + students_array[i].physics_score + students_array[i].story_score) / 4) >= 4) {
            printf("Last Name: %s, First Name: %s\n", students_array[i].lastName, students_array[i].firstName);
        }
    }
}
///
void grade_of_5_in_computer_science(struct students *students_array, int count) {
    printf("Surnames and names of students who received a grade of 5 in computer science.\n");
    for (int i = 0; i < count; i++) {
        if (students_array[i].informatics_score == 5) {
            printf("Last Name: %s, First Name: %s, Informatics Score: %hu\n", students_array[i].lastName, students_array[i].firstName, students_array[i].informatics_score);
        }
    }
}
///
// void print_to_file(struct students *students_array, int count)
// {
//     FILE *file = fopen("FileText.txt", "w");
//     if (file == NULL) {
//         perror("FileText.txt");
//         return;
//     }
    
    
//     fclose(file);

//  }
int main(void)
{
    setlocale(LC_ALL, "RUS");
    struct students students_array[1000];
    int count = 0;

    read_from_file(students_array, &count);
    
    middle_score_lessons(students_array, count);
    int total = maximum_amount_score(students_array, count);
    list_maximum_amount(students_array, count, total);
    students_score_above_is_4(students_array, count);
    grade_of_5_in_computer_science(students_array, count);
    print_to_file(students_array, count);

    return 0;
}