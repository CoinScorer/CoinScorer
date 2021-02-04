# Exchange Synchronous Data

## Candle Ticker start/stop

- Type: `Message`
- Start: `MessageType::ExchangeDataSynchronous::cmdCandleTickerStart`
- Stop: `MessageType::ExchangeDataSynchronous::cmdCandleTickerStop`
- Params: `XString strExchange, const stSymbolPair& symbol, TTimeframe timeframe`

``` cpp tab="Send"
SendMessage<XString, stSymbolPair, TTimeframe>(
  MessageType::ExchangeDataSynchronous::cmdCandleTickerStart::id(),
  "binance",
  stSymbolPair("bnb","btc"),
  TTimeframe(EnmTimeframe::Min1)
);

SendMessage<XString, stSymbolPair, TTimeframe>(
  MessageType::ExchangeDataSynchronous::cmdCandleTickerStop::id(),
  "binance",
  stSymbolPair("bnb","btc"),
  TTimeframe(EnmTimeframe::Min1)
);
```

``` cpp tab="Register"  
RegisterMessageCallback<XString, Currencies::stSymbolPair, TTimeframe>(
  MessageType::ExchangeDataSynchronous::cmdCandleTickerStart::id(),
  boost::bind(&method, this, _1, _2, _3)
);

RegisterMessageCallback<XString, Currencies::stSymbolPair, TTimeframe>(
  MessageType::ExchangeDataSynchronous::cmdCandleTickerStop::id(),
  boost::bind(&method, this, _1, _2, _3)
);
```
## Candle ticker

Ticker message for normal and high-resolution ticker.

- Type: `Message`
- Message: `MessageType::ExchangeDataSynchronous::onCandleTickerTick::id(exchange, symbol, timeframe)`
- Params: `tradeData:stTimeCandleStick`

``` cpp tab="Register"
RegisterMessageCallback<stTimeCandleStick>(
  MessageType::ExchangeDataSynchronous::onCandleTickerTick::id(exchange, pair, timeframe),
  boost::bind(&method, this, _1)
);
```

``` cpp tab="Send"
SendSynchronousMessage<stTimeCandleStick>(
  MessageType::ExchangeDataSynchronous::onCandleTickerTick::id(exchange, symbol, timeframe),
  dataCandleStick
);
```

## End Of Tick

Message send when new timeframe window is opened

- Type: `Message`
- Message: `MessageType::ExchangeDataSynchronous::onCandleTickerEOT::id()`
- Params: `timestamp_t`

``` cpp tab="Register"
RegisterMessageCallback<timestamp_t>(
  MessageType::ExchangeDataSynchronous::onCandleTickerEOT::id(),
  boost::bind(&method, this, _1)
);
```

``` cpp tab="Send"
SendSynchronousMessage<timestamp_t>(
  MessageType::ExchangeDataSynchronous::onCandleTickerEOT::id(),
  tmTimestamp
);
```
