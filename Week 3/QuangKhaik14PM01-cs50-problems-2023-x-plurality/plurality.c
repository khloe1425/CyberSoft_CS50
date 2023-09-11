#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX_CANDIDATES 9

// Khai báo cấu trúc để lưu trữ thông tin của ứng cử viên
struct Candidate {
    char name[50];
    int votes;
};

// Khai báo biến toàn cục để lưu trữ danh sách các ứng cử viên
struct Candidate candidates[MAX_CANDIDATES];
int numCandidates = 0;
int maxVotes = 0;

// Hàm để bầu cử cho ứng cử viên theo tên
int vote(const char *name) {
    for (int i = 0; i < numCandidates; i++) {
        if (strcmp(name, candidates[i].name) == 0) {
            candidates[i].votes++;
            if (candidates[i].votes > maxVotes) {
                maxVotes = candidates[i].votes;
            }
            return 1; // Lá phiếu thành công
        }
    }
    return 0; // Lá phiếu không hợp lệ
}

// Hàm để in ra ứng cử viên chiến thắng
void print_winner() {
    printf("Kết quả bầu cử:\n");
    for (int i = 0; i < numCandidates; i++) {
        if (candidates[i].votes == maxVotes) {
            printf("%s\n", candidates[i].name);
        }
    }
}

int main() {
    int numVoters;
    printf("Nhập số lượng cử tri: ");
    scanf("%d", &numVoters);

    printf("Nhập danh sách ứng cử viên:\n");
    for (int i = 0; i < numVoters; i++) {
        char candidateName[50];
        printf("Tên ứng cử viên %d: ", i + 1);
        scanf("%s", candidateName);

        strcpy(candidates[numCandidates].name, candidateName);
        candidates[numCandidates].votes = 0;
        numCandidates++;
    }

    printf("Bắt đầu bầu cử:\n");
    for (int i = 0; i < numVoters; i++) {
        char voterChoice[50];
        printf("Cử tri %d bầu chọn: ", i + 1);
        scanf("%s", voterChoice);

        int result = vote(voterChoice);
        if (result) {
            printf("Lá phiếu của cử tri %d đã được tính.\n", i + 1);
        } else {
            printf("Lá phiếu của cử tri %d không hợp lệ.\n", i + 1);
        }
    }

    print_winner();

    return 0;
}