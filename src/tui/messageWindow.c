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
    // Increment the last message until we are at the end
    messageWindowLastMessage = messageWindowLastMessage < 16 ? messageWindowLastMessage + 1 : 16;
    // Shift all messages up one, starting with the last
    for (size_t i = messageWindowLastMessage - 1; i > 0; i--)
    {
        strcpy(messageWindowMessages[i], messageWindowMessages[i - 1]);
    }
    // Calculate the max length of the line, so that it isn't bigger than our buffer.
    originalLineLength = strlen(line);
    newLineLength = originalLineLength >= messageWindowMessageSize ? messageWindowMessageSize -1 : originalLineLength;
    strncpy(messageWindowMessages[0], line, newLineLength);
    // Terminate the string incase the old message was longer.
    messageWindowMessages[0][newLineLength] = '\0';
    // Write the message onto the window buffer
    for (int i = 0; i < messageWindowLastMessage; i++)
    {
        mvwprintw(messageWindow, i + 1, 2, messageWindowMessages[i]);
    }
    // Refresh the window
    wrefresh(messageWindow);
}

int UpdateMessageWindow()
{
    box(messageWindow, 0, 0);
    mvwprintw(messageWindow, 0, 1, "Messages");
    wrefresh(messageWindow);
}