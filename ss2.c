#include <stdio.h>
#include <string.h>

struct UserAccount
{
    char user_id[21];
    char username[51];
    int plan_type;
    int days_overdue;
    int active_devices;
    long long final_fee;
    int is_downgraded;
};

int main(void)
{
    int n;
    struct UserAccount accounts[100];
    long long total_revenue = 0;
    int downgraded_count = 0;

    do
    {
        printf("Nhap so luong tai khoan (1 - 100): ");
        if (scanf("%d", &n) != 1)
        {
            while (getchar() != '\n')
                ;
            n = 0;
            continue;
        }
        if (n < 1 || n > 100)
        {
            printf("So luong khong hop le! Vui long nhap lai.\n");
        }
    } while (n < 1 || n > 100);

    for (int i = 0; i < n; i++)
    {
        printf("\n--- Nhap thong tin tai khoan thu %d ---\n", i + 1);

        printf("Ma tai khoan (user_id): ");
        scanf("%20s", accounts[i].user_id);
        while (getchar() != '\n')
            ;

        printf("Ten tai khoan (username): ");
        fgets(accounts[i].username, sizeof(accounts[i].username), stdin);
        size_t len = strlen(accounts[i].username);
        if (len > 0 && accounts[i].username[len - 1] == '\n')
        {
            accounts[i].username[len - 1] = '\0';
        }

        do
        {
            printf("Loai goi (1: Free, 2: Personal, 3: Family): ");
            if (scanf("%d", &accounts[i].plan_type) != 1)
            {
                while (getchar() != '\n')
                    ;
                accounts[i].plan_type = 0;
                continue;
            }
            if (accounts[i].plan_type < 1 || accounts[i].plan_type > 3)
            {
                printf("Goi khong hop le! Chi chap nhan gia tri tu 1 den 3.\n");
            }
        } while (accounts[i].plan_type < 1 || accounts[i].plan_type > 3);

        do
        {
            printf("So ngay no cuoc (days_overdue >= 0): ");
            if (scanf("%d", &accounts[i].days_overdue) != 1)
            {
                while (getchar() != '\n')
                    ;
                accounts[i].days_overdue = -1;
                continue;
            }
            if (accounts[i].days_overdue < 0)
            {
                printf("So ngay no khong duoc am! Nhap lai.\n");
            }
        } while (accounts[i].days_overdue < 0);

        do
        {
            printf("So thiet bi dang ket noi (active_devices >= 0): ");
            if (scanf("%d", &accounts[i].active_devices) != 1)
            {
                while (getchar() != '\n')
                    ;
                accounts[i].active_devices = -1;
                continue;
            }
            if (accounts[i].active_devices < 0)
            {
                printf("So thiet bi khong duoc am! Nhap lai.\n");
            }
        } while (accounts[i].active_devices < 0);

        accounts[i].is_downgraded = 0;
        accounts[i].final_fee = 0;

        if (accounts[i].days_overdue >= 3)
        {
            if (accounts[i].plan_type != 1)
            {
                accounts[i].plan_type = 1;
                accounts[i].is_downgraded = 1;
                downgraded_count++;
            }
            accounts[i].final_fee = 0;
        }
        else
        {
            if (accounts[i].plan_type == 2)
            {
                accounts[i].final_fee = 120000;
                if (accounts[i].active_devices > 1)
                {
                    accounts[i].final_fee += (long long)(accounts[i].active_devices - 1) * 30000;
                }
            }
            else if (accounts[i].plan_type == 3)
            {
                accounts[i].final_fee = 250000;
            }
            else
            {
                accounts[i].final_fee = 0;
            }
        }

        total_revenue += accounts[i].final_fee;
    }

    printf("\n====================================================================================================\n");
    printf("|                                BANG DOI SOAT TAI KHOAN BILLING                                   |\n");
    printf("====================================================================================================\n");
    printf("| %-12s | %-20s | %-8s | %-12s | %-12s | %-18s |\n",
           "Ma TK", "Ten TK", "Ma Goi", "Thiet Bi", "So Ngay No", "Phi Thuc Thu (VND)");
    printf("----------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        char plan_label[15];
        if (accounts[i].plan_type == 1)
        {
            strcpy(plan_label, "1 (Free)");
        }
        else if (accounts[i].plan_type == 2)
        {
            strcpy(plan_label, "2 (Personal)");
        }
        else
        {
            strcpy(plan_label, "3 (Family)");
        }

        printf("| %-12s | %-20s | %-8s | %12d | %12d | %18lld |\n",
               accounts[i].user_id,
               accounts[i].username,
               plan_label,
               accounts[i].active_devices,
               accounts[i].days_overdue,
               accounts[i].final_fee);
    }
    printf("====================================================================================================\n");

    printf("\n--- TONG KET KY BILLING ---\n");
    printf("Tong so tai khoan bi ha cap ve goi Free: %d\n", downgraded_count);
    printf("Tong doanh thu thuc te thu duoc       : %lld VND\n", total_revenue);

    return 0;
}