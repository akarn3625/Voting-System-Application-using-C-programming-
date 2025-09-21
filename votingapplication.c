#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> 

#define MAX_CANDIDATES 100
#define MAX_VOTERS 100
#define MAX_CONSTITUENCIES 100
#define MAX_LENGTH 100

typedef struct {
    char name[MAX_LENGTH];
    char party[MAX_LENGTH];
    char constituency[MAX_LENGTH];
    int votes;
} Candidate;

typedef struct {
    int sno;
    char name[MAX_LENGTH];
    char dob[MAX_LENGTH];
    char address[MAX_LENGTH];
    char password[MAX_LENGTH];
    int voted;
    int candidateIndex;
} Voter;

void adminLogin(Candidate candidates[], Voter voters[], int *numCandidates, int *numVoters);
void createElectionSchedule();
void candidateRegistration(Candidate candidates[], int *numCandidates);
void voterRegistration(Candidate candidates[], Voter voters[], int *numCandidates, int *numVoters);
void updateVoterDetails(Voter voters[], int numVoters);
void searchVoterDetails(Voter voters[], int numVoters);
void castVote(Candidate candidates[], Voter voters[], int numCandidates, int numVoters);
void voteResult(Candidate candidates[], int numCandidates);
void saveDataToFile(Candidate candidates[], Voter voters[], int numCandidates, int numVoters);
void loadDataFromFile(Candidate candidates[], Voter voters[], int *numCandidates, int *numVoters);
void viewAllVoterDetails(Candidate candidates[], Voter voters[], int numCandidates, int numVoters);

int main() {
    Candidate candidates[MAX_CANDIDATES];
    Voter voters[MAX_VOTERS];
    int numCandidates = 0;
    int numVoters = 0;

    loadDataFromFile(candidates, voters, &numCandidates, &numVoters);

    int choice;
    
    printf("\nVOTING SYSTEM\n");
    printf("1. Start\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            break;
        case 2:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice! Exiting...\n");
            return 0;
    }
    
    do {
        printf("\nVOTING SYSTEM\n");
        printf("1. Admin Login\n");
        printf("2. Voter\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                adminLogin(candidates, voters, &numCandidates, &numVoters);
                break;
            case 2:
                voterRegistration(candidates, voters, &numCandidates, &numVoters);
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please enter again.\n");
        }
    } while(1);
}

void adminLogin(Candidate candidates[], Voter voters[], int *numCandidates, int *numVoters) {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    
    printf("Enter admin username: ");
    scanf("%s", username);
    printf("Enter admin password: ");
    
    int index = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == '\r' || ch == '\n') {
            password[index] = '\0';
            break;
        } else if (ch == 8 && index > 0) {
            printf("\b \b");
            index--;
        } else {
            printf("*");
            password[index++] = ch;
        }
    }
    printf("\n");

    if(strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Admin login successful!\n");
        
        int adminChoice;
        do {
            printf("\nAdmin Menu\n");
            printf("1. Create Election Schedule\n");
            printf("2. Candidate Registration\n");
            printf("3. Update Voter Details\n");
            printf("4. Search Voter Details\n");
            printf("5. View All Voter Details\n");
            printf("6. Vote Result\n");
            printf("7. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &adminChoice);
            
            switch(adminChoice) {
                case 1:
                    createElectionSchedule();
                    break;
                case 2:
                    candidateRegistration(candidates, numCandidates);
                    break;
                case 3:
                    updateVoterDetails(voters, *numVoters);
                    break;
                case 4:
                    searchVoterDetails(voters, *numVoters);
                    break;
                case 5:
                    viewAllVoterDetails(candidates, voters, *numCandidates, *numVoters);
                    break;
                case 6:
                    voteResult(candidates, *numCandidates);
                    break;
                case 7:
                    printf("Logging out...\n");
                    return;
                default:
                    printf("Invalid choice! Please enter again.\n");
            }
        } while(1);
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

void createElectionSchedule() {
    FILE *file = fopen("schedule.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    fprintf(file, "Constituency\tDate of Election(yyyymmdd)\n");
    fprintf(file, "Kathmandu\t20220909\n");
    fprintf(file, "Gorkha\t20220909\n");
    fprintf(file, "Chitwan\t20220909\n");
    fprintf(file, "Pokhara\t20220909\n");
    
    fclose(file);
    printf("Election schedule created and stored in schedule.txt\n");
}

void candidateRegistration(Candidate candidates[], int *numCandidates) {
    if (*numCandidates >= MAX_CANDIDATES) {
        printf("Maximum candidates limit reached!\n");
        return;
    }
    
    printf("Enter name of candidate: ");
    scanf("%s", candidates[*numCandidates].name);
    printf("Enter political party: ");
    scanf("%s", candidates[*numCandidates].party);
    printf("Enter constituency: ");
    scanf("%s", candidates[*numCandidates].constituency);
    candidates[*numCandidates].votes = 0;
    
    (*numCandidates)++;
    printf("Candidate registered successfully!\n");
    saveDataToFile(candidates, NULL, *numCandidates, 0);
}

void voterRegistration(Candidate candidates[], Voter voters[], int *numCandidates, int *numVoters) {
    if (*numVoters >= MAX_VOTERS) {
        printf("Maximum voters limit reached!\n");
        return;
    }
    
    int choice;
    printf("VOTER SECTION\n");
    printf("1. Sign Up\n");
    printf("2. Login\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            printf("Enter your name: ");
            scanf("%s", voters[*numVoters].name);
            printf("Enter your date of birth (yyyy/mm/dd): ");
            scanf("%s", voters[*numVoters].dob);
            printf("Enter your address: ");
            scanf("%s", voters[*numVoters].address);
            printf("Enter your password: ");
            
            int index = 0;
            char ch;
            while (1) {
                ch = getch();
                if (ch == '\r' || ch == '\n') {
                    voters[*numVoters].password[index] = '\0';
                    break;
                } else if (ch == 8 && index > 0) {
                    printf("\b \b");
                    index--;
                } else {
                    printf("*");
                    voters[*numVoters].password[index++] = ch;
                }
            }
            printf("\n");
            
            char year[5];
            strncpy(year, voters[*numVoters].dob, 4);
            year[4] = '\0';
            int birthYear = atoi(year);
            int currentYear = 2080;
            if (currentYear - birthYear < 18) {
                printf("You are not eligible to vote as you are under 18 years old.\n");
                return;
            }
            
            voters[*numVoters].sno = *numVoters + 1;
            voters[*numVoters].voted = 0;
            voters[*numVoters].candidateIndex = -1;
            
            (*numVoters)++;
            printf("Voter registered successfully!\n");
            saveDataToFile(NULL, voters, 0, *numVoters);
            break;
        case 2:
            castVote(candidates, voters, *numCandidates, *numVoters);
            break;
        default:
            printf("Invalid choice!\n");
    }
}

void updateVoterDetails(Voter voters[], int numVoters) {
    int sno;
    printf("Enter Voter SNO to update details: ");
    scanf("%d", &sno);
    
    int i;
    for (i = 0; i < numVoters; i++) {
        if (voters[i].sno == sno) {
            printf("Enter new name: ");
            scanf("%s", voters[i].name);
            printf("Enter new date of birth (yyyy/mm/dd): ");
            scanf("%s", voters[i].dob);
            printf("Enter new address: ");
            scanf("%s", voters[i].address);
            printf("Enter new password: ");
            
            int index = 0;
            char ch;
            while (1) {
                ch = getch();
                if (ch == '\r' || ch == '\n') {
                    voters[i].password[index] = '\0';
                    break;
                } else if (ch == 8 && index > 0) {
                    printf("\b \b");
                    index--;
                } else {
                    printf("*");
                    voters[i].password[index++] = ch;
                }
            }
            printf("\n");
            
            printf("Voter details updated successfully!\n");
            saveDataToFile(NULL, voters, 0, numVoters);
            return;
        }
    }
    
    printf("Voter not found with SNO %d\n", sno);
}

void searchVoterDetails(Voter voters[], int numVoters) {
    int sno;
    printf("Enter Voter SNO to search details: ");
    scanf("%d", &sno);
    
    int i;
    for (i = 0; i < numVoters; i++) {
        if (voters[i].sno == sno) {
            printf("Voter Details:\n");
            printf("SNO: %d\n", voters[i].sno);
            printf("Name: %s\n", voters[i].name);
            printf("Date of Birth: %s\n", voters[i].dob);
            printf("Address: %s\n", voters[i].address);
            return;
        }
    }
    
    printf("Voter not found with SNO %d\n", sno);
}

void castVote(Candidate candidates[], Voter voters[], int numCandidates, int numVoters) {
    int voterSno;
    char password[MAX_LENGTH];
    int candidateIndex;
    
    printf("Enter your Voter SNO: ");
    scanf("%d", &voterSno);
    printf("Enter your password: ");
    
    int index = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == '\r' || ch == '\n') {
            password[index] = '\0';
            break;
        } else if (ch == 8 && index > 0) {
            printf("\b \b");
            index--;
        } else {
            printf("*");
            password[index++] = ch;
        }
    }
    printf("\n");
    
    int i;
    for (i = 0; i < numVoters; i++) {
        if (voters[i].sno == voterSno && strcmp(voters[i].password, password) == 0) {
            if (voters[i].voted) {
                printf("You have already cast your vote.\n");
                return;
            }
            
            printf("Candidates List:\n");
            for (int j = 0; j < numCandidates; j++) {
                printf("%d. %s - %s\n", j + 1, candidates[j].name, candidates[j].constituency);
            }
            
            printf("Enter the index of the candidate you want to vote for: ");
            scanf("%d", &candidateIndex);
            
            if (candidateIndex < 1 || candidateIndex > numCandidates) {
                printf("Invalid candidate index.\n");
                return;
            }
            
            voters[i].voted = 1;
            voters[i].candidateIndex = candidateIndex - 1;
            candidates[candidateIndex - 1].votes++;
            
            printf("Vote cast successfully!\n");
            saveDataToFile(candidates, voters, numCandidates, numVoters);
            return;
        }
    }
    
    printf("Invalid Voter SNO or password.\n");
}

void voteResult(Candidate candidates[], int numCandidates) {
    printf("Vote Results:\n");
    for (int i = 0; i < numCandidates; i++) {
        printf("%s (%s): %d votes\n", candidates[i].name, candidates[i].constituency, candidates[i].votes);
    }
}

void saveDataToFile(Candidate candidates[], Voter voters[], int numCandidates, int numVoters) {
    FILE *file = fopen("votingdetails.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    if (candidates != NULL) {
        fprintf(file, "%d\n", numCandidates);
        for (int i = 0; i < numCandidates; i++) {
            fprintf(file, "%s %s %s %d\n", candidates[i].name, candidates[i].party, candidates[i].constituency, candidates[i].votes);
        }
    }

    if (voters != NULL) {
        fprintf(file, "%d\n", numVoters);
        for (int i = 0; i < numVoters; i++) {
            fprintf(file, "%d %s %s %s %s %d %d\n", voters[i].sno, voters[i].name, voters[i].dob, voters[i].address, voters[i].password, voters[i].voted, voters[i].candidateIndex);
        }
    }

    fclose(file);
    printf("Data saved to file: votingdetails.txt\n");
}

void loadDataFromFile(Candidate candidates[], Voter voters[], int *numCandidates, int *numVoters) {
    FILE *file = fopen("votingdetails.txt", "r");
    if (file == NULL) {
        printf("No previous data found.\n");
        return;
    }

    fscanf(file, "%d", numCandidates);
    for (int i = 0; i < *numCandidates; i++) {
        fscanf(file, "%s %s %s %d", candidates[i].name, candidates[i].party, candidates[i].constituency, &candidates[i].votes);
    }

    fscanf(file, "%d", numVoters);
    for (int i = 0; i < *numVoters; i++) {
        fscanf(file, "%d %s %s %s %s %d %d", &voters[i].sno, voters[i].name, voters[i].dob, voters[i].address, voters[i].password, &voters[i].voted, &voters[i].candidateIndex);
    }

    fclose(file);
    printf("Data loaded from file: votingdetails.txt\n");
}

void viewAllVoterDetails(Candidate candidates[], Voter voters[], int numCandidates, int numVoters) {
    printf("All Voter Details:\n");
    for (int i = 0; i < numVoters; i++) {
        printf("SNO: %d\n", voters[i].sno);
        printf("Name: %s\n", voters[i].name);
        printf("Date of Birth: %s\n", voters[i].dob);
        printf("Address: %s\n", voters[i].address);
        printf("Voted: %s\n", voters[i].voted ? "Yes" : "No");
        if (voters[i].voted) {
            printf("Candidate Voted For: %s\n", candidates[voters[i].candidateIndex].name);
        }
        printf("\n");
    }
}
