#include <ncurses.h>                                                                
#include <unistd.h>                                                                                    
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string); 
int main(int argc, char *argv[])                                                    
{   
    int i=0;
    int j=0;    
    initscr();                      /* Start curses mode            */          
    if(has_colors() == FALSE)                                                   
    {       endwin();                                                           
	printf("Your terminal does not support color\n");                   
	exit(1);                                                            
    }                                                                           
    start_color();                  /* Start color                  */          
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2,COLOR_BLACK, COLOR_YELLOW);
    for(i=0;i<600;i++)
    { 
	if(i%2==0)
	    j=1;
	else
	    j=2;                                      
	attron(COLOR_PAIR(j));                                                      
	print_in_middle(stdscr, LINES / 2, 15, 0, "====Attention Shift Takers!!! Abnormal Activity Detected !!!====");         
    }
    attroff(COLOR_PAIR(1)); 
    endwin();                                                                   
}                                                                                   
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string)  
{       int length, x, y;                                                           
        float temp;                                                                 
                                                                                    
        if(win == NULL)                                                             
                win = stdscr;                                                       
        getyx(win, y, x);                                                           
        if(startx != 0)                                                             
                x = startx;                                                         
        if(starty != 0)                                                             
                y = starty;                                                         
        if(width == 0)                                                              
                width = 80;                                                         
                                                                                    
        length = strlen(string);                                                    
        temp = (width - length)/ 2;                                                 
        x = startx + (int)temp;                                                     
        mvwprintw(win, y, x, "=======ATTENTION!!! ATTENTION!!! SHIFT TAKERS!!! ABNORMAL ACTIVITY DETECTED !!! ATTENTION!!! ATTENTION!!!======");                                          
        mvwprintw(win, y+1, x, "                                                                                                               ");                                          
        mvwprintw(win, y+2, x, " _________    _________     _________     _________                    __________       ________               ");                                         
        mvwprintw(win, y+3, x, " |       |        |             |         |               |\\      |        |       |   |        |  |\\      |   ");                                         
        mvwprintw(win, y+4, x, " |_______|        |             |         |________       |  \\    |        |       |   |        |  |  \\    |   ");                            
	mvwprintw(win, y+5, x, " |       |        |             |         |               |    \\  |        |       |   |        |  |    \\  |   ");                                         
        mvwprintw(win, y+6, x, " |       |        |             |         |________       |      \\|        |       |   |________|  |      \\|   ");                                         
        mvwprintw(win, y+7, x, "                                                                                                               ");                                         
        mvwprintw(win, y+8, x, "=======ATTENTION!!! ATTENTION!!! SHIFT TAKERS!!! ABNORMAL ACTIVITY DETECTED !!! ATTENTION!!! ATTENTION!!!======");                                         


        refresh();              
	sleep(1);                                                                                                        
}                                                                                   
