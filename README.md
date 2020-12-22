# HAL_STM32_PN5180_SPI_DEMO

**使用STM32驱动PN5180模块读写ISO15693协议卡和和ISO14443A协议卡，目前ISO15693协议卡(ICODE)已经调试测试完成，单槽盘存和16槽盘存；现阶段ISO1443A(M1)卡还没有全部调试通过，已经实现的有REQA、读取UID、防冲撞还没有做完，不过单张卡可以直接通过然后获取SAK，最后的身份认证还没有测试通过，发起身份认证出现认证失败返回错误码2，这个错误码是超时的意思（卡片不存在），我还没有搞懂为什么，持续更新，如果你正在使用该模块，遇到了一样的问题，期待你的回复！~**




# ISO15693-ICODE卡读卡测试
---

![image](./icode-hardware.jpg)
![image](./icode-result.jpg)


# ISO14443A-M1卡读卡测试
---

**M1卡的读写我还没有完全调通，卡在了身份认证阶段。**

![image](./m1-hardware.jpg)
![image](./m1-result.jpg)
![image](./mifare_auth.jpg)

