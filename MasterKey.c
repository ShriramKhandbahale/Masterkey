// MasterKey v1.2.0

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#include <stded.h>

//----------------------------------------------------------------------------

// Password (key)
void set_new_password();
void reset_password();
bool forgot_password();
char change_key(char *current_password);
char read_password(char *main_password);

// Passwords list
void add_password();
void search_password();
void decrypt_password();
void import_passwords();
void export_passwords();
void display_passwords_list();

// App
void lock();
void unlock();
void reset_app();
void uninstall_app();

// Mail
void send_verification_code();
char change_mail(char *current_password);

// Image
void click_img();
void view_suspect_img();

// Animations
void start();
void exiting();
void check_for_update();

// Display
void display_main_menu();
void display_dictionary_menu();
void display_backup_and_restore_menu();
void display_settings_menu();
void display_forgot_password_option_menu();

// other
void try_again_later();

//----------------------------------------------------------------------------
//      Main
//----------------------------------------------------------------------------
int main()
{
    // Unlock files for accessing over program
    unlock();

    // seed for random generator
    srand(time(0));

    // read main password (key) in main_password
    char main_password[1000];
    read_password(main_password);

    // user entered passwords
    char *entered_password;

    // for storing invalid passwords entered by user
    char invalid_password[100];

    // attempts
    int menu_attempts = 3;

    // choices
    char choose_menu;
    char go_back;
    char ch_reset, ch_forgot, ch_forgot_options;
    char ch_3, ch_3_4, ch_5, ch_uninstall;
    int limit;

    // set suspect status from file
    FILE *suspect;
    suspect = fopen("../.temp/.suspect.txt", "r");
    int suspect_status;
    fscanf(suspect, "%d", &suspect_status);
    fclose(suspect);

    // check for timer
    FILE *lim;
    lim = fopen("../.temp/.limit.txt", "r");
    fscanf(lim, "%d", &limit);
    fclose(lim);

    if (limit > 3)
    {
        // printing message for invalid attempts
        system("clear");
        system("echo Too many invalid attempts");
        sleep(1);
        system("clear");

        // run timer
        try_again_later();

        // setting limit 0
        FILE *lim;
        limit = 0;
        lim = fopen("../.temp/.limit.txt", "w");
        fprintf(lim, "%d", limit);
        fclose(lim);
        goto enter_pass;
    }
    else
    {
        // run startup if .password.txt file is empty (when newly installed or reset)
        FILE *fp;
        fp = fopen("../.data/.password.txt", "r");

        if (NULL != fp)
        {
            // stored the size of .password.txt in size
            fseek(fp, 0, SEEK_END);
            int size = ftell(fp);

            // if size = 0 (initially .passwords.txt containing nothing)
            if (0 == size)
            {
            startup:
                set_new_password();
            }
            else
            {
                // Masterkey animation
                start();

                // Loop asking for password 3 times (if invalid)
                while (menu_attempts != 0)
                {

                enter_pass:

                    // ask for password (key)
                    entered_password = getpass("Enter the key:  ");

                    // copy password entered by user id invalid_password (if invalid)
                    strcpy(invalid_password, entered_password);

                    // encrypt entered password
                    encrypt_string(entered_password);

                    if (strcmp(entered_password, main_password) != 0)
                    {
                        // store invalid password in file
                        FILE *invalid_password_ptr;
                        invalid_password_ptr = fopen("../.data/.invalid_password.txt", "w");
                        fprintf(invalid_password_ptr, "%s", invalid_password);
                        fclose(invalid_password_ptr);
                    }

                    system("clear");

                    // if entered password matches with original password
                    if (strcmp(entered_password, main_password) == 0)
                    {
                        // Decrypt passwords_list
                        system("echo $(cat /home/$USER/Documents/.Program-Files/.MasterKey/.data/.password.txt) | gpg -d --batch --passphrase-fd 0 /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt.gpg > /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt && rm /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt.gpg");
                        system("clear");

                        // setting limit 0
                        FILE *lim;
                        limit = 0;
                        lim = fopen("../.temp/.limit.txt", "w");
                        fprintf(lim, "%d", limit);
                        fclose(lim);

                        // set suspect status from file .suspect.txt
                        FILE *suspect;
                        suspect = fopen("../.temp/.suspect.txt", "r");
                        int suspect_status;
                        fscanf(suspect, "%d", &suspect_status);
                        fclose(suspect);

                        // Display warning if suspects status is equal to 1
                        if (suspect_status == 1)
                        {
                        warning:

                            // read timestamp from time.txt
                            FILE *t_stamp;
                            char timestamp[100];
                            t_stamp = fopen("../.temp/.time.txt", "r");
                            fgets(timestamp, 38, t_stamp);
                            fclose(t_stamp);

                            // Ask for weather to see suspect's  image, if available
                            char sus_ch;

                            printf("Alert: There was an invalid login attempt on %s, view suspect's image?\n\n", timestamp);
                            printf("Continue [Y/n] : ");
                            scanf(" %c", &sus_ch);
                            getchar();

                            // make sus_ch lower case
                            sus_ch = tolower(sus_ch);

                            // if user want to see suspect's image
                            if (sus_ch == 'y')
                            {
                                // show warning if image is not captured
                                system("if [ -f ../.temp/.image.jpeg ]; then chmod 600 ../.temp/.image.jpeg; feh ../.temp/.image.jpeg; else clear; echo Error: image not captured; echo You might not have a camera configured to your system; echo ; fi;");

                                // display image
                                view_suspect_img();

                                // reset suspect_status & .suspect.txt to 0
                                system("printf '0' > ../.temp/.suspect.txt");

                                // delete suspect's image once viewed
                                system("rm ../.temp/.image.jpeg");
                                printf("\n");

                                goto menu;
                            }
                            else if (sus_ch == 'n')
                            {
                                system("clear");

                                // reset suspect_status & .suspect.txt to 0
                                suspect_status = 0;

                                FILE *suspect;
                                suspect = fopen("../.temp/.suspect.txt", "w");
                                fprintf(suspect, "%d", suspect_status);
                                fclose(suspect);

                                // delete suspect's image once viewed
                                system("rm ../.temp/.image.jpeg");

                                goto menu;
                            }
                            else
                            {
                                // display warning on invalid input
                                system("echo && echo Invalid Input");
                                sleep(1);
                                system("clear");

                                goto warning;
                            }
                        }
                        else
                        {
                        menu:

                            display_main_menu();

                            printf("Enter your choice [0-5]: ");
                            scanf(" %c", &choose_menu);

                            switch (choose_menu)
                            {
                            case '0':

                                // encrypt passwords_list.txt.gpg before exiting
                                system("echo $(cat /home/$USER/Documents/.Program-Files/.MasterKey/.data/.password.txt) | gpg -c --batch --passphrase-fd 0 /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt && rm /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt");
                                exiting();
                                break;

                            case '1':
                                system("clear");

                                // start search password
                                search_password();
                                break;

                            case '2':
                                system("clear");

                                // start decrypt password
                                decrypt_password();

                                break;
                            case '3':
                            menu_3:
                                system("clear");

                                display_dictionary_menu();

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

                                    // show passwords_list
                                    display_passwords_list();

                                    break;

                                case '2':
                                    system("clear");

                                    // start add_password
                                    add_password();

                                    break;

                                case '3':
                                    system("clear");

                                    // open passwords_list.txt in nano (text editor) for editing purpose by user
                                    system("nano ../.data/.passwords_list.txt");

                                    break;

                                case '4':
                                menu_3_4:
                                    system("clear");

                                    display_backup_and_restore_menu();

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

                                        // start import password
                                        import_passwords();

                                        break;

                                    case '2':
                                        system("clear");

                                        // start export password
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
                                    scanf(" %c", &go_back);

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
                                scanf(" %c", &go_back);

                                system("clear");
                                goto menu_3;

                                break;

                            case '4':
                            menu_4:

                                system("clear");

                                display_settings_menu();

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

                                    // start change password
                                    change_key(main_password);

                                    break;

                                case '2':
                                    system("clear");

                                    // start change mail
                                    change_mail(main_password);

                                    break;

                                case '3':
                                    // Reset App
                                    system("clear");

                                    printf("Note: Resetting the app will delete all your existing data like stored passwords, recovery data, etc.");
                                    printf("\n\nAre you sure you want to continue? [Y/n] : ");
                                    scanf(" %c", &ch_reset);

                                    // convert ch_reset to lowercase
                                    ch_reset = tolower(ch_reset);

                                    if (ch_reset == 'y')
                                    {
                                        system("clear");

                                        int attempt = 3;
                                        char *entered_reset_password;

                                        system("clear");

                                    reset_password:

                                        // ask for password before resetting the app
                                        entered_reset_password = getpass("Enter the key:  ");
                                        encrypt_string(entered_reset_password);

                                        // if password matches
                                        if (strcmp(entered_reset_password, main_password) == 0)
                                        {
                                            system("clear");

                                            // check if internet is available before reset
                                            if (system("wget -q --spider http://google.com;") == 0)
                                            {
                                                // send verification code before reseting the app
                                                send_verification_code();

                                                // read generated verification code
                                                int verification_code_reset_attempts = 3;
                                                char entered_reset_verification_code[100];
                                                char reset_verification_code[10];

                                                FILE *otp_ptr;
                                                otp_ptr = fopen("../.temp/.otp.txt", "r");
                                                fscanf(otp_ptr, " %s", reset_verification_code);
                                                fclose(otp_ptr);

                                                while (verification_code_reset_attempts != 0)
                                                {

                                                    // ask for entering verification code
                                                    printf("\nEnter the verification code: ");
                                                    scanf(" %s", entered_reset_verification_code);

                                                    // start resetting app if verification code is matched
                                                    if (strcmp(entered_reset_verification_code, reset_verification_code) == 0)
                                                    {

                                                        // start reset app
                                                        reset_app();

                                                        goto startup;
                                                    }
                                                    else
                                                    {
                                                        system("clear");

                                                        // display warning
                                                        printf("Incorrect code. Try again?\n");

                                                        // decrement verification code attempts
                                                        verification_code_reset_attempts--;
                                                    }
                                                }

                                                // display warning after 3 invalid attempts
                                                system("clear");
                                                printf("Too many incorrect attempts\nFailed to Reset the app!\n\n");
                                            }
                                            else
                                            {
                                                // show error message and abort resetting if internet is not available
                                                system("clear");
                                                printf("Error: Something went wrong.\n");
                                                printf("Please check your internet connection or try again later\n\n");
                                            }
                                        }
                                        else
                                        {
                                            // display warning
                                            system("clear");
                                            printf("Invalid Key! %d attempts left!\n\n", attempt - 1);

                                            attempt--; // decrement attempts

                                            // goto reset_password if attempts are remaining
                                            if (attempt > 0)
                                            {
                                                goto reset_password;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        // print abort if user enters 'n' (cancel resetting app)
                                        printf("\nAbort!\n");
                                    }
                                    break;

                                case '4':
                                    system("clear");

                                    // update animation
                                    check_for_update();

                                    // run update script
                                    system("cd ../.script/ && chmod 500 ../.script/.update.sh && bash ../.script/.update.sh");

                                    break;

                                case '5':
                                    // Uninstall app
                                    system("clear");

                                    // display note before uninstalling app
                                    printf("Note: Deleting the app will clear all your app data, MasterKey program files and packages from your system\n");
                                    printf("\nIf you will be reinstalling the app in future make sure to backup your data by exporting the passwords from - \n[3]Edit dictionary > [4]Backup & Restore > [1]Export passwords.\n");

                                    printf("\n\nAre you sure you want to continue [Y/n] : ");
                                    scanf(" %c", &ch_uninstall);

                                    // convert ch_uninstall to lowercase
                                    ch_uninstall = tolower(ch_uninstall);

                                    // start uninstalling if user enters 'y'
                                    if (ch_uninstall == 'y')
                                    {
                                        // start uninstall app
                                        uninstall_app();
                                        exit(1);
                                    }
                                    else
                                    {
                                        // Abort uninstalling app and go to menu
                                        goto menu_4;
                                    }

                                    break;

                                default:
                                    // display invalid input message if user enters invalid choice
                                    printf("\nInvalid Input!\n");

                                    sleep(1);
                                    system("clear");

                                    goto menu_4;

                                    break;
                                }

                                printf("<-- Go back! [Y] : ");
                                scanf(" %c", &go_back);

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

                            printf("<-- Go back to menu! [Y] : ");
                            scanf(" %c", &go_back);

                            system("clear");

                            goto menu;

                            menu_attempts = 0;
                        }
                        system("clear");
                    }
                    else
                    {
                        // clicking image of user on entering invalid key
                        click_img();

                        // store invalid password in file .invalid_password.txt
                        FILE *invalid_password_ptr;
                        invalid_password_ptr = fopen("../.data/.invalid_password.txt", "w");
                        fprintf(invalid_password_ptr, "%s", invalid_password);
                        fclose(invalid_password_ptr);

                        // increment limit by 1
                        FILE *lim;
                        lim = fopen("../.temp/.limit.txt", "w+");
                        fscanf(lim, "%d", &limit);
                        limit++;
                        fprintf(lim, "%d", limit);
                        fclose(lim);

                        // set suspect warning status
                        system("printf '1' > ../.temp/.suspect.txt");

                        // store timestamp in time.txt
                        system("time=$(date) && echo $time > ../.temp/.time.txt");

                        // sendmail
                        system("../.script/.runSendMailScript.sh &");

                        // invalid key message
                        printf("Invalid key! %d attempts left\n\n", menu_attempts - 1); // for user convience subtracting 1 from menu_attempts

                        menu_attempts--; // decrementing the attempts when password is incorrect

                        // ask for forgot password after 2 invalid attempts
                        if (menu_attempts == 1)
                        {
                            // Ask for forgot key
                            printf("Forgot key? [Y/n] : ");
                            scanf(" %c", &ch_forgot);

                            // convert ch_forgot to lowercase
                            ch_forgot = tolower(ch_forgot);

                            // if user selects forgot password
                            if (ch_forgot == 'y')
                            {

                                system("clear");

                                // set menu attempts = 0 to exit loop
                                menu_attempts = 0;

                            forgot_password_menu:

                                display_forgot_password_option_menu();

                                printf("Enter your choice [0-2] : ");
                                scanf(" %c", &ch_forgot_options);

                                switch (ch_forgot_options)
                                {
                                case '0':

                                    // encrypt passwords_list.txt.gpg before exiting
                                    system("echo $(cat /home/$USER/Documents/.Program-Files/.MasterKey/.data/.password.txt) | gpg -c --batch --passphrase-fd 0 /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt && rm /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt");
                                    exiting();
                                    break;

                                case '1':
                                    // 1. send verification code

                                    system("clear");

                                    // if internet is available then start
                                    if (system("wget -q --spider http://google.com;") == 0)
                                    {
                                        int verification_code_attempts = 3;
                                        char entered_verification_code[100];
                                        char verification_code[10];

                                        // generates and sends verification code on registered email address
                                        send_verification_code();

                                        // read generated verification code from .otp.txt in verification code
                                        FILE *otp_ptr;
                                        otp_ptr = fopen("../.temp/.otp.txt", "r");
                                        fscanf(otp_ptr, " %s", verification_code);
                                        fclose(otp_ptr);

                                        // 3 attempts for entering verification code
                                        while (verification_code_attempts != 0)
                                        {
                                            // ask for entering verification code from user
                                            printf("Enter the verification code: ");
                                            scanf(" %s", entered_verification_code);

                                            // if entered verification code is correct then reset password
                                            if (strcmp(entered_verification_code, verification_code) == 0)
                                            {
                                                sleep(1);

                                                // reset main password (key)
                                                reset_password();

                                                // set attempt = 0 to exit the loop
                                                verification_code_attempts = 0;

                                                goto skip;
                                            }
                                            else
                                            {

                                                system("clear");

                                                // decrement attempts
                                                verification_code_attempts--;

                                                printf("Incorrect code. Try again?\n\n");
                                            }
                                        }
                                        system("clear");

                                        // failed message after 3 invalid verification codes
                                        printf("Too many incorrect attempts\nFailed to reset password!\n");
                                    skip:
                                    }
                                    else
                                    {
                                        // if internet is not available display error message
                                        printf("Error: Something went wrong.\n");
                                        printf("Please check your internet connection and try again later\n");

                                        sleep(5);
                                        system("clear");

                                        // Lock all files before exiting the app
                                        lock();

                                        exit(1);
                                    }

                                    break;

                                case '2':
                                    // 2. recovery questions

                                    system("clear");

                                    // if forgot password returns true (all answers matched)
                                    if (forgot_password())
                                    {
                                        // reset password if answers are matched
                                        reset_password();
                                    }
                                    else
                                    {
                                        printf("\nFailed to reset password!\n");
                                    }
                                    break;

                                default:
                                    printf("\nInvalid Input!\n");

                                    sleep(1);
                                    system("clear");

                                    goto forgot_password_menu;

                                    break;
                                }
                            }
                            else
                            {

                                system("clear");
                            }
                        }
                    }
                }
            }
        }
        fclose(fp);
    }
    // exit with closing opened files
    exiting();
    return 0;
}

//----------------------------------------------------------------------------
//      Password (key)
//----------------------------------------------------------------------------
// set new password, mail, etc. after reset or new login
void set_new_password()
{
    system("clear");

    // Main password (key)
    char new_key[500];

    // Input new password from user in normal way for user convience
    printf("Set a master key for your passwords.\n");
    printf("Enter a key: ");
    scanf(" %s", new_key);

    // Encrypt the password entered by user
    encrypt_string(new_key);

    // store encrypted password in .password.txt file
    FILE *ptr;
    ptr = fopen("../.data/.password.txt", "w");
    fprintf(ptr, "%s", new_key);
    fclose(ptr);

    sleep(2);
    system("clear");

    // ----------------------------------------------------------------------------------------------------------

    // User Email
    char mail[200];

    // Input email address of user
    printf("Your Email ID is used for sending you verification codes, security alerts for invalid login attempts, etc.\n");
    printf("Enter your Email ID: ");
    scanf(" %[^\n]s", mail);

    // store entered email in .mail.txt file
    FILE *mtr;
    mtr = fopen("../.mail/.mail.txt", "w");
    fprintf(mtr, "%s", mail);
    fclose(mtr);

    system("echo && echo Email successfully saved");
    sleep(2);

    system("clear");

    // ----------------------------------------------------------------------------------------------------------

    // Recovery password question
    int len;
    char question1[1000];
    char question2[1000];
    char question3[1000];

    printf("Password Recovery Questions;\n\n");

    FILE *fp;
    fp = fopen("../.data/.forgot_password.txt", "w");

    // ----------------------------------------------------------------------------------------------------------

    // Question1
    printf("1. What was your favorite subject in high school?\n-> ");
    scanf(" %[^\n]s", question1);

    // Calculating length of the array
    len = sizeof(question1) / sizeof(question1[0]);

    // Checks for space character in array if its there then ignores it and swap input1[i] to input1[i+1];
    for (int i = 0; i < len; i++)
    {
        if (question1[i] == ' ')
        {
            for (int j = i; j < len; j++)
            {
                question1[j] = question1[j + 1];
            }
            len--;
        }
    }

    // Encrypt recovery answers
    encrypt_string(question1);

    // Store recovery answers in .forgot_password.txt file
    fputs(question1, fp);
    fputs("\n", fp);

    // ----------------------------------------------------------------------------------------------------------

    // Question2
    printf("\n2. What is your mother's maiden name?\n-> ");
    scanf(" %[^\n]s", question2);

    // Calculating length of the array
    len = sizeof(question2) / sizeof(question2[0]);

    // Checks for space character in array if its there then ignores it and swap input1[i] to input1[i+1];
    for (int i = 0; i < len; i++)
    {
        if (question1[i] == ' ')
        {
            for (int j = i; j < len; j++)
            {
                question2[j] = question2[j + 1];
            }
            len--;
        }
    }
    // Encrypt recovery answers
    encrypt_string(question2);
    // Store recovery answers in .forgot_password.txt file
    fputs(question2, fp);
    fputs("\n", fp);

    // ----------------------------------------------------------------------------------------------------------

    // Question3
    printf("\n3. What is the name of the town where you were born?\n-> ");
    scanf(" %[^\n]s", question3);

    // Calculating length of the array
    len = sizeof(question3) / sizeof(question3[0]);

    // Checks for space character in array if its there then ignores it and swap input1[i] to input1[i+1];
    for (int i = 0; i < len; i++)
    {
        if (question3[i] == ' ')
        {
            for (int j = i; j < len; j++)
            {
                question3[j] = question3[j + 1];
            }
            len--;
        }
    }

    // Encrypt recovery answers
    encrypt_string(question3);

    // Store recovery answers in .forgot_password.txt file
    fputs(question3, fp);
    fputs("\n", fp);

    // ----------------------------------------------------------------------------------------------------------

    fclose(fp);

    // setup entries done
    printf("\nSetup completed!\n");
    sleep(3);

    // exit app to reload new data
    exiting();
}

// Reset password after forgetting the password
void reset_password()
{
    system("clear");

    printf("Setting new Key Required!\n\n");

    char *new_key;
    new_key = getpass("Enter a new key: ");

    // Encrypt new key entered by user
    encrypt_string(new_key);

    printf("\nSetting new password...\n");

    // store encrypted new key in .password.txt file
    FILE *ptr;
    ptr = fopen("../.data/.password.txt", "w");
    fprintf(ptr, "%s", new_key);
    fclose(ptr);

    // done resetting password
    sleep(1);
    system("echo Done!");
    printf("\n");

    exiting();

    sleep(2);

    system("clear");
}

// Forgot Password Option
bool forgot_password()
{
    system("clear");

    // answer in each line in file
    char ans[1000];
    int line_no = 0;

    // length of answer for removing blank spaces from answer
    int len;

    // user input answers
    char input1[1000];
    char input2[1000];
    char input3[1000];

    // real answers
    char answer1[1000];
    char answer2[1000];
    char answer3[1000];

    // Question1
    printf("1. What was your favorite subject in high school?\n-> ");
    scanf(" %[^\n]s", input1);

    // Calculating length of the array
    len = sizeof(input1) / sizeof(input1[0]);

    // Checks for space character in array if its there then ignores it and swap input1[i] to input1[i+1];
    for (int i = 0; i < len; i++)
    {
        if (input1[i] == ' ')
        {
            for (int j = i; j < len; j++)
            {
                input1[j] = input1[j + 1];
            }
            len--;
        }
    }
    // Encrypt entered answer to compare
    encrypt_string(input1);

    // Question2
    printf("\n2. What is your mother's maiden name?\n-> ");
    scanf(" %[^\n]s", input2);

    // Calculating length of the array
    len = sizeof(input2) / sizeof(input2[0]);

    // Checks for space character in array if its there then ignores it and swap input1[i] to input1[i+1];
    for (int i = 0; i < len; i++)
    {
        if (input2[i] == ' ')
        {
            for (int j = i; j < len; j++)
            {
                input2[j] = input2[j + 1];
            }
            len--;
        }
    }
    // Encrypt entered answer to compare
    encrypt_string(input2);

    // Questions3
    printf("\n3. What is the name of the town where you were born?\n-> ");
    scanf(" %[^\n]s", input3);

    // Calculating length of the array
    len = sizeof(input3) / sizeof(input3[0]);

    // Checks for space character in array if its there then ignores it and swap input1[i] to input1[i+1];
    for (int i = 0; i < len; i++)
    {
        if (input3[i] == ' ')
        {
            for (int j = i; j < len; j++)
            {
                input3[j] = input3[j + 1];
            }
            len--;
        }
    }
    // Encrypt entered answer to compare
    encrypt_string(input3);

    // read file line by line in separate variables for each line
    FILE *ptr;
    ptr = fopen("../.data/.forgot_password.txt", "r");

    while (fgets(ans, sizeof(ans), ptr))
    {
        // at first line_no = 0 then first answer will be read in answer1
        if (line_no == 0)
        {
            strcpy(answer1, ans);
        }

        // then  at line_no = 1 answer2 will be read from file
        else if (line_no == 1)
        {
            strcpy(answer2, ans);
        }

        // then at line_no = 3 answer3 will be read from file
        else if (line_no == 2)
        {
            strcpy(answer3, ans);
        }

        line_no++;
    }

    // if all answer matched then make reset_password_status = true
    if (strcmp(answer1, input1) == 10 && strcmp(answer2, input2) == 10 && strcmp(answer3, input3) == 10)
    {
        return true;
    }

    // if all  answer are not matched then make reset_password_status = false
    else
    {
        return false;
    }

    fclose(ptr);
}

// changes current password
char change_key(char *current_password)
{
    int attempt = 3;

    char *new_password;
    char *entered_current_password;

password:
    // Input current key to confirm user
    entered_current_password = getpass("Enter the current key: ");

    // encrypt entered key to compare
    encrypt_string(entered_current_password);

    if (strcmp(entered_current_password, current_password) == 0)
    {
        // Hiddenly input new password
        new_password = getpass("Enter a new key: ");

        // show user their new password (key)
        printf("\nKey successfully changed to: %s\n\n", new_password);

        // Encrypt new password
        encrypt_string(new_password);

        // Store password in file
        FILE *ptr;
        ptr = fopen("../.data/.password.txt", "w");
        fprintf(ptr, "%s", new_password);
        fclose(ptr);

        // set attempt = 0 to exit
        attempt = 0;
    }
    else
    {
        // Warning of invalid attempt
        printf("Invalid key! %d attempts left!\n\n", attempt - 1);
        attempt--;

        if (attempt > 0)
        {
            goto password;
        }
    }
}

// Reads the current password from file
char read_password(char *main_password)
{
    // read password from file and store it in parameter variable
    FILE *ptr;
    ptr = fopen("../.data/.password.txt", "r");
    fscanf(ptr, " %[^\n]s", main_password);
    fclose(ptr);
}

//----------------------------------------------------------------------------
//      Passwords list
//----------------------------------------------------------------------------
// Adds the new password to .passwords_list
void add_password()
{
    char choose_menu = 'y';
    while (choose_menu == 'y' || choose_menu == 'Y')
    {
        system("clear");
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
        printf("Do you want to add another password? [Y/n]: ");
        scanf("%s", &choose_menu);
        printf("\n");
    }
}

// search passwords
void search_password()
{
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
}

// decrypt entered string
void decrypt_password()
{
    char encrypted_password[1000];
    printf("Enter the encrypted password: ");
    scanf(" %[^\n]s", encrypted_password);
    getchar();

    decrypt_string2(encrypted_password);

    printf("The decrypted password is: ");
    puts(encrypted_password);
    printf("\n");
}

// Imports the passwords to app from file
void import_passwords()
{
    system("clear");
    printf("Note: This will overwrite all the existing data in your dictionary.\n\n");
    if (system("read -p 'Enter the file path: ' filePath && cp -f $filePath /home/$USER/Documents/.Program-Files/.MasterKey/.data/.passwords_list.txt;") == 0)
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

// export the passwords_list as txt.gpg file
void export_passwords()
{

    if (system("cp -f ../.data/.passwords_list.txt /home/$USER/Documents/passwords.txt;") == 0)
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

        system("echo Passwords successfully exported to /home/$USER/Documents/passwords.txt");

        sleep(1);
    }
}

// display passwords in list
void display_passwords_list()
{
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
}

//----------------------------------------------------------------------------
//      App
//----------------------------------------------------------------------------
// locks files when called
void lock()
{
    system("sudo chown root /home/$USER/Documents/.Program-Files/.MasterKey/.data/ -R");
    system("sudo chown root /home/$USER/Documents/.Program-Files/.MasterKey/.mail/ -R");
    system("sudo chown root /home/$USER/Documents/.Program-Files/.MasterKey/.script/ -R");
    system("sudo chown root /home/$USER/Documents/.Program-Files/.MasterKey/.temp/ -R");
}

// unlocks files when called
void unlock()
{
    system("cd /home/$USER/Documents/.Program-Files/.MasterKey/.main -R");
    system("sudo chown $USER /home/$USER/Documents/.Program-Files/.MasterKey/.data/ -R");
    system("sudo chown $USER /home/$USER/Documents/.Program-Files/.MasterKey/.mail/ -R");
    system("sudo chown $USER /home/$USER/Documents/.Program-Files/.MasterKey/.script/ -R");
    system("sudo chmod 700 /home/$USER/Documents/.Program-Files/.MasterKey/ -R");
    system("sudo chown $USER /home/$USER/Documents/.Program-Files/.MasterKey/.temp/ -R");
}

// Resets App
void reset_app()
{

    // display intro
    sleep(1);
    system("clear");
    system("echo Reseting...");
    sleep(5);
    system("clear");
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

    FILE *list;
    list = fopen("../.data/.passwords_list.txt", "w");
    fclose(list);

    FILE *password;
    password = fopen("../.data/.password.txt", "w");
    fclose(password);

    printf("Done\n");

    system("clear");
}

// Uninstalls App
void uninstall_app()
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
}

//----------------------------------------------------------------------------
//      Mail
//----------------------------------------------------------------------------
// sends random 6 digit verification_code on registered email address
void send_verification_code()
{
    // generate verification code and send via email
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
        fprintf(otr, "%d", num);
    }
    fclose(otr);

    system("../.script/.runSendOtp.sh ");
}

// changes current mail
char change_mail(char *current_password)
{
    int attempt = 3;
    char *entered_current_password;

    FILE *ptr;
    ptr = fopen("../.data/.password.txt", "r");

password:
    entered_current_password = getpass("Enter the key: ");
    encrypt_string(entered_current_password);
    // puts(entered_current_password);

    if (strcmp(entered_current_password, current_password) == 0)
    {

        system("clear");
        char mail[200];
        printf("Enter the new email ID: ");
        scanf(" %[^\n]s", mail);
        FILE *mtr;
        mtr = fopen("../.mail/.mail.txt", "w");
        fprintf(mtr, "%s", mail);
        fclose(mtr);

        printf("\nEmail successfully changed to %s\n\n", mail);
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

    fclose(ptr);
}

//----------------------------------------------------------------------------
//      Image
//----------------------------------------------------------------------------
// clicks image when called
void click_img()
{
    system("streamer -f jpeg -o .image.jpeg -q");
    system("mv .image.jpeg ../.temp/");
    system("clear");
}

// opens clicked image
void view_suspect_img()
{
    system("cd .. && if [ -f .image.jpeg ]; then chmod 600 .image.jpeg; fi;");
}

//----------------------------------------------------------------------------
//      Animations
//----------------------------------------------------------------------------
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

// checking for update animation
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

    printf("\e[?25h");
}

//----------------------------------------------------------------------------
//      Display
//----------------------------------------------------------------------------
// Main menu interface
void display_main_menu()
{
    system("clear");
    printf("**************************************************************************\n");
    printf("Menu:\n");
    printf("[1] Search Password \n");
    printf("[2] Decrypt password\n");
    printf("[3] Edit Dictionary \n");
    printf("[4] Settings\n");
    printf("[0] Exit\n");
    printf("**************************************************************************\n");
}

// Dictionary menu interface
void display_dictionary_menu()
{
    printf("Edit Dictionary\n\n");
    printf("  [0] <-- Go back to menu!\n\n");
    printf("  [1] View Passwords\n");
    printf("  [2] Add Passwords\n");
    printf("  [3] Remove Passwords\n");
    printf("  [4] Backup & Restore\n");
}

// Backup & Restore menu interface
void display_backup_and_restore_menu()
{
    printf("Edit Dictionary\n\n");
    printf("  [0] <-- Go back\n\n");
    printf("  [1] Import Passwords\n");
    printf("  [2] Export Passwords\n");
}

// Settings menu interface
void display_settings_menu()
{
    printf("Settings:\n\n");
    printf("  [0] <-- Go back to menu!\n\n");
    printf("  [1] Change Key\n");
    printf("  [2] Change Email\n");
    printf("  [3] Reset App\n");
    printf("  [4] Check for updates\n");
    printf("  [5] Uninstall MasterKey App\n");
}

// Forgot Key menu interface
void display_forgot_password_option_menu()
{
    printf("Select way to reset password\n\n");
    printf("    [1] Send verification code\n");
    printf("    [2] Recovery Questions\n");
    printf("    [0] exit\n\n");
}

//----------------------------------------------------------------------------
//      Others
//----------------------------------------------------------------------------
// timer for try again later
void try_again_later()
{
    printf("\e[?25l");
    int n;
    FILE *ttr;
    ttr = fopen("../.temp/.timer.txt", "r");
    fscanf(ttr, "%d", &n);
    fclose(ttr);

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
        ptr = fopen("../.temp/.timer.txt", "w");
        fprintf(ptr, "%d", i);
        fclose(ptr);
    }

    printf("\e[?25h");
}
