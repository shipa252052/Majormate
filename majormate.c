#include <stdio.h>
#include <string.h>

#define MAJORS 7
#define SKILLS 8
#define SUBJECTS 6
#define INTERESTS 10
#define CAREERS 9

typedef struct {
    float ssc, hsc, cgpa;
    int background, semester;
    float subject[SUBJECTS];
    int skill[SKILLS];
    int interest[INTERESTS];
    int career[CAREERS];
    int strongSkill, weakSkill;
    int strongSubject, weakSubject;
} Student;

typedef struct {
    char name[40];
    int skill[SKILLS];
    int subject[SUBJECTS];
    int interest[INTERESTS];
    int career[CAREERS];
    int background[3];
} Major;

const char *skills[SKILLS] = {
    "Mathematics", "English", "Programming",
    "Communication", "Critical Thinking",
    "Research", "Problem Solving", "Creativity"
};

const char *subjects[SUBJECTS] = {
    "Mathematics", "English", "Computer Science",
    "Biology", "Economics", "Social Science"
};

const char *interests[INTERESTS] = {
    "Technology", "Environment", "Health", "Biology",
    "Business", "Economics", "Finance", "Politics",
    "Social Science", "Research"
};

const char *careers[CAREERS] = {
    "Software Developer", "Data Analyst", "Economist",
    "Financial Analyst", "Environmental Consultant",
    "Public Health Professional", "Researcher",
    "Entrepreneur", "Policy Analyst"
};

const char *backgrounds[3] = {
    "Science", "Commerce", "Arts/Humanities"
};

const char *minor[MAJORS] = {
    "Computer Science", "Economics", "Computer Science",
    "Biological Science", "Biological Science",
    "Economics", "Finance"
};

/* ---------- Function Prototypes ---------- */

int getInt(char prompt[], int min, int max);
float getFloat(char prompt[], float min, float max);
void inputStudent(Student *s);
void inputChoices(Student *s);
void setupMajors(Major m[]);
float calculateScore(Student *s, Major *m);
void sortResults(float score[], int order[]);
void showResults(Student *s, Major m[], float score[], int order[]);
void saveFile(Student *s, Major m[], float score[], int order[]);

/* ---------- Input Functions ---------- */

int getInt(char prompt[], int min, int max)
{
    int x;

    while (1)
    {
        printf("%s", prompt);

        if (scanf("%d", &x) == 1 &&
            x >= min && x <= max)
        {
            while (getchar() != '\n');
            return x;
        }

        while (getchar() != '\n');
        printf("Invalid input. Try again.\n");
    }
}

float getFloat(char prompt[], float min, float max)
{
    float x;

    while (1)
    {
        printf("%s", prompt);

        if (scanf("%f", &x) == 1 &&
            x >= min && x <= max)
        {
            while (getchar() != '\n');
            return x;
        }

        while (getchar() != '\n');
        printf("Invalid input. Try again.\n");
    }
}

/* ---------- Student Input ---------- */

void inputStudent(Student *s)
{
    int i;

    printf("\n===== EDUCATIONAL BACKGROUND =====\n");

    s->ssc = getFloat(
        "SSC/O-Level GPA (0-5): ", 0, 5);

    s->hsc = getFloat(
        "HSC/A-Level GPA (0-5): ", 0, 5);

    printf("\n1. Science\n");
    printf("2. Commerce\n");
    printf("3. Arts/Humanities\n");

    s->background =
        getInt("Academic background: ", 1, 3) - 1;

    s->semester =
        getInt("Semester completed (1-8): ", 1, 8);

    s->cgpa =
        getFloat("Current CGPA (0-4): ", 0, 4);

    printf("\n===== SUBJECT PERFORMANCE =====\n");

    for (i = 0; i < SUBJECTS; i++)
    {
        printf("%s mark: ", subjects[i]);
        s->subject[i] =
            getFloat("", 0, 100);
    }

    printf("\n===== SKILLS (1-10) =====\n");

    for (i = 0; i < SKILLS; i++)
    {
        printf("%s: ", skills[i]);
        s->skill[i] =
            getInt("", 1, 10);
    }

    printf("\n===== STRENGTHS / WEAKNESSES =====\n");

    for (i = 0; i < SKILLS; i++)
        printf("%d. %s\n", i + 1, skills[i]);

    s->strongSkill =
        getInt("Strongest skill: ", 1, SKILLS) - 1;

    s->weakSkill =
        getInt("Skill to improve: ", 1, SKILLS) - 1;

    for (i = 0; i < SUBJECTS; i++)
        printf("%d. %s\n", i + 1, subjects[i]);

    s->strongSubject =
        getInt("Strongest subject: ", 1, SUBJECTS) - 1;

    s->weakSubject =
        getInt("Weak subject: ", 1, SUBJECTS) - 1;

    inputChoices(s);
}

/* ---------- Interests and Careers ---------- */

void inputChoices(Student *s)
{
    int i;
    char answer;

    printf("\n===== INTERESTS =====\n");

    for (i = 0; i < INTERESTS; i++)
    {
        printf("%s? (Y/N): ", interests[i]);
        scanf(" %c", &answer);

        s->interest[i] =
            (answer == 'Y' || answer == 'y');
    }

    printf("\n===== CAREER GOALS =====\n");

    for (i = 0; i < CAREERS; i++)
    {
        printf("%s? (Y/N): ", careers[i]);
        scanf(" %c", &answer);

        s->career[i] =
            (answer == 'Y' || answer == 'y');
    }

    while (getchar() != '\n');
}

/* ---------- Major Information ---------- */

void setupMajors(Major m[])
{
    char names[MAJORS][40] = {
        "Economics",
        "Philosophy, Politics and Economics",
        "Environmental Science",
        "Biological Science",
        "Public Health",
        "Computer Science",
        "Finance"
    };

    int i, j;

    for (i = 0; i < MAJORS; i++)
    {
        strcpy(m[i].name, names[i]);

        for (j = 0; j < SKILLS; j++)
            m[i].skill[j] = 5;

        for (j = 0; j < SUBJECTS; j++)
            m[i].subject[j] = 5;

        for (j = 0; j < INTERESTS; j++)
            m[i].interest[j] = 5;

        for (j = 0; j < CAREERS; j++)
            m[i].career[j] = 5;

        for (j = 0; j < 3; j++)
            m[i].background[j] = 5;
    }

    /* Economics */
    m[0].skill[0] = 10;
    m[0].skill[4] = 9;
    m[0].skill[6] = 9;
    m[0].subject[0] = 10;
    m[0].subject[4] = 10;
    m[0].interest[5] = 10;
    m[0].career[2] = 10;

    /* PPE */
    m[1].skill[1] = 10;
    m[1].skill[3] = 10;
    m[1].skill[4] = 10;
    m[1].skill[5] = 9;
    m[1].subject[1] = 10;
    m[1].subject[5] = 10;
    m[1].interest[7] = 10;
    m[1].interest[8] = 10;
    m[1].career[8] = 10;

    /* Environmental Science */
    m[2].skill[5] = 10;
    m[2].skill[6] = 8;
    m[2].subject[0] = 7;
    m[2].subject[3] = 10;
    m[2].interest[1] = 10;
    m[2].interest[9] = 10;
    m[2].career[4] = 10;
    m[2].background[0] = 10;

    /* Biological Science */
    m[3].skill[5] = 10;
    m[3].subject[3] = 10;
    m[3].interest[3] = 10;
    m[3].interest[9] = 10;
    m[3].career[6] = 10;
    m[3].background[0] = 10;

    /* Public Health */
    m[4].skill[3] = 9;
    m[4].skill[5] = 10;
    m[4].subject[3] = 9;
    m[4].subject[5] = 9;
    m[4].interest[2] = 10;
    m[4].interest[8] = 10;
    m[4].career[5] = 10;

    /* Computer Science */
    m[5].skill[0] = 10;
    m[5].skill[2] = 10;
    m[5].skill[4] = 9;
    m[5].skill[6] = 10;
    m[5].subject[0] = 10;
    m[5].subject[2] = 10;
    m[5].interest[0] = 10;
    m[5].career[0] = 10;
    m[5].career[1] = 10;

    /* Finance */
    m[6].skill[0] = 10;
    m[6].skill[4] = 8;
    m[6].skill[6] = 9;
    m[6].subject[0] = 10;
    m[6].subject[4] = 9;
    m[6].interest[4] = 10;
    m[6].interest[6] = 10;
    m[6].career[3] = 10;
}

/* ---------- Scoring ---------- */

float calculateScore(Student *s, Major *m)
{
    float skillScore = 0;
    float subjectScore = 0;
    float interestScore = 0;
    float careerScore = 0;
    float total;
    int i;

    for (i = 0; i < SKILLS; i++)
        skillScore += s->skill[i] * m->skill[i];

    for (i = 0; i < SUBJECTS; i++)
        subjectScore +=
            (s->subject[i] / 10) * m->subject[i];

    for (i = 0; i < INTERESTS; i++)
        interestScore +=
            s->interest[i] * m->interest[i];

    for (i = 0; i < CAREERS; i++)
        careerScore +=
            s->career[i] * m->career[i];

    /* Convert each category to approximately 0-100 */

    skillScore /= 8;
    subjectScore /= 6;
    interestScore /= 10;
    careerScore /= 9;

    /* Weighted total */

    total =
        skillScore * 0.25 +
        subjectScore * 0.20 +
        interestScore * 0.20 +
        careerScore * 0.15 +

        (s->cgpa / 4.0 * 100) * 0.10 +

        m->background[s->background] * 10 * 0.05 +

        ((s->ssc + s->hsc) / 10 * 100) * 0.05;

    return total;
}

/* ---------- Sorting ---------- */

void sortResults(float score[], int order[])
{
    int i, j, temp;

    for (i = 0; i < MAJORS; i++)
        order[i] = i;

    for (i = 0; i < MAJORS - 1; i++)
    {
        for (j = i + 1; j < MAJORS; j++)
        {
            if (score[order[j]] >
                score[order[i]])
            {
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
}

/* ---------- Results ---------- */

void showResults(
    Student *s,
    Major m[],
    float score[],
    int order[])
{
    int i;

    printf("\n\n========================================\n");
    printf("       ACADEMIC RECOMMENDATION\n");
    printf("========================================\n");

    printf(
        "\nRecommended Major : %s\n",
        m[order[0]].name
    );

    printf(
        "Recommended Minor : %s\n",
        minor[order[0]]
    );

    printf(
        "Compatibility Score: %.1f%%\n",
        score[order[0]]
    );

    printf(
        "\nSecond-best Major : %s (%.1f%%)\n",
        m[order[1]].name,
        score[order[1]]
    );

    printf(
        "Third-best Major  : %s (%.1f%%)\n",
        m[order[2]].name,
        score[order[2]]
    );

    printf("\nStrongest Areas:\n");

    printf(
        "- Skill: %s (%d/10)\n",
        skills[s->strongSkill],
        s->skill[s->strongSkill]
    );

    printf(
        "- Subject: %s (%.1f/100)\n",
        subjects[s->strongSubject],
        s->subject[s->strongSubject]
    );

    printf("\nAreas to Improve:\n");

    printf(
        "- Skill: %s\n",
        skills[s->weakSkill]
    );

    printf(
        "- Subject: %s\n",
        subjects[s->weakSubject]
    );

    printf("\nSelected Career Goals:\n");

    for (i = 0; i < CAREERS; i++)
    {
        if (s->career[i])
            printf("- %s\n", careers[i]);
    }

    printf("\nAll Major Scores:\n");

    for (i = 0; i < MAJORS; i++)
    {
        printf(
            "%d. %-35s %.1f%%\n",
            i + 1,
            m[order[i]].name,
            score[order[i]]
        );
    }

    printf("\nWhy this major?\n");

    switch (order[0])
    {
        case 0:
            printf("- Strong mathematics/economics profile.\n");
            printf("- Suitable for analytical careers.\n");
            break;

        case 1:
            printf("- Strong communication and critical thinking.\n");
            printf("- Suitable for politics and policy.\n");
            break;

        case 2:
            printf("- Strong environmental/research interest.\n");
            printf("- Suitable for environmental careers.\n");
            break;

        case 3:
            printf("- Strong biology/research profile.\n");
            printf("- Suitable for scientific careers.\n");
            break;

        case 4:
            printf("- Strong health/research interest.\n");
            printf("- Suitable for public health careers.\n");
            break;

        case 5:
            printf("- Strong programming/problem-solving profile.\n");
            printf("- Suitable for technology careers.\n");
            break;

        case 6:
            printf("- Strong mathematics/business interest.\n");
            printf("- Suitable for financial careers.\n");
            break;
    }

    printf("\n========================================\n");
}

/* ---------- Save Report ---------- */

void saveFile(
    Student *s,
    Major m[],
    float score[],
    int order[])
{
    FILE *fp;
    int i;

    fp = fopen("recommendation.txt", "w");

    if (fp == NULL)
    {
        printf("Could not save file.\n");
        return;
    }

    fprintf(fp, "ACADEMIC MAJOR RECOMMENDATION\n\n");

    fprintf(
        fp,
        "Major: %s\n",
        m[order[0]].name
    );

    fprintf(
        fp,
        "Minor: %s\n",
        minor[order[0]]
    );

    fprintf(
        fp,
        "Score: %.1f%%\n\n",
        score[order[0]]
    );

    fprintf(fp, "All Major Scores:\n");

    for (i = 0; i < MAJORS; i++)
    {
        fprintf(
            fp,
            "%s - %.1f%%\n",
            m[order[i]].name,
            score[order[i]]
        );
    }

    fclose(fp);

    printf(
        "\nReport saved as recommendation.txt\n"
    );
}

/* ---------- Main ---------- */

int main()
{
    Student student;
    Major majors[MAJORS];
    float score[MAJORS];
    int order[MAJORS];
    int choice, i;

    setupMajors(majors);

    while (1)
    {
        printf("\n========================================\n");
        printf("   ACADEMIC MAJOR RECOMMENDATION SYSTEM\n");
        printf("========================================\n");

        printf("1. Start Assessment\n");
        printf("2. Exit\n");

        choice =
            getInt("Enter choice: ", 1, 2);

        if (choice == 2)
        {
            printf("Thank you!\n");
            break;
        }

        inputStudent(&student);

        for (i = 0; i < MAJORS; i++)
            score[i] =
                calculateScore(
                    &student,
                    &majors[i]
                );

        sortResults(score, order);

        showResults(
            &student,
            majors,
            score,
            order
        );

        if (getInt(
            "\nSave report? (1=Yes, 2=No): ",
            1, 2) == 1)
        {
            saveFile(
                &student,
                majors,
                score,
                order
            );
        }
    }

    return 0;
}
