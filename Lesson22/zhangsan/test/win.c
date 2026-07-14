// 我们代码是我用文心一言生成并调试通过的，具体要什么功能，大家可以试着了解一下
#include <stdio.h>
#include <string.h>
#include <ncurses.h>  
#include <unistd.h>  
  
#define PROGRESS_BAR_WIDTH 30  
#define BORDER_PADDING 2  
#define WINDOW_WIDTH (PROGRESS_BAR_WIDTH + 2 * BORDER_PADDING + 2) // 加边框的宽度  
#define WINDOW_HEIGHT 5  
#define PROGRESS_INCREMENT 3  
#define DELAY 300000  // 微秒（300毫秒）  
  
int main() {  
    initscr();  
    start_color();  
    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // 已完成部分：绿色前景，黑色背景  
    init_pair(2, COLOR_RED, COLOR_BLACK);    // 剩余部分（虽然用红色可能不太合适，但为演示目的）：红色背景  
    cbreak();  
    noecho();  
    curs_set(FALSE);  
  
    int max_y, max_x;  
    getmaxyx(stdscr, max_y, max_x);  
    int start_y = (max_y - WINDOW_HEIGHT) / 2;  
    int start_x = (max_x - WINDOW_WIDTH) / 2;  
  
    WINDOW *win = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, start_y, start_x);  
    box(win, 0, 0); // 加边框  
    wrefresh(win);  
  
    int progress = 0;  
    int max_progress = PROGRESS_BAR_WIDTH;  
  
    while (progress <= max_progress) {  
        werase(win); // 清除窗口内容  
  
        // 计算已完成的进度和剩余的进度  
        int completed = progress;  
        int remaining = max_progress - progress;  
  
        // 显示进度条  
        int bar_x = BORDER_PADDING + 1; // 进度条在窗口中的x坐标  
        int bar_y = 1; // 进度条在窗口中的y坐标（居中）  
  
        // 已完成部分  
        attron(COLOR_PAIR(1));  
        for (int i = 0; i < completed; i++) {  
            mvwprintw(win, bar_y, bar_x + i, "#");  
        }  
        attroff(COLOR_PAIR(1));  
  
        // 剩余部分（用背景色填充）  
        attron(A_BOLD | COLOR_PAIR(2)); // 加粗并设置背景色为红色（仅用于演示）  
        for (int i = completed; i < max_progress; i++) {  
            mvwprintw(win, bar_y, bar_x + i, " ");  
        }  
        attroff(A_BOLD | COLOR_PAIR(2));  
  
        // 显示百分比  
        char percent_str[10];  
        snprintf(percent_str, sizeof(percent_str), "%d%%", (progress * 100) / max_progress);  
        int percent_x = (WINDOW_WIDTH - strlen(percent_str)) / 2; // 居中显示  
        mvwprintw(win, WINDOW_HEIGHT - 1, percent_x, percent_str);  
  
        wrefresh(win); // 刷新窗口以显示更新  
  
        // 增加进度  
        progress += PROGRESS_INCREMENT;  
  
        // 延迟一段时间  
        usleep(DELAY);  
    }  
  
    // 清理并退出ncurses模式  
    delwin(win);  
    endwin();  
    return 0;  
}

