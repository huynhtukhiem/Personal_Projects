// Bản xem trước
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <shellapi.h>
#include <time.h>

// Cấu trúc của một từ vựng
typedef struct {
    char tu[50];
    char nghia[100];
    char loai[10];
} Tuvung;

// Cấu trúc của một câu hỏi
typedef struct {
    char Eng[100];
    char Vie[100];
} Word;

// Khai báo prototype
void Menu_Chinh();
void Nhap_tu_vung_moi();
void Chuan_hoa_chuoi(char str[]);
void Ghi_vao_file(Tuvung tv);
void Ghi_vao_file_data(Tuvung tv);
void Them_1_tu(Tuvung *tv, const char *Loai_tu);
Word* Doc_file_data(const char* filename, int* count);
void Tao_Quiz(Word* list, int n);
void On_tu_vung();
void Cai_dat();
// Nhập từ vựng mới và gia đình từ
void Nhap_tu_vung_moi() {
    int choice;
    char Y_N;
    do {
        Tuvung tv;
        printf("-----------Nhập từ mới----------\n");
        Them_1_tu(&tv, NULL);
        
        if (strcmp(tv.loai, "V") == 0 || strcmp(tv.loai, "N") == 0 ||
            strcmp(tv.loai, "Adj") == 0 || strcmp(tv.loai, "Adv") == 0) {
            printf("Bạn có muốn nhập tiếp các từ liên quan (Gia đình từ) của %s không? (y/n): ", tv.tu);
            scanf("%c", &Y_N);
            getchar();
            system("cls");
            if (Y_N == 'y' || Y_N == 'Y') {
                char *thu_tu_V[] = {"N", "Adj", "Adv"};
                char *thu_tu_N[] = {"V", "Adj", "Adv"};
                char *thu_tu_Adj[] = {"V", "N", "Adv"};
                char *thu_tu_Adv[] = {"V", "N", "Adj"};
                char **thu_tu;

                if (strcmp(tv.loai, "V") == 0) thu_tu = thu_tu_V;
                else if (strcmp(tv.loai, "N") == 0) thu_tu = thu_tu_N;
                else if (strcmp(tv.loai, "Adj") == 0) thu_tu = thu_tu_Adj;
                else thu_tu = thu_tu_Adv;

                for (int i = 0; i < 3; i++) {
                    printf("Nhập %s của %s (0: Dừng, Enter để bỏ qua): ", thu_tu[i], tv.tu);
                    char temp_tu[50];
                    fgets(temp_tu, sizeof(temp_tu), stdin);
                    temp_tu[strcspn(temp_tu, "\n")] = '\0';
                    if (strcmp(temp_tu, "0") == 0) break;
                    if (strlen(temp_tu) == 0) continue;

                    strcpy(tv.tu, temp_tu);
                    Chuan_hoa_chuoi(tv.tu);

                    printf("Nhập nghĩa tiếng Việt của từ %s (Enter để bỏ qua): ", tv.tu);
                    char temp_nghia[100];
                    fgets(temp_nghia, sizeof(temp_nghia), stdin);
                    temp_nghia[strcspn(temp_nghia, "\n")] = '\0';
                    strcpy(tv.nghia, strlen(temp_nghia) > 0 ? temp_nghia : "");
                    Chuan_hoa_chuoi(tv.nghia);

                    strcpy(tv.loai, thu_tu[i]);
                    Ghi_vao_file(tv);
                    Ghi_vao_file_data(tv);
                    printf("Đã lưu từ '%s' (%s) vào file tuvung.txt\n", tv.tu, tv.loai);
                    Sleep(200);
                    system("cls");
                }
            }
        }

        printf("-----Menu tính năng thêm từ vựng mới-----\n");
        printf("1: Thêm từ mới\n");
        printf("2: Mở file từ vựng bản thân đã lưu\n");
        printf("3: Về Menu chức năng chính\n");
        printf("0: Thoát chương trình\n");
        printf("Mời bạn chọn (VD: 1): ");
        scanf("%d", &choice);
        getchar();
        system("cls");
        switch (choice) {
            case 1:
                continue;
            case 2:
                ShellExecute(NULL, "open", "tuvung.txt", NULL, NULL, SW_MAXIMIZE);
                break;
            case 3:
                Menu_Chinh();
                break;
            case 0:
                printf("Đã thoát\n");
                exit(0);
            default:
                printf("Lựa chọn không hợp lệ!\n");
                Sleep(200);
                system("cls");
        }
    } while (choice != 0);
}
