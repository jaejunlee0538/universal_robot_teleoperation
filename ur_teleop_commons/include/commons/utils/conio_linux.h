/*
 *  terminal_io.h
 *  Author: Jakash3
 *  Date: 22 Dec 2011
 *  Some conio.h functions for GNU/Linux
 */
#ifndef TERMINAL_IO
#define TERMINAL_IO
 
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
 
// Turns terminal line buffering on or off
void terminal_lnbuf(int yn);
 
// Turns terminal keyboard echo on or off
void terminal_echo(int yn);
 
// Get next immediate character input (no echo)
int getch();
 
// Get next immediate character input (with echo)
int getche();
 
// Check if a key has been pressed at terminal
int kbhit();
 
// Set cursor position
void gotoxy(int x, int y);
 
// Clear terminal screen and set cursor to top left
void clrscr();



void terminal_lnbuf(int yn) {
   struct termios oldt, newt;
   tcgetattr(0, &oldt);
   newt = oldt;
   if (!yn) newt.c_lflag &= ~ICANON;
   else newt.c_lflag |= ICANON;
   tcsetattr(0, TCSANOW, &newt);
}
 
void terminal_echo(int yn) {
   struct termios oldt, newt;
   tcgetattr(0, &oldt);
   newt = oldt;
   if (!yn) newt.c_lflag &= ~ECHO;
   else newt.c_lflag |= ECHO;
   tcsetattr(0, TCSANOW, &newt);
}
 
void gotoxy(int x, int y) { printf("\x1B[%d;%df", y, x); }
 
void clrscr() { printf("\x1B[2J\x1B[0;0f"); }
 
int getch() {
   register int ch;
   terminal_lnbuf(0);
   terminal_echo(0);
   ch = getchar();
   terminal_lnbuf(1);
   terminal_echo(1);
   return ch;
}
 
int getche() {
   register int ch;
   terminal_lnbuf(0);
   ch = getchar();
   terminal_lnbuf(1);
   return ch;
}
 
int kbhit() {
   register int ret;
   fd_set fds;
   terminal_lnbuf(0);
   terminal_echo(0);
   struct timeval tv;
   tv.tv_sec = 0;
   tv.tv_usec = 0;
   FD_ZERO(&fds);
   FD_SET(0, &fds);
   select(1, &fds, 0, 0, &tv);
   ret = FD_ISSET(0, &fds);
   terminal_lnbuf(1);
   terminal_echo(1);
   return ret;
}
 
#endif