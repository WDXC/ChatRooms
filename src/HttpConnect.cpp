#include "HttpConnect.h"
#include "event2/buffer.h"
#include "event2/bufferevent.h"
#include "event2/event.h"
#include "event2/util.h"
#include <cstdio>
#include <cstring>
#include <event2/listener.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/socket.h>

static const char MESSAGE[] = "HELO, World!\n";
static const unsigned short PORT = 9995;

int32_t HttpConnect::m_cnt = 0;

HttpConnect::HttpConnect() : m_res("") {}

HttpConnect::~HttpConnect() {}

void HttpConnect::Init() {
  event_base *base;
  evconnlistener *listener;
  event *signal_event;

  struct sockaddr_in sin = {0};
  base = event_base_new();
  if (!base) {
    fprintf(stderr, "Could not initialize libevent!\n");
    return;
  }

  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);
  listener = evconnlistener_new_bind(base, listener_cb, (void *)base,
                                     LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
                                     -1, (sockaddr *)&sin, sizeof(sin));

  if (!listener) {
    fprintf(stderr, "Could not create a listener!\n");
    return;
  }

  signal_event = evsignal_new(base, SIGINT, signal_cb, (void *)base);
  if (!signal_event || event_add(signal_event, NULL) < 0) {
    fprintf(stderr, "Could not create/add a signal event!\n");
    return;
  }

  event_base_dispatch(base);
  evconnlistener_free(listener);
  event_free(signal_event);
  event_base_free(base);

  printf("close\n");
  return;
}

void HttpConnect::listener_cb(struct evconnlistener *listener,
                              evutil_socket_t fd, struct sockaddr *sa,
                              int socklen, void *user_data) {
  event_base *base = (event_base *)user_data;
  bufferevent *bev;

  bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
  if (!bev) {
    fprintf(stderr, "Error constructing bufferevent!");
    event_base_loopbreak(base);
  }
  bufferevent_setcb(bev, NULL, conn_writecb, conn_eventcb, NULL);
  bufferevent_enable(bev, EV_WRITE);
  bufferevent_disable(bev, EV_READ);

  bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
}

void HttpConnect::conn_writecb(struct bufferevent *bev, void *user_data) {
  evbuffer *output = bufferevent_get_output(bev);
  if (evbuffer_get_length(output) == 0) {
    printf("flushed answer\n");
    bufferevent_free(bev);
  }
}

void HttpConnect::conn_eventcb(struct bufferevent *bev, short events,
                               void *user_data) {
  if (events & BEV_EVENT_EOF) {
    printf("Connection closed.\n");
  } else if (events & BEV_EVENT_ERROR) {
    printf("Got an error on the connection: %s\n", strerror(errno));
  }
}

void HttpConnect::signal_cb(evutil_socket_t sig, short events,
                            void *user_data) {
  event_base *base = (event_base *)user_data;
  struct timeval delay = {1, 0};
  printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");
  event_base_loopexit(base, &delay);
}

std::string HttpConnect::getResString() {
    while (--m_cnt) {
        m_res += "helo ";
    }
    return m_res;
}
