#include <gnpch.h>
#include <platform/gn_curses.h>
#include <tui/messageWindow.h>
#include <tui/tuiShared.h>
#include <primitives/rectangle.h>

static WINDOW *messageWindow;
static Rectangle g_messageWindowRect;
static char **messageWindowMessages;
static int messageWindowMaxNumMessages;
static size_t messageWindowMessageSize;
static int messageWindowLastMessage;

int InitMessageWindow(int x, int y, int width, int height)
{
    g_messageWindowRect.x = x;
    g_messageWindowRect.y = y;
    g_messageWindowRect.w = width;
    g_messageWindowRect.h = height;
    messageWindowLastMessage = 0;
    messageWindowMessageSize = width - 5;
    messageWindowMaxNumMessages = height - 2;
    // Initialize the strings for use throughout the program to avoid runtime dynamic allocations
    messageWindowMessages = calloc(messageWindowMaxNumMessages, sizeof(char*));
    for (size_t i = 0; i < messageWindowMaxNumMessages; i++)
    {
        messageWindowMessages[i] = malloc(sizeof(char) * messageWindowMessageSize);
    }
    messageWindow = create_newwin(g_messageWindowRect.h, g_messageWindowRect.w, g_messageWindowRect.y, g_messageWindowRect.x);
    scrollok(messageWindow, TRUE);
}

void SendMessageToMessageWindow(const char *line)
{
    wclear(messageWindow);
    size_t newLineLength, originalLineLength = 0;
    // Increment the last message
    messageWindowLastMessage = messageWindowLastMessage < 16 ? messageWindowLastMessage + 1 : 16;
    // Shift all messages up one, starting with the last
    for (size_t i = messageWindowLastMessage - 1; i > 0; i--)
    {
        // oldLineLength = strlen(messageWindowMessages[i]);
        // newLineLength = strlen(messageWindowMessages[i - 1]);
        // if (oldLineLength > newLineLength)
            // memset(messageWindowMessages[i], '\0', oldLineLength);
            // memset(messageWindowMessages[i], '\0', oldLineLength);
        strcpy(messageWindowMessages[i], messageWindowMessages[i - 1]);
    }
    // Calculate the max length of the line, incase we are over the max line size so it doesn't wrap.
    originalLineLength = strlen(line);
    newLineLength = originalLineLength >= messageWindowMessageSize ? messageWindowMessageSize -1 : originalLineLength;
    // oldLineLength = strlen(messageWindowMessages[0]);
    // if (oldLineLength > newLineLength)
    //     memset(messageWindowMessages[0], '\0', oldLineLength);
    strncpy(messageWindowMessages[0], line, newLineLength);
    messageWindowMessages[newLineLength] = '\0';

    for (int i = 0; i < messageWindowLastMessage; i++)
    {
        mvwprintw(messageWindow, i + 1, 2, messageWindowMessages[i]);
    }
    wrefresh(messageWindow);
}

int UpdateMessageWindow()
{
    box(messageWindow, 0, 0);
    mvwprintw(messageWindow, 0, 1, "Messages");
    wrefresh(messageWindow);
}