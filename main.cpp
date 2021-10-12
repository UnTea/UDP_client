#pragma once

#define WIN32_LEAN_AND_MEAN

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include <ws2def.h>


#include <iostream>
#include <string>


std::string wsa_error() {
    int code = WSAGetLastError();

    switch (code) {
        case WSAEINTR: {
            return "WSAEINTR";
        }
        case WSAEBADF: {
            return "WSAEBADF";
        }
        case WSAEACCES: {
            return "WSAEACCES";
        }
        case WSAEDISCON: {
            return "WSAEDISCON";
        }
        case WSAEFAULT: {
            return "WSAEFAULT";
        }
        case WSAEINVAL: {
            return "WSAEINVAL";
        }
        case WSAEMFILE: {
            return "WSAEMFILE";
        }
        case WSAEWOULDBLOCK: {
            return "WSAEWOULDBLOCK";
        }
        case WSAEINPROGRESS: {
            return "WSAEINPROGRESS";
        }
        case WSAEALREADY: {
            return "WSAEALREADY";
        }
        case WSAENOTSOCK: {
            return "WSAENOTSOCK";
        }
        case WSAEDESTADDRREQ: {
            return "WSAEDESTADDRREQ";
        }
        case WSAEMSGSIZE: {
            return "WSAEMSGSIZE";
        }
        case WSAEPROTOTYPE: {
            return "WSAEPROTOTYPE";
        }
        case WSAENOPROTOOPT: {
            return "WSAENOPROTOOPT";
        }
        case WSAEPROTONOSUPPORT: {
            return "WSAEPROTONOSUPPORT";
        }
        case WSAESOCKTNOSUPPORT: {
            return "WSAESOCKTNOSUPPORT";
        }
        case WSAEOPNOTSUPP: {
            return "WSAEOPNOTSUPP";
        }
        case WSAEPFNOSUPPORT: {
            return "WSAEPFNOSUPPORT";
        }
        case WSAEAFNOSUPPORT: {
            return "WSAEAFNOSUPPORT";
        }
        case WSAEADDRINUSE: {
            return "WSAEADDRINUSE";
        }
        case WSAEADDRNOTAVAIL: {
            return "WSAEADDRNOTAVAIL";
        }
        case WSAENETDOWN: {
            return "WSAENETDOWN";
        }
        case WSAENETUNREACH: {
            return "WSAENETUNREACH";
        }
        case WSAENETRESET: {
            return "WSAENETRESET";
        }
        case WSAECONNABORTED: {
            return "WSWSAECONNABORTEDAEINTR";
        }
        case WSAECONNRESET: {
            return "WSAECONNRESET";
        }
        case WSAENOBUFS: {
            return "WSAENOBUFS";
        }
        case WSAEISCONN: {
            return "WSAEISCONN";
        }
        case WSAENOTCONN: {
            return "WSAENOTCONN";
        }
        case WSAESHUTDOWN: {
            return "WSAESHUTDOWN";
        }
        case WSAETOOMANYREFS: {
            return "WSAETOOMANYREFS";
        }
        case WSAETIMEDOUT: {
            return "WSAETIMEDOUT";
        }
        case WSAECONNREFUSED: {
            return "WSAECONNREFUSED";
        }
        case WSAELOOP: {
            return "WSAELOOP";
        }
        case WSAENAMETOOLONG: {
            return "WSAENAMETOOLONG";
        }
        case WSAEHOSTDOWN: {
            return "WSAEHOSTDOWN";
        }
        case WSASYSNOTREADY: {
            return "WSASYSNOTREADY";
        }
        case WSAVERNOTSUPPORTED: {
            return "WSAVERNOTSUPPORTED";
        }
        case WSANOTINITIALISED: {
            return "WSANOTINITIALISED";
        }
        case WSAHOST_NOT_FOUND: {
            return "WSAHOST_NOT_FOUND";
        }
        case WSATRY_AGAIN: {
            return "WSATRY_AGAIN";
        }
        case WSANO_RECOVERY: {
            return "WSANO_RECOVERY";
        }
        case WSANO_DATA: {
            return "WSANO_DATA";
        }
        default: {
            return "NO ERROR";
        }
    }
}

int main(int argc, char *argv[]) {
    // Startup winsock
    WSADATA data;
    WORD version = MAKEWORD(2, 2);
    int ws_ok = WSAStartup(version, &data);

    if (ws_ok != 0) {
        std::cerr << "Can't start winsock! " << std::endl;
        wsa_error();
        return 1;
    }

    // Create a hint structure for the server
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(54000);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    // Socket creation
    SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

    // Write out to that socket
    std::string string = argv[1];

    int send_ok = sendto(out, string.c_str(), string.size() + 1, 0, (sockaddr *) &server, sizeof(server));

    if (send_ok == SOCKET_ERROR) {
        std::cout << "Can't send " << std::endl;
        wsa_error();
    }

    // Close socket
    closesocket(out);

    // Shutdown winsock
    WSACleanup();

    return 0;
}
