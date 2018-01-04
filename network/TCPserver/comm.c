#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "comm.h"

typedef int Bool;
#define TRUE 1
#define FALSE 0

struct Server
{
    int m_sock;
    struct sockaddr_in* m_sAdd;  /*TODO remove from struct*/
    List* m_clients;
    UserFunc m_userFunc;
    size_t m_counter;
};

static ssize_t Send(int _sock, char* _buffer, size_t _len);
static ssize_t Receive(int _sock, char* _buffer, size_t _len);
static Bool MakeNonBlock(int _sock);

Server* CreateServer(UserFunc _cb, int _port)
{
    /*declarations*/
    Server* ser;
    int opt = 1;
    
    /*  malloc  */
    ser = malloc(sizeof(Server));
    if(!ser)
    {
        perror("malloc failed");
        return NULL;
    }
    
    /*  open socket  */
    ser->m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(ser->m_sock < 0)
    {
        perror("socket failed");
        free(ser);
        return NULL;
    }
    
    /*  setsockopt   */
    if(setsockopt(ser->m_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt failed\n");
    }
    
    /*  memset & struct sockaddr_in init  */
    ser->m_sAdd = calloc(sizeof(struct sockaddr_in), 1);
    if(!ser->m_sAdd)
    {
        perror("calloc failed");
        close(ser->m_sock);
        free(ser);
        return NULL;
    }
    ser->m_sAdd->sin_family = AF_INET;
    ser->m_sAdd->sin_port = htons(_port);
    ser->m_sAdd->sin_addr.s_addr = INADDR_ANY;
    MakeNonBlock(ser->m_sock);
    
    /*  bind  */
    if(bind(ser->m_sock, (struct sockaddr*)ser->m_sAdd, sizeof(struct sockaddr_in)) < 0)
    {
        perror("bind failed");
        close(ser->m_sock);
        free(ser);
        return NULL;
    }
    
    /*  listen  */
    if(listen(ser->m_sock, 32) < 0)
    {
        perror("listen failed");
        close(ser->m_sock);
        free(ser);
        return NULL;
    }
    
    /*  create list  */
    ser->m_clients = ListCreate();
    if(!ser->m_clients)
    {
        perror("List Create failed");
        close(ser->m_sock);
        free(ser);
        return NULL;
    }
    
    if(_cb)
    {
        ser->m_userFunc = _cb;
    }
    ser->m_counter = 0;
    
    return ser;
}

static ssize_t Send(int _sock, char* _buffer, size_t _len)
{
    ssize_t snd; 
    
    if((snd = send(_sock, _buffer, _len + 1, 0)) < 0)
    {
        perror("send failed");
    }
    
    return snd;
}

static ssize_t Receive(int _sock, char* _buffer, size_t _len)
{
    ssize_t rcv;
    
    if((rcv = recv(_sock, _buffer, _len - 1, 0)) < 0)
    {
/*        perror("receive failure");*/
    }
    
    return rcv;
}

int AcceptClients(Server* _server)
{
    socklen_t addrLen;
    int* client, *temp;
    Bool flag = FALSE;
    
    client = malloc(sizeof(int));
        
    if((*client = accept(_server->m_sock, (struct sockaddr*)_server->m_sAdd, &addrLen)) < 0)
    {
        free(client);
/*        perror("acception failed: ");*/
    }
    else
    {
        flag = TRUE;
        MakeNonBlock(*client);
        printf("Accepted Client in socket %d. Iternal No: %ld\n", *client, _server->m_counter);
        ListPushHead(_server->m_clients, client);
        ++_server->m_counter;
    }
    
    if(_server->m_counter > 1000)/* && flag == TRUE)*/
    {
        temp = malloc(sizeof(int));
        printf("Can't accept Client\n");
        ListPopHead(_server->m_clients, (void**)temp);
        free(temp);
        close(*client);
        --_server->m_counter;
    }
    
    return flag;
}

int TreatRequest(Server* _server)
{
    char ret[1024];
    ListItr itrEnd;
    int sock;
    ssize_t rcv;
    size_t len;
    char buf[1024];
    ListItr itr = ListItrBegin(_server->m_clients);
    
    len = sizeof(buf);
    itrEnd = ListItrEnd(_server->m_clients);
    
    /*receive*/
    while(itr != itrEnd)
    {
        sock = *(int*)ListItrGet(itr);
        rcv = Receive(sock, buf, sizeof(buf));
        if(rcv > 0)
        {
            /*_cb*/
            _server->m_userFunc(buf, &rcv, ret, &len);
            
            /*send message*/
            Send(sock, ret, sizeof(ret));
        }
        else if(rcv == 0)
        {
            close(sock);
            ListItrRemove(itr);
            --_server->m_counter;
        }
        
        itr = ListItrNext(itr);
    }
    return 0;
}

static Bool MakeNonBlock(int _sock)
{
    int flags;
    
    if((flags = fcntl(_sock, F_GETFL)) < 0)
    {
        perror("fcntl failed");
        return FALSE;
    }
    
    if(fcntl(_sock, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        perror("fcntl failed");
        return FALSE;
    }
    
    return TRUE;
}

int DestroySocket(void* _element, void* _context)
{
    int* ptr = _element;
    
    close(*ptr);
    free(ptr);
    
    return TRUE;
}

void ServerDestroy(Server* _server)
{
    ListDestroy(&_server->m_clients, DestroySocket);
    free(_server->m_sAdd);
}


























