#ifndef CLIENT_H
#define CLIENT_H

#include <string>

// Connects to the server at the specified IP address and port number, and
// sends the specified message to the server. Returns the response from the
// server, or an empty string on error.
std::string send_message(const std::string& ip_address, int port, const std::string& message);

#endif