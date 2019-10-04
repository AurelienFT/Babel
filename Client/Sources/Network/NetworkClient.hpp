/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** NetworkClient
*/

#ifndef NETWORKCLIENT_HPP_
#define NETWORKCLIENT_HPP_

#ifdef __linux__
	#include <sys/socket.h> 
	#include <netinet/in.h> 
	#include <sys/time.h>
	#include <unistd.h>
	#include <netdb.h>
	#include <arpa/inet.h>
	#include <strings.h>
	#include <unistd.h>
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define closesocket(s) close(s)
	typedef int SOCKET;
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr SOCKADDR;
#endif

#ifdef _WIN64
	#include <WinSock2.h>
	#include <windows.h>
#endif

#ifdef _WIN32
	#include <WinSock2.h>
	#include <windows.h>
#endif

#include <string>
#include <list>
#include <future>
#include <mutex>
#include "NetworkInterface.hpp"
#define PORT 1337
#define SERVER_ADDRESS "127.0.0.1"

class NetworkClient
{
private:
  /**
   * Constructor: do not allow to be called from outside of the class
   * to respect the Singleton principe
   */
  NetworkClient() = default;

  /**
   * Destructor
   */
  ~NetworkClient() = default;

public:
  /**
   * Do not allow copy constructor
   */
  NetworkClient(const NetworkClient &) = delete;

  /**
   * Do not allow assignation operator
   * @return nothing
   */
  NetworkClient &operator=(const NetworkClient &) = delete;

public:
  /**
   * Get singleton instance
   * This implementation is thread-safe using C++11 memory model
   * @return A NetworkClient raw pointer to the current instance
   */
  static NetworkClient *instance()
  {
    static std::mutex mInstanceMutex;
    static NetworkClient *mInstance{nullptr};
    std::lock_guard<std::mutex> lock(mInstanceMutex);

    if (!mInstance) {
      mInstance = new NetworkClient();
    }

    return mInstance;
  }


  void connection();
  int send_server(MessageType messageType, std::string message);
  MessageType receive_messageCode();
  std::string getReponse() const;
  void disconnect();
private:

  static NetworkClient *mInstance;
  static std::mutex mInstanceMutex;
  std::string _reponse;
  int _sockfd;
}; 


#endif /* !NETWORKCLIENT_HPP_ */