#pragma once
#include<string>

struct Header {
	int bodySize;
	int type;
};

enum MessageType {
	MT_BIND_NAME = 1,
	MT_CHAT_INFO = 2,
	MT_ROOM_INFO = 3,
};

//client send
struct BindName {
	char name[32];
	int nameLen;
};

//client send
struct ChatInformation {
	char information[256];
	int infoLen;
};

//server send
struct RoomInformation {
	BindName name;
	ChatInformation chat;
};

bool parseMessage(const std::string& input, int *type, std::string& outbuffer);