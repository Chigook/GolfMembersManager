#include "CardReader.h"

CardReader::CardReader(SPI* spi) : mfrc522(spi)
{

}

CardReader::~CardReader()
{

}

bool CardReader::isCard()
{
    uint8_t byte = mfrc522_request(PICC_REQALL, rfidData); //상속을 받을때는 객체 없이 method만 부르면 됨.
    if (byte == CARD_FOUND)
    {
        return true;
    } 
    else{
        return false;
    }
    
    return false;
}

DeviceData CardReader::getCardNumber()
{
    mfrc522_get_card_serial(rfidData);
    cardData.devName = "CardReader";
    cardData.devData.clear();       //std::vector<int> devData
    for (const auto data : rfidData){
        cardData.devData.push_back((int)data);
        //cardData.devData.emplace_back((int)data);
        //동작은 push_back과 emplace_back이 같으나
        //내부적으로 push_back 변수 자체를 받아서 넣는것이고
        //emplace_back은 상수화 시켜서 넣는 것. 속도상으로는 emplace_back이 좀 더 빠름
    }
    return cardData;
}