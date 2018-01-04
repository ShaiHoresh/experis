#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/time.h>
#include <errno.h>

#include "comm.h"

typedef int Bool;
#define TRUE 1
#define FALSE 0

struct Server
{
    int m_sock;
    struct sockaddr_in* m_sAdd;
    List* m_clients;
    UserFunc m_userFunc;
    WelcomeFunc m_welcome;
    size_t m_counter;
    fd_set m_bs;
};

static ssize_t Send(int _sock, char* _buffer, size_t _len);
static ssize_t Receive(int _sock, char* _buffer, size_t _len);
static Bool MakeNonBlock(int _sock);
static int AcceptClients(Server* _server/*, int* activity*/);
static int TreatRequest(Server* _server, fd_set _set, int* activity);
static void CloseSocket(Server* _server, int* _sock);
Bool Deny(int* _client);
Bool Join(Server* _server, int* _client);


Server* CreateServer(UserFunc _cb, WelcomeFunc _wcb, uint16_t _port)
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
    printf("socket no. %d\n", ser->m_sock);
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
    
    FD_ZERO(&ser->m_bs);
    FD_SET(ser->m_sock, &ser->m_bs);
    FD_SET(0, &ser->m_bs);
    
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
    
    if(_wcb)
    {
        ser->m_welcome = _wcb;
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
        perror("receive failure");
    }
    
    return rcv;
}

Bool Join(Server* _server, int* _client)
{
    char buf[1024];
    size_t len;
    
    printf("Accepted Client in socket %d. Iternal No: %ld\n", *_client, _server->m_counter);
    FD_SET(*_client, &_server->m_bs);
    ListPushHead(_server->m_clients, _client);
    ++_server->m_counter;

    if(_server->m_welcome)
    {
        _server->m_welcome(buf, &len);
        Send(*_client, buf, len);
    }
    
    return TRUE;
}

Bool Deny(int* _client)
{
    close(*_client);
    free(_client);
    
    return FALSE;
}

static int AcceptClients(Server* _server)
{
    socklen_t addrLen;
    int *client;
    Bool flag = FALSE;
    
    client = malloc(sizeof(int));
        
    if((*client = accept(_server->m_sock, (struct sockaddr*)_server->m_sAdd, &addrLen)) < 0)
    {
        free(client);
    }
    else if(_server->m_counter < 1000)
    {
        flag = Join(_server, client);
    }
    else
    {
        flag = Deny(client);
    }
    
    return flag;
}

static void CloseSocket(Server* _server, int* _sock)
{
    close(*_sock);
    FD_CLR(*_sock, &_server->m_bs);
    free(_sock);
}

static int TreatRequest(Server* _server, fd_set _set, int* activity)
{
    char ret[1024];
    ListItr itrEnd;
    int* sock;
    ssize_t rcv;
    size_t len;
    char buf[1024];
    ListItr temp, itr = ListItrBegin(_server->m_clients);
    
    len = sizeof(buf);
    itrEnd = ListItrEnd(_server->m_clients);
    
    /*receive*/
    while(itr != itrEnd && *activity)
    {
        sock = (int*)ListItrGet(itr);
        if(FD_ISSET(*sock, &_set))
        {
            --(*activity);
            rcv = Receive(*sock, buf, sizeof(buf));
            if(rcv > 0)
            {
                /*_cb*/
                if(_server->m_userFunc)
                {
                    _server->m_userFunc(buf, &rcv, ret, &len);
                }
                
                /*send message*/
                Send(*sock, ret, sizeof(ret));
            }
            else if(rcv == 0)
            {
                CloseSocket(_server, sock);
                temp = ListItrNext(itr);
                ListItrRemove(itr);
                itr = ListItrPrev(temp);
                --_server->m_counter;
            }
        }
        itr = ListItrNext(itr);
    }
    return 0;
}

int ServerRun(Server* _server)
{
    /*declarations*/
    fd_set temp;
    int activity, getClients;
    
    while(TRUE)
    {
        temp = _server->m_bs;
        getClients = 5;
        activity = select(1024, &temp, NULL, NULL, NULL);
        if(0 > activity && errno!=EINTR)
        {
            perror("select failed\n");
        }
        
        if(FD_ISSET(0, &temp))
        {
            break;
        }
        if(FD_ISSET(_server->m_sock, &temp))
        {
            while(AcceptClients(_server) && getClients--)
            {
                --activity;
            }
        }
        
        if(activity)
        {
            TreatRequest(_server, temp, &activity);
        }
    }
    
    return 1;
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
    free(_server);
}


























