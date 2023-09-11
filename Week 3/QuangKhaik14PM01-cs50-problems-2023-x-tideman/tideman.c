#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CANDIDATES 10
#define MAX_VOTERS 100

// Khai báo mảng hai chiều để lưu trữ tùy chọn ưu tiên của cử tri
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Khai báo cấu trúc để lưu trữ thông tin của ứng cử viên
struct Candidate {
    char name[50];
    int votes;
    bool eliminated;
};

// Khai báo mảng để lưu trữ danh sách các ứng cử viên
struct Candidate candidates[MAX_CANDIDATES];

// Biến toàn cục để lưu trữ số lượng ứng cử viên và cử tri
int candidate_count = 0;
int voter_count = 0;

// Hàm để bầu cử cho ứng cử viên theo tên
bool vote(int voter, int rank, char *name) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i].name) == 0) {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Hàm để tính toán số phiếu bầu hiện tại cho từng ứng cử viên
void tabulate() {
    for (int i = 0; i < voter_count; i++) {
        int rank = 0;
        while (candidates[preferences[i][rank]].eliminated) {
            rank++;
        }
        candidates[preferences[i][rank]].votes++;
    }
}

// Hàm để in ra ứng cử viên chiến thắng hoặc kết quả hòa
bool print_winner() {
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > voter_count / 2) {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Hàm để tìm ra số phiếu bầu tối thiểu cho ứng cử viên còn lại
int find_min() {
    int min_votes = voter_count;
    for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated && candidates[i].votes < min_votes) {
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}

// Hàm để kiểm tra xem cuộc bầu cử có kết thúc với tỷ số hòa hay không
bool is_tie(int min_votes) {
    for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated && candidates[i].votes != min_votes) {
            return false;
        }
    }
    return true;
}

// Hàm để loại bỏ ứng cử viên có số phiếu bầu ít nhất
void eliminate(int min_votes) {
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == min_votes) {
            candidates[i].eliminated = true;
        }
    }
}

int main() {
    // Nhập số lượng ứng cử viên và cử tri
    printf("Nhập số lượng ứng cử viên: ");
    scanf("%d", &candidate_count);
    printf("Nhập số lượng cử tri: ");
    scanf("%d", &voter_count);

    // Nhập danh sách các ứng cử viên
    for (int i = 0; i < candidate_count; i++) {
        printf("Nhập tên ứng cử viên %d: ", i + 1);
        scanf("%s", candidates[i].name);
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    // Nhập tùy chọn ưu tiên của từng cử tri
    for (int i = 0; i < voter_count; i++) {
        printf("Cử tri %d, nhập tùy chọn ưu tiên:\n", i + 1);
        for (int j = 0; j < candidate_count; j++) {
            char name[50];
            printf("Tùy chọn %d: ", j + 1);
            scanf("%s", name);
            if (!vote(i, j, name)) {
                printf("Lựa chọn không hợp lệ. Vui lòng nhập lại.\n");
                j--;
            }
        }
    }

    while (true) {
        tabulate();
        if (print_winner()) {
            break;
        }
        int min_votes = find_min();
        if (is_tie(min_votes)) {
            printf("Cuộc bầu cử kết thúc với tỷ số hòa.\n");
            break;
        }
        eliminate(min_votes);
    }

    return 0;
}
