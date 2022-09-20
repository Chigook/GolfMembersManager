#ifndef CARDREADER_H
#define CARDREADER_H

#include <iostream>
#include "mfrc522.h"
#include "DeviceData.h"

/*//: public class이름 상속의 표현 publc안의 내용은 다 가져온다 즉 mfrc522의 private은 사용 못함
//protected도 존재함 외부에서는 사용 못하지만 상속할 때는 사용 가능 함*/
class CardReader : public mfrc522
{
private:
    uint8_t rfidData[16];
    DeviceData cardData;

public:
    CardReader(SPI* spi);
    ~CardReader();
    bool isCard();
    DeviceData getCardNumber();
};

#endif