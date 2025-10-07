SDA와 SCL로 통신하는 방식

프로젝트 떄 쓰이는 mpu6050과 cap1188이 이걸 쓴다.

여기서 쓰려면 **`#include “Driver/i2c.h”`** 라이브러리가 필요하다

과정은

1. 정의
2. 마스터 초기화
3. 읽는 함수 만들기
4. 쓰는 함수 만들기
5. 메인에서 초기화와 쓰는 함수 작성

---

### 정의

```c
#define I2C_MASTER_SCL_IO           22      //SCL 핀    
#define I2C_MASTER_SDA_IO           21      //SDA 핀
#define I2C_MASTER_NUM              I2C_NUM_0   
#define I2C_MASTER_FREQ_HZ          100000   // 100kHz 주파수 
#define I2C_MASTER_TX_BUF_DISABLE   0           
#define I2C_MASTER_RX_BUF_DISABLE   0
```

---

### 마스터 초기화

마스터 모드를 설정하고(구조체정의) 드라이버 설치함

```c
void i2c_master_init()
{
    int i2c_master_port = I2C_MASTER_NUM; //쓸 I2C 포트번호
    
    i2c_config_t conf; //I2C 설정 구조체
     
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    
    i2c_param_config(i2c_master_port, &conf); //설정 적용
    i2c_driver_install(i2c_master_port, conf.mode,
                       I2C_MASTER_RX_BUF_DISABLE, //RX버퍼 비활성화
                       I2C_MASTER_TX_BUF_DISABLE, 0); //TX버퍼 비활성화
}
```
