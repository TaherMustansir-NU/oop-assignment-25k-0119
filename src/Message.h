#pragma once

#include <iostream>
#include <string>

using namespace std;

class Message {
private:
    int messageId;
    string senderName;
    string receiverName;
    string content;
    string timestamp;
    bool isRead;

    static int nextMessageId;

public:
    Message();
    Message(const string& sender, const string& receiver, const string& cont,
            const string& time);
    Message(const Message& other);
    ~Message();

    Message& operator=(const Message& other);

    void display() const;
    void markAsRead();
    void formatMessage() const;
    bool isFromUser(const string& username) const;

    int getMessageId() const { return messageId; }
    const string& getSenderName() const { return senderName; }
    const string& getReceiverName() const { return receiverName; }
    const string& getContent() const { return content; }
    const string& getTimestamp() const { return timestamp; }
    bool getIsRead() const { return isRead; }

    void setSenderName(const string& sender) { senderName = sender; }
    void setReceiverName(const string& receiver) { receiverName = receiver; }
    void setContent(const string& cont) { content = cont; }
    void setTimestamp(const string& time) { timestamp = time; }
    void setIsRead(bool read) { isRead = read; }
};

