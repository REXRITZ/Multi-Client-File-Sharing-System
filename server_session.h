#include "user.h"
#include<vector>
#include<queue>
#include<sys/socket.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<iostream>
#include<fstream>
#include<unistd.h>
#include<string.h>
#include<filesystem>

#define BACKLOG 4096
#define BUF_SIZE 1024
#define USER_DATA_PATH "./usermetadata.txt"
#define FILES_METADATA_PATH "./filemetadata.txt"
#define FILE_DIR_PATH "./files/"

class ServerSession {
    int sockfd;
    unordered_map<string, FileMetaData> filesMap;
    unordered_map<string, User> users;
    unordered_map<string, User> activeUsers; 
    pthread_mutex_t sessionLock;
    pthread_cond_t sessionWait;

    public:
        ServerSession();
        ~ServerSession();
        int getsockfd();
        int loadFileMetaData();
        int loadUserMetaData();
        int startServer(int, struct sockaddr_in);
        const char* authenticateUser(User, string);
        void checkout(string, int, string);
        void commit(string, int, string);
        void deleteFile(string, int, string);
        void addFile(string, int, string);
        void quit(int, string);
        string listall();
        void printUsers();
        void printFileMetaData();
};