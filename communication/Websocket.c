#웹소켓

TCP연결 방식으로 진행되는 통신

과정은

1. wifi 환경 설정
2. 서버 주소 알기
3. wifi 이벤트 핸들러로 연결 후 IP주소와 포트번호 얻기
4. wifi 초기화
5. 웹소켓 이벤트 핸들러로 서버 응답 분기별 처리
6. 웹소켓 시작 통신으로 연결 후 JSON 형태로 값 보내기
```cpp
		#define WIFI_SSID                 "추가예정"
    #define WIFI_PASS                 "추가예정"
    #define WEB_SERVER_ADDR           "추가예정"        
    #define CHECK_CONNECT             10000;   

    const char *TAG = "MPU6050";   
    static const char *WS = "ws_client";

    uint8_t CapValue = 0;
    int16_t MpuValueX = 0, mpuValueY = 0, mpuValueZ = 0;

    bool finished = false;

    //wifi 이벤트 핸들러
    static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                   int32_t event_id, void* event_data) {
        if (event_id == WIFI_EVENT_STA_START) {
            esp_wifi_connect();
        } else if (event_id == WIFI_EVENT_STA_DISCONNECTED) {
            esp_wifi_connect();
            ESP_LOGI(TAG, "재연결 시도 중...");
        } else if (event_id == IP_EVENT_STA_GOT_IP) {
            ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
            ESP_LOGI(TAG, "IP 주소 획득: " IPSTR, IP2STR(&event->ip_info.ip));
        }
    }

    //wifi 초기화
    void wifi_init() {
        esp_netif_init();
        esp_event_loop_create_default();
        esp_netif_create_default_wifi_sta();
        wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
        esp_wifi_init(&cfg);
        esp_event_handler_instance_t instance_any_id;
        esp_event_handler_instance_t instance_got_ip;
        esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, &instance_any_id);
        esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, &instance_got_ip);
        wifi_config_t wifi_config = {
            .sta = {
                .ssid = WIFI_SSID,
                .password = WIFI_PASS,
                .threshold.authmode = WIFI_AUTH_WPA2_PSK,
            },
        };
        esp_wifi_set_mode(WIFI_MODE_STA);
        esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
        esp_wifi_start();
        ESP_LOGI(TAG, "WiFi 초기화 완료");
    }

    //웹소켓 이벤트 핸들러
    static void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data){
        esp_websocket_event_data_t *data = (esp_websocket_event_data_t *)event_data;
        switch(event_id) {
            case WEBSOCKET_EVENT_CONNECTED:
                ESP_LOGI(WS, "WEBSOCKET 연결 성공");
                break;
            case WEBSOCKET_EVENT_DISCONNECTED:
                ESP_LOGI(WS, "WEBSOCKET 연결 끊김");
                break;
            case WEBSOCKET_EVENT_DATA:
                ESP_LOGI(WS, "Received=%.*s\n", data->data_len, (char*)data->data_ptr);

                if(data->data_len == 4 && strncmp((char*)data->data_ptr, "exit", 4) == 0){
                    finished = true;
                }
                break;
            case WEBSOCKET_EVENT_ERROR:
                ESP_LOGI(WS, "WEBSOCKET 에러");
                break;
            default:
                ESP_LOGI(WS, "Other event id:%d", event_id);
                break;
        }
    }

    //웹소켓 통신 시작
    void start_websocket_client(){
        esp_websocket_client_config_t websocket_cfg = {
            .uri = WEB_SERVER_ADDR,
        };

        esp_websocket_client_handle_t client = esp_websocket_client_init(&websocket_cfg);
        esp_websocket_register_events(client, WEBSOCKET_EVENT_ANY, websocket_event_handler, (void *)client);
        esp_websocket_client_start(client);

        while(!finished){
            if(esp_websocket_client_is_connected(client) == false){
                ESP_LOGW(WS, "웹소켓 연결 실패, 재시도 중...");
                vTaskDelay(pdMS_TO_TICKS(1000));
                continue;
            }
            char message[100];
            snprintf(message, sizeof(message), "{\"cap\": %d, \"mpu_x\": %d, \"mpu_y\": %d, \"mpu_z\": %d}", CapValue, MpuValueX, mpuValueY, mpuValueZ);
            esp_websocket_client_send_text(client, message, strlen(message), portMAX_DELAY);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }

        esp_websocket_client_stop(client);
        esp_websocket_client_destroy(client);
        vTaskDelete(NULL);
    }

```
