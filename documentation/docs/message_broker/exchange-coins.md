# Exchange Coins

## Request current symbol price

- Type: `Request`
- Message: `MessageType::ExchangeCoins::requestSymbolPrice`
- Returns: `double`
- Params: `XString strExchange, stSymbolPair symbol`

``` cpp tab="Send"
SendRequest<double, XString,stSymbolPair>(
  MessageType::ExchangeCoins::requestSymbolPrice::id(),
  "binance",
  stSymbolPair("btc","usdt")
);
```

``` cpp tab="Register"
RegisterRequestCallback<double, XString,stSymbolPair>(
  MessageType::ExchangeCoins::requestSymbolPrice::id(),
  boost::bind(&method, this, _1,_2)
);
```

``` cpp tab="Handler"
double method(const XString& strExchange, const stSymbolPair& symbol)
{

}
```

## Request known pairs

- Type: `Request`
- Message: `MessageType::ExchangeCoins::requestKnownPairs`
- Returns: `symbols:TlstSymbolPairs`
- Params: `XString strExchange`

``` cpp tab="Send"
SendRequest<TlstSymbolPairs, XString>(
  MessageType::ExchangeCoins::requestKnownPairs::id(),
  "binance"
);
```

``` cpp tab="Register"
RegisterRequestCallback<TlstSymbolPairs, XString>(
  MessageType::ExchangeCoins::requestKnownPairs::id(),
  boost::bind(&method, this, _1)
);
```


## Request market tickers with filter

- Type: `Request`
- Message: `MessageType::ExchangeCoins::requestFilteredMarketTickers`
- Returns: `symbols:TlstSymbolPairs`
- Params: `XString strExchange, stSymbolsFilterAdvanced filter`

``` cpp tab="Send"
SendRequest<TlstSymbolPairs, XString,timeframe_t>(
  MessageType::ExchangeCoins::requestFilteredMarketTickers::id(),
  "binance",
  filter
);
```

``` cpp tab="Register"
RegisterRequestCallback<TlstSymbolPairs, XString,stSymbolsFilterAdvanced>(
  MessageType::ExchangeCoins::requestFilteredMarketTickers::id(),
  boost::bind(&method, this, _1, _2)
);
```

## Notification of new symbol

- Type: `Message`
- Message: `MessageType::ExchangeCoins::notifyExchangeNewSymbol`
- Params: `XString strExchange, const stSymbolPair& symbol`

``` cpp tab="Send"
SendMessage<XString, stSymbolPair>(
  MessageType::ExchangeCoins::notifyExchangeNewSymbol::id(),
  boost::bind(&method, this, _1),
  exchange,
  symbol,
);
```

``` cpp tab="Register"
RegisterMessageCallback<XString, stSymbolPair>(
  MessageType::ExchangeCoins::notifyExchangeNewSymbol::id(),
  boost::bind(&method, this, _1, _2)
);
```

``` cpp tab="Handler"
void method(const XString& strExchange, const Modules::Currencies::stSymbolPair& pair)
{

}
```

## Notification of exchange prices update

- Type: `Message`
- Message: `MessageType::ExchangeCoins::notifyExchangePriceUpdated`
- Params: `XString strExchange`

``` cpp tab="Send"
SendMessage<XString, stSymbolPair>(
  MessageType::ExchangeCoins::notifyExchangePriceUpdated::id(),
  boost::bind(&method, this, _1),
  exchange,
);
```

``` cpp tab="Register"
RegisterMessageCallback<XString>(
  MessageType::ExchangeCoins::notifyExchangePriceUpdated::id(),
  boost::bind(&method, this, _1)
);
```

``` cpp tab="Handler"
void method(const XString& strExchange)
{

}
```