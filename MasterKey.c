// MasterKey v1.2

#include <stdio.h>
#include <stdlib.h>
#include <stded.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

void add_password();
void click_img();
void timer(int time);
void display_passwords_list();
void display_current_password();
void search_password();
char change_password(char *current_password);
char change_mail(char *current_password);
void display_menu();
char read_password(char *main_password);
void view_suspect_img();
void set_new_password();
void reset();
int forgot_password(int *r);
void reset_password();
void export_passwords();
void import_passwords();
void try_again();
void send_otp();
void lock();
void unlock();
void start();
void exiting();
void check_for_update();
void please_wait();

int main()
{

    unlock();
    system("clear");

    // seed for random generator
    srand(time(0));

    // setted pins for program execution in .password.txt file
    char main_password[1000];
    read_password(main_password);
    // printf("%s\n", main_password);
    // sleep(3);

    // user entered pins
    char *entered_password;
    char invalid_password[100];

    // attempts
    int menu_attempts = 3;

    // choices
    char choose_menu; // main menu
    char go_back;
    char ch_reset, ch_forgot, ch_forgot_options;
    char ch_3, ch_3_4, ch_5, ch_uninstall;
    int limit;

    // suspect warning
    // system("sudo chmod 700 ../.temp/.suspect.txt");
    FILE *suspect;
    suspect = fopen("../.temp/.suspect.txt", "r");
    int suspect_bool;
    fscanf(suspect, "%d", &suspect_bool);
    fclose(suspect);
    // system("sudo chmod 000 ../.temp/.suspect.txt");

    // system("sudo chmod 700 ../.data/.password.txt");
    FILE *fp;
    fp = fopen("../.data/.password.txt", "r");

    // check for timer
    FILE *lim;
    // system("sudo chmod 700 ../.temp/.limit.txt");
    lim = fopen("../.temp/.limit.txt", "r");
    fscanf(lim, "%d", &limit);
    fclose(lim);
    // system("sudo chmod 000 ../.temp/.limit.txt");

    if (limit > 3)
    {
        system("clear");
        system("echo Too many invalid attempts");
        sleep(1);
        system("clear");

        try_again();

        // setting limit 0
        FILE *lim;
        limit = 0;
        // system("sudo chmod 700 ../.temp/.limit.txt");
        lim = fopen("../.temp/.limit.txt", "w");
        fprintf(lim, "%d", limit);
        fclose(lim);
        // system("sudo chmod 000 ../.temp/.limit.txt");
        goto enter_pass;
    }
    else
    {

        if (NULL != fp)
        {
            fseek(fp, 0, SEEK_END);
            int size = ftell(fp);

            if (0 == size)
            {
            startup:
                set_new_password();
                // system("sudo chmod 000 ../.data/.password.txt");
            }
            else
            {
                // system("sudo chmod 000 ../.data/.password.txt");

                start();

                while (menu_attempts != 0)
                {

                enter_pass:
                    // timestamp
                    // system("sudo chmod 700 ../.temp/.time.txt");
                    FILE *t_stamp;
                    char timestamp[1000];
                    t_stamp = fopen("../.temp/.time.txt", "r");
                    fgets(timestamp, 38, t_stamp);
                    fclose(t_stamp);

                    entered_password = getpass("Enter the key:  ");
                    strcpy(invalid_password, entered_password);
                    encrypt_string(entered_password);
                    if (strcmp(entered_password, main_password) != 0)
                    {
                        FILE *invalid_password_ptr;
                        invalid_password_ptr = fopen("../.data/.invalid_password.txt", "w");
                        fprintf(invalid_password_ptr, "%s", invalid_password);
                        fclose(invalid_password_ptr);
                    }
                    // printf("\n*******%s*********\n", entered_password);
                    // sleep(3);

                    system("clear");

                    //   printf("\n******%d*******\n",strcmp(entered_password, main_password));
                    if (strcmp(entered_password, main_password) == 0)
                    {
                        system("echo $(cat /home/$USER/Documents/.Program-Files/.MasterKey/.data/.password.txt) | gpg -d --batch --passphrase-fd 0 /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt.gpg > /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt && rm /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt.gpg");
                        system("clear");

                        // setting limit 0
                        FILE *lim;
                        limit = 0;
                        // system("sudo chmod 700 ../.temp/.limit.txt");
                        lim = fopen("../.temp/.limit.txt", "w");
                        // system("sudo chmod 000 ../.temp/.limit.txt");
                        fprintf(lim, "%d", limit);
                        fclose(lim);

                        if (suspect_bool == 1)
                        {
                        warning:
                            char sus_ch;
                            printf("Alert: There was an invalid login attempt on %s, view suspect's image?\n\n", timestamp);

                            printf("Continue [Y/n] : ");
                            scanf(" %c", &sus_ch);
                            getchar();
                            sus_ch = tolower(sus_ch);
                            if (sus_ch == 'y')
                            {
                                // system("sudo chmod 600 ../.temp/.image.jpeg;");
                                system("if [ -f ../.temp/.image.jpeg ]; then chmod 600 ../.temp/.image.jpeg; feh ../.temp/.image.jpeg; else clear; echo Error: image not captured; echo You might not have a camera configured to your system; echo ; fi;");

                                view_suspect_img();
                                // system("sudo chmod 700 ../.temp/.suspect.txt");
                                suspect_bool = 0;
                                suspect = fopen("../.temp/.suspect.txt", "w");
                                fprintf(suspect, "%d", suspect_bool);
                                fclose(suspect);
                                // system("sudo chmod 000 ../.temp/.suspect.txt");
                                system("rm ../.temp/.image.jpeg");
                                printf("\n");
                                goto goback;
                                system("clear");
                            }
                            else if (sus_ch == 'n')
                            {
                                system("clear");
                                suspect_bool = 0;
                                // system("sudo chmod 700 ../.temp/.suspect.txt");
                                FILE *suspect;
                                suspect = fopen("../.temp/.suspect.txt", "w");
                                fprintf(suspect, "%d", suspect_bool);
                                fclose(suspect);
                                // system("sudo chmod 000 ../.temp/.suspect.txt");
                                system("rm ../.temp/.image.jpeg");

                                goto menu;
                            }
                            else
                            {

                                system("echo && echo Invalid Input");
                                sleep(1);
                                system("clear");
                                goto warning;
                            }
                        }
                        else
                        {

                            // 3 attempts for attempting the passwords
                        menu:
                            display_menu();
                            printf("Enter your choice [0-5]: ");
                            scanf(" %c", &choose_menu);

                            switch (choose_menu)
                            {
                            case '0':
                                system("sudo chmod 777 ../.data/.password.txt");
                                system("echo $(cat /home/$USER/Documents/.Program-Files/.MasterKey/.data/.password.txt) | gpg -c --batch --passphrase-fd 0 /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt && rm /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt");
                                system("clear");
                                exiting();
                                break;

                            case '1':
                                system("clear");
                                search_password();
                                break;

                            case '2':
                                system("clear");
                                char code[1000];
                                printf("Enter the encrypted password: ");
                                scanf(" %[^\n]s", code);
                                getchar();

                                decrypt_string2(code);

                                printf("The decrypted password is: ");
                                puts(code);
                                printf("\n");

                                break;
                            case '3':
                            menu_3:
                                system("clear");
                                printf("Edit Dictionary\n\n");
                                printf("  [0] <-- Go back to menu!\n\n");
                                printf("  [1] View Passwords\n");
                                printf("  [2] Add Passwords\n");
                                printf("  [3] Remove Passwords\n");
                                printf("  [4] Backup & Restore\n");
                                printf("\nEnter your choice [0-4]: ");
                                scanf(" %c", &ch_3);

                                switch (ch_3)
                                {
                                case '0':
                                    system("clear");
                                    goto menu;
                                    break;

                                case '1':
                                    system("clear");
                                    display_passwords_list();
                                    break;

                                case '2':
                                    system("clear");
                                    add_password();
                                    break;

                                case '3':
                                    system("clear");
                                    // system("sudo chmod 700 ../.data/.passwords_list.txt");
                                    system("nano ../.data/.passwords_list.txt");
                                    // system("sudo chmod 000 ../.data/.passwords_list.txt");
                                    break;

                                case '4':
                                menu_3_4:
                                    system("clear");
                                    printf("Edit Dictionary\n\n");
                                    printf("  [0] <-- Go back\n\n");
                                    printf("  [1] Import Passwords\n");
                                    printf("  [2] Export Passwords\n");
                                    printf("\nEnter your choice [0-2]: ");
                                    scanf(" %c", &ch_3_4);

                                    switch (ch_3_4)
                                    {
                                    case '0':
                                        system("clear");
                                        goto menu_3;
                                        break;

                                    case '1':
                                        system("clear");
                                        import_passwords();
                                        break;

                                    case '2':
                                        system("clear");
                                        export_passwords();

                                        break;

                                    default:
                                        printf("\nInvalid Input!\n");
                                        sleep(1);
                                        system("clear");
                                        goto menu_3_4;
                                        break;
                                    }

                                    printf("\n<-- Go back! [Y] : ");
                                    fflush(stdin);
                                    scanf(" %c", &go_back);
                                    getchar();
                                    system("clear");
                                    goto menu_3;
                                    break;

                                default:
                                    printf("\nInvalid Input!\n");
                                    sleep(1);
                                    system("clear");
                                    goto menu_3;
                                    break;
                                }

                                printf("<-- Go back! [Y] : ");
                                fflush(stdin);
                                scanf(" %c", &go_back);
                                getchar();
                                system("clear");
                                goto menu_3;
                                break;

                            case '4':
                            menu_4:

                                system("clear");
                                printf("Settings:\n\n");
                                printf("  [0] <-- Go back to menu!\n\n");
                                printf("  [1] Change Key\n");
                                printf("  [2] Change Email\n");
                                printf("  [3] Reset App\n");
                                printf("  [4] Check for updates\n");
                                printf("  [5] Uninstall MasterKey App\n");
                                // printf("  [5] About\n");
                                // printf("  [5] Developer Mode\n");
                                printf("\nEnter your choice [0-5]: ");
                                scanf(" %c", &ch_5);

                                switch (ch_5)
                                {
                                case '0':
                                    system("clear");
                                    goto menu;
                                    break;

                                case '1':
                                    system("clear");
                                    change_password(main_password);
                                    break;

                                case '2':
                                    system("clear");
                                    change_mail(main_password);
                                    break;

                                case '3':
                                    system("clear");
                                    printf("Note: Resetting the app will delete all your existing data like stored passwords, recovery data, etc.");
                                    printf("\n\nAre you sure you want to continue? [Y/n] : ");
                                    scanf(" %c", &ch_reset);
                                    getchar();
                                    ch_reset = tolower(ch_reset);

                                    if (ch_reset == 'y')
                                    {
                                        system("clear");

                                        char *entered_reset_password;
                                        int attempt = 3;

                                        system("clear");
                                    reset_password:

                                        entered_reset_password = getpass("Enter the key:  ");
                                        encrypt_string(entered_reset_password);

                                        if (strcmp(entered_reset_password, main_password) == 0)
                                        {
                                            system("clear");
                                            if (system("wget -q --spider http://google.com;") == 0)
                                            {
                                                // system("sudo chmod  600 ../.temp/.otp.txt");
                                                // system("sudo chmod  600 ../.mail/.mail.txt");
                                                send_otp();

                                                int otp_reset_attempts = 3;
                                                char entered_reset_otp[100];
                                                char reset_otp[10];

                                                FILE *rotr;
                                                rotr = fopen("../.temp/.otp.txt", "r");
                                                fscanf(rotr, " %s", reset_otp);
                                                fclose(rotr);
                                                while (otp_reset_attempts != 0)
                                                {

                                                    printf("\nEnter the verification code: ");
                                                    scanf(" %s", entered_reset_otp);

                                                    if (strcmp(entered_reset_otp, reset_otp) == 0)
                                                    {
                                                        sleep(1);
                                                        system("clear");
                                                        system("echo Reseting...");
                                                        sleep(3);
                                                        system("clear");
                                                        sleep(2);
                                                        system("echo \"Hi $USER, Welcome to MasterKey App\"");
                                                        printf("\n\n");
                                                        sleep(1);
                                                        printf("              MasterKey\n");
                                                        printf("\"One Password for All Your Passwords...\"");
                                                        printf("\n\n");
                                                        sleep(4);
                                                        system("echo \"       © 2022 The Sudoers Club\"");
                                                        sleep(5);
                                                        system("clear");

                                                        reset();

                                                        printf("Done\n");
                                                        system("clear");
                                                        goto startup;
                                                        otp_reset_attempts = 0;
                                                        // system("sudo chmod 000 ../.temp/.otp.txt");
                                                        // system("sudo chmod 000 ../.mail/.mail.txt");
                                                    }
                                                    else
                                                    {
                                                        system("clear");
                                                        otp_reset_attempts--;
                                                        printf("Incorrect code. Try again?\n");
                                                        // sleep(1);
                                                        // system("sudo chmod 000 ../.temp/.otp.txt");
                                                        // system("sudo chmod 000 ../.mail/.mail.txt");
                                                    }
                                                }
                                                system("clear");
                                                printf("Too many incorrect attempts\nFailed to Reset the app!\n\n");
                                                // system("sudo chmod 000 ../.temp/.otp.txt");
                                                // system("sudo chmod 000 ../.mail/.mail.txt");
                                            }
                                            else
                                            {
                                                system("clear");
                                                printf("Error: Something went wrong.\n");
                                                printf("Please check your internet connection or try again later\n\n");
                                            }
                                        }
                                        else
                                        {
                                            system("clear");
                                            printf("Invalid Key! %d attempts left!\n\n", attempt - 1);
                                            attempt--;
                                            if (attempt > 0)
                                            {
                                                goto reset_password;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        printf("\nAbort!\n");
                                    }
                                    break;

                                case '4':
                                    // update
                                    system("clear");
                                    check_for_update();
                                    system("cd ../.script/ && chmod 500 ../.script/.update.sh && bash ../.script/.update.sh");
                                    break;

                                case '5':
                                    system("clear");
                                    printf("Note: Deleting the app will clear all your app data, MasterKey program files and packages from your system\n");
                                    printf("\nIf you will be reinstalling the app in future make sure to backup your data by exporting the passwords from - \n[3]Edit dictionary > [4]Backup & Restore > [1]Export passwords.\n");
                                    printf("\n\nAre you sure you want to continue [Y/n] : ");
                                    scanf(" %c", &ch_uninstall);

                                    ch_uninstall = tolower(ch_uninstall);

                                    if (ch_uninstall == 'y')
                                    {

                                        system("clear");
                                        system("echo \"We're sorry to see you go!\"");
                                        sleep(3);
                                        system("echo && echo \"Deleting MasterKey program files...\"");
                                        sleep(3);
                                        system("clear");
                                        system("rm -rf /home/$USER/Documents/.Program-Files/");
                                        system("sudo rm /usr/include/stded.h");
                                        system("sed -i -e '/masterkey/d' /home/$USER/.bashrc");
                                        system("rm /home/$USER/.run_masterkey.sh");
                                        sleep(1);
                                        system("clear");
                                        system("echo && echo deleting installed packages...");
                                        sleep(3);
                                        system("clear");
                                        system("echo && echo App successfully uninstalled!");
                                        sleep(3);
                                        system("clear");
                                        exit(1);
                                    }
                                    else
                                    {
                                        goto menu_4;
                                    }

                                    break;

                                default:
                                    printf("\nInvalid Input!\n");
                                    sleep(1);
                                    system("clear");
                                    goto menu_4;
                                    break;
                                }

                                printf("<-- Go back! [Y] : ");
                                fflush(stdin);
                                scanf("%c", &go_back);
                                getchar();
                                // printf("%c", go_back);
                                system("clear");
                                goto menu_4;

                                break;

                            default:
                                printf("\nInvalid Input!\n");
                                sleep(1);
                                system("clear");
                                goto menu;
                                break;
                            }
                        goback:
                            printf("<-- Go back to menu! [Y] : ");
                            fflush(stdin);
                            scanf("%c", &go_back);
                            getchar();
                            // printf("%c", go_back);
                            system("clear");

                            goto menu;

                            menu_attempts = 0;
                        }
                        system("clear");
                    }
                    else
                    {
                        click_img(); // clicking image of user in he/she enters wrong key

                        // timestamp
                        // system("sudo chmod 700 ../.temp/.time.txt");

                        system("time=$(date) && echo $time > ../.temp/.time.txt");
                        // system("sudo chmod 000 ../.temp/.time.txt");

                        suspect_bool = 1;
                        // system("sudo chmod 700 ../.temp/.suspect.txt");
                        FILE *suspect;
                        suspect = fopen("../.temp/.suspect.txt", "w");
                        fprintf(suspect, "%d", suspect_bool);
                        fclose(suspect);
                        // system("sudo chmod 000 ../.temp/.suspect.txt");

                        // setting limit
                        FILE *lim;
                        // system("sudo chmod 700 ../.temp/.limit.txt");
                        lim = fopen("../.temp/.limit.txt", "w+");

                        fscanf(lim, "%d", &limit);
                        limit++;
                        fprintf(lim, "%d", limit);
                        fclose(lim);
                        // system("sudo chmod 000 ../.temp/.limit.txt");

                        // sendmail
                        // system("sudo chmod 700 ../.mail/.mail.txt");
                        // system("sudo chmod 700 ../.temp/.time.txt");
                        system("../.script/.runSendMailScript.sh &");

                        // attempt message
                        printf("Invalid key! %d attempts left\n\n", menu_attempts - 1); // for user convience subtracting 1 from menu_attempts

                        menu_attempts--; // decrementing the attempts when pin is incorrect

                        if (menu_attempts == 1)
                        {
                            printf("Forgot key? [Y/n] : ");
                            scanf(" %c", &ch_forgot);

                            ch_forgot = tolower(ch_forgot);
                            if (ch_forgot == 'y')
                            {
                                system("clear");
                                printf("Select way to reset password\n\n");
                                printf("    [1] Send verification code\n");
                                printf("    [2] Recovery Questions\n");
                                printf("    [0] exit\n\n");
                                printf("Enter your choice [0-2] : ");
                                scanf(" %c", &ch_forgot_options);

                                switch (ch_forgot_options)
                                {
                                case '1':

                                    system("clear");

                                    if (system("wget -q --spider http://google.com;") == 0)
                                    {
                                        // system("sudo chmod  600 ../.temp/.otp.txt");
                                        // system("sudo chmod  600 ../.mail/.mail.txt");
                                        send_otp();

                                        int otp_attempts = 3;
                                        char entered_otp[100];
                                        char otp[10];

                                        FILE *rotr;
                                        rotr = fopen("../.temp/.otp.txt", "r");
                                        fscanf(rotr, " %s", otp);
                                        fclose(rotr);
                                        while (otp_attempts != 0)
                                        {

                                            printf("Enter the verification code: ");
                                            scanf(" %s", entered_otp);

                                            if (strcmp(entered_otp, otp) == 0)
                                            {
                                                sleep(1);
                                                reset_password();
                                                otp_attempts = 0;
                                                goto skip;
                                                // system("sudo chmod 000 ../.temp/.otp.txt");
                                                // system("sudo chmod 000 ../.mail/.mail.txt");
                                            }
                                            else
                                            {
                                                system("clear");
                                                otp_attempts--;
                                                printf("Incorrect code. Try again?\n\n");
                                                // sleep(1);
                                                // system("sudo chmod 000 ../.temp/.otp.txt");
                                                // system("sudo chmod 000 ../.mail/.mail.txt");
                                            }
                                        }
                                        system("clear");
                                        printf("Too many incorrect attempts\nFailed to reset password!\n");
                                        // system("sudo chmod 000 ../.temp/.otp.txt");
                                        // system("sudo chmod 000 ../.mail/.mail.txt");
                                    skip:
                                    }
                                    else
                                    {
                                        printf("Error: Something went wrong.\n");
                                        printf("Please check your internet connection and try again later\n");
                                        sleep(5);
                                        system("clear");
                                        lock();

                                        exit(1);
                                    }

                                    break;

                                case '2':
                                    system("clear");
                                    int r;
                                    forgot_password(&r);

                                    if (r == 1)
                                    {
                                        reset_password();
                                    }
                                    else
                                    {
                                        printf("\nFailed to reset password!\n");
                                    }
                                    break;

                                default:
                                    break;
                                }
                            }
                            else
                            {
                                system("clear");
                            }
                        }

                        // system("sudo chmod 000 ../.mail/.mail.txt");
                    }
                }
            }
        }
    }

    fclose(fp);
    // system("sudo chmod 000 ../.data/.password.txt");
    return 0;
}

// Functions

// Adds the new password to .passwords_list
void add_password()
{
    char choose_menu = 'y';
    while (choose_menu == 'y' || choose_menu == 'Y')
    {
        system("clear");
        // system("sudo chmod 700 ../.data/.passwords_list.txt");
        FILE *ptr;
        ptr = fopen("../.data/.passwords_list.txt", "a");
        char name[1000];
        char password[1000];

        printf("Note: Name will be stored as ( <name> --> <encrypted_password> );\n\n");
        printf("Enter a name for the password: ");
        scanf(" %[^\n]s", name);
        getchar();
        sleep(1);

        printf("Enter the password for %s: ", name);
        fflush(stdin);
        scanf(" %[^\n]s", password);

        // char *str = password;

        encrypt_string2(password);

        fputs(name, ptr);
        fprintf(ptr, " --> ");
        fputs(password, ptr);
        fprintf(ptr, "\n");

        printf("\nPassword successfully added to the dictionary!\n");
        sleep(2);
        system("clear");
        fclose(ptr);
        // system("sudo chmod 000 ../.data/.passwords_list.txt");
        printf("Do you want to add another password? [Y/n]: ");
        scanf("%s", &choose_menu);
        printf("\n");
    }
}

// clicks image when called
void click_img()
{
    // system("sudo apt install streamer");
    system("streamer -f jpeg -o .image.jpeg -q");
    system("mv .image.jpeg ../.temp/");
    system("clear");
}

// display passwords in list
void display_passwords_list()
{
    // system("sudo chmod 400 ../.data/.passwords_list.txt");
    FILE *ptr;
    ptr = fopen("../.data/.passwords_list.txt", "r");

    char whole_string[1000], c;
    int i = 0;

    while ((c = fgetc(ptr)) != EOF)
    {
        whole_string[i] = c;
        i++;
    }
    whole_string[i] = '\0';
    printf("**********************************************************************\n");
    puts(whole_string);
    printf("**********************************************************************\n");

    fclose(ptr);
    // system("sudo chmod 000 ../.data/.passwords_list.txt");
}

// search passwords
void search_password()
{
    // system("sudo chmod 400 ../.data/.passwords_list.txt");
    char passwords_list[5000];

    int ctr = 0;
    char search[1000];

    FILE *ptr;

    ptr = fopen("../.data/.passwords_list.txt", "r");

    char c;
    int i = 0;

    while ((c = fgetc(ptr)) != EOF)
    {
        passwords_list[i] = c;
        i++;
    }
    passwords_list[i] = '\0';
    fclose(ptr);

    printf("Search for password: ");
    scanf(" %s", search);

    char *res = strstr(passwords_list, search);

    if (res)
    {
        printf("\nMatched Password: ");
        while (isprint(res[ctr]))
        {
            putchar(res[ctr]);
            ctr++;
        }
        printf("\n\n");
    }
    else
    {
        printf("\n%s did not matched to any passwords in your dictionary\n\n", search);
    }
    // system("sudo chmod 000 ../.data/.passwords_list.txt");
}

// changes current password
char change_password(char *current_password)
{
    // system("sudo chmod 700 ../.data/.password.txt");
    char *new_password;
    int attempt = 3;
    char *entered_current_password;

    FILE *ptr;
    ptr = fopen("../.data/.password.txt", "w");

password:
    entered_current_password = getpass("Enter the current key: ");
    encrypt_string(entered_current_password);
    // puts(entered_current_password);

    // printf("\n********%d********\n", strcmp(entered_current_password, current_password));
    if (strcmp(entered_current_password, current_password) == 0)
    {
        new_password = getpass("Enter a new key: ");
        printf("\nKey successfully changed to: %s\n\n", new_password);
        encrypt_string(new_password);
        fprintf(ptr, "%s", new_password);
        attempt = 0;
    }
    else
    {
        click_img();
        printf("Invalid key! %d attempts left!\n\n", attempt - 1);
        attempt--;
        if (attempt > 0)
        {
            goto password;
        }
        else
        {
            encrypt_string(current_password);
            fprintf(ptr, "%s", current_password);
        }
    }

    // system("sudo chmod 000 ../.data/.password.txt");
    fclose(ptr);
}

// changes current mail
char change_mail(char *current_password)
{
    // system("sudo chmod 700 ../.data/.password.txt");
    int attempt = 3;
    char *entered_current_password;

    FILE *ptr;
    ptr = fopen("../.data/.password.txt", "r");

password:
    entered_current_password = getpass("Enter the key: ");
    encrypt_string(entered_current_password);
    // puts(entered_current_password);

    // printf("\n********%d********\n", strcmp(entered_current_password, current_password));
    if (strcmp(entered_current_password, current_password) == 0)
    {

        system("clear");
        // system("sudo chmod 700 ../.mail/.mail.txt");
        char mail[200];
        printf("Enter the new ID: ");
        scanf(" %[^\n]s", mail);
        FILE *mtr;
        mtr = fopen("../.mail/.mail.txt", "w");
        fprintf(mtr, "%s", mail);
        fclose(mtr);

        printf("\nEmail successfully changed to %s\n\n", mail);
        // system("sudo chmod 000 ../.mail/.mail.txt");
    }
    else
    {
        click_img();
        printf("Invalid key! %d attempts left!\n\n", attempt - 1);
        attempt--;
        if (attempt > 0)
        {
            goto password;
        }
    }

    // system("sudo chmod 000 ../.data/.password.txt");
    fclose(ptr);
}

// main menu interface
void display_menu()
{
    printf("**************************************************************************\n");
    printf("Menu:\n");
    printf("[1] Search Password \n");
    printf("[2] Decrypt password\n");
    printf("[3] Edit Dictionary \n");
    // printf("[4] View Suspect's Picture\n");
    printf("[4] Settings\n");
    printf("[0] Exit\n");
    printf("**************************************************************************\n");
}

// Reads the current password from file
char read_password(char *main_password)
{
    // system("sudo chmod 700 ../.data/.password.txt");
    FILE *ptr;
    ptr = fopen("../.data/.password.txt", "r");
    fscanf(ptr, " %[^\n]s", main_password);
    fclose(ptr);
    // printf("%s\n", main_password);

    // return main_password;
    // system("sudo chmod 000 ../.data/.password.txt");
}

// opens clicked image
void view_suspect_img()
{
    system("cd .. && if [ -f .image.jpeg ]; then chmod 600 .image.jpeg; fi;");
}

// set new password, mail, etc. after reset or new login
void set_new_password()
{
    system("clear");

    // system("sudo chmod 700 ../.data/.password.txt");
    char new_key[1000];
    FILE *ptr;
    ptr = fopen("../.data/.password.txt", "w");
    printf("Set a master key for your passwords.\n");
    printf("Enter a key: ");
    scanf(" %s", new_key);
    // system("echo && echo Your key has been successfully set as:");
    encrypt_string(new_key);
    fprintf(ptr, "%s", new_key);
    fclose(ptr);
    sleep(2);
    // system("sudo chmod 000 ../.data/.password.txt");

    system("clear");

    // system("sudo chmod 700 ../.mail/.mail.txt");
    char mail[200];
    printf("Your Email ID is used for sending you verification codes, security alerts for invalid login attempts, etc.\n");
    printf("Enter your Email ID: ");
    scanf(" %[^\n]s", mail);
    FILE *mtr;
    mtr = fopen("../.mail/.mail.txt", "w");
    fprintf(mtr, "%s", mail);
    fclose(mtr);
    system("echo && echo Email successfully saved");
    sleep(2);
    // system("sudo chmod 000 ../.mail/.mail.txt");

    // system("sudo chmod 700 ../.data/.forgot_password.txt");
    FILE *fp;
    fp = fopen("../.data/.forgot_password.txt", "w");

    char question1[1000];
    char question2[1000];
    char question3[1000];

    system("clear");

    printf("Password Recovery Questions;\n\n");

    printf("1. What was your favorite subject in high school?\n");
    printf("-> ");
    fflush(stdin);
    scanf(" %[^\n]s", question1);
    getchar();
    int i, len = 0, j;

    // Calculating length of the array
    len = sizeof(question1) / sizeof(question1[0]);

    // Checks for space character in array if its there then ignores it and swap input1[i] to input1[i+1];
    for (i = 0; i < len; i++)
    {
        if (question1[i] == ' ')
        {
            for (j = i; j < len; j++)
            {
                question1[j] = question1[j + 1];
            }
            len--;
        }
    }
    encrypt_string(question1);
    fputs(question1, fp);
    fputs("\n", fp);

    printf("\n2. What is your mother's maiden name?\n");
    printf("-> ");
    fflush(stdin);
    scanf(" %[^\n]s", question2);
    getchar();
    len = 0;

    // Calculating length of the array
    len = sizeof(question2) / sizeof(question2[0]);

    // Checks for space character in array if its there then ignores it and swap input1[i] to input1[i+1];
    for (i = 0; i < len; i++)
    {
        if (question1[i] == ' ')
        {
            for (j = i; j < len; j++)
            {
                question2[j] = question2[j + 1];
            }
            len--;
        }
    }
    encrypt_string(question2);
    fputs(question2, fp);
    fputs("\n", fp);

    printf("\n3. What is the name of the town where you were born?\n");
    printf("-> ");
    fflush(stdin);
    scanf(" %[^\n]s", question3);
    getchar();
    len = 0;

    // Calculating length of the array
    len = sizeof(question3) / sizeof(question3[0]);

    // Checks for space character in array if its there then ignores it and swap input1[i] to input1[i+1];
    for (i = 0; i < len; i++)
    {
        if (question3[i] == ' ')
        {
            for (j = i; j < len; j++)
            {
                question3[j] = question3[j + 1];
            }
            len--;
        }
    }
    encrypt_string(question3);
    fputs(question3, fp);
    fputs("\n", fp);

    fclose(fp);
    // system("sudo chmod 000 ../.data/.forgot_password.txt");
    printf("\nSetup completed!\n");
    sleep(3);
    exiting();
}

// Resets App
void reset()
{
    // system("sudo chmod 700 ../.data/.passwords_list.txt");
    FILE *list;
    list = fopen("../.data/.passwords_list.txt", "w");
    fclose(list);
    // system("sudo chmod 000 ../.data/.passwords_list.txt");

    // system("sudo chmod 700 ../.data/.password.txt");
    FILE *pin;
    pin = fopen("../.data/.password.txt", "w");
    fclose(pin);
    // system("sudo chmod 000 ../.data/.password.txt");
}

// Forgot Password Option
int forgot_password(int *r)
{
    system("clear");
    // system("sudo chmod 700 ../.data/.forgot_password.txt");
    FILE *ptr;
    ptr = fopen("../.data/.forgot_password.txt", "r");

    char ans[1000];
    int k = 0;

    char input1[1000];
    char input2[1000];
    char input3[1000];

    char answer1[1000];
    char answer2[1000];
    char answer3[1000];
    // // char answer2[50];
    // // char answer3[50];

    // printf("\nPassword Recovery Questions;\n\n");
    printf("1. What was your favorite subject in high school?\n");
    printf("-> ");
    fflush(stdin);
    scanf(" %[^\n]s", input1);
    getchar();
    int i, len = 0, j;

    // Calculating length of the array
    len = sizeof(input1) / sizeof(input1[0]);

    // Checks for space character in array if its there then ignores it and swap input1[i] to input1[i+1];
    for (i = 0; i < len; i++)
    {
        if (input1[i] == ' ')
        {
            for (j = i; j < len; j++)
            {
                input1[j] = input1[j + 1];
            }
            len--;
        }
    }

    encrypt_string(input1);
    // printf("\n%s\n", input1);

    printf("\n2. What is your mother's maiden name?\n");
    printf("-> ");
    fflush(stdin);
    scanf(" %[^\n]s", input2);
    getchar();
    len = 0;

    // Calculating length of the array
    len = sizeof(input2) / sizeof(input2[0]);

    // Checks for space character in array if its there then ignores it and swap input1[i] to input1[i+1];
    for (i = 0; i < len; i++)
    {
        if (input2[i] == ' ')
        {
            for (j = i; j < len; j++)
            {
                input2[j] = input2[j + 1];
            }
            len--;
        }
    }

    encrypt_string(input2);
    // printf("\n%s\n", input2);

    printf("\n3. What is the name of the town where you were born?\n");
    printf("-> ");
    fflush(stdin);
    scanf(" %[^\n]s", input3);
    getchar();
    len = 0;

    // Calculating length of the array
    len = sizeof(input3) / sizeof(input3[0]);

    // Checks for space character in array if its there then ignores it and swap input1[i] to input1[i+1];
    for (i = 0; i < len; i++)
    {
        if (input3[i] == ' ')
        {
            for (j = i; j < len; j++)
            {
                input3[j] = input3[j + 1];
            }
            len--;
        }
    }

    encrypt_string(input3);
    // printf("\n%s\n", input3);

    while (fgets(ans, sizeof(ans), ptr))
    {
        if (k == 0)
        {
            strcpy(answer1, ans);
        }
        else if (k == 1)
        {
            strcpy(answer2, ans);
        }
        else if (k == 2)
        {
            strcpy(answer3, ans);
        }

        k++;
    }

    // printf("\n********%d*********\n", strcmp(answer1, input1));
    // printf("\n********%d*********\n", strcmp(answer2, input2));
    // printf("\n********%d*********\n", strcmp(answer3, input3));

    if (strcmp(answer1, input1) == 10 && strcmp(answer2, input2) == 10 && strcmp(answer3, input3) == 10)
    {
        *r = 1;
    }
    else
    {
        *r = 0;
    }

    fclose(ptr);
    // system("sudo chmod 000 ../.data/.forgot_password.txt");
}

// Reset password after forgetting the password
void reset_password()
{
    system("clear");
    // system("cd /home/$USER/Documents/Downloads/passwords");
    // system("sudo chmod 700 ../.data/.password.txt");
    FILE *ptr;
    char *new_key;
    ptr = fopen("../.data/.password.txt", "w");
    printf("Setting new Key Required!\n\n");
    new_key = getpass("Enter a new key: ");
    encrypt_string(new_key);
    fprintf(ptr, "%s", new_key);
    printf("\nSetting new password...\n");
    sleep(1);
    system("echo Done!");
    printf("\n");
    system("echo exiting...");
    sleep(2);
    system("clear");
    fclose(ptr);
    // system("sudo chmod 000 ../.data/.password.txt");
}

// Imports the passwords to app
void import_passwords()
{
    system("clear");
    printf("Note: This will overwrite all the existing data in your dictionary.\n\n");
    if (system("read -p 'Enter the file path: ' filePath && cp -f $filePath /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt.gpg && echo $(cat /home/$USER/Documents/.Program-Files/.MasterKey/.data/.password.txt) | gpg -d --batch --passphrase-fd 0 /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt.gpg > /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt && rm /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt.gpg;") == 0)
    {

        usleep(500000);
        system("clear");
        sleep(1);

        printf("\e[?25l");

        printf("Importing [>                    ]    0%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Importing [==>                  ]    10%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Importing [====>                ]    20%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Importing [======>              ]    30%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Importing [========>            ]    40%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Importing [==========>          ]    50%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Importing [============>        ]    60%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Importing [==============>      ]    70%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Importing [================>    ]    80%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Importing [==================>  ]    90%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Importing [====================>]    100%c \n\n", 37);
        usleep(500000);

        system("clear");
        printf("Passwords successfully imported\n");

        printf("\e[?25h");
    }
}

// export the passwords_list as txt file
void export_passwords()
{
    // system("sudo chmod 700 ../.data/.passwords_list.txt");

    if (system("echo $(cat /home/$USER/Documents/.Program-Files/.MasterKey/.data/.password.txt) | gpg -c --batch --passphrase-fd 0 /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt") == 0 && system("cp -f ../.data/.passwords_list.txt.gpg /home/$USER/Documents/passwords.txt.gpg && rm -f /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt.gpg;") == 0)
    {
        system("clear");

        printf("\e[?25l");

        printf("Exporting [>                    ]    0%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Exporting [==>                  ]    10%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Exporting [====>                ]    20%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Exporting [======>              ]    30%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Exporting [========>            ]    40%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Exporting [==========>          ]    50%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Exporting [============>        ]    60%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Exporting [==============>      ]    70%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Exporting [================>    ]    80%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Exporting [==================>  ]    90%c \n", 37);
        usleep(300000);
        system("clear");

        printf("Exporting [====================>]    100%c \n\n", 37);
        usleep(500000);

        printf("\e[?25h");

        system("echo Passwords successfully exported to /home/$USER/Documents/passwords.txt.gpg");

        sleep(1);
    }
    // system("sudo chmod 000 ../.data/.passwords_list.txt");
}

// timer for try again later
void try_again()
{
    printf("\e[?25l");
    int n;
    FILE *ttr;
    // system("sudo chmod 700 ../.temp/.timer.txt");
    ttr = fopen("../.temp/.timer.txt", "r");
    fscanf(ttr, "%d", &n);
    fclose(ttr);
    // system("sudo chmod 000 ../.temp/.timer.txt");

    if (n <= 1)
    {
        n = 60;
    }

    for (int i = n; i >= 1; i--)
    {
        printf("Try again in %d sec\n", i);
        sleep(1);
        system("clear");
        FILE *ptr;
        // system("sudo chmod 700 ../.temp/.timer.txt");
        ptr = fopen("../.temp/.timer.txt", "w");
        fprintf(ptr, "%d", i);
        fclose(ptr);
        // system("sudo chmod 000 ../.temp/.timer.txt");
    }

    printf("\e[?25h");
}

// sends random 6 digit otp
void send_otp()
{
    // system("sudo chmod 600 ../.temp/.otp.txt");

    FILE *wotr;
    wotr = fopen("../.temp/.otp.txt", "w");
    fclose(wotr);

    int lower = 1, upper = 9, count = 6;
    int i;

    FILE *otr;
    otr = fopen("../.temp/.otp.txt", "w");

    for (i = 0; i < count; i++)
    {
        int num = (rand() % (upper - lower + 1)) + lower;
        // printf("%d", num);
        fprintf(otr, "%d", num);
    }
    fclose(otr);

    // system("sudo chmod 700 ../.mail/.mail.txt");
    system("../.script/.runSendOtp.sh ");

    // system("sudo chmod 000 ../.temp/.otp.txt");
    // system("sudo chmod 000 ../.mail/.mail.txt");
}

// locks files when called
void lock()
{
    system("sudo chown root /home/$USER/Documents/.Program-Files/.MasterKey/.data/ -R");
    // system("sudo chmod 000 /home/$USER/Documents/.Program-Files/.MasterKey/.data/ -R");
    system("sudo chown root /home/$USER/Documents/.Program-Files/.MasterKey/.mail/ -R");
    // system("sudo chmod 000 /home/$USER/Documents/.Program-Files/.MasterKey/.mail/ -R");
    system("sudo chown root /home/$USER/Documents/.Program-Files/.MasterKey/.script/ -R");
    // system("sudo chmod 000 /home/$USER/Documents/.Program-Files/.MasterKey/.script/ -R");
    system("sudo chown root /home/$USER/Documents/.Program-Files/.MasterKey/.temp/ -R");
}

// unlocks files when called
void unlock()
{
    system("cd /home/$USER/Documents/.Program-Files/.MasterKey/.main -R");
    system("sudo chown $USER /home/$USER/Documents/.Program-Files/.MasterKey/.data/ -R");
    // system("sudo chmod 700 /home/$USER/Documents/.Program-Files/.MasterKey/.data/ -R");
    system("sudo chown $USER /home/$USER/Documents/.Program-Files/.MasterKey/.mail/ -R");
    // system("sudo chmod 700 /home/$USER/Documents/.Program-Files/.MasterKey/.mail/ -R");
    system("sudo chown $USER /home/$USER/Documents/.Program-Files/.MasterKey/.script/ -R");
    system("sudo chmod 700 /home/$USER/Documents/.Program-Files/.MasterKey/ -R");
    system("sudo chown $USER /home/$USER/Documents/.Program-Files/.MasterKey/.temp/ -R");
}

// starting app animation
void start()
{
    system("clear");

    printf("\e[?25l");

    printf("-MasterKey-\n");
    printf("\n");
    usleep(250000);
    system("clear");

    printf("-MasterKey-\n");
    printf(".\n");
    usleep(250000);
    system("clear");

    printf("-MasterKey-\n");
    printf("..\n");
    usleep(250000);
    system("clear");

    printf("-MasterKey-\n");
    printf("...\n");
    usleep(250000);
    system("clear");

    printf("-MasterKey-\n");
    printf(" ..\n");
    usleep(250000);
    system("clear");

    printf("-MasterKey-\n");
    printf("  .\n");
    usleep(250000);
    system("clear");

    printf("-MasterKey-\n");
    printf("\n");
    usleep(250000);
    system("clear");

    printf("\e[?25h");
}

// exit animation
void exiting()
{
    system("clear");

    printf("\e[?25l");

    printf("exiting...\n");
    sleep(1);

    printf("\e[?25h");
    system("clear");

    lock();

    exit(1);
}

// please wait
void check_for_update()
{
    system("clear");

    printf("\e[?25l");

    printf("Checking for updates\n");
    usleep(250000);
    system("clear");

    printf("Checking for updates.\n");
    usleep(250000);
    system("clear");

    printf("Checking for updates..\n");
    usleep(250000);
    system("clear");

    printf("Checking for updates...\n");
    usleep(250000);
    system("clear");

    printf("Checking for updates ..\n");
    usleep(250000);
    system("clear");

    printf("Checking for updates  .\n");
    usleep(250000);
    system("clear");

    printf("Checking for updates\n\n");
    usleep(250000);
    // system("clear");

    printf("\e[?25h");
}

// please wait
void please_wait()
{
    system("clear");

    printf("\e[?25l");

    printf("Please wait\n");
    usleep(250000);
    system("clear");

    printf("Please wait.\n");
    usleep(250000);
    system("clear");

    printf("Please wait..\n");
    usleep(250000);
    system("clear");

    printf("Please wait...\n");
    usleep(250000);
    system("clear");

    printf("Please wait ..\n");
    usleep(250000);
    system("clear");

    printf("Please wait  .\n");
    usleep(250000);
    system("clear");

    printf("Please wait\n\n");
    usleep(250000);
    // system("clear");

    printf("\e[?25h");
}
