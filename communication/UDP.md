신뢰성은 없지만 빠른 통신 프로토콜, 근거리 LAN 환경에서 사용

BSD 소켓 함수에서 socket 함수의 인자로 SOCK_DGAM 옵션을 통해 설정 가능

- socket 함수?
    
    ```c
    int socket(int domain, int type, int protocol); //type 부분에 SOCK_DGAM 들어감
    ```
    
    네트워크 통신을 위한 소켓(통신 창구)을 만드는 함수
    
    SOCK_DGAM은 UDP, SOCK_STREAM은 TCP
    

### **일반적으로 서버와 클라이언트가 주고받는 법**

<aside>

- `sendto()` 함수를 통해 메세지를 전달
- `recvfrom()` 함수를 통해 수신
- 사용이 끝나면 `close` 로 닫음
- 서버는 `bind()`를 사용하는데, 클라이언트가 잘 찾아오게 소켓에 addr를 부여해주는 것임

```c
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

</aside>

- addr?
    
    어디로 데이터를 보내고 받을지 알려줄 때 사용하는 **주소 정보**
    
    소켓에 addr을 전달하는 건 이 소켓이 어떤 주소랑 연결될지 알려주는 것임
    

![스크린샷 2025-07-08 200234.png](attachment:b08c462a-e05a-401d-a4cf-5310f528be18:스크린샷_2025-07-08_200234.png)

만일 UDP 네트워크 domain을 인터넷 통신 방식으로 설정하게 된다면 bind에서 주소 체계를 설정할 때

```c
struct sockaddr_in {
    __uint8_t sin_len;
    sa_family_t sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];

};
```

의 구조체를 사용해서 IP주소에 넣어줘야만 한다.
