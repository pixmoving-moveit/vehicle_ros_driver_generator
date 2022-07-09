
## Tool Framework

* `gen.py` : 总控制
* `extract_dbc_meta.py`: 解析dbc生成ymal文件

* `gen_msg_file.py`: 根据解析的yaml文件，生成msg消息功能包
* `gen_protocols.py`: 根据解析的yaml文件，生成c++代码-数据解析
* `gen_ros_node.py`:  生成发布订阅节点代码
* `gen_config_file.py`:  生成编译文件 

https://github.com/ApolloAuto/apollo/blob/master/docs/technical_tutorial/images/vehicle_adaption_tutorial/yml.png

```
dbc_file：重新填写你的DBC文件名称，DBC文件名称一般以品牌名称命名，并以.dbc结束；

protocol_conf：与上述DBC文件名称命名相同，填写ge3.yml；

car_type：填写姓名；

sender_list：[ ] ：发送列表，这里默认为空；

sender：此处修改为与 DBC 内部定义的 Apollo 的名称一致，ge3 的 DBC 内部定义的 Apollo 名称为 SCU。
```
