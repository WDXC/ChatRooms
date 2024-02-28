#ifndef HTTP_CONNECT_H_
#define HTTP_CONNECT_H_

#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <sys/socket.h>
#include <string>

class HttpConnect {
public:
  HttpConnect();
  ~HttpConnect();

public:
  void Init();

public:
  std::string getResString();

public:
  static void listener_cb(struct evconnlistener *, evutil_socket_t,
                          struct sockaddr *, int socklen, void *);
  static void conn_writecb(struct bufferevent *, void *);
  static void conn_eventcb(struct bufferevent *, short, void *);
  static void signal_cb(evutil_socket_t, short, void *);
  static int32_t m_cnt;

private:
  std::string m_res;
};

#endif
