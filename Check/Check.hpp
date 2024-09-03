#ifndef CHECK_HPP
#define CHECK_HPP

#include <string>

/* ----------------- Main Arguments Check ----------------- */
bool CheckPort(int port);

/* ----------------- Password Check ----------------------- */
bool CheckPassword(string password);

/* ----------------- Nickname Check ----------------------- */
bool CheckIsValidNickname(string nickname);

/* ----------------- Channel Check ------------------------ */
bool CheckChannelName(string channelName);

/* ----------------- Commands Check ----------------------- */
void CheckDoubleCommands(vector<string> &commandList);

#endif