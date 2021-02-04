# Exchange History Data

## Demand download historic data by interval

- Type: `Demand`
- Message: `MessageType::ExchangeDataHistoric::demandDownloadHistoricDataByInterval`
- Returns: `candles:XCandlesGapContainerSimple`
- Params: `XString strExchange, const stSymbolPair& symbol, TTimeframe timeframe, TTimestampInterval timeInterval, bool bReturnAllDownloadedData`

``` cpp tab="Send"
SendDemand<XCandlesGapContainerSimple, stSymbolPair, TTimeframe, TTimestampInterval,bool>(
  MessageType::ExchangeDataHistoric::demandDownloadHistoricDataByInterval::id(),
  boost::bind(&method, this, _1),
  symbol,
  tfTimeframe,
  timestampInterval,
  bReturnAllDownloadedData
);
```

``` cpp tab="Register"
RegisterDemandCallback<XCandlesGapContainerSimple, XString, stSymbolPair, TTimeframe, TTimestampInterval, bool>(
  MessageType::ExchangeDataHistoric::demandDownloadHistoricDataByInterval::id(),
  boost::bind(&method, this, _1, _2, _3, _4, _5, _6)
);
```

``` cpp tab="Handler"
void method(Atomix::MessageBroker::IDemandEvent<XCandlesGapContainerSimple>* demandEvent, const XString& strExchange, const Modules::Currencies::stSymbolPair& pair, const TTimeframe& tfTimeframe, const TTimestampInterval& tmTimeInterval, bool bReturnAllDownloadedData)
{

}
```

## Demand download historic data by amount

- Type: `Demand`
- Message: `MessageType::ExchangeDataHistoric::demandDownloadHistoricDataByAmount`
- Returns: `candles:XCandlesGapContainerSimple`
- Params: `XString strExchange, const stSymbolPair& symbol, TTimeframe timeframe, TTimestamp timestmap, int nAmount, bool bReturnAllDownloadedData`

Note: Requires amount data starting by dataTimestamp. For forward pass `+amount`, for backward `-amount`

``` cpp tab="Send"
SendDemand<XCandlesGapContainerSimple, XString, stSymbolPair, TTimeframe, TTimestamp, int,bool>(
  MessageType::ExchangeDataHistoric::demandDownloadHistoricDataByAmount::id(),
  boost::bind(&method, this, _1),
  strExchange,
  symbol,
  tfTimeframe,
  timestamp,
  nAmount,
  bReturnAllDownloadedData
);
```

``` cpp tab="Register"
RegisterDemandCallback<XCandlesGapContainerSimple, XString, stSymbolPair, TTimeframe, TTimestamp, int,bool>(
  MessageType::ExchangeDataHistoric::demandDownloadHistoricDataByAmount::id(),
  boost::bind(&method, this, _1, _2, _3, _4, _5,_6,_7)
);
```

``` cpp tab="Handler"
void method(Atomix::MessageBroker::IDemandEvent<XCandlesGapContainerSimple>* demandEvent, const XString& strExchange, const Modules::Currencies::stSymbolPair& pair, const TTimeframe& tfTimeframe, const TTimestamp& tmTimestamp, int nAmount, bool bReturnAllDownloadedData)
{

}
```
