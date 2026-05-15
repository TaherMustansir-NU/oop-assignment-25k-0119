#include "Message.h"

using namespace std;

int Message::nextMessageId = 0;

Message::Message()
    : messageId(++nextMessageId), senderName("Unknown"), receiverName("Unknown"),
      content("No content"), timestamp("00:00:00"), isRead(false) {
}

Message::Message(const string& sender, const string& receiver, const string& cont,
                 const string& time)
    : messageId(++nextMessageId), senderName(sender), receiverName(receiver),
      content(cont), timestamp(time), isRead(false) {
}

Message::Message(const Message& other)
    : messageId(other.messageId), senderName(other.senderName),
      receiverName(other.receiverName), content(other.content),
      timestamp(other.timestamp), isRead(other.isRead) {
}

Message::~Message() {
}

Message& Message::operator=(const Message& other) {
    if (this != &other) {
        messageId = other.messageId;
        senderName = other.senderName;
        receiverName = other.receiverName;
        content = other.content;
        timestamp = other.timestamp;
        isRead = other.isRead;
    }
    return *this;
}

void Message::display() const {
    cout << "Message " << messageId << "\n";
    cout << "From: " << senderName << "\n";
    cout << "To: " << receiverName << "\n";
    cout << "Time: " << timestamp << "\n";
    cout << "Status: " << (isRead ? "Read" : "Unread") << "\n";
    cout << "Content: " << content << "\n";
}

void Message::markAsRead() {
    if (!isRead) {
        isRead = true;
        cout << "Message " << messageId << " marked as read\n";
    }
}

void Message::formatMessage() const {
    cout << "[" << timestamp << "] " << senderName << " -> " << receiverName
         << ": " << content << (isRead ? " [Read]" : " [Unread]") << "\n";
}

bool Message::isFromUser(const string& username) const {
    return senderName == username;
}
