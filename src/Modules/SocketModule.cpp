#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include "Modules/SocketModule.h"
#include "Objects/IntegerObject.h"
#include "Objects/StringObject.h"

SocketModule::SocketModule() : Module("Socket") {
  MapStrFunc initMap = { { "initWithFamily:andStream:",
                           BIND_INIT_F(SocketModule::init, 2) } };
  MapStrProp propMap = {
    { "AF_INET", std::make_shared<IntegerObject>(AF_INET) },
    { "SOCK_STREAM", std::make_shared<IntegerObject>(SOCK_STREAM) },
    { "SOCK_DGRAM", std::make_shared<IntegerObject>(SOCK_DGRAM) },
    { "INADDR_ANY", std::make_shared<IntegerObject>(INADDR_ANY) }
  };

  setInitMap(initMap);
  setPropMap(propMap);
}

SObject SocketModule::init(const VecSObject &v) {
  auto inst = std::make_shared<SocketModule>();
  MapStrFunc funcMap = {
    { "bindHost:andPort:", BIND_METH_F(SocketModule::bind, inst.get(), 2) },
    { "listen:", BIND_METH_F(SocketModule::listen, inst.get(), 1) },
    { "accept", BIND_METH_F(SocketModule::accept, inst.get(), 0) },
    { "close", BIND_METH_F(SocketModule::close, inst.get(), 0) },
    { "recvN:", BIND_METH_F(SocketModule::recv, inst.get(), 1) },
    { "send:", BIND_METH_F(SocketModule::send, inst.get(), 1) },
  };
  inst->setFuncMap(funcMap);
  inst->setInstance();

  inst->domain_ = AF_INET;
  inst->type_ = SOCK_STREAM;
  inst->proto_ = 0;
  inst->socket_ = socket(inst->domain_, inst->type_, inst->proto_);
  return inst;
}

SObject SocketModule::bind(const VecSObject &v) {
  assert(socket_ != -1);
  long port = v.back()->getInt();
  struct sockaddr_in serv_addr;
  ::memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = domain_;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(port);
  ::bind(socket_, reinterpret_cast<sockaddr *>(&serv_addr), sizeof(serv_addr));
  return nullptr;
}

SObject SocketModule::listen(const VecSObject &v) {
  assert(socket_ != -1);
  long conns = v.back()->getInt();
  conns = 1;
  ::listen(socket_, conns);
  return nullptr;
}

SObject SocketModule::accept(const VecSObject &v) {
  assert(socket_ != -1);
  accept_ = ::accept(socket_, static_cast<sockaddr*>(NULL), NULL);
  return nullptr;
}

SObject SocketModule::recv(const VecSObject &v) {
  assert(accept_ != -1);
  int readBytes = v.back()->getInt();
  char *readBuffer = new char[readBytes];
  ::memset(readBuffer, 0, readBytes);
  int n = ::read(accept_, readBuffer, sizeof(readBuffer)-1); 
  assert(n != 0);
  std::string buffer(readBuffer);
  delete readBuffer;
  return std::make_shared<StringObject>(buffer);
}

SObject SocketModule::send(const VecSObject &v) {
  assert(accept_ != -1);
  auto buffer= v.back()->toString();
  ::write(accept_, buffer.c_str(), buffer.length()); 
  return nullptr;
}

SObject SocketModule::close(const VecSObject &v) {
  ::close(accept_);
  accept_ = -1;
  return nullptr;
}
