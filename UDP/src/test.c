#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    int frappe;
    while (!kbhit())
    {
        frappe = getch();
        if (frappe == 'a')
        {
            outtextxy(10, 10, "Touche 'a' saisie.");
            delay(500);
        }
        else
            cleardevice();
    }

    return 0;
}
