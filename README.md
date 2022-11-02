
## Tool Framework

* `gen.py` : 主程序，调用其他code，生成`pix_{car_type}_driver` 和 `pix_{car_type}_driver_msgs`
* `extract_dbc_meta.py`: 解析dbc生成ymal文件
* `gen_msg_file.py`: 根据解析的yaml文件，生成msg消息功能包
* `gen_protocols.py`: 根据解析的yaml文件，生成c++代码-数据解析
* `gen_ros_node.py`:  生成发布订阅节点代码
* `gen_config_file.py`:  生成编译文件 

## HOW TO USE
### 1. 将你的DBC文件存放入`config`文件夹中，例如`pixmoving.dbc`
### 2. 在`config`文件夹下新建一个配置文件`{your_config}_conf.yml`，例如`pix_moving_conf.yml`
```yaml
dbc_file: pixmoving.dbc # 需要读取的dbc文件地址
protocol_conf: pixmoving.yml # 生成的协议文档
car_type: hooke # 车辆名称，如车辆名称是hooke，生成的package就是pix_hooke_driver与pix_hooke_driver_msgs
sender_list: [A2V_DriveCtrl, A2V_BrakeCtrl, A2V_SteerCtrl, A2V_VehicleCtrl, A2V_WheelCtrl] # 从上位机发送的CAN报文的名称，可从DBC文件中找到
sender: ACU # sender 名称
black_list: []

output_dir: output # 输出文件夹
config_dir: config/ # 配置文件所在目录

```
### 3. 运行`gen.py`
```bash
python3 gen.py config/pixmoving_conf.yml # 传入配置文件地址
```

### 4. 使用自动生成的代码
生成的代码示例结构如下，放到你的workspace下，进行编译，并编写相应自动驾驶软件的interface
```bash
├── pix_hooke_driver
│   ├── CMakeLists.txt
│   ├── include
│   │   ├── a2v_brakectrl_131.hpp
│   │   ├── a2v_drivectrl_130.hpp
│   │   ├── a2v_steerctrl_132.hpp
│   │   ├── a2v_vehiclectrl_133.hpp
│   │   ├── a2v_wheelctrl_135.hpp
│   │   ├── Byte.hpp
│   │   ├── v2a_brakestafb_531.hpp
│   │   ├── v2a_chassiswheelanglefb_541.hpp
│   │   ├── v2a_chassiswheelrpmfb_539.hpp
│   │   ├── v2a_chassiswheeltirepressfb_540.hpp
│   │   ├── v2a_drivestafb_530.hpp
│   │   ├── v2a_powerstafb_535.hpp
│   │   ├── v2a_steerstafb_532.hpp
│   │   ├── v2a_vehiclefltsta_537.hpp
│   │   ├── v2a_vehiclestafb_536.hpp
│   │   └── v2a_vehicleworkstafb_534.hpp
│   ├── package.xml
│   └── src
│       ├── a2v_brakectrl_131.cc
│       ├── a2v_drivectrl_130.cc
│       ├── a2v_steerctrl_132.cc
│       ├── a2v_vehiclectrl_133.cc
│       ├── a2v_wheelctrl_135.cc
│       ├── Byte.cc
│       ├── command_node.cc
│       ├── report_node.cc
│       ├── v2a_brakestafb_531.cc
│       ├── v2a_chassiswheelanglefb_541.cc
│       ├── v2a_chassiswheelrpmfb_539.cc
│       ├── v2a_chassiswheeltirepressfb_540.cc
│       ├── v2a_drivestafb_530.cc
│       ├── v2a_powerstafb_535.cc
│       ├── v2a_steerstafb_532.cc
│       ├── v2a_vehiclefltsta_537.cc
│       ├── v2a_vehiclestafb_536.cc
│       └── v2a_vehicleworkstafb_534.cc
└── pix_hooke_driver_msgs
    ├── CMakeLists.txt
    ├── msg
    │   ├── a2v_brakectrl_131.msg
    │   ├── a2v_drivectrl_130.msg
    │   ├── a2v_steerctrl_132.msg
    │   ├── a2v_vehiclectrl_133.msg
    │   ├── a2v_wheelctrl_135.msg
    │   ├── v2a_brakestafb_531.msg
    │   ├── v2a_chassiswheelanglefb_541.msg
    │   ├── v2a_chassiswheelrpmfb_539.msg
    │   ├── v2a_chassiswheeltirepressfb_540.msg
    │   ├── v2a_drivestafb_530.msg
    │   ├── v2a_powerstafb_535.msg
    │   ├── v2a_steerstafb_532.msg
    │   ├── v2a_vehiclefltsta_537.msg
    │   ├── v2a_vehiclestafb_536.msg
    │   └── v2a_vehicleworkstafb_534.msg
    └── package.xml

```
